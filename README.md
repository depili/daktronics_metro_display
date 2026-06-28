# Daktronics AF-6700 communication reverse engineering

I received some old led displays from the Finnish Länsimetro. They came with no documentation and no communications software. So the challenge was to figure out how they work.

These are monochrome amber displays. The controller is marked as "PCB236/PCB237" and they have been manufactured by Data display in Ireland and delivered by Scannotec. They have been made around the year 2016.

Data displays company has since been acquired by Daktronics.

The goal of the project is to figure out the protocol for reusing the displays. This project then falls under the [[EU right to decompile to achieve interoperability]]
## What the vendor provides

There isn't much available publicly about the displays, just few KB articles on the daktronics site, none of them about communications or anything really interesting. 

Some of the KB articles point to [dakfiles.daktronics.com ](https://dakfiles.daktronics.com/). This seems to be a almost forgotten fileshare platform with quite abysmal performance. Browsing it we see an interesting [firmware file](https://dakfiles.daktronics.com/downloads/Transportation/Firmware/AF-670x%20Controller%20(236-237)/Rev%202_5.zip)  and [DMS_tool.zio](https://dakfiles.daktronics.com/downloads/Transportation/Utilities/DMS%20Tool.zip) that is referenced in some of the KB articles.

## Hardware

The controller uses a `AT91SAM9260` arm MCU and a FPGA. There is a 20pin JTAG connector on it labeled "SAM ICE I/F". External communication is via optocouplers and isolated RS232 / RS485 drivers.

There are two dip switch blocks on the controller, each with 8 switches. SW1 controls the boot up process, with default being all off. SW2 controls the unit address and the baud rate.

## Protocol

The communications protocol is a ascii-only serial protocol over UART. Baudrate is set by a switch SW1.1 to either 9600 or 19200. The UART frame is 8 data bits, no parity, 1 stop bit. See [[Commands for DDX protocol]] for the display commands.

### Message frames to displays

Message frames sent to the display:
1. Start of frame marker: `[` 
2. Group part of the address: `0` to `8` 
3. Unit address: `A` to `Z` 
4. Payload
5. Optional checksum: `/` followed by the checksum in ascii hex.
	- Modulo 256 sum of all bytes from steps 1. - 4.
6. End of frame marker: `]`

Message frames sent by the displays:
1. Start of frame marker: `[`
2. Unit address letter: `A` to `Z`
3. Status byte, two hex characters
4. `,`  separator
5. Hw status byte, two hex characters
6. Optional  payload
	1. `:` for start of reply payload marker
	2. Command specific payload
7. Start of checksum marker: `/` 
8. Two ascii hex digits, containing modulo 256 checksum of all bytes from steps 1. - 6.
9. End of frame marker: `]`

Detailed status message frame:
1. Start of frame marker: `[`
2. Magic identifier: `FFP`
3. page number for last error, 3 digits, base 10
4. Separator `:`
5. line number for last error, 3 digits, base 10
6. Separator `:`
7. Detailed error code from last command, 2 hex digits
8. Separator `/`
9. Current display FPS, 3 digits, base10
10. String: `fps`
11. Separator `/`
12. String `LS`
13. Light sensor data, characters
	1. Raw sensor A reading, 2 hex digits
	2. Raw sensor B reading, 2 hex digits
	3. Current brightness, 2 digits, base 10
14. Checksum: `/` followed by 2 hex digits with modulo 256 sum of all bytes from steps 1. - 13.
15. End of frame marker: `]` 
### Error codes

The hex-encoded byte in acks and nacks is a bitfield:
* 0x01 - not ready
* 0x02 - bad parameter
* 0x04 - denied / wrong scope
* 0x08 - bad separator (missing `<>`etc)
* 0x20 - checksum missmatch

The detail byte available via `!?F`:
- 0x02 - page not allocated
- 0x03 - !pl parsing failed
- 0x04 - page index out of bounds
- 0x32 - line install: unknown mode byte
- 0x51 - graphics: page > 32 check failed
- 0x52 - graphics slot not in use
- 0x53 - graphics: x+w overflows panel
- 0x54 - graphics: y+h overflows panel
- 0x55 - graphics: x overflows panel
- 0x56 - graphics: y overflows panel
- 0x62 - graphics: page sprite slots full
- 0x70 - graphics: install: gfx id or slot id out of bounds
- 0x71 - graphics: install: gfx id not allocated
- 0x72 - graphics: install requested w too small
- 0x73 - graphics: install requested h too small
- 0x90 - line index out of bounds
- 0x91 - line geometry overflows panel
- 0x93 - !dl no active page
- 0x96 - bad parse
- 0x98 - line outside active page
- 0x99 - !lr bad param
- 0x9a - no active page
- 0x9b - line doesn't match active page
- 0x9c - !lp bad param
- 0x9d - !lp no active page
- 0x9e - !pz bad parse
- 0x9f - !dl line doesn't belong to active page
- 0xa0 - !zm parse failure
- 0xa1 - !zm value = 0
- 0xa2 - !zm value `>7`
- 0xa4 - !dl no active page context
- 0xa5 - !dz / !ra parse failure
- 0xea - !Fs bad format
- 0xeb - !Fs framerate `<50`
- 0xec - !FS framerate `>600`
- 0xed - !Fx bad format
- 0xee - !Fx value `>9`
#### Example messages

- `[AY00,0F/F7]`
	- Positive ACK from unit address `A`
- `[AN02,0F/EE]`
	- Negative NACK from unit address A, general error type `0x02` 
- `[FFP000:000:00/064fps/LS040450/C9]`
- `[0A!ps01!m1!dl1jpL<Helsinki Hacklab>!dl2jpL<By: Depili>!dl3jpL<26-06-21>!pl01]` 
	- Command string sent to `0A` without a checksum
## Configuration

The units have an internal [[Config file]]. With the `RM2040` version firmware you can dump it with the `!??` command, for `RM2037` I had to use a breakpoint with JTAG to get the config file from a local buffer in stack on the configuration parsing function.