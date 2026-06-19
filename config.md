# Configuration Reference (`config_parse`)

`config_parse` runs at boot and populates the device's global configuration. It first tries to load a binary blob (`FUN_20002058(0, &DAT_20187678, 'ACFG')`); on failure it parses a **text config file** (`config_file`, CRC in `config_file_crc`) line by line.

These globals are the same ones the runtime `!XX` command set reads and writes (see the protocol reference), so the config file is effectively the persisted form of the command state.

## File format

- Header magic: `ACFG` (`0x47464341`).
- One `Key=Value` per line; lines read via `FUN_2000d108(…, 0x200)`.
- Parsing ends at a line that is just `.` (`local_228[0]=='.' && [1]=='\0'`).
- Booleans accept `Y`/`N` case-insensitively (compared via `& 0x5f`).
- Numbers parsed by `FUN_2000cff4` (signed int) / `FUN_2000d05c`; lists are comma-separated; some values are single letters.
- Out-of-range numeric values are clamped (shown below).

> Confidence: defaults and the clearly-keyed handlers are read directly from the code. A handful of keys whose handler is ambiguous in the deep `if/else` nest are marked **(inferred)**. `DAT_xxxx` names are unresolved globals.

---

## 1. Power-on defaults (set before parsing)

| Global | Default | Meaning |
|---|---|---|
| `conf_pix`, `DAT_20174528` | `0x100` (256) | pixels per channel |
| `DAT_20023898` | `8` | channels |
| `DAT_20023894` | `1` | colours |
| `DWORD_2002388c` | `8` | rows per line |
| `DAT_2002370c` / `DAT_20023710` | `0x46`/`0x1e` (70/30) | speed pair |
| `DAT_2002391c` | `2000` | message timeout (ms) |
| `DAT_20023938` | `4` | fixed font flag |
| `DAT_200238c4` | `0x49` (`'I'`) | current mode |
| `DAT_200238c8` | `1` | start-timed-out |
| `DAT_200238f8` | `0xFFFFFFFF` | brightness cap = none |
| `DAT_200238e8` | `0` | FX slowdown |
| `DAT_200238a0` | `'O'` | swap char |
| `DAT_200238a4` | `1` | scroll-if-too-wide |
| `DAT_20174538` | `0` | double-sided |
| `DAT_20174534` | `0` | flash |
| `DAT_20174580` | `0` | (see `!sb`/`!rb`) |
| `INT_20023704` | `0x5a0` (1440) | brightness/clock control derived value |
| `DAT_20064200`, `DAT_20064204` | `0` | debug enable / debug param |
| `DAT_20174558`,`5c`,`60`,`64`,`68`,`6c` | `0` | leading-zero suppression flags |
| `DAT_20174724` | `0` | defined-zone count |
| `fpga_flags` | `\|= 0x80000000` | light sensor enabled |
| `DAT_20187494[0..7]` | `1` | lines per channel |
| `DAT_20187534[0..255]` | identity | character remap table |
| `DAT_2018df74[0..15]` | `0` | per-zone entry counts |
| `DAT_20191fe0[…]` | `0` | zone geometry table (x/y/w/h) |

---

## 2. Panel geometry

| Key | Global(s) | Constraint | Cmd |
|---|---|---|---|
| `Pixels=` | `conf_pix`, `DAT_20174528` | — | — |
| `Channels=` | `DAT_20023898` | 1–8 | — |
| `Colours=` | `DAT_20023894` | 1–3 (1=mono, 2/3=multi) | `!uk` |
| `RowsPerLine=` | `DWORD_2002388c` | 7–9 | — |
| `ChannelLengths=` | `DAT_2018df4c[0..7]` | comma list; flags lengths as explicit | — |
| `LinesPerChannel=` | `DAT_20187494[0..7]` | comma list | — |
| `missingLEDs=` | `DAT_20187658[0..7]` | comma list | — |
| `DriveType=` | `DAT_20023880` | `M`/`T`/`D` scan type | — |
| `doublesided=` | `DAT_20174538` | Y/N | — |
| `MLSlot=` *(inferred)* | `DAT_2002389c` | `D`/`O` | — |

Derived afterward (not config keys): `DAT_20023888` (max lines), `DAT_20023884` (block size, from a 1→0x800 … 16→0x80 lookup), `DAT_20189680[]` (channel pixel counts rounded to M=128/T,D=32 boundaries), `conf_lines`, `DAT_2017452c`/`DAT_20174530` (colour-mode buffer strides), `DAT_200238b8`/`DAT_200238bc` (computed canvas dimensions).

---

## 3. Brightness / sensor

| Key | Global(s) | Constraint | Cmd |
|---|---|---|---|
| `MinBr=` | `DAT_200238f0` | 0→1, >30→20 | `!uy` |
| `MaxBr=` | `DAT_200238f4` | 25–98 (`0x19`–`0x62`) | `!ux` |
| `CapBr=` | `DAT_200238f8` | 25–98; default none | `!sg`/`!?f` |
| `MaxADC=` | `DAT_2002390c` | 5–127 | — |
| `BrightControl=` | `INT_20023704` | 50–160 → `FUN_20002640(0x8ca00, v*RowsPerLine)` | `!Fs` |
| `LightSensor=` *(inferred)* | — (parsed) | — | — |
| `LSType=` | `fpga_flags` bit31 | `'0'`→off (`FUN_200004d0(0,0x48)`), else on | — |
| `PSU=` | `fpga_flags` low nibble | `Y[,1-3]` sets bits / `N` clears | — |
| `HygrosenTempProbe=` | `DAT_201746b8` (+ `DAT_20191fd8`, `DAT_2018df40`, `DAT_20191fdc`) | Y/N + probe params | — |
| `Temp=` *(inferred)* | — (parsed) | — | — |
| `LEDmon=` *(inferred)* | — (parsed) | — | — |

---

## 4. Timing / motion

| Key | Global(s) | Constraint | Cmd |
|---|---|---|---|
| `Speed=` | `DAT_2002370c`, `DAT_20023710` | each ÷10, cap 100; comma pair | `!uf`/`!rf` |
| `Timeout=` | `DAT_2002391c` | ×1000, 1–90 | `!uq`/`!rq` |
| `MaintTime=` | `DAT_20023924` | 1–15 | `!um`/`!rm` |
| `PinLock=` | `DAT_20023928` | 1–60 | `!ul`/`!rl` |
| `Flash=` | `DAT_20174534` | <10 | `!Fx` |
| `FXslowdown=` | `DAT_200238e8` | <99 | `!rp` |
| `MaxScrolls=` | `DAT_20023800` | — | `!ua`/`!?s` |
| `speedDivisorM=` | `DAT_20023724` | 1–19 | — |
| `speedDivisorD=` | `DAT_20023728` | 1–19 | — |
| `speedDivisorMB=` | `DAT_2002372c` | 1–19 | — |
| `speedDivisorDB=` | `DAT_20023730` | 1–200 | — |

---

## 5. Display behavior / content

| Key | Global(s) | Constraint | Cmd |
|---|---|---|---|
| `CurrentMode=` | `DAT_200238c4` | `R/U/V/r/u/v`→codes, else `I` | `!se` |
| `FixedFontFlag=` *(inferred)* | `DAT_20023938` | masked to 0–9, else 4 | `!rs` |
| `scrollIfTooWide=` | `DAT_200238a4` | Y/N | — |
| `truncateOnChar=` | `DAT_2002380c` path (mode latch `bVar1`) | Y/N | — |
| `truncateOnWord=` | `DAT_2002380c` path (mode latch) | Y/N | — |
| `modeChangeClearsContent=` | `DAT_200238a8` | Y/N | `!ut` |
| `CfgFixedContentDefMode=` | `DAT_200238c0` | Y/N | — |
| `internalMsgMode=` | `DAT_2002380c` | N/Y mode select | `!to` |
| `MainChannel=` | `DAT_2002380c` | N/Y mode select | `!to` |
| `Succession=` | `DAT_2002380c` | N/Y mode select | `!to` |
| `defSeqEffect=` | `DAT_20023808` (+ `FUN_20009014`) | atoi | — |
| `Sequence=` | `DAT_20023860` | up to 3 Y/N → bits 0/1/2 | `!ub` |
| `LedErrorsMaxMin=` | `DAT_20023934`, `DAT_20023930` | two values | `!uh`/`!rh` |
| `swapChar=` | `DAT_200238a0` | single char | — |
| `RGSwap=` | `conf_swap` bit0 | Y/N | — |
| `RBSwap=` | `conf_swap` bit1 | Y/N | — |
| `StartTimedOut=` | `DAT_200238c8` | `Y`→1 | — |
| `DLMx=` | `DAT_2002393c`, `DAT_20023940` | hex digit 0–F | `!mX` |

---

## 6. Localization

| Key | Global(s) | Constraint | Cmd |
|---|---|---|---|
| `autoDetectArabic=` | `DAT_20174548` | Y/N | `!ad` |
| `translateArabic=` | `DAT_2017454c` | Y/N | — |
| `ArabicLigatures=` | `DAT_20187274[]` table (+ `DAT_200d8a4c`) | comma value groups, `-` terminated | — |
| `Multi-Languages=` | `DAT_20187534[]` remap | index,value pairs, `-` terminated | — |
| `suppressHourLeadingZero=` | `DAT_20174558` | Y/N | — |
| `suppressMinsLeadingZero=` | `DAT_2017455c` | Y/N | — |
| `suppressSecsLeadingZero=` | `DAT_20174560` | Y/N | — |
| `suppressDayLeadingZero=` | `DAT_20174564` | Y/N | — |
| `replaceHoursLeadingZero=` | `DAT_20174568` | Y/N | — |
| `suppressMonLeadingZero=` | `DAT_2017456c` | Y/N | — |

---

## 7. Communications / bus

| Key | Global(s) | Constraint | Cmd |
|---|---|---|---|
| `FixedUARTspeed=` | `DAT_201746bc` (port1) / `DAT_201746c0` (port2) | `port,baud`; baud ∈ {9600, 19200, 57600, 115200} | — |
| `BaudOption=` | `usart_flip` | `≠'1'` → 2 | — |
| `PROTOCOL=` | `DAT_20023970` | `≠N` → 1 | `!uu` |
| `NextBusSize=` | `DAT_2017468c[]` | name string (≤31 chars) | `!rt` reads it |
| `NextBusDDX=` | `DAT_20174688` (+ clears `DAT_200d8a54`) | Y → night-brightness on | `!NB`/`!?N` |
| `DDXmodalPage=` | `DAT_200d8a60` | <16 else 0 | `!qf` |
| `DDXfixedLine=` | `DAT_200d8a64` | <16 else 0 | `!qi` |
| `Master=` | `DAT_200d8a54` | Y/N | `!sf` |
| `Clever-Devices-Zi=` | `DAT_20023948` | `Y` → enables the `!Zi` attention sequence | (`!Zi`) |
| `FixedClockLine=` *(inferred)* | — | — | — |

`DAT_200d8a68`/`DAT_200d8a6c` are also set by a comms key (`FUN_2000cff4` pair) — these back the `!cc`/list commands; key name not pinned down.

---

## 8. Real-time clock / DST

| Key | Global(s) | Notes |
|---|---|---|
| `DST=` | `DAT_201745c4` (start month), `DAT_201745c8` (start week: `F/L/Q/S/T`→1/5/4/2/3), `DAT_201745cc` (end month), `DAT_201745d0` (end week), `DAT_201745d4`, `DAT_201745d8`, `DAT_201745dc` | format `month,week,month,week[,…]`; validity requires months 1–12 and start<end; on success sets `DAT_201745dc = 0x31121955` (valid marker) and calls `FUN_2000f82c`/`FUN_2000f28c` |

---

## 9. Zone / region definitions

Zone records are loaded by lines beginning with a zone index (`1`–`F`/decimal), parsed by the block that walks tokens until `*`:

| Token | Field | Global |
|---|---|---|
| `x` | x position | `DAT_20191fe0[(zone*0x29 + line)*4]` |
| `y` | y position | `DAT_20191fe4[…]` |
| `w` | width | `DAT_20191fec[…]` |
| `h` | height | `DAT_20191fe8[…]` |
| `l` | line index | sets current `line` (`local_24 - 1`) |

Per-zone line count → `DAT_2018df74[zone]`; total defined zones → `DAT_20174724`. These are what `!qm` (dump) / `!ql` (list) / `!qc` (count) report at runtime.

---

## 10. Cross-reference summary (config ↔ command)

| Config key | Runtime set | Runtime query |
|---|---|---|
| `CapBr=` | `!sg` | `!?f` |
| `MaxBr=` | `!ux` | — |
| `MinBr=` | `!uy` | — |
| `Speed=` | `!uf` | `!rf` |
| `Timeout=` | `!uq` | `!rq` |
| `MaintTime=` | `!um` | `!rm` |
| `PinLock=` | `!ul` | `!rl` |
| `MaxScrolls=` | `!ua` | `!?s` |
| `LedErrorsMaxMin=` | `!uh` | `!rh` |
| `FXslowdown=` | — | `!rp` |
| `Flash=` | `!Fx` | — |
| `BrightControl=` | `!Fs` | — |
| `CurrentMode=` | `!se` | — |
| `NextBusDDX=` | `!NB` | `!?N` |
| `DDXmodalPage=` | — | `!qf` |
| `DDXfixedLine=` | — | `!qi` |
| `Sequence=` | `!ub` | — |
| `PROTOCOL=` | `!uu` | — |
| `Clever-Devices-Zi=` | — | (`!Zi` enable) |

---

## Notes

- **Device picture firms up.** Config keys — `Pixels`, `Channels`, `Colours`, `RowsPerLine`, `ChannelLengths`, `LinesPerChannel`, `missingLEDs`, `MinBr`/`MaxBr`/`CapBr`, `DriveType` (M/T/D scan), `doublesided`, Arabic/multi-language handling, DST — confirm the earlier inference: this is an **LED matrix display / electronic-signage controller** (multi-channel, multi-colour panels, brightness/light-sensor control, scrolling text, RTC/DST, localization).
- **Inferred keys.** `MLSlot`, `LightSensor`, `Temp`, `LEDmon`, `FixedClockLine`, and `FixedFontFlag`'s store are marked inferred where the handler↔key pairing in the deeply nested `if/else` chain wasn't unambiguous. Their globals/constraints are read correctly even where the exact key label is tentative.
- **`DAT_20023860`** (set by `Sequence=`/`DST=` paths and `!ub`) is a sequence/effect-mode bitfield reused across several handlers.