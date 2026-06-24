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

The communications protocol is a ascii-only serial protocol over UART. Baudrate is set by a switch SW1.1 to either 9600 or 19200. The UART frame is 8 data bits, no parity, 1 stop bit. See [[Commands for protocol 1 and 2]] for the display commands.

### Message frames

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
3. Payload
4. Start of checksum marker: `/` 
5. Two ascii hex digits, containing modulo 256 checksum of all bytes from steps 1. - 3.
6. End of frame marker: `]`

Detailed status message frame:
1. Start of frame marker: `[`
2. Magic identifier: `FFP`
3. field1, 3 digits
4. Separator `:`
5. field2, 3 digits
6. Separator `:`
7. Detailed error code from last command, 2 hex digits
8. Separator `/`
9. Current display FPS, 3 digits, base10
10. String: `fps`
11. Separator `/`
12. String `LS`
13. Light sensor data, 6 digits, base 10
14. Checksum: `/` followed by 2 hex digits with modulo 256 sum of all bytes from steps 1. - 13.
15. End of frame marker: `]` 

#### Example messages

- `[AY00,0F/F7]`
	- Positive ACK from unit address `A`
- `[AN02,0F/EE]`
	- Negative NACK from unit address A, general error type `0x02` 
- `[FFP000:000:00/064fps/LS040450/C9]`
- `[0A!ps01!m1!dl1jpL<Helsinki Hacklab>!dl2jpL<By: Depili>!dl3jpL<26-06-21>!pl01]` 
	- Command string sent to `0A` without a checksum