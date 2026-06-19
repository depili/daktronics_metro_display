# How to Display "Hello World" — RM2040 Protocol Walkthrough

A complete, byte-level worked example for putting text on the Daktronics RM2040 LED sign over its serial command channel. Builds on `serial_protocol_reference.md` and `text_display_commands.md`.

> Reconstructed from reverse engineering. The framing, address derivation, and checksum are read directly from the parser (`USART_rx_something`) and are exact. The `!dl` attribute code `jp` and the optional page sub-commands follow the firmware's own `.rodata` templates (`!dl01jpL<…>`); exact behavior of optional sub-arguments may vary by firmware build.

---

## 1. Which channel

The sign has two serial input formats. Text/content uses the **bracket command channel** (`[ … ]`), not the `@;…;` numeric channel. Everything below is the bracket channel.

**Link settings:** 8 data bits, baud per the unit's `FixedUARTspeed=` config — one of **9600 / 19200 / 57600 / 115200**. (Parity/stop assumed 8N1; confirm against your unit.)

---

## 2. Frame anatomy

```
[ <AA> <command-body> /<CK> ]
│  │         │          │   └─ ']' end-of-frame (triggers parse + display)
│  │         │          └───── '/' + 2 hex digits: additive checksum
│  │         └──────────────── one or more '!' command tokens
│  └────────────────────────── 2 ASCII bytes: device address
└───────────────────────────── '[' start-of-frame
```

- **`[`** (0x5B) — start. Resets the receive buffer; not included in the checksum sum but used as its seed.
- **Address `<AA>`** — 2 ASCII bytes. The device id is computed as:
  ```
  id = (byte0 & 0x07) << 4 | (byte1 & 0x0F)
  ```
  `"00"` → id 0 = **broadcast** (all units). `"01"` → id 1. To target unit *N* (0–127), choose two bytes whose masked bits yield *N* (digits work directly: `"0".."9"`, then letters for the high nibble).
- **Command body** — `!`-prefixed tokens (§3). Any non-`!` filler between tokens is ignored by the parser.
- **Checksum `/<CK>`** — optional but recommended. Two uppercase hex digits:
  ```
  CK = ( 0x5B  +  Σ(every byte after '[' up to but not including '/') ) & 0xFF
  ```
  i.e. seed with `'['`, add the address bytes and the whole command body. If present, `buf[len-3]` must be `'/'`.
- **`]`** (0x5D) — end. The frame is parsed and acted on here.

(The "6 semicolons" rule from the other channel does **not** apply here — the bracket channel is delimited purely by `[` … `]`.)

---

## 3. The command: `!dl` (define line)

Displaying one line of text needs a single command, **`!dl`** (define line):

```
!dl <line#> <attr> jp<justify> <text>
```

| Part | Hello-World value | Meaning |
|---|---|---|
| `!dl` | `!dl` | define-line token (opcode 0xB4) |
| `<line#>` | `01` | line number, 1–40 (must exist on the active page) |
| `<attr>jp` | `jp` | attribute code — `jp` selects the default mode/colour |
| `<justify>` | `L` | `L` left · `R` right · `C` centre · `N` none |
| `<text>` | `<Hello World>` | the text, bracketed by `<` … `>` |

The line's position/size comes from the page geometry already configured on the unit, so the command carries only the text and attributes. A bare `!dl` writes to (and shows on) the **current page** — no page-management commands are required for a basic message.

---

## 4. Worked example — broadcast "Hello World"

**Frame (ASCII):**

```
[00!dl01jpL<Hello World>/C9]
```

**Frame (hex):**

```
5B 30 30 21 64 6C 30 31 6A 70 4C 3C 48 65 6C 6C
6F 20 57 6F 72 6C 64 3E 2F 43 39 5D
```

**Byte-by-byte:**

| Bytes | ASCII | Role |
|---|---|---|
| `5B` | `[` | start-of-frame |
| `30 30` | `00` | address → id 0 (broadcast) |
| `21 64 6C` | `!dl` | define-line command |
| `30 31` | `01` | line number 1 |
| `6A 70` | `jp` | default attribute (mode/colour) |
| `4C` | `L` | justify left |
| `3C` | `<` | text start |
| `48 65 6C 6C 6F 20 57 6F 72 6C 64` | `Hello World` | the text |
| `3E` | `>` | text end |
| `2F` | `/` | checksum introducer |
| `43 39` | `C9` | checksum = (0x5B + Σ payload) & 0xFF |
| `5D` | `]` | end-of-frame |

**Checksum check:** sum the bytes of `00!dl01jpL<Hello World>` (everything between `[` and `/`), add `0x5B`, keep the low byte → `0xC9`. ✓

Send those 28 bytes out the serial port and line 1 of the current page reads **Hello World**.

---

## 5. Variations

All checksums below are pre-computed for copy-paste.

**Address a specific unit (id 1):**
```
[01!dl01jpL<Hello World>/CA]
```

**Centre it, in colour 3** (the `\3` markup selects palette colour 3):
```
[0A!dl01jpC<\3Hello World>]
```

**Full sequence with explicit page management** (select page 1, clear it, write, show it) — mirrors the firmware's own internal `display_text` output:
```
[0A!m1!ffc!dl01jpL<Hello World>!ps01]
```
- `!m1` — select page 1 as the active/edit page
- `!ffc` — clear the frame
- `!dl01jpL<Hello World>` — define line 1
- `!ps01` — show page 1

**Two lines:** concatenate two `!dl` commands (recompute the checksum over the new body):
```
[00!dl01jpC<Hello>!dl02jpC<World>/…]
```

**Scrolling text:** use scroll mode instead of `jp`. Mode is the `<attr>` field; a scroll mode byte (`s`) replaces the default — e.g. the line scrolls rather than statically justifying. (Exact mode-byte encoding is in `cmd_define_line`; `jp` = static default.)

**Dynamic content** inside the `<…>` text via backslash markup:
- `\h05` set colour 05 · `\0`–`\9` palette colour
- `\+2` / `\-2` font size up/down · `\f` / `\s` direction LTR/RTL
- `\c d` insert the **time** · `\d{ddd www}` insert a formatted **date**
- `$1B` insert a raw byte by hex

Example with a clock: `<Time \cd>` → `[00!dl01jpL<Time \cd>/…]` (recompute checksum).

---

## 6. Computing the checksum (any body)

```python
def frame(addr: str, body: str) -> str:
    payload = addr + body
    ck = (0x5B + sum(ord(c) for c in payload)) & 0xFF
    return f"[{payload}/{ck:02X}]"

print(frame("00", "!dl01jpL<Hello World>"))   # -> [00!dl01jpL<Hello World>/C9]
```

The checksum is **optional**: a frame with no `/CK` (e.g. `[00!dl01jpL<Hello World>]`) is also accepted — the unit only verifies the checksum when a `/` appears three bytes before `]`. Including it is safer on a noisy link.

---

## 7. What comes back

If the command requested a reply (controlled by the addressing/flags), the unit answers on the same port with a tagged bracket frame:

```
[FFP…/CK]
```

carrying status fields and its own additive checksum. A protocol/parse problem instead surfaces as an error reply code: `0x01` line error, `0x20` checksum mismatch, `0x40` buffer overflow, `0x80` timeout. For `!dl` specifically, malformed input sets detail codes such as `0x90` (bad line number), `0xA8` (doesn't fit), or `0x31` (bad justify).

---

## 8. Quick checklist

1. Open the serial port at the unit's configured baud, 8 data bits.
2. Build the body: `!dl01jpL<Hello World>`.
3. Prefix the 2-byte address (`00` = broadcast).
4. Compute `CK = (0x5B + Σ(address+body)) & 0xFF`.
5. Wrap: `[` + address + body + `/` + `CK` + `]`.
6. Send the bytes; optionally read the `[FFP…]` reply.

Minimal frame to send right now:

```
[00!dl01jpL<Hello World>/C9]
```