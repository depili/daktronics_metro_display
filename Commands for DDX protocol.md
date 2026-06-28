# Command list
The list is broken in two, the well-understood commands and commands that I know exist but aren't currently completely understood. Argument fields are denoted with \[arg]. Specific types of common arguments are:
* `[nn]` - Number, base 10
* `[hh]` - Hex
* `[Y/N]` - `Y`  or `N` 
* `[0-100]`  - Number, base 10, 0-100, inclusive.

The protocol column notes if a command is only available in protocol mode 1 or 2. Version column denotes if the command is only available on RM2037 or RM2040 firmware.
### Confirmed

| Proto | Version | Command                                      | Example                                      | Function                                        |
| ----- | ------- | -------------------------------------------- | -------------------------------------------- | ----------------------------------------------- |
|       | RM2040  | `!??`                                        |                                              | [[#`!??` dump unit info]]                       |
|       |         | `!?b`                                        |                                              |                                                 |
|       |         | `!?d`                                        |                                              | [[#`!?d` get rtc date]]                         |
|       |         | `!?e`                                        |                                              | [[#`!?e` get number of led errors]]             |
|       |         | `!?F[+\-]`                                   | `!?F+` `!?F-`                                | [[#`!?F` detailed error & state report toggle]] |
|       |         | `!?j`                                        |                                              | [[#`!?j` get jumper configuration]]             |
|       |         | `!?n`                                        |                                              | [[#`!?n` get serial numer]]                     |
|       |         | `!?p`                                        |                                              | [[#`!?t` get RTC time]]                         |
|       |         | `!?t`                                        |                                              | [[#`!?t` get RTC time]]                         |
|       |         | `!?v`                                        |                                              | [[#`!?v` get firmware version]]                 |
|       |         | `!?z`                                        |                                              | [[#`!?z` get display dimension]]                |
|       |         | `!dg`                                        |                                              | [[#`!dg` - draw graphics]]                      |
|       |         | `!dl[line][mirror][effect][justify]<[text]>` | `!dl01jpL<Hello world!>`                     | [[#`!dl` - display line]]                       |
|       |         | `!Fm[mapping definition]*`                   | `!Fmm8l1x0y0h16w160l2x0y40h8w48*`            | [[#`!Fm` display mapping definition]]           |
|       |         | `!kg`                                        | `!kg0,8,8<XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX>` | [[#`!kg` define sprite]]                        |
|       |         | `!kt`                                        |                                              | Define stored text                              |
|       |         | `!m[mapping]`                                | `!m1`                                        | Select the text line mapping                    |
|       |         | `!pc[Y/N]`                                   | `!pcY`                                       | Set the page carry flag                         |
|       |         | `!pd[nn]`                                    | `!pd01`                                      | Delete page                                     |
|       |         | `!pl[page list]`                             | `!pl01``!pl01,02,03` `!pl*`                  | Define page playlist                            |
|       |         | `!ps[page]`                                  | !ps01                                        | Clear and load the page for redifinition        |
|       |         | `!px`                                        | `!px`                                        | Clear the playlist                              |
|       |         | `!rf`                                        |                                              | Get current blink timings                       |
|       |         | `!rl`                                        |                                              | Get current pin lockout timer                   |
|       |         | `!rm`                                        |                                              | Get current maintenance mode timeout            |
|       |         | `!rp`                                        |                                              | Get timeout value                               |
|       |         | `!rq`                                        |                                              | Get current sequence timer                      |
|       |         | `!sd[date]`                                  |                                              | Set date, WMMDDYY                               |
|       |         | `!st[time]`                                  | `!st123456`                                  | Set RTC time, HHMMSS                            |
|       |         | `!tl`                                        | `!tl`                                        | Run led test                                    |
|       |         | `!to[1-3]`                                   | `!to1`                                       | Set text overflow mode                          |
|       |         | `!tp[n]`                                     | `!tp1`                                       | Show test pattern, 0 disables                   |
|       |         | `!up[nn]`                                    | `!up05`                                      | Set communications timeout                      |
|       |         | `!uq[1-20]`                                  | `!uq08`                                      | Set text sequence timing                        |
|       | RM2037  | `!zm[protocol]`                              | `!zm1`                                       | Set protocol variant                            |
|       |         | `!zb`                                        | `!zb`                                        | Reboot the system                               |
## Parsed, but unconfirmed

| Proto | Version | Command           | Example                   | Function                                    |
| ----- | ------- | ----------------- | ------------------------- | ------------------------------------------- |
|       |         | `!?a`             |                           |                                             |
|       |         | `!?c`             |                           | Get colors?                                 |
|       |         | `!?f`             |                           | Read max brightness?                        |
|       | RM2040  | `!?g`             |                           |                                             |
|       |         | `!?h`             |                           |                                             |
|       |         | `!?i`             |                           |                                             |
|       | RM2040  | `!?k`             |                           | Returns `S`, `A`, `M` or `None`             |
|       | RM2040  | `!?l`             |                           | PCB type                                    |
|       |         | `!?m`             |                           |                                             |
|       | RM2040  | `!?N`             |                           | Next bus ddx?                               |
|       |         | `!?o`             |                           |                                             |
|       | RM2040  | `!?q`             |                           | Sensor status`                              |
|       |         | `!?s`             |                           |                                             |
|       | RM2040  | `!?u`             |                           |                                             |
|       |         | `!ad[Y/N]`        | `!adY`                    | Set auto detect arabic                      |
|       | RM2040  | `!BEdebug-1[Y/N]` |                           |                                             |
|       |         | `!cc[Y/N]`        |                           | Set "carry over previous page lines" option |
|       |         | `!cd`             |                           | Clear display?                              |
|       |         | `!cl[ll],[nn]`    |                           | Clear line?                                 |
|       | RM2040  | `!cp`             |                           |                                             |
|       | RM2040  | `!Dc`             |                           |                                             |
|       | RM2040  | `!DD`             |                           |                                             |
|       |         | `!df[nnn]`        |                           | Define frame?                               |
|       |         | `!dp[nn]`         |                           | Page dwell period                           |
|       | RM2040  | `!DR`             |                           |                                             |
|       |         | `!dr[nn]`         |                           | Frame duration?                             |
|       |         | `!dw`             |                           | Set "wait for all loops" flag on the page   |
|       | RM2040  | `!ffc`            |                           |                                             |
|       | RM2040  | `!ffd[n]`         |                           |                                             |
|       | RM2040  | `!ffr`            |                           |                                             |
|       |         | `!Fs[50-600]`     |                           | Set framerate / FPS?                        |
|       |         | `!Fx[0-9]`        |                           | Set FX slowdown?                            |
|       |         | `!kb`             |                           | Custom glyph?                               |
| 2     |         | `!lc[ll],[nn]`    |                           | Protocol 2                                  |
| 2     |         | `!lh[ll],[nn]`    |                           | Protocol 2                                  |
| 2     |         | `!lp[ll],[nn]`    |                           | Protocol 2                                  |
| 1     |         | `!lp[nn]`         |                           | Set loop count for current line             |
| 2     |         | `!lr[ll],[nn]`    |                           | Protocol 2                                  |
| 2     |         | `!ls[nn]`         |                           | Protocol 2                                  |
|       |         | `!LS[n]`          |                           | Light sensor stuff?                         |
| 2     |         | `!lt`             | `!lt*` `!lt01` `!lt01,02` | Protocol 2; line clear                      |
|       |         | `!pr`             |                           | Reset all pages?                            |
|       | RM2040  | `!qc`             |                           | Get modes count and active?                 |
|       | RM2040  | `!qe[off],[len]`  |                           |                                             |
|       | RM2040  | `!qf`             |                           |                                             |
|       | RM2040  | `!qi`             |                           |                                             |
|       | RM2040  | `!ql`             |                           | Get modes with lines?                       |
|       | RM2040  | `!qm<H>`          |                           | Get one modes definitions                   |
|       |         | `!rb`             |                           | Get current brightness cap?                 |
|       |         | `!re`             |                           |                                             |
|       | RM2040  | `!rh`             |                           | Read led error thresholds                   |
|       | RM2040  | `!rj`             |                           |                                             |
|       | RM2040  | `!rp`             |                           |                                             |
|       |         | `!rs`             |                           | Get current effect slowdown value?          |
|       |         | `!rt`             |                           | Get raw RTC bytes?                          |
|       |         | `!sa`             |                           | Set address                                 |
|       |         | `!sb[0-100]`      |                           | Set brightness?                             |
|       |         | `!se[effect]`     |                           | Set default effect                          |
|       |         | `!sf[Y/N]`        |                           |                                             |
|       | RM2040  | `!sg[n]`          |                           | Set max brightness?                         |
|       |         | `!si`             |                           |                                             |
|       |         | `!sp`             |                           |                                             |
|       | RM2040  | `!sr`             |                           |                                             |
|       | RM2040  | `!ua[n]`          |                           | Set max scrollers?                          |
|       | RM2040  | `!ub[0,1,3,5,7]`  |                           |                                             |
|       | RM2040  | `!ud<text>*`      |                           | Timeout message?                            |
|       |         | `!ue[0,1]`        |                           |                                             |
|       |         | `!uf[nn],[nn]`    |                           | Set flash duty cycle                        |
|       | RM2040  | `!uh`             |                           | Set led error tresholds                     |
|       | RM2040  | `!ui[0-100]`      |                           |                                             |
|       |         | `!ul[0-60]`       |                           | Set pin code lockout timer?                 |
|       |         | `!um[0-15]`       |                           | Set maintenance mode timeout?               |
|       | RM2040  | `!uo`             |                           |                                             |
|       | RM2040  | `!ur`             |                           |                                             |
|       |         | `!us[0-9]`        |                           | Set effect slowdown?                        |
|       | RM2040  | `!ut`             |                           |                                             |
|       | RM2040  | `!uu[Y/N]`        |                           |                                             |
|       | RM2040  | `!uw[0-100]`      |                           |                                             |
|       | RM2040  | `!ux[0-100]`      |                           |                                             |
|       | RM2040  | `!uy[n]`          |                           |                                             |
|       |         | `!za`             |                           | Show configured AMSG?                       |
|       |         | `!zb`             |                           | Reboot                                      |
|       |         | `!zl`             |                           |                                             |
|       |         | `!zo[HH]`         |                           | FPGA poke to register 0x034                 |
|       |         | `!zp[1-8]`        |                           |                                             |
|       |         | `!zr`             |                           |                                             |
|       |         | `!zx`             |                           | Reboot to loader 2                          |
|       |         | `!zy`             |                           | Reboot to loader 3                          |
|       |         | `!zz`             |                           | Reboot to loader 5                          |
# Detailed command descriptions
## `!??` dump unit info

RM2040 only.
## `!?a[serial]` get address

Probably for broadcast messages to find address for given serial?

## `!?b` get current brightness

## Examples

- TX: `[0A!?b]`
- RX: `[AY00,8F:015/CF]`
	- Current brightness 15%
## `!?d` get rtc date

### Examples
- TX: `[0A!?d]`
- RX: `[AY00,8F:4062526/A2]`
	- Thursday, Day: 25 Month: 06, Year: 26

## `!?e` get number of led errors

## `!?f` get max brightness

The `!lt` command or a boot time configuration with the dip switches runs a led test, measuring the current draw of each led. This command reports the number of leds that failed the test.
## `!?F` detailed error & state report toggle

This command can be used to turn on or off detailed state replies. `!?F+`  turns them on, `!?F-` off. Plain `!?F` gives one time message.
### Examples
- TX: `[0A!?F+]` 
- RX: `[AY00,8F/FF][FFP000:000:00/064fps/LS040431/C8]`


## `!?g`


## `!?i` get some string


## `!?j` get jumper configuration

Returns the jumper state

## `!?l` get light sensor PCB type

RM2040 only. Returns either `PCB294`  or `PCB175` 

## `!?n` get serial numer

Returns the units serial number

## `!?m` get some error flag?

The data is reset after being read.


## `!?o`


## `!?p` query presence

Always returns `1` . Used to verify unit is present at address.

## `!?r` get some FPGA register value

RM2040 only.

## `!?t` get RTC time

Returns the current RTC time of the unit, HHMMSS format.

## `!?x` get the DDX fixed line

RM2040 only.

### Examples
- TX: `[0A!?t]`
- RX: `[AY00,8F:154218/6E]`
	- clock: 15:42:18
## `!?v` get firmware version

### Examples

- TX: `[0A!?v]`
- RX: `[AY00,8F:2037,1010/F3]`
	- RM2037 version 1.01.0
## `!?z` get display dimension

Reply fields:
- RM2037:
	1. width
	2.  height
	3. color type; `M` single color, `C` dual color
- RM2040
	1.  width
	2.  height
	3.  colour type; `M` single colour, ´C` dual colour
	4. `SS` single sided, `DD` dual sided
### Examples

- TX: `[0A!?z]`
- RX: `[AY00,8F:0160,0048,M/71]`'
	- 160 pixels wide, 48 pixels high, single colour

## `!df[nnn]` - display frame

This command is used for defining animation frames. It takes a sprite defined by `!kg` and draws it full screen. Use with `!dr` to define the animation by repeating `!df[nnn]!dr[nnn]...`

### Examples

```
[0A!kg001,008,008<XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX>]
[0A!kg002,008,008<CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC>]
[0A!ps01!m1!dl01spL<Page 1>!dl02olL<line2>!pcY!dp1]
[0A!ps02!m1!dl01rdL<Page 2>!df001!dr001!df002!dr001!lp04!dp1!pl01,02]
```
### Arguments
`!df[sprite]` which is the base 10 index for the sprite created with `!kg`
## `!dg` - draw graphics

This command draws sprites defined via `!kg` to the page.
### Arguments
`!dg[sprite],[x],[y],[w],[h],0,0` where:
- `[sprite]` is the sprite index as defined in `!kg` store
- `[x]` is the x coordinate, base 10, left edge is `x=0`
- `[y]` is the y coordinate, base 10, top edge is `y=0`
- `[w]` is the width in pixels
- `[h]` is the height in pixels
- Remaining two fields are parsed but not used.
## `!dl` - display line

This command defines lines on a page. For RM2037 protocol=1 and RM2040 in general the definition should be in the same protocol frame with a page and line mapping selects, ie `!ps01!m1!dl01...` command string.
### Arguments
`!dl[line][mirror][effect][justify][text]` where:
* `[line]` Line number, base10
* `[mirror]` Optional `+` character, causes the line to be mirrored
* `[effect]` Two character effect code:
	* Main modes
		* `jp`  jump, does instant text transition to a static message
		* `S0` Scroll infinite copies of the message, no whitespace between the copies
		* `S1` - `S9` Scroll number of copies of the message, stop when the last copy of the message has fully entered the screen. No whitespace between the copies
		* `s0` Infinite scroll of the message, next copy enters when the last character has left the screen
		* `s1` - `s9` Scroll number of copies of the message, stop when the last copy of the message has fully exited the screen. Full clear line between the copies
		* `C0` & `CA`  Keep the first segment of the text split with `|` static, scroll infinite copies of the next segment back-to-back after the static part
		* `C1` - `C9`  Keep the first segment of the text split with `|` static, scroll number of copies of the next segment back-to-back next to the static part
		* 'c0'  Keep the first segment of the text split with `|` static, scroll infinite copies of the next segment with white space spacing next to the static part
		* 'c1' - `c9`  Keep the first segment of the text split with `|` static, scroll number of copies of the next segment with white space spacing next to the static part
		* `sq`  Sequence, parts of the text split with `|` separator cycle per the defined sequence timing
	* Line reveal effects
		* `oc` Open center, the text is revealed column at a time from center
		* `oe` Open ends, the text is revealed column at a time from both ends
		* `ol` Open left, the text is revealed column at a time from left
		* `or` Open right, the text is revealed column at a time from right
		* `rd`  Roll down, the line is revealed from top down
		* `ru`  Roll up, the line is revealed from bottom up
		* `sp`  Sparkle, the text is revealed few random pixels at a time
* `[justify]` Text justification, one of the following characters:
	* `C` - Centered
	* `L` - Left justified
	* `N` - "Natural", taken from the text direction?
	* `R` - Right justified
* `[text]` Either `<text>` inline definition or `*[nn]` reference for stored text string. Text content supports escape codes:
	* Control characters
		* `|` - Field separator for modes that use fields, otherwise rendered as is
		* `>` - End of the text marker
		* `$[hex]` - Insert raw byte per the hex digits
	* Escapes for control characters:
		* `\\` -> `\`
		* `\|` -> `|`
		* `\>` -> `>`
		* `\$` -> `$` 
	* Colors, no-ops on monographic displays
		* `\r` - Red
		* `\g` - Green
		* `\a` - Amber (both red and green leds on)
	* Typeface
		* `\b` or `\B` - Select font 2, bold by default
		* `\n` or `\N` - Select font 1, variable spaced normal by default
		* `\x` or `\X` - Select fixed width font 3
		* `\F1` to `\F4`  - Select font by index
	* Blink
		* `\f` - Text following will blink
		* `\s` - Text following will be static
	* Real time clock
		* `\t{HH:MM:SS}` - Time of day with format string
		* `\t[HEX]` - Where `[HEX]` is two hex digits, time of day with format from a table
		* `\d{DD.MM.YY} - Date with format string
		* `\d[HEX]` - Where `[HEX]` is two hex digits, date with format from a table
	* Temperature
		* `\T` - Display 3 digit temperature measurement
		* `\D0` and `\D1`  Temperature variants
	* Misc
		* `\i[NN]` - Inline sprite, where `[NN]` is the sprite index in base 10
		* `\p[NN]` - Pad NN pixels?
	* Unknown
		* `\+[d]` and `\-[d]` - Maybe vertical position adjustments
		* `\0` - `\9` 
		* `\o` - Update the row mode for the next part?
		* `\ci`
		* `\cd`
		* `\O`
		* `\P`
		* `\h[nn]`
		* `\v[x]` where `[x]` is either `T`, `B` or `M`
		* `\v+[nn]`
		* `\v-[nn]` 
		* `\w1` - `\w3`
### Examples
* `!dl01jpL<Hello World>`
* `!dl02sqL<Hello|World|Sequence>`
* `!dl03s0L<Hello scroller!>`
* `!dl04c0L<Static|scroller>`

## `!dp[nn]` display pause

Used to define pauses between page swaps or line draws. Parameter is the pause in seconds in base 10.

## `!dr` animation delay

This command is used with `!df` and `!dg` to define animations.
### Arguments

`[delay]` where delay is the animation delay in graphics ticks, base 10.

## `!dw`

Somehow related to page advance, currently unknown...

## `!Fm` display mapping definition

This command allows definition of the line mappings recalled by `!m[0-F]` commands. Mappings defined by the config file cannot be redefined.
### Arguments
`!Fmm[m]{l[ll]x[xx]y[yy]h[hh]w[ww]}...*`' where
- `[m]` - Mapping designator, `[0-F]`
- `{l[ll]x[xx]y[yy]h[hh]w[ww]}...` one or more line definitions, where:
	- `[ll]` - Line number
	- `x[xx]` - X coordinate, left edge is `X=0`
	- `y[yy]` - Y coordinate, top row is `Y=0`
	- `h[hh]` - Line height in pixels
	- `w[ww]` - Line width in pixels
- `*`  - End of input marker

### Examples
* `[0A!Fmm8l1x0y0h16w160l2x0y40h8w48*]`
	* Mapping: 8
	* Lines
		1. x: 0, y: 0, h: 16, w: 160
		2. x: 0, y: 40, h: 8, w: 48

## `!Fs[n]` set frame rate

Allows changing the display refresh rate, parameter is the desired rate in base 10 Hz. Limits: `60-600` 

## !eb i2c flash edit byte?


## `!ew` i2c flash edit string?


## `!ew` i2c flash edit word?


## `!kg` define sprite

This command is used to define a reusable graphics sprite. The maximum size of a sprite is 32768 pixels in total.
### Arguments
`!kg[sprite],[w],[h]<[pixeldata]>` where:
* `[sprite]` is the sprite index, base 10, 0-24
* `[w]` is the width in pixels
* `[h]` is the height in pixels
* `[pixeldata]` is the pixel data encoded as two pixels per byte

### Pixel data encoding

Pixels are encoded one row at a time, two pixels per byte. When `[w]` is odd then the right pixel of the last byte of each row is unused.

The encoding is `0x40 | (left << 3) | (right)

| Pixel value | Meaning       |
| ----------- | ------------- |
| 0           | off           |
| 1           | red           |
| 2           | green         |
| 3           | amber (R + G) |
| 4           | transparent   |

This gives us following ascii characters for the encoding:

| ASCII | Hex  | Left pixel  | Right pixel    |
| ----- | ---- | ----------- | -------------- |
| `@`   | 0x40 | Off         | Off            |
| `A`   | 0x41 | Off         | Red            |
| `B`   | 0x42 | Off         | Green          |
| `C`   | 0x43 | Off         | Amber          |
| `D`   | 0x44 | Off         | Transparent    |
| `H`   | 0x48 | Red         | Off            |
| `I`   | 0x49 | Red         | Red            |
| `J`   | 0x4A | Red         | Green          |
| `K`   | 0x4B | Red         | Amber          |
| `L`   | 0x4C | Red         | Transparent    |
| `P`   | 0x50 | Green       | Off            |
| `Q`   | 0x51 | Green       | Red            |
| `R`   | 0x52 | Green       | Green          |
| `S`   | 0x53 | Green       | Amber          |
| `T`   | 0x54 | Green       | Transparent    |
| `X`   | 0x58 | Amber       | Off            |
| `Y`   | 0x59 | Amber       | Red            |
| `Z`   | 0x5A | Amber       | Green          |
| `[`   | 0x5B | Amber       | Amber          |
| `\`   | 0x5C | Amber       | Transparent    |
| `     | 0x60 | Transparent | Off            |
| `a`   | 0x61 | Transparent | Red            |
| `b`   | 0x62 | Transparent | Green          |
| `c`   | 0x63 | Transparent | Amber          |
| `d`   | 0x64 | Transparent | Transparent \| |
### Examples
* `!kg000,008,008<XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX>`
	* `8x8` sprite with id `0`, alternating amber and off vertical columns
* `!kg000,002,001<[>`

## `!kt` store text

## `!m0` to `!mF` load line mapping

These commands are used after `!ps` to select the line mapping to use for the page definition. Mappings are both loaded from the config with the `DLMx=`  keys and defined run-time with the `!Fm` command. These take no parameters.

## `!pc` page carry

This controls the "carry" flag in the page. If the flag is set line content is copied from the previous page, assuming both use the same line mapping, as a base. If not set the page clears all lines that do not have any content set. Use `!pcY` to set and `!pcN` to clear. Default state depends on the config file.

## `!pd[nn]` page delete

Deletes a page and removes it from playlists, freeing all assigned graphics objects. Argument is the page number, in base 10

### Examples

- `!pd01`
## `!pl` playlist

Select the pages to use for a playlist. Page durations are set with the `!dp`, `!lp` and `!dw` commands when the page is defined. Argument is either a comma separated list of page identifiers or `*` for all defined pages. 

If the pages do not have durations defined with `!dp` or other mechanisms they will block the advancement.

### Examples

- `!pl01,02,04`

## `!ps` page select

Selects the page to modify. Argument is the page numbe in base 10. Should be followed by the line mapping select and line definitions on the same protocol frame.

### Examples

- `!ps01!m1!dl01ruC<Hello there>`

## `!px` clear playlist

Deletes the playlist, doesn't delete the pages.

## `!rb` get and `!sb[nnn]` set brightness

Gets and sets the panel brightness, in percent base 10.

## `!rf` get blink duty cycles

Get the current blinking text duty cycles

## `!rl` get and `!ul` set current lockout timer for pin lock

Get and set the current timer in minutes that is used between unsuccessful pin code entry attempts. Value `0-60`

## `!rm` get and `!um[nn]` set maintenance mode timeout

Get and set the time in minutes for the maintenance mode timeout, value: `1-5`.
### Examples
- `!rm`
- `!um4`

## `!rp` get and `!up[nn]` set the protocol timeout

Read and set the timeout, in minutes, after which the display enters a timed out state if no new messages have been received. By default the display will go blank on timeout.

### Examples
- `!rp`
- `!up00` - disable the timeout
- `!up05` - set 5 minute timeout

## `!rq` get and `!uq` set the sequence timer

Read and set the timer, in seconds, used for the text display mode `sq`. See  [[Commands for DDX protocol#`!dl` - display line]]

### Examples
- `!uq5`

## `!rs`

RM2037: returns 4

## `!rt` read temperature


## `!sd` set date

Sets the current RTC date. Format is `WMMDDYY` where `W` is the day-of-week, ´DD´ day-of-month, `MM` month and `YY`  year.

## `!se` set default segment effect

Sets the default segment effect. Valid values: `S`, `s`, `C`, `c`, `I`

## `!sf` set succession flag

`!sfY` sets, rest reset the flag

## `!sg` set brighness cap



## `!tl` test leds

Run the led test sequence and update the failed led counter.

## `!to` set text overflow behaviour

Used to control what happens when text doesn't fit completely on the line, parameter: `1-3`
1. scroll
2. truncate character
3. truncate word

## `!tp` test pattern

Show various test patterns. Parameter `0-6`, `0` disables, others are different patterns.

## `!ua[nn]` update max scrollers value


## `!ub`


## `!uf[nnn],[nnn]` set blink timings


## `!uk[nn]` update some fpga flags

## `!ul` update jumper values?


## `!ul[nn]` set pin lockout time


## `!xM` set multi-languages stuff


## `!zm` set communication protocol

`RM2037` only. Set the communication variant. Only `!zm1` is really understood.


## `!zb` reboot the system

Reboots back to the application.

# Communication examples

In the protocol 1 (assumed DDX) one needs to include `!ps`, `!m` and `!dl` commands in single protocol frame.

```
[0A!ps01!m1!dl01jpL<Helsinki Hacklab metro station announcement system scroller thingy>!dl02jpL<By: Depili>!dl03jpL<26-06-21>!pl01]
```

A simple playlist cycling between pages with 1 second intervals:
```
[0A!ps01!m1!dl01jpL<Page 1>!dp1]
[0A!ps02!m1!dl01jpL<Page 2>!dp1!pl01,02]
```

Protocol 2 (assumed LDDX) might work with this:
```
[0A!ls01!m1!dl1jpL<Helsinki Hacklab metro station announcement system scroller thingy???>!dl2jpL<By: Depili>!dl3jpL<26-06-21>!pl01]
```
