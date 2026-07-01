1. Connect your computer to the RS-232 cable with the DB9 connector
2. Open a serial terminal to the display; 19200 baud, 8 data bits, no parity, 1 stop bit
3. Power on the display, note the address it is configured to on the boot screen
4. Send the following setup command, it switches the display to protocol 1
	1. `[xx!zm1]`, where `xx` is your displays address
	2. The display should reply with `[xY00,8F/FF]` where `x` is the letter from the address
5. Compose and send your text
	1. `[xx!ps01!m1!dl1jpL<line1>!dl2jpL<line2>!dl3jpL<line3>!dl4jpL<line4>!dl5jpL<line5>!pl01]`
		- Where:
			- `0x` is the address
				- Discard the number (group) that is shown on the splash screen, just use `0` and the letter, most likely `0A`
			- `!ps01` selects page1
			- `!m1` uses the line definitions from the internal config file
			- `!dl0x` where `x` is the line number, 1-5 define the line contents
				- `jp` is the default mode, others still to be figured out
				- `L` is the justification or centering, possible values: `L, R or C`
				- `<`  is the start of text marker
					- Text follows
						- `\t{HH:MM:SS}` gets the RTC time from the display and shows it
				- `>` is the end of text / end of !dl command marker
			- By default lines that don't fit will scroll
	2. The display should reply with `[xY00,8F/FF]`
	3. Repeat text updates, the display will time out after 3 minutes without a new state update
			  
## Other settings
* You can set the internal time with a command `[xx!stHHMMSS]` where:
	* `xx` is the display address
	* `HH` current hours, 24h format
	* `MM` current minutes
	* `SS` current seconds