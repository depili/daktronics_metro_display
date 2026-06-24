# Command list
The list is broken in two, the well-understood commands and commands that I know exist but aren't currently completely understood. Argument fields are denoted with \[arg]. Specific types of common arguments are:
* `[nn]` - Number, base 10
* `[hh]` - Hex
* `[Y/N]` - `Y`  or `N` 
* `[0-100]`  - Number, base 10, 0-100, inclusive.

The protocol column notes if a command is only available in protocol mode 1 or 2. Version column denotes if the command is only available on RM2037 or RM2040 firmware.
### Confirmed

| Proto | Version | Command                                      | Example                               | Function                                 |
| ----- | ------- | -------------------------------------------- | ------------------------------------- | ---------------------------------------- |
|       | RM2040  | `!??`                                        |                                       | Full ID dump, not supported on RM2037    |
|       |         | `!?b`                                        |                                       | Get current brightness                   |
|       |         | `!?d`                                        |                                       | Get current RTC date                     |
|       |         | `!?e`                                        |                                       | Get number of failed leds                |
|       |         | `!?F[modifier]`                              | `!?F+`                                | Detailed error / state query / mode set  |
|       |         | `!?j`                                        |                                       | Get jumper state                         |
|       |         | `!?n`                                        |                                       | Get serial number                        |
|       |         | `!?p`                                        |                                       | Query presense                           |
|       |         | `!?t`                                        |                                       | Get current RTC time                     |
|       |         | `!?v`                                        |                                       | Query version                            |
|       |         | `!?z`                                        |                                       | Get panel size                           |
|       |         | `!dg`                                        |                                       | Draw sprite                              |
|       |         | `!dl[line][mirror][effect][justify]<[text]>` | `!dl01jpL<Hello world!>`              | Define a text line                       |
|       |         | `!Fm[mapping definition]*`                   | `[0A!Fmm8l1x0y0h16w160l2x0y40h8w48*]` | Define text line mapping                 |
|       |         | `!kg`                                        |                                       | Define sprite                            |
|       |         | `!kt`                                        |                                       | Define stored text                       |
|       |         | `!m[mapping]`                                | `!m1`                                 | Select the text line mapping             |
|       |         | `!pc[Y/N]`                                   | `!pcY`                                | Set the page carry flag                  |
|       |         | `!pd[nn]`                                    | `!pd01`                               | Delete page                              |
|       |         | `!pl[page list]`                             | `!pl01``!pl01,02,03` `!pl*`           | Define page playlist                     |
|       |         | `!ps[page]`                                  | !ps01                                 | Clear and load the page for redifinition |
|       |         | `!px`                                        | `!px`                                 | Clear the playlist                       |
|       |         | `!rf`                                        |                                       | Get current blink timings                |
|       |         | `!rl`                                        |                                       | Get current pin lockout timer            |
|       |         | `!rm`                                        |                                       | Get current maintenance mode timeout     |
|       |         | `!rp`                                        |                                       | Get timeout value                        |
|       |         | `!rq`                                        |                                       | Get current sequence timer               |
|       |         | `!sd[date]`                                  |                                       | Set date, WMMDDYY                        |
|       |         | `!st[time]`                                  | `!st123456`                           | Set RTC time, HHMMSS                     |
|       |         | `!tl`                                        | `!tl`                                 | Run led test                             |
|       |         | `!to[1-4]`                                   | `!to1`                                | Set text overflow mode                   |
|       |         | `!tp[n]`                                     | `!tp1`                                | Show test pattern, 0 disables            |
|       |         | `!up[nn]`                                    | `!up05`                               | Set communications timeout               |
|       |         | `!uq[1-20]`                                  | `!uq08`                               | Set text sequence timing                 |
|       |         | `!zm[protocol]`                              | `!zm1`                                | Set protocol variant                     |
|       |         | `!zb`                                        | `!zb`                                 | Reboot the system                        |
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
|       |         | `!dp[nn]`         |                           | Page dwell period?                          |
|       | RM2040  | `!DR`             |                           |                                             |
|       |         | `!dr[nn]`         |                           | Frame duration?                             |
|       |         | `!dw`             |                           | Some page flag                              |
|       | RM2040  | `!ffc`            |                           |                                             |
|       | RM2040  | `!ffd[n]`         |                           |                                             |
|       | RM2040  | `!ffr`            |                           |                                             |
|       |         | `!Fs[50-600]`     |                           | Set framerate / FPS?                        |
|       |         | `!Fx[0-9]`        |                           | Set FX slowdown?                            |
|       |         | `!kb`             |                           | Custom glyph?                               |
| 2     |         | `!lc[ll],[nn]`    |                           | Protocol 2                                  |
| 2     |         | `!lh[ll],[nn]`    |                           | Protocol 2                                  |
| 2     |         | `!lp[ll],[nn]`    |                           | Protocol 2                                  |
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
## `!dl` - display line

### Arguments
`[line][mirror][effect][justify][text]` where:
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
## `!Fm` display mapping definition

This command allows definition of the line mappings recalled by `!m[0-F]` commands. Mappings defined by the config file cannot be redefined.
### Arguments
`[m]{l[ll]x[xx]y[yy]h[hh]w[ww]}...*`' where
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

# Communication examples

In the protocol 1 (assumed DDX) one needs to include `!ps`, `!m` and `!dl` commands in single protocol frame.

```
[0A!ps01!m1!dl1jpL<Helsinki Hacklab metro station announcement system scroller thingy>!dl2jpL<By: Depili>!dl3jpL<26-06-21>!pl01]
```
Protocol 2 (assumed LDDX) might work with this:
```
[0A!ls01!m1!dl1jpL<Helsinki Hacklab metro station announcement system scroller thingy???>!dl2jpL<By: Depili>!dl3jpL<26-06-21>!pl01]
```
