# A Handheld Z80 Retro Computer
[![Figma](https://img.shields.io/badge/Figma-F24E1E?logo=figma&logoColor=white)](#)
[![ReadMe](https://img.shields.io/badge/ReadMe-018EF5?logo=readme&logoColor=fff)](#)
[![AssemblyScript](https://img.shields.io/badge/AssemblyScript-007AAC?logo=assemblyscript&logoColor=fff)](#)
[![C++](https://img.shields.io/badge/C++-%2300599C.svg?logo=c%2B%2B&logoColor=white)](#)
[![Kicad](https://img.shields.io/badge/KiCad-8.0%7C9.0%7C10.0-blue)](#)
[![Esp32](https://img.shields.io/badge/Platform-ESP32-informational?style=flat&logo=Arduino&logoColor=white&color=00979D)](#)

Hello Im 12zcab from Hong Kong and I designed this Z80 Retro Computer :DD

# Zine Page
https://www.figma.com/design/0DzeSIebLkugrNq00bVcSF/Untitled?node-id=0-1&t=Gd1BAF2dvagKk23V-1
![Zine](https://github.com/12zcab/Handheld-Z80-Retro-Computer/blob/main/img/Zine.png)

# Images
![Design](https://github.com/12zcab/Handheld-Z80-Retro-Computer/blob/main/img/design.png)
![Route](https://github.com/12zcab/Handheld-Z80-Retro-Computer/blob/main/img/RouteNewest.png)
![PCB](https://github.com/12zcab/Handheld-Z80-Retro-Computer/blob/main/img/PCBNewest.png)

# What is this?
This is a portable handheld computer made with z80 customized for assembly language programming and simplified system for educational purpose.
The computer comtains a Z80 cpu,a SPI screen,a Esp32 C3 Supermini and 2 EEPROM slot,a RAM slot,a buzzer,some leds,2 7segments and a extendable port for IO.
The computer support Dual-UART communication, one with the Esp32 and one for extending.
# What it does?
It just let you run simple programs on it and let you bring it anywhere!
My final goal is to write a fully functional Operating System and make it as simple as possible on this computer!
With the ESP32 C3 Supermini connected through UART,you can draw on SPI screen and output characters just like connected to a VT100 Terminal (for old computers)
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
##Memory Map
| Address | Compoenent | Function |
|----|----|----|
|0x0000 - 0x7FFF| EEPROM | Executable Code of Operating System |
|0x8000 - 0xFEFF| RAM or EEPROM | Multibanked External EEPROM and RAM |
|0xFF00 - 0xFFFF| IO Outputs | for Output,UART,and also other Extension Usage |
|----|----|----|


# Compoenents

## Main Compoenents
| Name | Usage | Quantity |
|----|----|----|
| Z84C00xxP | The CPU of the Computer | 1 |
| ESP32 C3 Supermini | The Micro Controller Board for Serial Output Processing | 1 |
| 3.5inch SPI Screen 14Pin| For Displaying Serial Output | 1 |
| DS12885+ Clock Module | Clock Module For Z80 | 1 |
| 62256 | 32k RAM for Z80 | 1 |
| 28C256 | 32k EEPROM for External file and Bootloader and Applications | 2 |
| HDSP-7501 | 7 Segment Display for Z80 Output | 2 |
| 16550 | UART Communication IC for Z80 IO | 2 |
| PTS 810 SMD Button | Keyboard Input for Z80 | 64 |
| 4 Pin 6mm Switch | Reset Button for Z80 | 1 |
| LED SMD 1206 | SMD LED with internal resistor for Signal and Data Bus displaying | 39 |
| Buzzer | D12mm height 9.5mm with RM7.6mm Buzzer for ESP32 C3 Supermini to Emit sound when receive specific serial input from Z80 | 1 |
| CR2032 battery holder | Battery for DS12885+ Clock Module | 1 |

## Logic Gates and ICs
| Name | Usage | Quantity |
|----|----|----|
| 74HC573 | A Registor for Input and Output and Multibanking | 5 |
| 74HC04 | Hex Logic Invertor for toggling High-Activate Signals and Low-Activate Signals | 2 |
| 4068 | 8 Input AND/NAND Logic Gate for IO Signal Filtering | 1 |
| 74154 | 4 to 16 Decoder for IOS Address Decoding | 1 |
| 74HC00 | Quad NAND Gate | 2 |

## Crystals
| Name | Usage | Quantity |
|----|----|----|
| 4 Pin Crystals | 20MHz and 1.8432MHz for CPU and UART ic respectively | 2 |
| 2 Pin Crystal | 32768Hz for DS12885+ Clock Module | 1 |

## Resistors
| Name | Usage | Quantity |
|----|----|----|
| 1K resistor | 7 segment display resistor to prevent the display BURn :D | 2 |
| 10K resistor | Pull-up Resistors | 4 |
