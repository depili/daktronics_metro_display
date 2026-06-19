# Text Display Commands (Daktronics RM2040)

Reference for the **content / text-display** portion of the command protocol — the `!`-commands that define what appears on the LED panel. This complements `serial_protocol_reference.md` (transport + full opcode list) and `config_reference.md` (boot configuration).

Firmware identified from the `.rodata` banner: **`RM2040 v1.04.4 Copyright (c) MMXIX Daktronics (Ireland)`** (2019).

> Confidence: the command structure, `!dl` argument layout, attribute model, error codes, and pipeline are read from the decompiled handlers (`cmd_define_line`, `display_text`, `command_parse?`). The **markup control-code table and escape syntax** (§5) are now read directly from the shaper `markup_compile` (`FUN_20014660`).

---

## 1. Content pipeline

```
display_text(...)                     internal "show these lines" API
   │  builds an ASCII command string ("!m… !ffc  !dl…<text>…  !ps…")
   ▼
submit_command_string (FUN_2001b98c)  wraps string in a command descriptor
   ▼
process_commands (0x2001b974)         command_parse?(desc) + reply builder
   ▼
command_parse?                        tokenizes !XX, dispatches per opcode
   ├─ cmd_define_line   (!dl)         parse line + attributes + text
   │     ├─ FUN_20014660              shape/tokenize text (RTL/Arabic) -> control codes
   │     ├─ markup reflow + segment split
   │     └─ FUN_2000a2cc / FUN_200097b8   create line / segment objects
   ├─ cmd_frame_flush   (!ff)
   ├─ cmd_page_show     (!ps) / cmd_page_load (!pl)
   ├─ cmd_page_preset_select (!m/!mX)
   └─ …
   ▼
display_refresh (FUN_2000c298) / render_until_idle (FUN_2000cf7c)
   ▼
framebuffer banks  ──▶  LED panel
```

Both externally received frames and internally generated messages (`display_text`) flow through the **same** `command_parse?` interpreter. `command_parse?` ignores any non-`!` characters, so literal scaffolding in a generated string is skipped — only `!XX` tokens act.

---

## 2. Text-display command set

| Command | Opcode | Handler | Purpose |
|---|---|---|---|
| `!dl` | 0xb4 | `cmd_define_line` | **define a line**: position, attributes, justify, text |
| `!ff` | 0xbe | `cmd_frame_flush` | frame / page clear & commit |
| `!ps` | 0x8d | `cmd_page_show` | select the **visible** page |
| `!pl` | 0x90 | `cmd_page_load` | select the **edit** page |
| `!ls` | 0x92 | `cmd_line_list_select` | line/list addressing |
| `!dw` | 0xba | `cmd_display_window` | scroll window (also valid inline in `!dl`) |
| `!dp` | 0xb9 | `cmd_display_position` | display position (also inline) |
| `!m` / `!mX` | 0xb0 | `cmd_page_preset_select` | select page / preset slot |

Typical message (as emitted by `display_text`):

```
!m<slot> !ffc   !dl<line><mode><colour>jp<justify> <text> >   …(repeat per line)…   !ps<page>
```

---

## 3. The `!dl` command (define line)

```
!dl <line#> [+] <mode><colour> jp<justify>  ( *<bufN>  |  <text> )  [inline-modifiers]
```

### Header fields

| Field | Encoding | Notes |
|---|---|---|
| `<line#>` | decimal (`atoi`) | 1–40 (`≤0x28`); must be ≤ active page's line count; defaults to `g_default_line_ptr` if absent |
| `+` | optional literal `+` | append/sticky flag (`local_74`); affects visibility bit |
| `<mode>` | 1 byte | display mode (see §4); read with `<colour>` via `FUN_20013c58` |
| `<colour>` | 1 byte | colour / attribute high byte |
| `jp<justify>` | `jp` + 1 byte | justify: `N` none, `C` centre, `R` right, `L` left — anything else → error `0x31` |

Line geometry (x / y / w / h) is **not** in the command — it comes from `g_line_geometry_table` (per-page/per-line, stride `0x10`, 0x29 lines/page) and is bounds-checked against `g_panel_dim_w_ptr * g_panel_dim_h_ptr` (overflow → error `0xa8`). Two geometry modes are selected by `g_geometry_mode_ptr` (per-line table vs. a fixed rectangle in `g_fixed_geometry_blk`).

### Content (one of)

| Form | Meaning |
|---|---|
| `*<N>` | recall a pre-stored 2 KB text buffer `N` (0–199) from `g_stored_text_bufs` into the working slot |
| `<text>` | inline text, bracketed by `<` … `>`; `<>` alone → a single space |

Inline text is copied to a 2 KB working buffer (`g_text_buf_base`, `0x800`-byte slots) and passed through `FUN_20014660` (shape/tokenize; a distinct sub-mode when `<mode>` = `q`/0x71). High-bit bytes (≥0x80) trigger multi-byte / RTL handling when the Arabic options (`g_arabic_detect_ptr` / `g_arabic_translate_ptr`) are enabled.

### Inline modifiers (after the text)

When multi-segment mode is active (`g_multi_segment_ptr`), a nested token loop parses trailing modifiers attached to the line:

| Token | Opcode | Effect |
|---|---|---|
| `!lp` | 0x95 | set a value field on the line |
| `!dp` | 0xb9 | display position → `puVar30[0]/[1]` |
| `!dw` / `!bf` | 0xba / 0xbf | mark scroll/window flag (`puVar30[5] |= 4`) when mode is `s`/`S` and colour set |
| `!ff` | 0xc0 | numeric param |
| `!ff` | 0xc2 | set flag (`puVar30[5] |= 0x40`) |

### Error codes (`*g_cmd_error_detail_ptr` + `*g_cmd_error_ptr |= 2/8`)

| Detail | Meaning |
|---|---|
| `0xa4` | no active channel |
| `0x90` | invalid line number (0, out of range, or > page line count) |
| `0xa8` | line doesn't fit panel |
| `0x31` | bad justify character |
| `0x9f` | line-number mismatch with explicit override |
| `0x82` | working-buffer allocation failed |

---

## 4. Line attribute model

| Attribute | Source | Values |
|---|---|---|
| **Mode** | `<mode>` byte | `I` static (default), `s`/`S` scroll, `q` raw/quick (0x71), `C`/`c` … |
| **Colour** | `<colour>` byte | colour / attribute index |
| **Justify** | `jp<justify>` | `N` / `C` / `R` / `L` |
| **Scroll speed** | derived | `g_line_speed* >> 0x26` (reciprocal scale) |
| **Visibility/sticky** | `+` prefix → `local_74` | sets line flag `+0x14` bit1 |

A single `!dl` line may contain **multiple attribute runs** — see §5. Each run becomes its own segment object with its own mode/colour/justify.

---

## 5. Text markup language

Inside a `<…>` text body, a **backslash-escape markup language** controls colour, font, fields, and direction. `markup_compile` (`0x20014660`, formerly `FUN_20014660`) translates it into the binary control-code stream that `cmd_define_line` then reflows and segments.

### 5.1 Markup escapes (authoring syntax)

| Escape | Effect |
|---|---|
| `$XX` | insert a **raw byte** by 2 hex digits |
| `\\` `\$` `\|` | escaped literal `\` `$` `|` |
| `\|` vs bare `\|` | bare `\|` is a **column/segment separator** (in multi-column mode); `\\|` is a literal pipe |
| `\0` … `\9` | select **palette colour** 0–9 |
| `\h<NN>` | set colour to value `NN` (2 digits) |
| `\C<n>` | colour by **custom-palette value** `n` (looked up in `g_colour_value_table_ptr`) |
| `\S<n>` | colour by **index** `n` (0–19) |
| `\+<n>` / `\-<n>` | font size **+/− n** |
| `\v+<n>` / `\v-<n>` / `\vT` / `\vM` / `\vB` | font size / **vertical align** Top / Middle / Bottom |
| `\w<1-3>` | width 1–3 |
| `\D<0\|1>` | double-size flag |
| `\f` / `\s` | text **direction** LTR / RTL |
| `\o` | open a formatting **group** |
| `\r` / `\g` / `\a` | attribute select 1 / 2 / 3 |
| `\N` `\n` / `\B` `\b` / `\X` `\x` / `\F<n>` | level/param 1 / 2 / 0x13 / `n` |
| `\T` | toggle/tab code |
| `\i<NN>` | insert **image/icon** `NN` |
| `\j<NNN>` / `\k<NNN>` | parameter (0–255) |
| `\p<HH>` / `\p+<HH><HH>` | pen / position code |
| `\O` / `\P` | field placeholder (`000`) |
| `\t{…}` / `\t<HH>` | **time field** — `{…}` format with `h`/`m`/`s`/`a` tokens, or `<HH>` preset (see 5.3) |
| `\c d…` / `\c i…` | **time field** (12-/24-hour clock) |
| `\d{…}` or `\d<HH>` | **date field** with format spec (see 5.3) |
| `\>` | end-of-text marker |

### 5.2 Emitted control codes (authoritative — from `markup_compile`)

| Code | Bytes | From escape | Meaning |
|---|---|---|---|
| `0x00` | 1 | bare `\|` | segment/column separator; `00 0F` = end-of-buffer |
| `0x01`/`0x02`/`0x03` | 1 | `\r`/`\g`/`\a` | attribute select |
| `0x04` (+code) | var | date components | field-component run, `09`-terminated |
| `0x06` | 2 | `\i` | image / icon (1 arg) |
| `0x08` | 1 | `\T` | standalone toggle |
| `0x09` | 1 | — | field terminator |
| `0x0B` | 2 | `\j` | parameter (1 arg) |
| `0x0C` | 2 | `\D` | double-size flag (1 arg) |
| `0x0E` | var | `\c` | **dynamic time field** (arg 01=24h / 02=12h, then digits, `09`-term) |
| `0x10` | 2 | `\0`–`\9` | palette colour (arg 0x10+digit) |
| `0x11` | 2 | `\h` | colour set (1 arg) |
| `0x12` | 2–3 | `\+` `\-` `\v` | font size / vertical align |
| `0x14` | 4 | `\P` | field placeholder |
| `0x15` | 4 | `\O`, date | field placeholder / date-day |
| `0x16` | 1 | `\o` | **group open** |
| `0x18` | 2 | `\w` | width (1 arg) |
| `0x19` | 2 | `\C` `\S` | colour by index / custom-palette |
| `0x1A` | 2–3 | `\p` | pen / position |
| `0x1B` / `0x1C` | 1 | `\f` / `\s` | text direction LTR / RTL |
| `0x1D` | 2 | `\N\B\X\F\b\n\x` | level / parameter (1 arg) |
| `0x1E` | 2 | `\k` | parameter (1 arg) |

Error/abort: `markup_compile` sets `*g_markup_error_ptr |= 2` (bad parameter) or `= 8` (truncated / unterminated). A bare `>` or `\>` emits `00 0F` and returns.

`cmd_define_line` then re-flows this stream: the `0x16` group mechanism pushes a marker and, on pop, re-emits the prevailing colour (`0x11`), font (`0x12`), direction (`0x1B`/`0x1C`), and level (`0x1D`) so nested groups inherit state correctly — the bidirectional handling supports the Arabic path.

### 5.3 Date & time fields (`\d`, `\t`, `\c`)

`\d{…}` (date, via `cmd_define_line`) and `\t{…}` (time, via `markup_time_field`) take a brace-delimited format whose letters expand to components (repetition count selects the form; letter **case toggles upper/lower** via bit 0x80). Each component is emitted as a `0x04 <code>` run; literal characters pass through; `}` ends the field (`0x09`).

Date letters (`\d`): `d`/`dd` day, `m`/`mm`/`mmm`/`mmmm` month (numeric / padded / abbrev / full), `w`/`www` weekday, `yy`/`yyyy` year.
Time letters (`\t`): `h`/`hh` hours, `m`/`mm` minutes, `s`/`ss` seconds, `a` am/pm.

The `\d<HH>` / `\t<HH>` hex forms select a preset ordering: the low bits pick which components appear and the separators (`:` for time, `/` for date), the next bits pick field order, and a bit selects 12-/24-hour or era style.

`\c d…` / `\c i…` is the simpler clock insertion (`0x0E` dynamic field, arg `01`=24h / `02`=12h).

### 5.4 Inline attribute-change (segment split)

During `cmd_define_line`'s final pass, a `0x00` followed by an attribute spec starts a new **segment**. The spec encodes a 24-bit attribute word:

```
bit  31     : sign → clears the sticky/visible flag
bits 23..16 : mode    (-> local_68)
bits 15..8  : colour  (-> local_64)
bits  7..0  : justify (-> local_6c)
```

Spec forms after `0x00`: `C`/`N`/`R`/`L` (justify only), or `+` introducing a `<mode><colour>` pair or one of the literal directives `jp` / `tv` / `rs`, parsed by `parse_inline_attr` (`FUN_2001411c`) — which builds the attribute word, or resets it to 0 on an unrecognized spec. Each homogeneous run becomes a render buffer (`FUN_20009ad8`) and a line/segment object (`FUN_2000a2cc` single, `FUN_200097b8` multi), carrying geometry, justify, mode, colour, and speed.

---

## 6. Page model

| Command | Form | Behaviour |
|---|---|---|
| `!m<slot>` | preset 0–15 | **select active page**; falls back to page 1 if the requested slot is empty; saves previous page index |
| `!ps<page>` | page 0–107 | **show page**: set the visible page and commit it (`FUN_2000b144`); errors `2` (bad number) / `4` (≥108) |
| `!pl*` | — | **load all pages** into the playlist |
| `!pl<n>,<n>,…` | list | **define page playlist** to cycle through (parsed into a list, committed via `FUN_2000b230`); unterminated → error `8` |
| `!ffc[+]<name>` | clear | clear/delete content (by template name or number) |
| `!ffd<n>` | delete | free page `n` (channel `'j'`) |
| `!ffr d` / `!ffr o` / `!ffr…` | run/reset | reset the display buffer (`d`/`o` variants) or restore default content (`FUN_20016fe4` + reload) |

Storage channels are identified by letter: `'f'` (0x66), `'h'` (0x68), `'j'` (0x6a) name the working / display / page-store banks.

Other structure:

| Concept | Mechanism |
|---|---|
| **Lines per page** | up to 0x29 (41) entries in `g_line_geometry_table` / `g_page_linecount_table` |
| **Stored buffers** | 200 × 2 KB text buffers in `g_stored_text_bufs`, recalled with `*<N>` |
| **Render** | `display_refresh` walks page→line→segment objects, paints, and flips framebuffer banks; `render_until_idle` forces a synchronous full render |

The line/segment objects are reached through the table accessors `FUN_20008f1c` (page), `FUN_20008f90`/`FUN_20008fd8` (line), `FUN_20008ec4` (segment). Object flags: `+0x14` bit1 = active/visible, bit6 = pending; `+0x19`/`+0x1a` = colour/justify; `+0x10` = recalled-buffer index.

---

## 7. `display_text` convenience wrapper

`display_text(line0..3 specs, value, clear, render_mode, slot)` is the firmware's internal print API:

1. Optional clear (`clear_current_message`).
2. Selects target slot (`slot`, 0–15) and reads its layout mode.
3. Emits `!m<slot> !ffc`, then per non-null line a `!dl` with the line's `(text, attr, char)`, then a trailing 2-digit `value` (0–99 percentage) and a page-show.
4. Submits via `submit_command_string` → `command_parse?`.
5. Runs `display_refresh`, and if `render_mode == 0` on the local channel (`'g'`), forces `render_until_idle`.

The four per-line specs map directly onto `!dl`'s `<mode><colour>` (the 2 attribute bytes) and the attribute char.

---

## 8. Open items

The text-display layer is now fully traced end to end: transport → `command_parse?` → `cmd_define_line` → `markup_compile`/`markup_time_field` → segment/line objects → `display_refresh`. The page handlers (`!m`/`!ps`/`!pl`/`!ff`) and both markup sub-parsers (`markup_time_field` for `\t`, `parse_inline_attr` for inline `+` specs) are decoded.

Minor residual unknowns, not needed for the command format:
- The page-commit/free internals (`FUN_2000b144`, `FUN_2000b230`, `FUN_2000ad7c`, `FUN_20009014`) — the storage/playlist back-end behind `!ps`/`!pl`/`!ff`.
- The exact `display_text` literal pointers (`DAT_2000bdec`–`DAT_2000be00`); §1/§7 use the `.rodata` template strings, which are the same forms.