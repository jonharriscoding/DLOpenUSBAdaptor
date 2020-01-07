# DLOpenUSBAdaptor
An Open Version of a USB / Serial Adaptor to Communicate with Dragon's Lair, Space Ace &amp; Thayer's Quest Scoreboard Units

## Latest News - 7/1/2020
My apologies for the delay in any activity at the moment, I haven't been able to do much due to needing to relocate the workshop into my garage and I can have a clear space to work on this. I hope tomorrow once my medication has had a chance to kick in properly and not leaving me with a foggy head I can start some wiring up and debugging.

## THE MAIN GOAL 
The idea here is to use an Arduino Uno or Compatable to create a USB Serial Interface for the Scoreboard Unit to the Dragon's Lair Laserdisc Arcade game, and implement a simple serial protocol to allow communication by the Daphne Emulator - However, I don't have the skill set needed to add the changes to Daphne. 

So, I'm hoping once I make this adaptor from the Arduino, support can be implemented into the Daphne Emulator, or other Emulators by others.

For now, I'm just setting up the repository with information and I expect to be tinkering on December 30th 2019 through Jan 1st 2020 and getting the connection schematic up.

## WHAT YOU SHOULD KNOW
This project is in it's infancy stages. I do not claim to be a professional coder by any means. I consider myself to be at Hobbyist / Amateur level. But my aim is to make this an open project so that others can come in, tweak the code, and make the adaptor available to all who may need it in the future.

## WHY A USB SERIAL ADAPTOR?
Put simply, Parallel Ports have vanished from native Windows support in the way that the Daphne Emulator needs to access them, in order for the Scoreboard Units to work. Making a USB Serial adaptor is still an option because Serial Ports are still widely supported on PC, and provide a convienant USB connection, also offering a +5V Power Source for lighting the segments of the Scoreboard. 

## WHY ARDUINO?
'Cause it's what I had handy! Plus, it's got a built in USB to Serial Port conversion and programmable Microcontroller on board, which we can program to interface the BCM7218 IC's used for driving the display digits. They are also extremely cheap and require no modification to interface to the Scoreboard.


# Setting out the project aims

## Serial Protocol
There will need to be a command system to allow the segments to be controlled by emulators, plus the Skill Lights.

### Baud Rate
Until I get this project going with more traction, i'm going to leave this at 9600bps for testing. Once debugging is done, this can be amended.

### Hey, I'm here!
So, to aid the Emulator ensuring it's got a valid adaptor for the Scoreboard on a com port, you can send
`[DAPHNE?]` and it would return `[SAVEME!]`

### Up To Date Code
Send `[VERSION?]` to receive `[VERSION#.##]` - This would then allow the Emulator to ensure it's talking to the most appropriate code version. Obviously, replace the Hashes with Numbers for the version number.

### Skill Lights
Send `[SKILL#@]` to control the Skill Lights. Replace # with 1 for the Easy Light, 2 for the Medium Light & 3 for the Hard Light. Replace @ with 0 to turn that light off, or 1 to turn it on.

### Control of the Segments
The LED's are split into two banks of 8 digits.
* The first bank will use it's first 6 digits for the Player 1 Score, Then the 7th for Player 1 Lives and the 8th for Player 2 Lives.
* The second bank will use it's first 6 digits for the Player 2 Score, then the 7th and 8th Digits for the amount of credits in the game.

To set the digits, 

* Send `[DISP1######ab]` replacing # with player 1 score data, a for P1 lives, b for p2 lives
* Send `[DISP2######cd]` replace # with player 2 score data, cd for credits

If you need a character to be off, replace the appropriate section with a space. 
So for example to set the display for Player 1 for a score of 100, with 3 lives, and the 2nd player off send `[DISP1###1003#]` followed by `[DISP2######cd]` replacing cd with the number of credits, replacing # with spaces in the given examples.

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
