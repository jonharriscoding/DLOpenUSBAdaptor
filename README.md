# DLOpenUSBAdaptor
An Open Version of a USB / Serial Adaptor to Communicate with Dragon's Lair, Space Ace &amp; Thayer's Quest Scoreboard Units

THE MAIN GOAL (Dec 26th, 2019)

The idea here is to use an Arduino Uno or Compatable to create a USB Serial Interface for the Scoreboard Unit to the Dragon's Lair Laserdisc Arcade game, and implement a simple serial protocol to allow communication by the Daphne Emulator - However, I don't have the skill set needed to add the changes to Daphne. 

So, I'm hoping once I make this adaptor from the Arduino, support can be implemented into the Daphne Emulator by others.

For now, I'm just setting up the repository with information and I expect to be tinkering on December 30th 2019 through Jan 1st 2020 and getting the connection schematic up.


# Some Initial Stuff

# Skill LEDs
This is to support the Skill Light Indicator that was present on Space Ace Cabinets
These are currently planned to be ACTIVE HIGH signals. If using own LEDs, you will need to calculate the resistance value for each LED's resistor to avoid the Arduino Popping your LEDs!

# Baud Rate
Until I get this project going with more traction, i'm going to leave this at 9600bps for testing. Once debugging is done, this can be amended.

# Hey, I'm here!
I plan on having the adaptor give a return signal to confirm that a connection has been made to the correct serial port. 

# Serial Protocol
There will need to be a command system to allow the segments to be controlled by emulators, plus the Skill Lights.
