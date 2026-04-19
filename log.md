Day1 18/4/2026

what will we do?

A Handheld Z80 based device with a LOTS of cool feature

1.IT MUST HAVE A KEYBOARD

2.IT HAVE A BIOS

3.IT HAVE A OPERATING SYSTEM

4.IT CAN LOAD BINARY FILES

5.IT CAN OUTPUT SOUND

6.IT MUST HAVE A SCREEN OFCOURSE EHHEEEEEEE(i think may be power with esp32 by reading UART(can receive ansi and VT350 commands))

7.IT BETTER CAN USE ESP32 TO DO INTERNET AND BLUETOOTH(DONT RELY TOO MUCH THOUGH...)

8.it can connect UART to computer :D 16550UART CHIP

9.better connect a tfcard

welp today lets make a really simple z80 circuit that can read from a eeprom when start :D



Memory

0x0000 to 0x7FFF 32kb BIOS + Program EEPROM (first half writable but second half is not.)

0x8000 to 0xFFFF 32kbRAM and 32kb ROM (Paged)

0xFF00 to 0xFFFsF Input and Output

what i need to do:
1.finish the Double UART
2.finish the SPI Screen and the esp32 c3 supermini
3. finish the eeprom and ram
4. write a simple bios
5.write a test program
6.add a 7segment led output io module
7.add some controllable pins for further extend




Day 2 19/4/2026
OHH YAEAH ITS OUR second day erm unfortunately i  dont really have much time today but nvm lets complete the UART thing first :D

what ive done:
1.UART
2.SPI screen
3.buzzer
4.Multibanking chip achieved with 573
what i need to do:
1. finish the eeprom and ram
2. write a simple bios
3. write a test program
4. add a 7segment led output io module
5. add some controllable pins for further extend
6. add status leds
7. reset,halt,resume button(if needed i guess)
8. controllable leds to fully utilize the 573 for multi banking

Part2
what ive done:
1.banking logic (totally)
2.searching for how z80 interrupt and halt and wait works.

what i need to do:
write a simple bios
write a test program
add some controllable pins for further extend
add status leds
reset,halt,resume button(if needed i guess)
