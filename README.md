# DLOpenUSBAdaptor
An Open Version of a USB / Serial Adaptor to Communicate with Dragon's Lair, Space Ace &amp; Thayer's Quest Scoreboard Units

##THE MAIN GOAL (Dec 26th, 2019)

The idea here is to use an Arduino Uno or Compatable to create a USB Serial Interface for the Scoreboard Unit to the Dragon's Lair Laserdisc Arcade game, and implement a simple serial protocol to allow communication by the Daphne Emulator - However, I don't have the skill set needed to add the changes to Daphne. 

So, I'm hoping once I make this adaptor from the Arduino, support can be implemented into the Daphne Emulator, or other Emulators by others.

For now, I'm just setting up the repository with information and I expect to be tinkering on December 30th 2019 through Jan 1st 2020 and getting the connection schematic up.


# Some Initial Stuff



## Serial Protocol
There will need to be a command system to allow the segments to be controlled by emulators, plus the Skill Lights.

### Baud Rate
Until I get this project going with more traction, i'm going to leave this at 9600bps for testing. Once debugging is done, this can be amended.

### Hey, I'm here!
So, to aid the Emulator ensuring it's got a valid adaptor for the Scoreboard on a com port, you can send
[DAPHNE?]
and it would return
[SAVEME!]

### Up To Date Code
Send [VERSION?] to receive [VERSION#.##] - This would then allow the Emulator to ensure it's talking to the most appropriate code version. Obviously, replace the Hashes with Numbers for the version number.

### Skill Lights
Send [SKILL#@] to control the Skill Lights. Replace # with 1 for the Easy Light, 2 for the Medium Light & 3 for the Hard Light. Replace @ with 0 to turn that light off, or 1 to turn it on.

## Connections

### Interfacing the Scoreboard to the Arduino
From Scoreboard Pin -> To Arduino Pin (Function)
* Scoreboard 1 to Arduino 3 (D3)
* Scoreboard 2 to Arduino 4 (D2)
* Scoreboard 3 to Arduino 5 (D1)
* Scoreboard 4 to Arduino 6 (D0)
* Scoreboard 5 to Arduino 7 (A2)
* Scoreboard 6 to Arduino 8 (A1)
* Scoreboard 7 to Arduino 9 (A0)
* Scoreboard 8 to Arduino 10 (DEN1)
* Scoreboard 9 to Arduino 11 (DEN2)
* Scoreboard 10 - NO CONNECTION
* Scoreboard 11, 12, 13 - +5V
* Scoreboard 14, 15, 16 - Ground Connection

### Interfacing the Skill Lights to the Arduino
This is to support the Skill Light Indicator that was present on Space Ace Cabinets
These are currently planned to be ACTIVE HIGH signals. If using own LEDs, you will need to calculate the resistance value for each LED's resistor to avoid the Arduino Popping your LEDs!

* Skill Hard Light is on Arduino A0
* Skill Medium Light is on Arduino A1
* Skill Easy Light is on Arduino A2


### A VERY rough connections diagram!
![Image of Connections](https://github.com/jonharriscoding/DLOpenUSBAdaptor/blob/master/dl_adaptor.png)

*I apologise if you find the graphic not to engineering standards but if you had essential tremor you'd find this difficult to do.*
