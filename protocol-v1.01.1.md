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
| `<MA>` | mode + attribute, 2 chars, decoded by `parse_mode`. Low byte = mode char (`S`=static, `s`=scroll, `C`=clock, `c`=…, `q`=queue/multi-segment, `I`=icon). High byte = colour/attribute byte. `I` is only treated as a mode change when the *previous* segment ended with `j`, `r`, or `t`; otherwise the bytes are taken as plain text. |
| `<J>` | justify, 1 char: `N` / `L` / `R` / `C`. Anything else → bad-param `0x02`. |
| `*<DDD>` | recall stored text buffer: 3 decimal digits (0–999). Under the alt handler with `*DAT_20014078 != 0` the form is 2 digits + 100 internally → range 100–199. |
| `<…text…>` | inline body terminated by `>` or NUL. Allocated to a fresh slot via `FUN_20024128` (or `FUN_2002842c` for the bidi pre-processor path under the alt handler). Compiled by `FUN_2000c8c0` (with flag `1` for mode `q`). |

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
- `parse_mode` returns a packed `(attr<<8)|mode` but the full mode/colour table has not been enumerated.
- The `W`-family per-zone routing and the `FUN_200254d4`/`FUN_200274ac`/`FUN_20029828` chain need deeper analysis.
- The `R Time/Date/Temperature Now` adjuster code paths are only partly traced — the `±<HH>` arithmetic is confirmed; the field-write side-effects (`DAT_20072244`, `DAT_20072258`, `DAT_20031864`) need follow-up.
