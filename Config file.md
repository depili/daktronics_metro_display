The units have an internal config file. This is a template extracted from the vendor utilities:
```
ChannelLengths=128,128,128,128,0,0,0,0 ; Sign dependent.
LinesPerChannel=1,1,1,1,0,0,0,0        ; Physical Lines on channels.
missingLEDs=0,0,0,0,0,0,0,0  ; Compensation for missing leds on channels.
Pixels=128                   ; Pixel lenght of longest Physical Line.
doublesided=N                ; Default = Single sided.
DriveType=M                  ; Multiplexed = M Direct Drive = D T = DD Ticker.
Channels=4                   ; Number of Channels used.
Colours=1                    ; Number of colors.
RowsPerLine=8                ; number of pixel rows on the physical board.
speedDivisorM=5              ; mux SpeedA: 3.333 MHz.
speedDivisorD=19             ; mux SpeedB: 1MHz calc example =  40/(1+19)/2 = 1.
speedDivisorMB=19            ; DD SpeedA: 1 MHz.
speedDivisorDB=200           ; DD SpeedB: to 0.1 MHz.
BrightControl=O              ; O - OE-line, D - D-line.
PSU=N                        ; Opto's = 0 P = input pin N = No monitoring.
LEDmon=Y                     ; Led monitoring Y=yes N=no.
Temp=Y                       ; Temp monitoring Y=yes N=no.
LightSensor=Y,1              ; N=No, Y=yes [1-3] 1=read master, 2=slave, 3=average.
LSType=1                     ; 1 = PCB289 0 = PCB175
MainChannel=1                ; 1=RS485 main comms, 2=RS232 main comms.
BaudOption=1,19200           ; Switch (SET) option 1 for UART 0 and
                             ; UART 1 (Main RS232 and RS485).
BaudOption=2,9600            ; Switch (NOT SET) option 2 for UART 0 and
                             ; UART 1 (Main RS232 and RS485).
BaudOption=3,9600            ; Baud option for 'Spare' UART.
Speed=65                     ; mux 1.8ms.
FXslowdown=0                 ; no effects skip.
RGSwap=N                     ; swap red-green channels.
RBSwap=N                     ; swap read-back.
HygrosenTempProbe=N          ; no HygrosenTempProbe (Temp Sensor).
StartTimedOut=Y              ; Show Timeout Message After Sign on.
scrollIfTooWide=N            ; Scroll text if it does not fit.
truncateOnChar=Y             ; Truncate on character if text does not fit.
truncateOnWord=N             ; Truncate on word if the Text does not fit.
Timeout=5                    ; Main Comm's Timeout in minutes 0=disabled.
CfgFixedContentDefMode=1     ; Mode configured fixed content should use.
CurrentMode=1                ; Mode the sign starts in.
internalMsgMode=1            ; Mode used by internal messaging (sign on etc. default = 0)
ClearOldQueue=N              ; delete pages in old queue that are not in new !ps.
Succession=Y                 ; Allow syntax like
                             ; [!ls01|!ps01]!dl01jpc<Suc 1>!dp02!dl01ruL<Suc 2>!dp02.
defSeqEffect=I               ; Default Effect used by Sequences I=jump.
suppressHourLeadingZero=N    ; Extract lz hrs Y=yes N=No.
suppressMinsLeadingZero=N    ; Extract lz mins Y=yes N=No.
suppressSecsLeadingZero=N    ; Extract lz Secs Y=yes N=No.
suppressDayLeadingZero=N     ; Extract lz Days Y=yes N=No.
replaceHoursLeadingZero=N    ; Replace (with blank, same width as zero)
                             ; lz hrs Y=yes N=No.
suppressMonLeadingZero=N     ;
ignoreDP=N                   ; block the use !dp (display pause) commmands.
PROTOCOL=01                  ; main protocol 1=DDX Modal 2=LDDX.
Master=Y                     ; .
Sequence=3                   ; deafult sequence (sq) rate.
Flash=700,300                ; Flash rate 70% on / 30% on.
MaintTime=1                  ; Maintenance Channel timeout.
PinLock=3                    ;
MaxADC=20                    ;
MinBr=15                     ;
MaxBr=90                     ;
#CapBr=50                    ;
FixedFontFlag=N              ; Y = font 3 fixed, N = font 3 is not fixed
#DDXmodalPage=0,0,32,256     ; x, y, h, w
DST=03,S,11,F,2,1            ; Start month, FSTQL Sunday, last month, FSTQL Sunday.
#DDXfixedLine=1,N,C,jp,<\\t\{hh:mm\}>  ; line num, Show when timed out, just, effect,<Text>
#swapChar=7B,7D              ; swap char A with B hex char A, hex char B
autoDetectArabic=N           ; if text string has char above 0x80 consider it an arabic string
translateArabic=N            ; Scan and translate Arabic strings
                             ; (set start middle end versions etc.).
#ArabicLigatures=D1 C9,92 D1 ; swap pattern 1 with pattern 2.
                             ; chars A B, B A e.g. swap char sequence
                             ; 0xD1 0xC9 with 0xD1 0x92
MaxScrolls=10                ; Includes scroll-if-too-wide fields and calling ats
DLMx=m1
l1x00y000h8w128
l2x00y008h8w128
l3x00y016h8w128
l4x00y024h8w128*
DLMx=m2
l1x00y003h12w128
l2x00y017h12w128*
DLMx=m3
l1x00y000h16w128
l2x00y016h16w128*
DLMx=m4
l1x00y004h24w128*
DLMx=m5
l1x00y000h32w128*
AF6700 Config template.
```
# Config file from my RM2037 units
```
DriveType=M        M - Multiplexed, D - Direct Drive, T - DD Ticker. Default:M.
ChannelLengths=160,160,160,160,160,48,0,0	           4 lines mono colour.
LinesPerChannel=1,1,1,1,1,1,0,0                single sided 1 line per channel.
missingLEDs=0,0,0,0,0,0,0,0                deliberately missing LEDs on boards.
doublesided=N              the higher channels will mirror the lower  channels.
BrightControl=O     O - OE-line, D - D-line.                         Default:O.
Pixels=160          Length of longest channel (display width).     Default:128.
Channels=6          Number of attached data channels.                Default:8.
Colours=1           Number of colours.                               Default:2.
RowsPerLine=8       Number of pixel rows for each channel (7,8 or 9).Default:8.
Speed=60            Frames per second (50-600).                     Default:60.
FXslowdown=0        Slow down effects at high frame speeds (0-7).    Default:0.
LightSensor=Y      Use auto light sensor feature (Y/N).             Default:Y.
PSU=O               PSU monitoring    (O - via opto inputs,
                                      P - input pin,
                                      N - no monitoring).            Default:N.
Temp=N                Temperature monitoring (Y/N).                  Deafult:Y.
LEDmon=Y                                              LED monitoring Default:Y.
PROTOCOL=02                                    Allowed Protocols: 01:DDX modal.
RGSwap=N
RBSwap=N
Master=Yes
Timeout=5                                           Time in minutes. Default:4.
StartTimedOut=Y                                 Initially timed out? Default N.
scrollIfTooWide=Y                            scroll text if too wide for field.
Sequence=3         seconds for each text sequence.                   Default:2.
Flash=700,300      On time (ms) and off time (ms).             Default:700,300.
MaintTime=0        Maintenance time idele timeout in minutes.        Default:1.
PinLock=3          PIN error lockout in minutes.                     Default:3.
MaxADC=20          Limit light sensor reading.              Default: 48 (0x30).
MinBr=15           Minimum allowed brightness percentage.            Default:1.
MaxBr=95           Maximum allowed brightness percentaage.          Default:98.
MainChannel=2                                                   485 main comms.
CurrentMode=1
RepeatDLs=Y                                                         DEFAULT: Y.
CarryPageContent=N                                                  DEFAULT: N.
Succession=N                                                        DEFAULT: N.
translateArabic=N                                                    NO arabic.
autoDetectArabic=N                                                   No arabic.
replaceHoursLeadingZero=Y
DDXfixedLine=6,Y,C,jp,<\t{HH:MM}>        line#, showTimedOut,just,fx,<text>.
DLMx=m1
l1  x0   y0  h8 w160
l2  x0   y8  h8 w160
l3  x0   y16 h8 w160
l4  x0 	 y24 h8 w160
l5  x0   y32 h8 w160
l6  x0 	 y40 h8 w48*
160x40 48x8 mono singlesided
.
```
