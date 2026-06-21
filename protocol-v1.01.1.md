# RM2040 Serial Protocol & Command Reference — firmware v1.01.1

Daktronics RM2040 LED sign controller (Atmel AT91SAM7 / ARM7TDMI). Reverse-engineered from `command_parse` at `0x200141c8` in the v1.01.1 RAM-resident image. This is a strictly older, smaller command set than the v1.04.4 image documented in [protocol.md](protocol.md); use this file only when working against v1.01.1 firmware.

Commands that the dispatch tree recognises but routes to no `case` (i.e. silently denied) and the empty no-op slots are **omitted** from this document — they are protocol reservations, not features.

## 1. Physical layer & frame format

Assumed identical to the v1.04.4 description (8-N-1 at 9600/19200/57600/115200, multidrop, polled RX, ≥1 ms inter-byte gap). The frame envelope is the same:

```
[ <AA> <command-body> /<CK> ]
```

- `[` (`0x5B`) start of frame, seeds the checksum.
- `<AA>` 2-char device address. The two address bytes are matched by `cmd_addr_match` exactly as in v1.04.4 (`0@` = broadcast, `0A`–`0Z` = unit by LOW address, `1`–`8` + any 2nd char = HIGH group, `00` = invalid).
- body = one or more `!`-prefixed command tokens (non-`!` filler between tokens is skipped). When the configured protocol mode allows it, three raw escapes (`R…`, `W…`, `Z…`, `d…`) may appear instead — see §3.
- `/<CK>` optional 2-hex-digit checksum, seeded with `'['`, verified only when byte at end-3 is `/`.
- `]` (`0x5D`) end of frame → parse + execute.

Reply paths (success `Y`, error `N`, transport NAK, `[FFP…]` status) are emitted in the same shape as v1.04.4.

## 2. Mnemonic encoding & scope gating

Each command is `!` plus a 2-character mnemonic. The dispatcher packs the mnemonic as `(char1<<8)|char2` and maps it through a binary if/else tree to `(scope<<16)|opcode`. The opcode then drives a single big switch.

- The unit's current addressing scope is `param_1[2]`. Each command entry encodes a scope mask (bits 16–17). If `param_1[2] & scope_mask == 0` the command is rejected with error class `0x04` (denied/wrong scope). Almost all commands in v1.01.1 are `scope = 3` (scopes 1+2). The only exceptions:
  - **scope-1-only**: `!sc`, `!si`, `!?c`, `!?i`, `!?m`
  - **scope-2-only**: `!zl`
- Opcodes outside the range `0x10`–`0xFD` are rejected with the same `0x04`.
- A handful of mnemonics are mapped to opcode `0` (e.g. `!vr`, `!vw`) — those are dropped silently with no error.

## 3. Protocol-version gating

The config parser sets one of seven `g_protocol_N` flags depending on the configured protocol/feature pack. The command dispatcher consults these directly to decide which mnemonics are even visible:

| Flag | Address | Role |
|---|---|---|
| `g_protocol_1` | `0x2008563c` | enables `p…` / `m…` / `c…` / `d…` / `!kt` / `!kg` content commands |
| `g_protocol_2` | `0x20085644` | enables `l…` (`ls`/`lr`/`lc`/`lp`/`lh`/`lt`); selects the `cmd_dl_handler_alt` path for `!dl`; enables `!cd`/`!cl` |
| `g_protocol_3` | `0x20085648` | enables the raw `R` / `W` / `Z*` / `d` non-`!` escapes at the top of the parse loop |
| `g_protocol_4` | `0x20085640` | also enables `p…` content commands; gates `!pb` |
| `g_protocol_5` | `0x20085638` | enables the `F…` / `P…` / `T…` / `D…` / `fc` / `fz` / `fa` family entries in the dispatch tree |
| `g_protocol_6` | `0x2008564c` | settable by `!zm 6`; no command currently gates on it in v1.01.1 |
| `g_protocol_7` | `0x20085650` | enables `!rc`/`!ra`/`!ld`/`!uc`; remaps `!rl` and `!?v` to their alt variants |

The flags are mutually exclusive: `!zm` clears all of them before setting the requested one (with `!zm 7` setting both `g_protocol_2` and `g_protocol_7`). Commands gated on `g_protocol_5` are documented in §6, gated on `g_protocol_7` in §7, etc. A mnemonic only reaches its handler when the dispatch tree currently includes it AND its scope mask passes.

## 4. Settings

Most setters persist; many flag the live config dirty (`DAT_200722ac |= 1`). The `!r*` reads listed in §5 mirror these.

| Set | Format | Stored / effect |
|---|---|---|
| `!sa` | `!sa<serial><A><N>` | If `<serial>` matches the 12-byte UID at `DAT_20031898`, set HIGH group from `<A>` (`'1'`–`'8'`) and LOW unit from `<N>` (`'A'`–`'P'`), and acknowledge. Bad `<A>` or `<N>` → bad-param. |
| `!st` | `!st<HH><MM><SS>` *(inferred handler `cmd_st_handler`)* | RTC time |
| `!sd` | `!sd<W><MM><DD><YY>` | RTC date (weekday 1–7, validated; month 1–12) via `cmd_sd_set_date` |
| `!sb` | `!sb<n≤100>` | `DAT_200722a0` (brightness backstop) |
| `!se` | `!se<mode>` | parsed by `parse_mode` → `g_bCfgDefSeqEffect` (current mode) |
| `!sf` | `!sf<Y\|N>` | master-mode / `Succession` flag `g_dwCfgSuccession` |
| `!ad` | `!ad<Y\|N>` | Arabic auto-detect flag `g_dwCfgArabicAutoDetect` |
| `!cc` | `!cc<Y\|N>` | `CarryPageContent` flag `g_dwCfgCarryPageContent` |
| `!sp` | `!sp…` | spec/refresh handler via `FUN_2000c780`; recomputes a refresh table — internals not yet decoded |
| `!si` *(scope 1)* | `!si<nnnn>` | `DAT_200318ec` / `DAT_200c67bc` |
| `!to` | `!to<1\|2\|3\|4>` | message mode selector; `1`/`2`/`3` set one of `g_dwCfgScrollIfTooWide` / `g_dwCfgTruncateOnChar` / `g_dwCfgTruncateOnWord`; `4` is the *query* form that appends the current mode (`ts c`/`tc`/`tw`) to the reply buffer |
| `!up` | `!up<nn>` | `g_dwCfgTimeout` (`Timeout=`), then `FUN_2000441c` (apply) |
| `!uq` | `!uq<n=1–20>` | `g_dwCfgSequenceMs = n*1000` ms (`Sequence=`); updates every active queue-text segment's countdown field |
| `!uf` | `!uf<aaa,bbb>` | scroll speeds A,B → `g_dwCfgFlashSpeedA` / `g_dwCfgFlashSpeedB` (`Flash=`). 3 digits each by default; 4 digits each when `g_protocol_7` is on. Both clamp to ≥ `10` and treat `999` as `1000`. |
| `!us` | `!us<0–9>` | scan-speed/refresh index → `DAT_20031904` + `g_bright_clock_ctrl` lookup + `ISR_drive_setup` + `FUN_20000680` |
| `!um` | `!um<n<16>` | `g_dwCfgMaintTime` (`MaintTime=`) |
| `!ul` | `!ul<n<61>` | `g_dwCfgPinLock` (`PinLock=`) |
| `!ue` | `!ue<0\|1>` | `DAT_200318f8` |
| `!Fs` | `!Fs<50–600>` *(gated by `g_protocol_5`)* | recomputes `g_bright_clock_ctrl = 0x8ca00 / (g_dwCfgRowsPerLine * n)` then `ISR_drive_setup`. <50 → err `0xeb`, >600 → err `0xec`, bad parse → err `0xea` |
| `!Fx` | `!Fx<0–9>` *(gated by `g_protocol_5`)* | 1- or 2-digit flash value. >9 → err `0xee`, bad parse → err `0xed` |
| `!LS` | `!LS<n>` *(gated by `g_protocol_5`)* | `DAT_20031890` (light-sensor level), valid `2…5000` |
| `!Fm` | — *(gated by `g_protocol_5`)* | `cmd_Fm_handler` — handler implemented but format not yet decoded |

## 5. Queries (return data)

| Cmd | Format | Returns |
|---|---|---|
| `!??` | `!??` | full ID dump |
| `!?a` | `!?a<UID>` | match 12-byte UID at `DAT_20031898`; on hit, append `:<HIGH>,<LOW>` to the reply |
| `!?t` | `!?t` | RTC time: `:HHMMSS` (hex bytes via `bin_to_hex` of `g_rtc_*`) |
| `!?d` | `!?d` | RTC date: `:WDDMMYY` (weekday is 1 hex digit; DD/MM/YY are 2 hex digits each) |
| `!?b` | `!?b` | `:<DAT_200318b4>` (current brightness, 3 dec) |
| `!?s` | `!?s` | `:` only (empty payload — handler reserved) |
| `!?c` *(scope 1)* | `!?c` | sub-`!?d` family — geometry equivalent |
| `!?i` *(scope 1)* | `!?i` | sub-`!?j` family |
| `!?m` *(scope 1)* | `!?m` | mirror of `DAT_20072364` (cleared after read) |
| `!?n` | `!?n` | `:<UID>` (12 bytes from `DAT_20031898`) |
| `!?v` | `!?v` | app version: `:<HHHH>,<HHHH>` (4-digit hex each). Under `g_protocol_7` the digit widths drop to 3,2. |
| `!?z` | `!?z` | geometry: `:<panel-px>,<panel-rows×lines>,<M\|C>` |
| `!?j` | `!?j` | `:<PIO_byte>` (2 hex) from `read_PIO_and_unkown_mmap` |
| `!?e` | `!?e` | failure log — `cmd_qe_rl_handler` |
| `!?o` | `!?o` | mirror of `DAT_20072360` (cleared after read) |
| `!?h` | `!?h` | hw-flags byte (also clears `DAT_200318c0` and `DAT_2007235c`); under `g_protocol_7`, bit `0x40` is OR'd in when bit `0x01` is set |
| `!?F` | `!?F<+\|-\|...>` | `cmd_qF_handler` — also accepts `+` / `-` to set `DAT_20085664` directly |
| `!rp` | `!rp` | `:<g_dwCfgTimeout>` (2 dec) |
| `!rt` | `!rt` | dumps the 6 raw RTC bytes (`DAT_2008c180…` or, when `DAT_200318d4 == 1`, `DAT_20090a60…`) with `_` → `0xb0` substitution. No `:` prefix. |
| `!rq` | `!rq` | `:<g_dwCfgSequenceMs/1000>` (2 dec) — current `!uq` value in seconds |
| `!rf` | `!rf` | `:<aaa>,<bbb>` (or 4,4 under `g_protocol_7`) — current `!uf` scroll speeds (`g_dwCfgFlashSpeedA`/`B`) |
| `!rm` | `!rm` | `:<g_dwCfgMaintTime>` (2 dec) |
| `!rl` | `!rl` | `:<g_dwCfgPinLock>` (2 dec). **Under `g_protocol_7`** the mnemonic dispatches to a different opcode handled by `cmd_qe_rl_handler` instead. |
| `!re` | `!re` | `:<DAT_200318f8>` (1 dec) |
| `!rb` | `!rb` | `:<DAT_200722a0>` (3 dec — runtime brightness backstop, not the `Sb=` config) |
| `!rs` | `!rs` | `:<DAT_20031904>` (2 dec) — current `!us` index |

## 6. Pages, lines, message content

Available only when the corresponding mode flag(s) are set (§3).

### 6.1 Active page / channel slot — `!m0` … `!mF`

`!m<0–F>` selects active page slot 0–15 by writing `g_dwCfgCurrentMode = hex_digit` (the boot `CurrentMode=` setting is overwritten). When `g_protocol_2` is set, the previous active slot's siblings (everything but the current and mirror entries) are torn down via `FUN_2002de6c` + `FUN_200265d8` first.

### 6.2 Page commands — `!p*`

| Cmd | Format | Effect |
|---|---|---|
| `!ps` | `!ps<page>` | select & show page `<page>` (3-digit decimal via `FUN_2000c780`). Tears down the previous page if any. Loads the page via `FUN_20025268`; failure sets error `(slot<<24) \| code`. Range > 0x64 → err `0x04`. |
| `!pd` | `!pd<page,2 dec>` | delete: `FUN_2002de6c(page, 0)` |
| `!pr` | `!pr` | page reset / commit: `FUN_200268c0` |
| `!pl` | `!pl*` or `!pl<n>,<n>,…` | playlist: `*` enumerates every loaded page (skipping current), otherwise an explicit comma-separated list. Each entry is parsed by `FUN_2000c780`; non-`,` non-`!`/NUL terminator → syntax error `0x08`. With `g_dwCfgCarryPageContent` set and ≥2 entries it also clones the page lines into fresh slots. |
| `!px` | `!px` | clear the playlist table (`DAT_200ce428[0..99]` = -1) and counter |
| `!pc` | `!pc<Y\|n>` | set/clear `DAT_2053f4ec[active*0xfc]` (page checked flag) |

### 6.3 Lines — `!l*` *(gated by `g_protocol_2`)*

| Cmd | Format | Effect |
|---|---|---|
| `!ls` | `!ls<…>` | line-select; shares the `!lc` handler body |
| `!lc` | `!lc<line,2 dec>` | select line within active page, marking `DAT_2053f4b4` |
| `!lr` | `!lr<line,2 dec>` | re-show / refresh line; updates mirror slot. Errors `0x99` bad-param, `0x9a` no active page, `0x9b` wrong line |
| `!lp` | `!lp<line,2 dec>` | set per-line priority `DAT_2053f500` (0 → -1) |
| `!lh` | `!lh<line,2 dec>` | hold line: `DAT_2053f4f8 = 1`. Errors `0x96`/`0x97`/`0x98` |
| `!lt` | `!lt*` or `!lt<line>,<line>,…` | line-touch / clear: `*` clears every active-page line, otherwise comma-list of 2-digit line numbers. Range > `g_page_lines_count` → err `0x90`, bad parse → err `0x9e` |

### 6.4 Display content — `!d*`, `!c*`, `!k*` *(gated by `g_protocol_1`/`g_protocol_2`)*

| Cmd | Format | Effect |
|---|---|---|
| `!cd` | `!cd` | clear current message: tears down all secondary slots in the active page |
| `!cl` | `!cl<line,1 dec>` | clear single line via `FUN_2002a444` |
| `!dl` | `!dl<NN>[+]<MA><J>{ *<DDD> \| <…> }` | define a line. **Two implementations**: `cmd_dl_handler` (default) and `cmd_dl_handler_alt` (when `g_protocol_2` is set). See §6.5. |
| `!dg` | `!dg<v1,3 dec><v2,3 dec>…<v7,3 dec>` | install a 7-value graphics record onto the active line via `FUN_20023868`. Active page required (else err `0xff000002`). |
| `!df` | `!df<n,3 dec>` | append/sub: with no existing record `division(g_dwCfgChannels*g_dwCfgRowsPerLine, g_dwCfgColours)` is used; otherwise the next free slot (up to 16) gets `n`. Slot exhaustion → err `(slot<<24) \| 0x62 \| (n<<16)` |
| `!dr` | `!dr<n,3 dec>` | adds `n` to the current `!df` slot's count |
| `!dp` | `!dp<n>` | dwell/period: parses via `FUN_2000c780`, writes the per-line dwell at `DAT_2053f4cc/d0`. Under `g_protocol_7` (mirror mode) the value is also written to the mirrored slot. |
| `!dw` | `!dw` | clears the per-page "dirty/window" flag `DAT_2053f4f0` |
| `!kt` | `!kt<slot><<text>>` | compile markup into custom text slot. `<slot>` is 3-digit decimal (2-digit + 100 offset under `g_protocol_7`); max `0x327` (999). Body is `<…>` consumed by `FUN_2000c8c0`, copied into the slot at `&DAT_2055b000 + slot*0x1000` (or `0x205bf000 + slot*0x1000` under `g_protocol_7`). |
| `!kg` | `!kg<n,3 dec>,<h,3 dec>,<w,3 dec><<pixels>>` | compile pixel matrix into custom graphics slot `n` (≤24, max `h*w=0x4000`). Body in `<…>`: 4 bits/px packed by halves, terminated by `>`. Stored at `&DAT_20887000 + n*0x4000`; header `DAT_200722f8[n] = w \| (h<<16) \| 0x80000000`. |

### 6.5 `!dl` argument format

```
!dl<NN>[+]<MA><J>{ *<DDD> | <…text…> }
```

| Part | Meaning |
|---|---|
| `<NN>` | line number. If first char is `'0'`, exactly one digit follows (lines 1–9 as `01`…`09`). Otherwise the decimal is consumed by `FUN_2000c780`. Line `0` → bad-param. |
| `[+]` | optional. **Present** → continuation segment (clears the default-attr flag). **Absent** → this is the line's default attribute segment. |
| `<MA>` | mode + colour, 2 chars, decoded by `parse_mode` (see §6.5.1 below). Returns a packed 16-bit `(colour<<8) \| mode`. Only ~50 input pairs are recognised; everything else falls through to mode `I`. |
| `<J>` | justify, 1 char: `N` / `L` / `R` / `C`. Anything else → bad-param `0x02`. |
| `*<DDD>` | recall stored text buffer: 3 decimal digits (0–999). Under the alt handler with `*DAT_20014078 != 0` the form is 2 digits + 100 internally → range 100–199. |
| `<…text…>` | inline body terminated by `>` or NUL. Allocated to a fresh slot via `FUN_20024128` (or `FUN_2002842c` for the bidi pre-processor path under the alt handler). Compiled by `FUN_2000c8c0` (with flag `1` for mode `q`). |

#### 6.5.1 `<MA>` — `parse_mode` (`0x2000c25c`)

`parse_mode` reads exactly two bytes, looks the 16-bit pair up in the rodata table at `0x2000c638..0x2000c71f`, and returns `(colour<<8) \| mode_byte`. The caller splits the result:

```c
uVar11 = parse_mode(pcVar18);
mode    = uVar11 & 0xff;       // low byte
colour  = (uVar11 >> 8) & 0xff; // high byte
```

**Primary modes — `<letter><digit>`:** the first char is the mode kind, the second is the colour index `0`–`9`.

| `<letter>` (mode byte) | Pairs accepted | Notes |
|---|---|---|
| `S` (0x53) | `S0`…`S9` | static. `S0` returns just mode (colour 0); `S1`–`S9` return mode + colour. Slots `+0x3b0`/`+0x3c4` get `S`/`S`. |
| `s` (0x73) | `s0`…`s9` | scroll. Slots get `S`/`s`. |
| `C` (0x43) | `C0`…`C9`, `CA` | clock with static base. Slots get `C`/`S`. `CA` collapses to plain `C`. |
| `c` (0x63) | `c0`…`c9` | clock with scroll base. Slots get `c`/`s`. |

**Two-letter shortcuts** — both bytes are letters; these don't carry a colour digit (returned colour is `0`), and they don't write the per-mode slot pair (they fall through `LAB_200139d0` and only set the colour/`local_48` fields):

| Input | Mode byte returned |
|---|---|
| `ru` | `R` (0x52) |
| `dr` | `r` (0x72) |
| `oc` | `V` (0x56) |
| `oe` | `v` (0x76) |
| `ol` | `U` (0x55) |
| `or` | `u` (0x75) |
| `ac` | `c` (0x63) — collapses to plain `c` (no colour) |
| `ps` | `*` (0x2A) |
| `qs` | `q` (0x71) — enables the `\|`-separated multi-segment splitter inside `<…text…>` and calls `FUN_2000c8c0` with flag `1` |

**Fallback**: any 2-byte input not in the tables above returns `0x49` = `'I'` (icon).

`'I'` is treated as a *real* mode change by `cmd_dl_handler_alt` only when the **previous** non-NUL byte in the parsed buffer was `j`, `r`, or `t` (the icon-disambiguation rule); otherwise the two bytes are reinterpreted as plain text and the previous segment's attributes are kept.

So the practical rule for an author writing a `!dl` body is: pick one of the 41 `<letter><digit>` combinations or the 9 two-letter shortcuts; anything else is text.

**Continuation segments (alt handler only).** After the first segment commits via `FUN_20024ce8`, the parsed buffer is re-walked, with `\0` bytes splitting segments. Each subsequent segment can re-prefix with any of:

- `<M><A>` — new mode+attr only
- `+<M><A>` — same but tagged as continuation
- `<M><A><J>` / `+<M><A><J>` — also new justify
- `<J>` alone (`N`/`L`/`R`/`C`) — new justify only
- anything else — plain text, reuse previous attributes

Each continuation segment is installed via `FUN_20024338(page, 0, segment_index, slot, qwidth, justify, mode, 1)`.

**Errors deposited in `DAT_20014074`** (alt handler): `0xa4` no active channel · `0x91` line geometry overflows the panel · `0x93` no active page · `0x9f` line doesn't belong to active page · plus `cmd_flags |= 2` (bad-param) or `cmd_flags |= 8` (syntax / slot exhaustion).

## 7. `g_protocol_7` alternates

When `g_protocol_7` is set, four additional mnemonics become available *and* two existing ones change meaning:

| Cmd | Effect |
|---|---|
| `!uc` | active-page commit via `FUN_2002de6c` + `FUN_20012208` (1 digit, must be 0 or 1) |
| `!rc` | reply `:<DAT_2053f4d8[active*0x3f]>` (1 dec) |
| `!ra` | no-op (case present but empty) — *kept for completeness only because the alt-mode handler reserves it* |
| `!ld` | mirror of the `!ps` page-load body |
| `!rl` | **re-routed** to `cmd_qe_rl_handler` instead of the `!rl` plain read |
| `!?v` | reply widths drop from 4,4 to 3,2 hex digits |

## 8. Test, debug, reboot

| Cmd | Format | Effect |
|---|---|---|
| `!tp` | `!tp<0–9>` | test-pattern index → `DAT_200722b4`. Shares the trailing parse path with `!zb`. |
| `!tl` | `!tl` | run LED failure scan (`led_test`) |
| `!zr` | `!zr` | `cmd_zr_handler` → `parse_config` re-run, `FUN_200268c0`, then (if `g_protocol_2` is on) page commit. *Not* a reboot in this build; see `!zz`. |
| `!za` | `!za` | sets `DAT_20072374 = 0`, `DAT_20072378 = 1` (show AMSG / armed flag). Aliased to `!zd`. |
| `!zp` | `!zp<1–8>` | `cmd_zp_handler`. Range-checks, then calls into the handler. |
| `!zo` | `!zo<HH>` | direct FPGA register poke: `fpga_reg34_write(hex_byte)`. Bad hex → bad-param. |
| `!zm` | `!zm<1–7>` | reconfigure the active protocol flag: clears all `g_protocol_1..7`, then sets the one whose number matches `<1–6>` (or, for `7`, both `g_protocol_2` and `g_protocol_7`), and `mem_init`s. `0` → err `0xa1`, parse fail → `0xa0`, ≥8 → `0xa2`. |
| `!zz` | `!zz` | gated on address chars `'0'`,`!='@'`: flush UART, `gpbr_set_word(0,5)`, `gpbr_set_word(1, port)`, `gpbr_set_word(2, baud-strap)`, `system_reset`. Then falls through to `!zb`'s tail. |
| `!zb` | `!zb` | flush UART, then `system_reset` (plain reboot). Also runs after `!zz` / `!zx` / `!zy`. |
| `!zx` | `!zx` | same address gate as `!zz`: `gpbr_set_word(0,2)`, reset (mode 2). |
| `!zy` | `!zy` | same gate: `gpbr_set_word(0,3)` + port + baud-strap, reset (mode 3). |
| `!zl` *(scope 2)* | `!zl` | clears `DAT_20072414` |

`GPBR0` selects the bootloader mode after reset; `GPBR1` records the port the command arrived on; `GPBR2` is the strapped baud constant (`0x2580` = 9600 or `0x4b00` = 19200 depending on PIO bit `0x80`). The bootloader interprets these; this image only sets and resets.

## 9. Raw (non-`!`) escapes (`g_protocol_3`-gated)

When `g_protocol_3` is set, the parser inspects each new token's first byte before the `!` check and may take one of these paths:

| First byte | Format | Effect |
|---|---|---|
| `R` | `Rx Time Now <±><HH>` / `Rx TIME NOW …` | adjust RTC time field by signed hex offset |
| `R` | `Rx Date Now <MMDDYY>` / `Rx DATE NOW …` | set RTC date (validated; weekday auto-computed) |
| `R` | `Rx Temperature Now <±><HH>` / `Rx Temp Now <±><HH>` (case variants) | set temperature offset |
| `W` | `W//` | RTC/zone sync helper (clears DDX entries, then `FUN_2002e038`) |
| `W` | `W//snu…` | per-zone select-and-update (`FUN_200254d4('M')` + `FUN_200274ac('M',…)` + optional `FUN_20029828`) |
| `W` | `W…S<dst>i` / `W…<dst>C…` / `W…<dst>P<text>` | per-zone targeted ops (delete-set / clear / push text) using `FUN_200254d4('S')` |
| `Z` | `ZB?` / `ZB<n≤100>` | get / set `DAT_200722a0` brightness backstop (runtime, not `Sb=`); reply `ZB<UID>:<val>,<sensor>` |
| `Z` | `ZC` | reply with `ZC<UID>:<reg_0x2007235c>,<FPGA_0x6000030>,<DAT_2007228c>` (clears both); for diagnostic capture |
| `Z` | `ZD` | re-arm: `mem_init`, set `g_protocol_1`, `g_dwCfgCurrentMode = 1` |
| `Z` | `ZL` | `led_test` (same as `!tl`) |
| `Z` | `ZO?` / `ZO<n>` | get / set `g_dwCfgTimeout` (`Timeout=`); setter also runs `FUN_2000441c` |
| `Z` | `ZP` | reply `ZP<UID>:<FPGA_0x6000030>` |
| `Z` | `ZQ<a><b>` | sets pair `g_dwCfgCarryLastLines = (a=='\x01')`, `g_dwCfgQueueMsThenSs = (b=='\x01')` |
| `Z` | `ZR` | `system_reset` |
| `Z` | `ZS` | reply `ZS<UID>: PCB236 UID is <UID>` |
| `Z` | `ZT<0–7>` | `DAT_200722b4 = digit` (0 stores as 0) |
| `Z` | `ZV` | reply `ZV<UID>:<hi-hex>-<lo-hex>` of `get_app_version` |
| `Z` | `ZZ:<UID12>` | UID-gated reset-with-flag path: reply with current baud (`9600 N81` / `19200 N81`), `gpbr_set_word(0,5)`, port, baud-strap, `system_reset`. Equivalent to `!zz` but UID-keyed instead of address-keyed. |
| `d` | `d…` | `cmd_d_raw_handler` — accepted whenever `g_protocol_3` is set, even outside an `!` token |

The reply for the `Z` family uses the literal `Z<letter>` prefix followed by the hex unit address (`DAT_200815dd`) rather than the standard `[U Y …]` envelope. Checksums are still appended.

## 10. Error & status codes

The handler-local error byte (e.g. `DAT_20014074` for `cmd_dl_handler_alt`, `DAT_20085660` for the main switch) carries a code that's surfaced back through the `N`-reply path together with `cmd_flags`:

| Class (`cmd_flags`) | Meaning |
|---|---|
| `0x02` | bad parameter (parse failure, out-of-range, unknown sub-letter) |
| `0x04` | denied / unknown opcode / wrong scope |
| `0x08` | syntax (missing `<` / `>`, slot exhaustion, bad delimiter) |
| `0x20` | checksum mismatch (set during framing, before dispatch) |

Detail codes seen in v1.01.1 (set alongside `cmd_flags`):

- `0xa4` no active channel/page context (for `!dl`)
- `0x93` no active page selected
- `0x9f` line doesn't belong to active page (default-line mismatch)
- `0x90`/`0x91` line geometry / range error
- `0x96`–`0x9c` `!lh`/`!lr`/`!lp` line-op codes
- `0xa0`–`0xa2` `!zm` parameter errors
- `0xea`–`0xee` `!Fs`/`!Fx` parameter errors

## 11. Config-key ↔ global cross-reference

The boot-time `ACFG` parser (`parse_config` at `0x20007c10`) populates the globals consulted by the runtime. Every `key=` token in the config file maps to one or more globals; the table below covers the keys that affect serial-command behaviour (geometry-only and EDF-internal keys are omitted — see `parse_config_v1.01.1.c`).

| Config key | Global(s) | Range / notes |
|---|---|---|
| `PROTOCOL=` | `g_protocol_1`–`g_protocol_7` | feature pack — sets exactly one flag (PROTOCOL=3 sets 1+3, PROTOCOL=7 sets 2+7); see §3 |
| `CurrentMode=` | `g_dwCfgCurrentMode` | `0`–`F`; later overwritten by `!m<0–F>` |
| `MainChannel=` | `g_dwCfgMainChannel` | `'1'` → leaves at 1; any other char → 2 |
| `Pixels=` | `g_dwCfgPixels` | panel width (rounded up to multiple of 8) |
| `Channels=` | `g_dwCfgChannels` | 1–8 |
| `Colours=` | `g_dwCfgColours` | 1–3 |
| `RowsPerLine=` | `g_dwCfgRowsPerLine` | 7–9 |
| `Speed=` | `g_bright_clock_ctrl` | 50–600 (stored as `0x8ca00 / (Speed * RowsPerLine)`) |
| `FXslowdown=` | `g_dwCfgFxSlowdown` | 0–9 (initial `!Fx` value) |
| `Timeout=` | `g_dwCfgTimeout` | 0–99 (initial `!up` value) |
| `Sequence=` | `g_dwCfgSequenceMs` | 1–90s, stored as ms (initial `!uq` value) |
| `Flash=` | `g_dwCfgFlashSpeedA`, `g_dwCfgFlashSpeedB` | initial `!uf` A,B (1–100 each, stored `/10`) |
| `MaintTime=` | `g_dwCfgMaintTime` | 1–15 (initial `!um`) |
| `PinLock=` | `g_dwCfgPinLock` | 1–60 (initial `!ul`) |
| `MinBr=` | `g_dwCfgMinBrightness` | 1–20 |
| `MaxBr=` | `g_dwCfgMaxBrightness` | 25–98 |
| `MaxADC=` | `g_dwCfgMaxAdc` | 5–127 |
| `defMsgJust=` | `g_bCfgDefMsgJust` | L/R/C (initial `!dl` justify) |
| `defMsgEffect=` | `g_bCfgDefMsgEffect` | I/R/S/U/r/s/u (initial `!dl` mode) |
| `defMsgDuration=` | `g_dwCfgDefMsgDuration` | (initial dwell) |
| `defSeqEffect=` | `g_bCfgDefSeqEffect` | I/R/U/V/r/u/v — also the `!se` target |
| `Succession=` | `g_dwCfgSuccession` | Y/N — `!sf` target |
| `CarryPageContent=` | `g_dwCfgCarryPageContent` | Y/N — `!cc` target |
| `autoDetectArabic=` | `g_dwCfgArabicAutoDetect` | Y/N — `!ad` target |
| `translateArabic=` | `g_dwCfgTranslateArabic` | Y/N |
| `ArabicLigatures=` | `g_dwCfgArabicLigaturesEnabled` + `g_dwArabicLigatureCount` (+ table) | per-protocol Arabic glyph substitution table |
| `RepeatDLs=` | `g_dwCfgRepeatDls` | Y/N |
| `ClearOldQueue=` | `g_dwCfgClearOldQueue` | Y/N |
| `queueMsThenSs=` | `g_dwCfgQueueMsThenSs` | Y/N — also settable via `ZQ` |
| `carryLastlines=` | `g_dwCfgCarryLastLines` | Y/N — also settable via `ZQ` |
| `scrollIfTooWide=` | `g_dwCfgScrollIfTooWide` | Y/N — `!to1` mode |
| `truncateOnChar=` | `g_dwCfgTruncateOnChar` | Y/N — `!to2` mode |
| `truncateOnWord=` | `g_dwCfgTruncateOnWord` | Y/N — `!to3` mode |
| `suppressHourLeadingZero=` | `g_dwCfgSuppressHourLz` | Y/N — clock-field rendering |
| `suppressMinsLeadingZero=` | `g_dwCfgSuppressMinsLz` | Y/N |
| `suppressSecsLeadingZero=` | `g_dwCfgSuppressSecsLz` | Y/N |
| `suppressDayLeadingZero=` | `g_dwCfgSuppressDayLz` | Y/N |
| `replaceHoursLeadingZero=` | `g_dwCfgReplaceHoursLz` | Y/N (default `Y`) |
| `suppressMonLeadingZero=` | `g_dwCfgSuppressMonLz` | Y/N |
| `EDFalwaysDefault=` | `g_dwCfgEdfAlwaysDefault` | Y/N |
| `EDFmaximumTrains=` | `g_dwCfgEdfMaxTrains` | numeric |
| `EDFcntDownEaAnsEd=` | `g_dwCfgEdfCntDown` | Y/N |
| `HygrosenTempProbe=` | `g_dwCfgHygrosenTempProbe` | Y/N |
| `LightSensor=` | `g_dwCfgLightSensorEnabled` | Y/N |
| `Temp=` | `g_dwCfgTempEnabled` | Y/N |
| `LEDmon=` | `g_dwCfgLedmonEnabled` | Y/N |
| `DriveType=` | `g_drive_type` | `M`/`T`/`D` |
| `speedDivisorM=` | `g_dwCfgSpeedDivisorM` | 1–19 |
| `speedDivisorD=` | `g_dwCfgSpeedDivisorD` | 1–19 |
| `BrightControl=` | `g_dwCfgBrightControl` | `D`/`O` |
| `PSU=` | `g_abCfgPsu` | first char (`'N'` default) |
| `doublesided=` | `g_dwCfgDoublesided` | Y/N |
| `ignoreDP=` | `g_dwCfgIgnoreDp` | Y/N |
| `swapChar=` | `g_abCfgSwapCharTable` + `g_dwCfgSwapCharCount` | translation pairs |
| `RGSwap=` / `RBSwap=` | `g_dwCfgRgbSwapBits` | bit 0 = RGSwap, bit 1 = RBSwap |
| `Master=` | `g_dwCfgMaster` | Y/N |
| `StartTimedOut=` | `g_dwCfgStartTimedOut`, `g_dwCfgStartTimedOutInit` | both set on `Y` |
| `ChannelLengths=` | `g_dwCfgChannelLengths[8]` | per-channel pixel width |
| `missingLEDs=` | `g_dwCfgMissingLeds[8]` | per-channel missing-LED count |
| `LinesPerChannel=` | `g_dwCfgLinesPerChannel[8]` | per-channel line count |
| `DLMx=` | `g_dwCfgDlmxX/Y/H/W`, `g_dwCfgDlmxLinesPerIndex`, `g_dwCfgDlmxCount`, `g_dwCfgDlmxHasZero`, `g_dwCfgTotalWidthDlmx` | per-mode per-line geometry — these tables back `!Fm` zone lookups |
| `DDXmodalPage=` | `g_dwCfgDdxModalV1`…`V4` | modal-page geometry |
| `DDXfixedPage=` | `g_dwCfgDdxFixedPage`, `g_dwCfgDdxFixedYn`, `g_dwCfgDdxFixedSet`, `g_dwCfgDdxZoneX/Y/H/W`, `g_abCfgDdxZoneNames` | fixed-page zone table (up to 20 zones × 256-byte name) |
| `DDXfixedLine=` | `g_dwCfgDdxFixedPage`, `g_dwCfgDdxFixedYn`, `g_dwCfgDdxFixedSet`, `g_abCfgDdxLineField1/2/3` + compiled body via `FUN_2000c8c0` | fixed-line layout |
| `DST=` | `g_dwCfgDstStartMonth/Week/EndMonth/EndWeek/StartDow/EndDow`, `g_dst_valid_marker` | DST window; `g_dst_valid_marker` is set to `0x31121955` only when the full record validates |
| `EDF_PAGE=` | (large table at `DAT_200a7a68`) | not yet decoded |

## 12. Open items

- Handlers `cmd_st_handler`, `cmd_qF_handler`, `cmd_Fm_handler`, `cmd_zr_handler`, `cmd_zp_handler`, `cmd_qe_rl_handler` are mapped to addresses but their internal byte formats are not yet decoded.
- The `W`-family per-zone routing and the `FUN_200254d4`/`FUN_200274ac`/`FUN_20029828` chain need deeper analysis.
- The `R Time/Date/Temperature Now` adjuster code paths are only partly traced — the `±<HH>` arithmetic is confirmed; the field-write side-effects (`DAT_20072244`, `DAT_20072258`, `DAT_20031864`) need follow-up.
- Visual semantics of `parse_mode`'s 13 mode bytes (per §6.5.1) are inferred from the rodata names but not confirmed on hardware — see §13 for the test plan that would pin them down.

## 13. Test plan — pinning down `cmd_dl_handler_alt`

Everything in §6.5 was reconstructed from the dispatch / record-write code; the *visual semantics* of each mode and the colour digit mapping have not been verified against a running unit. The probes below are designed to be small, observable, and to isolate one variable at a time. Send each probe with a checksum if the unit demands it (assume the unit's low address is `1` → addressed as `0A`; substitute as needed).

### 13.1 Preamble

Every probe assumes this baseline:

```
[0A!zb]                       reboot (clean slate)
[0A!se S]                     CurrentMode → static
[0A!?v]                       sanity check: confirm firmware v1.01.1 reply
[0A!?z]                       record geometry: `pixels,rows×lines,M|C`
[0A!?q]                       record initial brightness state
[0A!m1!ffc]                   select slot 1, clear frame
[0A!ps01]                     show page 01 (forces an active page context, else !dl returns AN02,A4)
```

Reset between probes with `[0A!cd]` (clear current message) — avoids leftover segments from a previous test polluting the line records.

### 13.2 Primary modes — `S` / `s` / `C` / `c`

Goal: confirm which mode actually renders as static text, scroll, static clock, scrolling clock — and confirm the `(primary, secondary)` slot pairing maps to visible behaviour.

| # | Command | What to observe | Confirms |
|---|---|---|---|
| 1 | `[0A!dl01S1N<HELLO>]` | text "HELLO" should appear stationary in the line's default position, colour 1 | `MODE_STATIC` writes `(S,S)` and the renderer treats the pair as plain static |
| 2 | `[0A!dl01s1N<HELLO>]` | text should scroll horizontally; same colour | `MODE_SCROLL` writes `(S,s)` and `s` in the secondary slot is the scroll trigger |
| 3 | `[0A!dl01C1N<>]` | live clock face should appear, static (no scroll); empty `<>` because clock fields come from RTC | `MODE_CLOCK_STATIC` writes `(C,S)` |
| 4 | `[0A!dl01c1N<>]` | live clock that scrolls in/out (likely 12-h format if `C` was 24-h) | `MODE_CLOCK_SCROLL` writes `(c,s)` — also tests whether case difference encodes 12h vs 24h |
| 5 | `[0A!dl01C0N<>]` then `[0A!dl01CAN<>]` | both should render identically | `CA` is the documented alias for `C0` |

For #3/#4 also issue `[0A!st<HHMMSS>]` first so the clock has a known time.

### 13.3 Colour digit (0–9)

Goal: enumerate what each digit shows. Probe each in turn with the same text so only the digit changes:

```
[0A!dl01S0N<X>]   for X in {S0..S9}
[0A!cd]           between each
```

Record the colour you see for each digit (`0` and `1`–`9`). Specifically watch for:
- whether `0` is a "no colour" / inherit case (it returns just the mode byte with high byte 0)
- which digit gives the brightest / which gives the dimmest
- whether `5`–`9` access secondary colours only on multi-colour units (`!?z` returns `M` or `C`)

### 13.4 Shortcut-word modes (effect overrides)

Hypothesis (§6.5.1): the 9 two-letter shortcuts are *effect overrides* — they update colour + default-attr only, do not touch the per-line slot pair, and so reuse whatever S/s/C/c the renderer last installed.

Test: install a baseline static line first, then re-send `!dl` for the same line with a shortcut mode. The text content should stay; the visual effect changes.

| # | Setup | Effect probe | What to observe |
|---|---|---|---|
| 6 | `[0A!dl01S1N<HELLO>]` | `[0A!dl01ruN<HELLO>]` | text remains "HELLO" but with the `ru` effect (likely "run-up" / vertical roll-up entrance) |
| 7 | (same) | `[0A!dl01drN<HELLO>]` | likely "drop" entrance |
| 8 | (same) | `[0A!dl01olN<HELLO>]` | likely "open from left" / "lift" |
| 9 | (same) | `[0A!dl01orN<HELLO>]` | likely "open from right" / "roll" |
| 10 | (same) | `[0A!dl01ocN<HELLO>]` | likely "open from centre" |
| 11 | (same) | `[0A!dl01oeN<HELLO>]` | likely "open from edges" |
| 12 | (same) | `[0A!dl01psN<HELLO>]` | likely "pause" — text appears then holds |

Name each effect from what you see. The proposed enum names (`MODE_RUN`, `MODE_DROP`, `MODE_LIFT`, `MODE_ROLL`, `MODE_OPEN_V_UPPER`, `MODE_OPEN_V_LOWER`, `MODE_PAUSE`) can be revised to match.

Also send **without** a preceding static install:

```
[0A!cd]
[0A!dl01ruN<FRESH>]
```

If §6.5 is right (these don't write the slot pair), behaviour without a baseline static may be undefined or fall back to whatever the per-line slot was at boot. If it works fine, the inference about slot-pair persistence is wrong.

### 13.5 Queue mode `qs` — segment splitter & qwidth

Goal: confirm `|` inside `<…>` splits the body into independently-rendered queue segments, and that segment width = `Sequence` (seconds).

```
[0A!se S]                                          // CurrentMode static
[0A!ps01!cd]
[0A!dl01qs1N<AAA|BBB|CCC>]                         // three queue segments
```

Watch: the line should cycle `AAA` → `BBB` → `CCC` → repeat, with each segment held for `Sequence` seconds (default 2s from `parse_config` initial value, or whatever your config set).

Then probe the qwidth = SequenceMs/1000 relationship:

```
[0A!uq 5]                                          // set sequence to 5s
[0A!dl01qs1N<AAA|BBB|CCC>]
                                                   // confirm each segment holds 5s
[0A!uq 1]
[0A!dl01qs1N<AAA|BBB|CCC>]
                                                   // confirm 1s cadence
```

Confirms `g_dwMagicDiv1000` is used to convert `g_dwCfgSequenceMs` to a per-segment seconds count written into `qwidth` / `qwidth_mirror`.

Also test a non-`qs` mode with `|` in the body:

```
[0A!dl01S1N<AAA|BBB|CCC>]
```

If `|` only acts as a separator under `MODE_QUEUE`, this should display the literal text `AAA|BBB|CCC` as one static line. Confirms the `(text_byte == '|' && uVar14 == 0x71)` gate.

### 13.6 Icon disambiguation

Goal: confirm `'I'` (the `parse_mode` fallback) only becomes a *real* mode-change when the preceding parsed byte is `j`, `r`, or `t`.

```
[0A!dl01IjN<…>]      // I-mode with j prefix — should render as icon "j"
[0A!dl01IrN<…>]      // I-mode with r prefix
[0A!dl01ItN<…>]      // I-mode with t prefix
[0A!dl01IxN<…>]      // I-mode with x prefix — should be treated as text "Ix", not a mode change
```

The first three should render the unit's built-in icons for `j`/`r`/`t` (likely journey/road/transit symbols). The fourth should fall through to text. Also exercise the disambiguation *within* a continuation segment by chaining inside `qs`:

```
[0A!dl01qs1N<TEXT|IjFOO|IxBAR>]
```

Expect: `TEXT` → icon-j-then-FOO → `IxBAR` as literal text in the third slot.

### 13.7 Stored-buffer recall (`*`)

Goal: confirm the slot-id form and the `g_protocol_7` alt addressing.

```
[0A!kt000<HELLO BUFFER>]            // compile to text slot 0
[0A!kt050<SLOT FIFTY>]
[0A!kt999<EDGE>]                    // top of range
[0A!dl01S1N*000]                    // recall slot 0
[0A!cd]
[0A!dl01S1N*050]                    // recall slot 50
[0A!cd]
[0A!dl01S1N*999]                    // recall top slot
```

Expect each `!dl…*<DDD>` to render the corresponding buffer text. Then trigger the alt mode (if you can reach `g_protocol_7` — typically via `[0A!zm 7]` which rotates the protocol flags and reboots into mode-7) and re-test:

```
[0A!zm 7]                           // switch to g_protocol_2 + g_protocol_7
... reboot, re-prelude, re-store buffers ...
[0A!dl01S1N*42]                     // 2-digit form
```

Expect `*42` to render slot **142** (2-digit + 100 offset under `g_protocol_7`), not slot 42 — that's the divergent behaviour `g_pProtocol7` controls.

### 13.8 The `+` prefix

Goal: confirm whether `+` produces any visible difference vs no-prefix on a *first* segment.

```
[0A!cd]
[0A!dl01S1N<HELLO>]      // no +
[0A!cd]
[0A!dl01+S1N<HELLO>]     // with +
```

If §6.5 is right, the only difference is the `default_attr_seg0` field (`1` vs `0`). The visual output may be identical or may differ in attribute inheritance — note which.

Then test `+` on a continuation segment in queue mode:

```
[0A!dl01qs1N<RED\1|+BLUE\2|YELLOW\3>]
```

Inside the parsed buffer the continuation `+BLUE` should be tagged as a continuation segment (`default_attr` cleared). Compare the visual effect of the middle segment to the others to see what `default_attr` controls — likely whether the previous segment's attributes carry over.

### 13.9 Continuation segments without `qs`

Hypothesis from §6.5: only `MODE_QUEUE` enters the continuation walk. Verify:

```
[0A!dl01S1N<ABC\0DEF\0GHI>]
```

The `\0` bytes are NULs that *would* be segment splits in queue mode. In `S` mode the handler returns after committing segment 0, so DEF/GHI should be ignored / not rendered (or rendered as garbled trailing bytes). If they render as separate segments, the inference about the early return for S/s/C/c is wrong.

### 13.10 Error path probes

Each should produce a specific error reply:

| Probe | Expected reply / behaviour |
|---|---|
| `[0A!dl00S1N<X>]` | bad-param (`02`) — line `0` rejected |
| `[0A!dl01S1Z<X>]` | bad-param — justify `Z` is none of `N/L/R/C` |
| `[0A!dl01S1N!X]` | syntax (`08`) — body delimiter is neither `*` nor `<` |
| `[0A!dl41S1N<X>]` | likely bad-param via `0x91` — line 41 likely exceeds `g_dwCfgDlmxLinesPerIndex[mode]` (current panel-line count) |
| `!dl` with no active page | reply `AN02,A4` — `0xa4` no active channel/page context |
| `[0A!dl01S1N*9999]` | bad-param — `*<DDD>` only reads 3 digits, but value > 999 cannot be expressed; if it parses as `999` then probably succeeds |
| Recall an unwritten slot: `[0A!dl01S1N*042]` after a clean reboot | empty render or fallback — confirms slot-empty handling |

### 13.11 Mode → record write verification (debugger)

If a debugger is attached, set a watchpoint on `g_pLineRecordTable[active_line].primary_mode_seg0` (offset `+0x3b0`) and `+0x3c4`. After each probe in §13.2 confirm the byte values match the table:

| Probe | Expected `+0x3b0`, `+0x3c4` |
|---|---|
| `S1` | `0x53`, `0x53` (`S`, `S`) |
| `s1` | `0x53`, `0x73` (`S`, `s`) |
| `C1` | `0x43`, `0x53` (`C`, `S`) |
| `c1` | `0x63`, `0x73` (`c`, `s`) |
| any of `ru/dr/oc/oe/ol/or/ps/qs/Ix`, `I` fallback | **unchanged** from prior install |

Also watch `+0x3d8` (colour): every successful probe should write `local_4c` here, regardless of mode.

And for queue mode: `+0xec` and `+0x13c` should both equal `g_dwCfgSequenceMs / 1000`.

### 13.12 Resulting actions

After running the plan, update:

- §6.5.1's short-word "Likely meaning" column with the real visual effect names.
- The `parse_mode_t` enum members in Ghidra (e.g. `MODE_RUN` → whatever it actually does).
- §6.5's `<MA>` description if the colour-digit semantics turn out to be unit-dependent (single vs multi-colour panels may interpret differently).
- §12 to remove the `parse_mode` semantics open item.
