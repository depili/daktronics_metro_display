# RM2040 Serial Protocol & Command Reference

Daktronics RM2040 LED sign controller (firmware v1.04.4 / MMXIX). Reverse-engineered from the RAM-resident ARM image; addressing, framing, checksum, and reply format are taken directly from `USART_rx_ddx`, `cmd_addr_match`, `send_command_reply`, and `command_parse`. Items inferred but not byte-confirmed are marked *(inferred)*.

## 1. Physical layer

- **19200 baud, 8 data bits, no parity, 1 stop bit (8-N-1).** Baud is set by config `FixedUARTspeed=` (9600 / 19200 / 57600 / 115200).
- **Insert ≥1 ms between bytes** (the manufacturer tool uses 2 ms). The receiver services bytes in a polled loop over a small ring buffer; a gapless stream overruns it and the frame is lost or NAKed.
- Multidrop: each unit has a hardware-pin address (below); frames are addressed, and only the matching unit acts/replies.

## 2. Command frame format

```
[ <AA> <command-body> /<CK> ]
```

| Field | Bytes | Meaning |
|---|---|---|
| `[` | `0x5B` | start of frame (resets the RX buffer; not stored, but seeds the checksum) |
| `<AA>` | 2 ASCII | device address (§2.2) |
| body | n | one or more `!`-prefixed command tokens; non-`!` filler between tokens is skipped |
| `/<CK>` | 3 ASCII | **optional** checksum: `/` + 2 hex digits (§2.3) |
| `]` | `0x5D` | end of frame → parse + execute |

### 2.1 Command tokens

Each command is `!` + a 2-character mnemonic, optionally followed by arguments the handler consumes. The resolver packs the mnemonic as `(char1<<8)|char2`, maps it to `(scope<<16)|opcode`, and the dispatcher rejects it with error `0x04` if the addressing scope doesn't satisfy the command's scope bits.

### 2.2 Addressing

The unit's own address is read from hardware pins: a **HIGH group 1–8** (pin bits 5–7; 0 reads as 8) and a **LOW unit 1–26** (pin bits 0–4). The two address characters are matched by `cmd_addr_match`:

| Address chars | Selects |
|---|---|
| `0@` | **all units (broadcast / wildcard)** |
| `0A` … `0Z` | one unit by LOW address (`A`=1 … `Z`=26) |
| `1` … `8` (+ any 2nd char) | every unit in that HIGH group |
| `00` | **nothing — invalid; not a broadcast** |

No match → the frame is silently dropped (no reply). Example: a unit with low address 1 is addressed as `0A`; broadcast to everything is `0@`.

### 2.3 Checksum

```
CK = ( 0x5B + Σ(every byte from <AA> through end of body) ) & 0xFF
```

Two uppercase hex digits, seeded with `'['`. It is **optional**: the unit only verifies it when the byte three positions before `]` is `/`. Frames may be sent with no `/CK`.

## 3. Reply frame format

Three reply paths exist, distinguished by the 2nd/3rd characters.

### 3.1 Command reply — `send_command_reply` (the normal path)

```
[ <U> <T> <code> [,<status>] <fields> /<CK> ]
```

| Field | Meaning |
|---|---|
| `<U>` | unit char = LOW address + `'@'` (`A` = unit 1) |
| `<T>` | **`Y`** (0x59) if the command succeeded (result == 0); **`N`** (0x4E) if it errored |
| `<code>` | 2 hex of the command result/error class (§3.4) |
| `,<status>` | 2 hex status byte (appended unless suppressed in some modes) |
| `<fields>` | `:`-separated query data, when the command produced any (e.g. `!?v`, `!??`) |
| `/<CK>` | checksum, same rule as commands |

**Gate:** this fires only when the command descriptor's reply bit (`flags & 1`, from `g_cmd_flag0_src`) is set — which it is when the unit is addressed individually. Example: `[AN02,0F/EE]` = unit 1, **error**, code `0x02` (bad parameter), status `0x0F`. The same path returns `[AY…]` on success.

### 3.2 Transport NAK — `msg_compose_some_reply` (link errors, unconditional)

```
[ <U> N <code> ,<status> /<CK> ]
```

Sent regardless of the reply gate when the *transport* rejects a frame. `<code>` ∈ `01` line error · `20` checksum mismatch · `40` buffer overflow · `80` inter-char timeout. (Same wire shape as a `N` command reply, but the codes are disjoint.)

### 3.3 Status reply — `[FFP…]`

A separate status frame (`[FFP<n>:<n>:<hex>/<fps>fps/LS…/CK]`) carrying frame-buffer indices, refresh rate, and light-sensor levels. Also gated on the reply bit.

### 3.4 Error & status codes

**Command class** (the `<code>` in a `N` reply): `02` bad parameter · `04` denied / unknown / wrong scope · `08` syntax.

**`!dl` detail codes** (set internally, surfaced via detail fields): `A4` no active channel/page context · `90` bad line number · `A8` line doesn't fit the panel · `31` bad justify char · `9F` default-line mismatch.

**Addressed-mode (`'i'`) line-op codes:** `96` / `98` / `99` / `9A` / `9B` / `9C` (from `!lh`/`!lr`/`!lp`).

## 4. Command reference

Format notation: `<n>` decimal, `<HH>` hex, `Y|N` yes/no letter, `<…>` bracketed text. "Reply" = the command returns query data.

### 4.1 Content & display

| Cmd               | Format                          | Effect                                                                                                                                                                                     |
| ----------------- | ------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| `!dl`             | `!dl<line><attr>jp<just><text>` | define a line. `<attr>jp` = default attribute; `<just>` = `N`/`C`/`R`/`L`; text in `<…>`, or `*<buf 0–199>` to recall a stored 2 KB buffer. Requires an active page/channel context first. |
| `!cd`             | `!cd`                           | clear the current message                                                                                                                                                                  |
| `!ff`             | `!ffc` / `!ffd<n>` / `!ffr…`    | frame: clear / delete page `n` / reset                                                                                                                                                     |
| `!cl`             | `!cl…`                          | clear line *(handler `FUN_20019538`)*                                                                                                                                                      |
| `!cp`             | `!cp…`                          | *(handler `FUN_20017830`)*                                                                                                                                                                 |
| `!dp`             | `!dp…`                          | display position                                                                                                                                                                           |
| `!dw`             | `!dw`                           | display window                                                                                                                                                                             |
| `!dg`             | —                               | draw graphics                      |
| `!df`             | —                               |                       |
| `!dr`             | —                               |  |
| `!kb`             | `!kb<n><…>`                     | compile markup into custom glyph slot `n` (0–255)                                                                                                                                          |
| `!kt`             | `!kt<n><…>`                     | compile markup into custom text slot `n` (0–255)                                                                                                                                          |
| `!kg`             | `!kg<n>,<h>,<w><...>`           | compile markup into custom graphics slot `n`                                                                                                                                                     |
| `!cc`             | `!cc<F?>:<…>`                   | FPGA/clock self-test → reply `Pass`/`Fail`                                                                                                                                                 |

### 4.2 Pages

| Cmd | Format | Effect |
|---|---|---|
| `!m0`…`!mF` | `!m<0–F>` | select active page slot 0–15 (NB mode: `!m1` selects slot **2**) |
| `!mX`/`!mx` | — | select slot from `g_dlmx_mirror` |
| `!ps` | `!ps<page 0–107>` | show a page |
| `!pl` | `!pl*` or `!pl<n,n,…>` | load all pages / define page playlist |
| `!pd`/`!pr`/`!px` | — | page delete / reset / clear *(handlers `FUN_2001b4cc`/`2000b03c`/`200095ec`)* |
| `!ls`/`!lc` | `!ls<…>` / `!lc<…>` | line-list select (`!lc` also sets a flag) |
| `!li`/`!lt` | — | list insert / *(handlers `FUN_2001beb4(…,'i')` / `FUN_2001942c`)* |

### 4.3 Settings — set & read back

Set commands persist (many flag the config dirty). Each typically has a `!r_` read-back.

| Set         | Format                | Stored                            | Read back |
| ----------- | --------------------- | --------------------------------- | --------- |
| `!sa`       | `!sa<serial><address>`| group, address                    | `!?t`     |
| `!st`       | set time *(inferred)* | RTC                               | `!?t`     |
| `!sd`       | `!sd<W><MM><DD><YY>`  | RTC date (weekday 1-7, validated) | `!?d`     |
| `!sf`       | `!sf<Y\|N>`           | master mode                       | —         |
| `!se`       | `!se<mode>`           | current mode (`S/s/C/c`→`I`)      | —         |
| `!sg`       | `!sg<n>`              | brightness cap (clamped)          | `!?f`     |
| `!sb`       | `!sb<n≤100>`          | `DAT_20174580`                    | `!rb`     |
| `!si`       | `!si<nnnn>`           | `DAT_20023920`                    | `!?i`     |
| `!ux`       | `!ux<n≤100>`          | max brightness                    | —         |
| `!uy`       | `!uy<n>`              | min brightness                    | —         |
| `!ui`/`!uw` | `<n≤100>`             | brightness clamps                 | —         |
| `!Fs`       | `!Fs<50–160>`         | scan/refresh rate                 | —         |
| `!Fx`       | `!Fx<0–9>`            | flash                             | —         |
| `!LS`       | `!LS<n≤5000>`         | light-sensor level                | —         |
| `!uq`       | `!uq<1–20>`           | message timeout (s)               | `!rq`     |
| `!uf`       | `!uf<aaa,bbb>`        | scroll speeds A,B                 | `!rf`     |
| `!um`       | `!um<n<16>`           | maintenance time                  | `!rm`     |
| `!ul`       | `!ul<n<61>`           | PIN lock                          | `!rl`     |
| `!ua`       | `!ua<n>`              | max scrolls                       | `!?s`     |
| `!ub`       | `!ub<0/1/3/5/7>`      | sequence flags                    | —         |
| `!uh`       | `!uh<N\|C><n>`        | LED error min/max                 | `!rh`     |
| `!ue`       | `!ue<0\|1>`           | `DAT_2002392c`                    | `!re`     |
| `!ut`       | `!ut<…>`              | mode-change-clears (`≠N`)         | —         |
| `!to`       | `!to<1–3>`            | message mode (`!to4` = query)     | —         |
| `!tp`       | `!tp<0–7>`            | test pattern select               | —         |
| `!ud`       | `!ud<text>*`          | timeout message                   | `!rd`     |
| `!uo`       | `!uo`                 | set dlmx from sensor              | `!?u`     |
| `!ad`       | `!ad<Y\|N>`           | auto-detect Arabic                | —         |

### 4.4 Queries (return data)

* `!??` full ID dump
* `!?v` app version `XXXX,XXXX`
* `!?n` serial number
* `!?b` current brightness
* `!?c`/`!?z` geometry (`pixels,rows×lines,M|C,S|D`; device name in NB mode)
* `!?f` brightness cap
* `!?s` max scrolls
* `!?k` board mode (`S`/`A`/`M`/`None`)
* `!?l` PCB rev (`PCB294`/`PCB175`)
* `!?q` brightness/sensor status
* `!?h` hw flags (clears)
* `!?e` failure log
* `!?g` dlmx mirror
* `!?N` next-bus state (`NBon`/`NBoff`)
* `!?p` presence → `1`
* `!rj`/`!rt`/`!rp` name/string read-backs
* `!qc`/`!ql`/`!qm` zone count/list/detail
	* 
* `!qf`/`!qi` ddx page/line
* `!qe<off>,<len>` memory dump (reply type `Y`).

### 4.5 Display zones

A **zone** is a named display region made of one or more rectangular **lines** (`x`, `y`, `h`, `w`). Up to **16 zones** (indices `0x0`–`0xF`) exist, each holding up to **41 lines**.

The first `g_zone_count` zones (`0` … `g_zone_count-1`) are **defined in the boot config (`ACFG`) and are protected** — `!Fm` cannot modify them. Zones from `g_zone_count` upward are **user zones**, defined/cleared at runtime with `!Fm` and read back with `!q*`.

#### Define / clear a user zone — `!Fm`

```
!Fm m<zoneHex> { l<n> x<X> y<Y> h<H> w<W> } … *
```

- `m<zoneHex>` — target zone (one hex digit). Must satisfy `g_zone_count ≤ zone ≤ 0xF` (config zones are protected).
- For each line: `l<n>` selects line `n` (1–40), then `x`/`y`/`h`/`w` set that line's rectangle (pixels). Repeat `l…x…y…h…w…` per line.
- `*` ends the command.
- An **empty** spec (`!Fm m<zone> *`, no lines) **clears** the zone (`line_count = 0`).

Validation (all reject with bad-parameter, reply code `zone<<16 | code`):

| Code | Meaning |
|---|---|
| `0x13` | zone index out of range (`< g_zone_count` or `> 0xF`) |
| `0x14` | bad line number (> 40) |
| `0x15` / `0x16` | bad `x` / bad `y` |
| `0x17` / `0x18` | `h` exceeds panel height / `w` exceeds panel width |
| `0x19` | two lines overlap |
| `0x1a` | total `y+h` exceeds panel height |
| `0x1b` | `x+w` exceeds the channel length at that `y` |
| `0x1c` | unexpected end / syntax |

#### Read zones — `!q*`

| Cmd | Format | Returns |
|---|---|---|
| `!qc` | `!qc` | zone count: `<g_zone_count>,<active−configured>` |
| `!ql` | `!ql` | hex indices of zones that have lines, comma-separated |
| `!qm` | `!qm<hex>` | one zone's lines: `M<id>,` then per line `L<n>x<xxxx>y<yyy>h<hhh>w<wwww>` (or `M<id>,NL` if empty) |

#### Storage model

- `g_zone_count` — number of config-defined (protected) zones.
- `g_zone_line_count[zone]` — active line count per zone (`0` = empty/cleared).
- `g_zone_x` — per-zone line table, stride `0x290` bytes/zone (41 lines × 4 words `x,y,h,w`).

> Note: zone *control* commands `!za/!zb/!zd/!zl/!zo/!zp` and the `!zr/!zy/!zz` reboot commands are unrelated to display zones — see §4.5.1 / the reboot section.

#### `!z*` reboot / backup-register commands

These stage a flag in the battery-backed backup registers and reboot the controller — see §4.5.1.

| Cmd | Format | Effect |
|---|---|---|
| `!zr` | `!zr` | `GPBR0 = 2`, then reset |
| `!zy` | `!zy` | `GPBR0 = 3`, `GPBR1 = port`, `GPBR2 = strap value`, then reset |
| `!zz` | `!zz` | `GPBR0 = 5`, `GPBR1 = port`, `GPBR2 = strap value`, then reset |
| `!zb` | `!zb` | reset only (no flag set) — plain reboot |

All four: **ack → flush the port → (stage GPBR) → reset**. `!zr/!zy/!zz` act **only when individually addressed** (not broadcast) and the address high-nibble is 0; otherwise ignored silently.

#### Other `!z*` commands

| Cmd           | Format        | Effect                                                                                                                                  |
| ------------- | ------------- | --------------------------------------------------------------------------------------------------------------------------------------- |
| `!zo`         | `!zo<hex>`    | **direct FPGA register poke** — writes the value to the FPGA register at `0x60000034` (external bus). Unrelated to the reboot commands. |
| `!zp`         | `!zp<1–8>`    | validates range, then no-op (calls an empty stub; reserved)  |
| `!zl`         | `!zl`         | clear `DAT_2017471c` (scope 2 only)                          |
| `!za` / `!zd` | `!za` / `!zd` | Show message stored in SPI (AMSG)                            |

#### 4.5.1 Reboot / backup-register mechanism

The controller is an **Atmel AT91SAM7 (ARM7TDMI)**. `!zr/!zy/!zz` hand a value to the bootloader across a reset using the battery-backed General Purpose Backup Registers:

```
gpbr_set_word(0, <mode>)   ; GPBR0 = bootloader mode  (zr=2, zy=3, zz=5)
gpbr_set_word(1, <port>)   ; GPBR1 = source port      (zy/zz only)
gpbr_set_word(2, <value>)  ; GPBR2 = strap-selected   (zy/zz only)
system_reset()             ; RSTC_CR = 0xA500000D  -> reboot
```

- `gpbr_set_word(i, v)` writes `GPBR[i]` (`*PTR_GPBR_0 = 0xFFFFFD50`, registers 0–3). These survive reset while backup power is present.
- `system_reset()` writes `RSTC_CR` (`0xFFFFFD00`) `= 0xA500000D` = key `0xA5` + `PROCRST | PERRST | EXTRST` — a full processor/peripheral/external reset.
- `GPBR0` is the **bootloader mode selector** (observed values 2 / 3 / 5). `GPBR1` records the **port** the command arrived on so the bootloader can reply on it. `GPBR2` is a value chosen by a **PIO strap bit (`0x400`)** between two config constants (e.g. board side/position).
- The meaning of modes 2/3/5 lives in the **bootloader**, which is not in this application image. The shape (reboot into a mode, remember the port) is consistent with **firmware-update / recovery entry**.
- The same `system_reset()` is used by the **PIN-lockout path** (`pin_lock_stuff`), confirming it is a genuine reset rather than a mailbox.

> Caution: `!zr/!zy/!zz/!zb` reboot the sign. Do not issue them as part of normal display updates.

### 4.6 Diagnostics & debug

* `!BEdebug-1<Y|N>` enable debug (password-gated)
* `!DR<n>` debug register
* `!DD` *(handler `FUN_200175e8`)*
* `!Dc` *(handler `FUN_2000b37c`)*
* `!Fm` *(handler `FUN_20018dc0`)*
* `!tl` run LED failure scan.

### 4.7 Mode / comms

* `!NB<Y|N>` next-bus mode (also clears master mode; **changes several command meanings**)
* `!uu<Y|N>` protocol select
* `!ur<N>` notify flag (`DAT_20174730`)
* `!sr` NB-only refresh.

> **NB (next-bus) mode caveat:** when `!NBY` is active, `!m1`→slot 2, `!?c` returns the device name instead of geometry, and `!sr` becomes active. Query `!?N` to check state.

## 5. Text content & markup

Inside a `!dl` `<…>` body, backslash codes set colour/font/fields. Summary: `\0`–`\9`/`\h<HH>` colour · `\+`/`\-`/`\v` font size · `\w` width · `\f`/`\s` LTR/RTL · `\c d`/`\c i` clock (24/12 h) · `\d{…}` date field · `\t{…}` time field · `\i` icon · `$<HH>` raw byte · `\o` group. An inline `\x00`-introduced attribute change (`+<mode><colour>` or `jp`/`tv`/`rs`) starts a new segment. The clock/date fields read the RTC set by `!st`/`!sd`. (See the dedicated markup reference for the full control-code table.)

## 6. Worked examples

Assume unit low address 1 (addressed `0A`). Checksums optional; shown where computed.

```
Display one line (needs page context first):
[0A!m1!ffc!dl01jpC<Hello World>!ps01]

Query firmware version:
[0A!?v]            -> [AY<XXXX,XXXX>/CK]    (success, type Y)

Query full info:
[0A!??]            -> [FFP… multi-field …/CK]

Broadcast (all units):
[0@!m1!ffc!dl01jpC<Hello>!ps01]

A rejected command returns the N variant, e.g.:
[0A!dl01jpC<Hi>]   -> [AN02,0F/EE]   (no active page context: bad param 0x02)
```

## 7. Notes & open items

* `!st` time format, the zone handlers, and several delegated handlers (`!up`, `!us`, `!uc`, `!rc`, `!?r`, `!?j`, `!?x`, `!DD`, `!Fm`) are mapped to their addresses but not yet fully decoded.
* `!dl` requires an active channel/page; if a bare `!dl` returns `AN02` (detail `A4`), select a page first (`!m…`) or check that the unit's config defines a text channel/page geometry.