# Features

1.UART
2.Multibank RAM/EEPROM and Status LED Output
3.DS12885+ Clock Module
4.Keyboard
5.7 Segments
6.Extend IO Port

# UART Programming

## This Paragraph is written by referring the document [Document Link](https://forum.mapleboard.org/topic/uart8250-%252525E8%25252588%25252587-ns16550-%252525E6%252525B7%252525B1%252525E5%25252585%252525A5%252525E5%25252589%25252596%252525E6%2525259E%25252590/)

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

# DS12885+ Clock Module Programming
not yet finished
# Keyboard Programming
# 7 Segment Display Programming
# Extend IO Port Programming