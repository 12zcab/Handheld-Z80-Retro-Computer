Hello Im 12zcab from Hong Kong and I designed this Z80 Retro Computer :DD

# What is this?
This is a portable handheld computer made with z80 customized for assembly language programming and simplified system for educational purpose.
The computer comtains a Z80 cpu,a SPI screen,a Esp32 C3 Supermini and 2 EEPROM slot,a RAM slot,a buzzer,some leds,2 7segments and a extendable port for IO.
The computer support Dual-UART communication, one with the Esp32 and one for extending.
# What it does?
It just let you run simple programs on it and let you bring it anywhere!
My final goal is to write a fully functional Operating System and make it as simple as possible on this computer!
With the ESP32 C3 Supermini connected through UART,you can draw on SPI screen and output characters just like connected to a Terminal (for old computers)
With the Buzzer,7segments and the keyboard also with the extendable port,you can build alsome retro coding projects on this old-fashion Cyberdeck :D
# Why it exists?
Erm it all started when I found a video about old pokemon games and i started to play Gen 1 pokemon games on emulators(Red Version).
I found it a really amazing experience to have play a game with greyscale and 8 bit musics.
Then I asked my parents and found that we actually have a real gameboy athome!!
I then started to research on how gameboy works and study on the Disassembled PokeRed gameboy assembly code on github and I was shocked on how elegance it is the original assembly code.
Then I learnt the gbz80 instruction set,also the boot rom of the gameboy,then also 8086,8051,8085 and z80 assembly.
I followed a youtube video and built my first z80 computer and started to do a few assembly programming on it and yah its really fun [Ytlink](https://youtu.be/A0VpPRWrqHc?si=ajm_OGpBwFbzzyzW).
I recently found Fallout Event on HackClub and instantly found this a great oppertunity to design my own real z80 computer that is simple and workable.


# Basic Structure
--Memory Map--
| Address | Compoenent | Function |
|----|----|----|
|0x0000 - 0x7FFF| EEPROM | Executable Code of Operating System |
|0x8000 - 0xFEFF| RAM or EEPROM | Multibanked External EEPROM and RAM |
|0xFF00 - 0xFFFF| IO Outputs | for Output,UART,and also other Extension Usage |
|----|----|----|


--Compoenents Used--
| Name | Usage | Quantity |
