# Features

1.UART
2.Multibank RAM/EEPROM and Status LED Output
3.DS12885+ Clock Module
4.Keyboard
5.7 Segments
6.Extend IO Port

# UART Programming [Reference Document](https://forum.mapleboard.org/topic/uart8250-%252525E8%25252588%25252587-ns16550-%252525E6%252525B7%252525B1%252525E5%25252585%252525A5%252525E5%25252589%25252596%252525E6%2525259E%25252590/)
The computer uses dual 16550 UART IC for UART communication.
The main 16550 is on IO Address 0xFF20 and the other one is on IO Address 0xFF30
The main 16550 is dedicated for Terminal Display and Internet function with ESP32 on board while the other one is free to use it any way you want.

16550 Have 3 Address Lines for 8 Registers.
It have 2 Modes depending on the DLAB set.(Bit 7 for Register 0b011)


```z80asm
; Assume we wanna write to ESP32
UART_ADDR EQU 0xFF20

; Registers
; Receive Buffer Register
UART_RBR   EQU UART_ADDR + 0
; Transmitter Holding Register
UART_THR   EQU UART_ADDR + 0
; Interrupt Enable Register
UART_IER   EQU UART_ADDR + 1
; FIFO Control Register
UART_FCR   EQU UART_ADDR + 2
; Line Control Register
UART_LCR   EQU UART_ADDR + 3
;Line Status Register
UART_LSR   EQU UART_ADDR + 5

; 1. Set DLAB (Divisor Latch Access Bit)
ld a, 80h       ; DLAB = 1
out (UART_LCR), a

; 2. Set Baud Rate (1.8432 MHz crystal, 9600 baud)
; Divisor = 1843200 / (16 * 9600) = 12 (0x0C)
ld a, 0Ch
out (UART_ADDR + 0), a ; LSB
ld a, 00h
out (UART_ADDR + 1), a ; MSB

; 3. Clear DLAB, set 8N1 (8 data bits, no parity, 1 stop bit)
ld a, 03h
out (UART_LCR), a

; 4. Enable FIFOs (16550 Specific)
ld a, 07h       ; Enable RX/TX FIFOs and reset them
out (UART_FCR), a


send_char:
    in a, (UART_LSR) ; Read Line Status Register
    bit 5, a         ; Test bit 5 (Transmitter Holding Register Empty)
    jr z, send_char  ; Loop if 0 (busy)
    ld a, 'A'        ; Character to send
    out (UART_THR), a
    ret


receive_char:
    in a, (UART_LSR) ; Read Line Status Register
    bit 0, a         ; Test bit 0 (Data Ready)
    jr z, receive_char ; Loop if 0 (no data)
    in a, (UART_RBR) ; Read received byte
    ret

```

# Multibank RAM/EEPROM and Status LED Programming
It's just basically a 74hc573 on IO Port 4(0xFF40).
Bit 0: Low_Activate ChipSelect Signal for 32k RAM on address 0x8000 to 0xFEFF
Bit 1: Low_Activate ChipSelect Signal for EEPROM on address 0x8000 to 0xFEFF
Bit 2-7: Status LED on board

```z80asm
; Define IO Address
BANK_REG   EQU 0xFF40

; Enable EEPROM and Disable RAM and Turn Off all LEDs
ld a, 01h
out (BANK_REG), a

; Enable RAM and Disable EEPROM and Turn On all LEDs
ld a, FEh
out (BANK_REG), a
```

# DS12885+ Clock Module Programming [Reference Document](https://www.analog.com/media/en/technical-documentation/data-sheets/DS12885-DS12C887A.pdf)
It's on the IO  Port of the Z80.
The Clock Module have two modes : BCD Mode and Binary Mode

### Table 2A. Time, Calendar, and Alarm Data Modes—BCD Mode (DM = 0)


| ADDRESS | BIT 7 | BIT 6 | BIT 5 | BIT 4 | BIT 3 | BIT 2 | BIT 1 | BIT 0 | FUNCTION | RANGE |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :--- | :--- |
| 00H | 0 | \<- | 10 Seconds | -> | \<- | Seconds | -> | | Seconds | 00–59 |
| 01H | 0 | \<- | 10 Seconds | -> | \<- | Seconds | -> | | Seconds Alarm | 00–59 |
| 02H | 0 | \<- | 10 Minutes | -> | \<- | Minutes | -> | | Minutes | 00–59 |
| 03H | 0 | \<- | 10 Minutes | -> | \<- | Minutes | -> | | Minutes Alarm | 00–59 |
| 04H | AM/PM | 0 | 10 Hours | | \<- | Hours | -> | | Hours | 1–12 +AM/PM / 00–23 |
| 05H | AM/PM | 0 | 10 Hours | | \<- | Hours | -> | | Hours Alarm | 1–12 +AM/PM / 00–23 |
| 06H | 0 | 0 | 0 | 0 | 0 | \<- | Day | -> | Day | 01–07 |
| 07H | 0 | 0 | \<- | 10 Date | \<- | Date | -> | | Date | 01–31 |
| 08H | 0 | 0 | 0 | 10 Mo. | \<- | Month | -> | | Months | 01–12 |
| 09H | \<- | 10 Years | -> | | \<- | Year | -> | | Year | 00–99 |
| 0AH | UIP | DV2 | DV1 | DV0 | RS3 | RS2 | RS1 | RS0 | Control | — |
| 0BH | SET | PIE | AIE | UIE | SQWE | DM | 24/12 | DSE | Control | — |
| 0CH | IRQF | PF | AF | UF | 0 | 0 | 0 | 0 | Control | — |
| 0DH | VRT | 0 | 0 | 0 | 0 | 0 | 0 | 0 | Control | — |
| 0EH-31H | X | X | X | X | X | X | X | X | RAM | — |
| 32H | \<- | 10 Century | -> | | \<- | Century* | -> | | Century* | 00–99 |
| 33H-7FH | X | X | X | X | X | X | X | X | RAM | — |
---

### Table 2B. Time, Calendar, and Alarm Data Modes—Binary Mode (DM = 1)


| ADDRESS | BIT 7 | BIT 6 | BIT 5 | BIT 4 | BIT 3 | BIT 2 | BIT 1 | BIT 0 | FUNCTION | RANGE |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: | :--- | :--- |
| 00H | 0 | 0 | \<- | -> | Seconds | <- | -> | | Seconds | 00–3B |
| 01H | 0 | 0 | \<- | -> | Seconds | <- | -> | | Seconds Alarm | 00–3B |
| 02H | 0 | 0 | \<- | -> | Minutes | <- | -> | | Minutes | 00–3B |
| 03H | 0 | 0 | \<- | -> | Minutes | <- | -> | | Minutes Alarm | 00–3B |
| 04H | AM/PM | 0 | 0 | \<- | -> | Hours | <- | -> | Hours | 01–0C +AM/PM / 00–17 |
| 05H | AM/PM | 0 | 0 | \<- | -> | Hours | <- | -> | Hours Alarm | 01–0C +AM/PM / 00–17 |
| 06H | 0 | 0 | 0 | 0 | 0 | \<- | Day | -> | Day | 01–07 |
| 07H | 0 | 0 | 0 | \<- | -> | Date | <- | -> | Date | 01–1F |
| 08H | 0 | 0 | 0 | 0 | \<- | -> | Month | | Months | 01–0C |
| 09H | 0 | \<- | -> | Year | <- | -> | <- | -> | Year | 00–63 |
| 0AH | UIP | DV2 | DV1 | DV0 | RS3 | RS2 | RS1 | RS0 | Control | — |
| 0BH | SET | PIE | AIE | UIE | SQWE | DM | 24/12 | DSE | Control | — |
| 0CH | IRQF | PF | AF | UF | 0 | 0 | 0 | 0 | Control | — |
| 0DH | VRT | 0 | 0 | 0 | 0 | 0 | 0 | 0 | Control | — |
| 0EH-31H | X | X | X | X | X | X | X | X | RAM | — |
| 32H | N/A | N/A | \<- | -> | Century* | <- | -> | | Century* | — |
| 33H-7FH | X | X | X | X | X | X | X | X | RAM | — |

---

**Notes:**
* **X** = Read/Write Bit.
* **\*** = DS12C887, DS12C887A only. General-purpose RAM on DS12885, DS12887, and DS12887A.
* **Note**: Unless otherwise specified, the state of the registers is not defined when power is first applied. Except for the seconds register, 0 bits in the time and date registers can be written to 1, but may be modified when the clock updates. 0 bits should always be written to 0 except for alarm mask bits.

```z80asm
; =====================================================================
; DS12885+ REAL TIME CLOCK DRIVER (Z80)
; Port Mapping:
; FF71h -> AS High (Address Strobe High)
; FF70h -> AS Low  (Latch Address / Data Access)
; =====================================================================

; --- Port Definitions ---
RTC_CMD      EQU 0FF71h    ; Port with A0=1 (AS High)
RTC_DATA     EQU 0FF70h    ; Port with A0=0 (AS Low)

; --- Internal Register Map ---
RTC_SEC      EQU 00h       ; Seconds
RTC_MIN      EQU 02h       ; Minutes
RTC_HOUR     EQU 04h       ; Hours
RTC_DAY_WEEK EQU 06h       ; Day of week (1-7)
RTC_DAY_MON  EQU 07h       ; Day of month (1-31)
RTC_MONTH    EQU 08h       ; Month (1-12)
RTC_YEAR     EQU 09h       ; Year (00-99)
RTC_REG_A    EQU 0Ah       ; Status Register A
RTC_REG_B    EQU 0Bh       ; Status Register B

; =====================================================================
; INITIALIZATION: Setup Oscillator and 24-Hour BCD Mode
; =====================================================================
INIT_RTC:
    ; 1. Setup Register A: Turn on the 32.768kHz oscillator
    LD A, RTC_REG_A
    CALL SELECT_REG
    LD A, 00100000b       ; DV2-0 = 010 (Osc On), RS3-0 = 0000 (None)
    OUT (C), A

    ; 2. Setup Register B: 24Hr mode, BCD format, Daylight Savings Off
    LD A, RTC_REG_B
    CALL SELECT_REG
    LD A, 00000010b       ; DM=0 (BCD), 24/12=1 (24Hr), DSE=0
    OUT (C), A
    RET

; =====================================================================
; READ TIME: Safely reads Seconds, Minutes, and Hours
; Returns: H = Hours, D = Minutes, E = Seconds (all BCD)
; =====================================================================
GET_TIME:
    ; Step 1: Wait for Update-In-Progress (UIP) bit to be clear
    ; This ensures we don't read data while the clock is updating.
WAIT_RTC:
    LD A, RTC_REG_A
    CALL SELECT_REG
    IN A, (C)
    AND 80h               ; Check bit 7 (UIP)
    JR NZ, WAIT_RTC       ; Loop if update is in progress

    ; Step 2: Read values
    LD A, RTC_SEC
    CALL SELECT_REG
    IN E, (C)             ; E = Seconds

    LD A, RTC_MIN
    CALL SELECT_REG
    IN D, (C)             ; D = Minutes

    LD A, RTC_HOUR
    CALL SELECT_REG
    IN H, (C)             ; H = Hours
    RET

; =====================================================================
; WRITE TIME: Set clock to 14:05:00 (Example)
; =====================================================================
SET_TIME_EXAMPLE:
    ; 1. Enter "Set Mode" (Stop updates)
    LD A, RTC_REG_B
    CALL SELECT_REG
    LD A, 10000010b       ; Set SET bit (7) to 1
    OUT (C), A

    ; 2. Write New Time (14:05:00)
    LD A, RTC_SEC
    CALL SELECT_REG
    LD A, 00h
    OUT (C), A

    LD A, RTC_MIN
    CALL SELECT_REG
    LD A, 05h
    OUT (C), A

    LD A, RTC_HOUR
    CALL SELECT_REG
    LD A, 14h             ; 2 PM in BCD
    OUT (C), A

    ; 3. Exit "Set Mode" (Resume updates)
    LD A, RTC_REG_B
    CALL SELECT_REG
    LD A, 00000010b       ; Clear SET bit
    OUT (C), A
    RET

; =====================================================================
; HELPER: Multiplexed Address Latch
; Input: A = Register Index
; Output: BC = RTC_DATA port address for subsequent IN/OUT
; =====================================================================
SELECT_REG:
    LD BC, RTC_CMD        ; A0 = 1 (AS High)
    OUT (C), A            ; Put index on data bus
    LD BC, RTC_DATA       ; A0 = 0 (AS High-to-Low transition)
    OUT (C), A            ; Address is now latched inside DS12885
    RET

```


# Keyboard Programming
Keyboard is connected to two 74hc573s,IO Port 0 (0xFF00) for Row Select and IO Port 1(0xFF10) for Column Read.
Although the keyboard is wired as a 8x8 matrix,the layout on the PCB is 16*4.
Please refer to the KiCad Design before programming as the layout is a bit hard to describe in pure text document.
Note that as no diodes are connected to the keyboard circuit, multiple(more than two) keypress may cause glitched input
```z80asm
COL   EQU 0xFF00
ROW   EQU 0xFF10
; Select Column
LD A,01h
OUT (COL),A
; Read Row
IN A,(ROW)
```
# 7 Segment Display Programming
7 Segment Display is on IO Port 5 and 6.(0xFF50 and 0xFF60)
```z80asm
LEFT_SEVEN_SEG   EQU 0xFF50
RIGHT_SEVEN_SEG   EQU 0xFF60

;Display qp on the seven segment displays
;Bit 0-7 for A-G and DP respectively
;Letter q:abcfg
;Letter p:abefg
;Their Binary Representation:0b11100110 and 0b11001110 (E6h and h respectively)
LD A,E6h
OUT (LEFT_SEVEN_SEG),A

LD A,CEh
OUT (RIGHT_SEVEN_SEG),A
```
# Extend IO Port Programming
The extend IO Port(2.54 Connector PinHead 40pin)
| PinNum.(From left to right,Start from 1) | PinName |
| 1 | 5V |
| 2 | GND |
| 3 | TX2 |
| 4 | RX2 |
| 5 | !M1 |
| 6 | !MREQ |
| 7 | !IORQ |
| 8 | !RD |
| 9 | !WR |
| 10 | !INT |
| 11 | !HALT |
| 12 | !RESET |
| 13 | IO8 |
| 14 | CLK |
| 16-31 | A0-A15 |
| 33-40 | D0-D7 |
