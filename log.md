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

3\. finish the eeprom and ram

4\. write a simple bios

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

1\. finish the eeprom and ram
2\. write a simple bios
3\. write a test program
4\. add a 7segment led output io module
5\. add some controllable pins for further extend
6\. add status leds
7\. reset,halt,resume button(if needed i guess)
8\. controllable leds to fully utilize the 573 for multi banking



Part2

what ive done:

1.banking logic (totally)
2.searching for how z80 interrupt and halt and wait works.



what i need to do:

1. write a simple bios
2. write a test program
3. add some controllable pins for further extend
4. add status leds
5. reset,halt,resume button(if needed i guess)




Day 3 20/4/2026

what i will do today:

1. finish the status leds
2. add some controllable pins
3. reset halt and resume :D
 after some consideration i think i will just abandon the interrupt as humm I WRITE THE CODE I WRITE THE PROGRAMS NAD I DESIGN IT :D so i think i dont need them :DDDDD:D:D:DD:D:DDDDDDDDDDDDDDDDDDD

what ive done:
1. all of the schematics
2. layout the keyboard and led and spiscreen for the pcb

what i need to do:

1. write a simple bios
2. write a test program
3. layout the pcb

Day 4 21/4/2026

what ive done today:
1.layout the pcb
2.route the pcb(yah sorry with autoroute cuz my routing technique is kinda bad)

what i need to do:
1.write a bootloader
2.write a test program
3.write a program for esp32 to display serial datas

Day 5 22/4/2026

what ive done today:
1.rerouted the pcb (bruh Freeroute is terrible)
2.added the extension port
3.wrote something on the README.md

Day 6 23/4/2026

what ive done today:
1.edited the README.md to add the components list
2.autorouted AGAIIINNN with Electra and THATS WAS AMAZING OMG ITS SOOOOO COOL

Day 7 24/4/2026

what ive done today:
1.Wrote file for Programming on the Computer.
2.Fixed a wiring problem on PCB(Not Logic Gate Inverted for the interrupt Signal 16550) and reroute the wiring again.

Day 8 25/4/2026

what ive done today:
1.Finished the Programmer Manual

Day 9 1/5/2026

what ive done today:
1.Simplified the Multibank Circuit (Reduced SMD usage)
2.Rerouted the pcb again for the modification made
(I Tried EAGLE,AutoRoute,and even asked Ai to help me write a simple autoroute application but erm in the end i used electra :| electra is amazing...)

Day 10 3/5/2026

what ive done today:
Wrote a Script for the Video
Updated the BOM list
Updated the Documentation
Started to create the project video

Day 11 12 4/5/2026 and 5/5/2026

Human Reroute again and again :D

Day 13 7/5/2026
Wrote some assembly for Memory loading and 7 segment output and searched for how to write those assembly and tested on ASM80.com

Day 14-15 8/5/2026 9/5/2026
Continued to route the PCB

Day 16 11/5/2026
I realized the layout that I designed for the PCB was already wrong from the start...
the Layout is too terrible and too hard to route (why there are so many signals wiring that need to be routed across the whole board XDDDDDD)
Yah I redesigned the layout and i think now the layout is much more cleaner :D
the Interrupt Signals and the ReadWriteChipSelect signals are still hard to route though but the Data buses and Address buses are much better :D

Day 17 12/5/2026
humm actually the current layout is still not yet the best one but i think i will keep the current one and try to add more space for me to route by pushing a bit the edges :D

Day 1819 13-14/5/2026
FINISHED ROUTING PART and Re-Upload for review again :D