//################################################################
//# Dragon's Lair Scoreboard Adaptor
//# Target Board : Arduino Nano 5v
//# Arduino IDE : 1.8.10
//# Version : 1.0
//# Date : 28th November 2019
//# Jonathon Harris 
//#
//# WARNING - I HAVE NOT YET TESTED THIS CODE! TRY AT YOUR OWN RISK, I AM NOT LIABLE FOR ANY DAMAGE OR HARM THAT MAY COME AS A RESULT
//# NO WARRANTY IS OFFERED OR IMPLIED UNDER ANY CIRCUMSTANCE!
//################################################################
//# ICM7218 Interfacing Code
//# Some of the code is based upon the Scoreboard Testing code posted at https://www.daphne-emu.com:9443/phpBB2/viewtopic.php?f=2&t=3135
//# It is however apparent that this code was based upon code found at http://ardugonic.blogspot.com/2010/05/driving-8-digits-7-segment-display-with.html
//# Just want to give credit where credit is due.
//################################################################

//################################################################
//# Main Scoreboard Comms Protocol
//# Send [DISP1######ab] replace # with player 1 score data, a for P1 lives, b for p2 lives
//# Send [DISP2######cd] replace # with player 2 score data, cd for credits
//# Send [SKILL#a] replace # with 1 for easy mode, 2 for medium mode, 3 for hard mode - replace a with 0 for off, 1 for on.
//################################################################



//#################################################################
//# Definitions, Variables, Constants
//#################################################################

const int SerialBaudRate = 9600; //Serial Baud Rate can be adjusted here rather than in the main code.

//Assigning Pin Numbers
const int OutputDEN1 = 10; //Connect to Scoreboard Pin 8
const int OutputDEN2 = 11; //Connect to Scoreboard Pin 9
const int OutputDA0 = 9; //Connect to Scoreboard Pin 7
const int OutputDA1 = 8; //Connect to Scoreboard Pin 6
const int OutputDA2 = 7; //Connect to Scoreboard Pin 5
const int OutputDD0 = 6; //Connect to Scoreboard Pin 4
const int OutputDD1 = 5; //Connect to Scoreboard Pin 3
const int OutputDD2 = 4; //Connect to Scoreboard Pin 2
const int OutputDD3 = 3; //Connect to Scoreboard Pin 1
const int SkillEasy = A2; //Connect to the Easy Skill Light
const int SkillMedium = A1; //Connect to the Medium Skill Light
const int SkillHard = A0; //Connect to the Hard Skill Light

int SkillLevel = 0;
int SkillState = 0;

String LEDDriver1Display = "";
String LEDDriver2Display = "";
String SerialPortBuffer = "";
String VersionIdentifier = "[VERSION1.00]";




void setup() {

//Enable Serial Port for Communications
Serial.begin(SerialBaudRate); //Enabled on pins 0 and 1.

  
//Configure Pin Modes
pinMode(OutputDEN1,OUTPUT);
pinMode(OutputDEN2,OUTPUT);
pinMode(OutputDA0,OUTPUT);
pinMode(OutputDA1,OUTPUT);
pinMode(OutputDA2,OUTPUT);
pinMode(OutputDD0,OUTPUT);
pinMode(OutputDD1,OUTPUT);
pinMode(OutputDD2,OUTPUT);
pinMode(OutputDD3,OUTPUT);
pinMode(SkillEasy,OUTPUT);
pinMode(SkillMedium,OUTPUT);
pinMode(SkillHard,OUTPUT);

//Set all pins low
digitalWrite(OutputDEN1,LOW);
digitalWrite(OutputDEN2,LOW);
digitalWrite(OutputDA0,LOW);
digitalWrite(OutputDA1,LOW);
digitalWrite(OutputDA2,LOW);
digitalWrite(OutputDD0,LOW);
digitalWrite(OutputDD1,LOW);
digitalWrite(OutputDD2,LOW);
digitalWrite(OutputDD3,LOW);
digitalWrite(SkillEasy,LOW);
digitalWrite(SkillMedium,LOW);
digitalWrite(SkillHard,LOW);


}

void loop() {
//There is no code within "loop" as all routines are automatically called by sending serial data.
}

//#################################################################
//# SKILL LIGHT CONTROLS
//#################################################################

void SkillLights(int Level, int State)
{
 if (Level == 1 && State == 0)
  {
    digitalWrite(SkillEasy, LOW); 
  }
 if (Level == 1 && State == 1)
  {
    digitalWrite(SkillEasy, HIGH); 
  }
  
 if (Level == 2 && State == 0) 
  {
    digitalWrite(SkillMedium, LOW); 
  }
 
 if (Level == 2 && State == 1)
  {
    digitalWrite(SkillMedium, HIGH); 
  }
  
 if (Level == 3 && State == 0)
  {
     digitalWrite(SkillHard, LOW);
  }
  
 if (Level == 3 && State == 1)
  {
    digitalWrite(SkillHard, HIGH); 
  }
}

//###################################################################################################################################################################
//# ICM7218D INTERFACE ROUTINES
//###################################################################################################################################################################

//################################################
//# WRITE CONTROL WORD
//################################################
void UpdateDisplay(int DisplayToUpdate)
{
  if (DisplayToUpdate == 1)
  {
    //Write CONTROL WORD first

  digitalWrite(OutputDEN1,HIGH); //Set WRITE high
  delay(1);
  digitalWrite(OutputDEN1,LOW); //Set WRITE low 
  delay(1);
  //Send 8 Digits

  for (int Counter = 0; Counter <= 7; Counter ++) //for 0 to 7
    {
      writeDigit(Counter,LEDDriver1Display[Counter],DisplayToUpdate);  
    }

  }

if (DisplayToUpdate == 2)
  {
    //Write CONTROL WORD first

  digitalWrite(OutputDEN2,HIGH); //Set WRITE high
  delay(1);
  digitalWrite(OutputDEN2,LOW); //Set WRITE low 
  delay(1);
  //Send 8 Digits

  for (int Counter = 0; Counter <= 7; Counter ++) //for 0 to 7
    {
      writeDigit(Counter,LEDDriver2Display[Counter],DisplayToUpdate);  
    }

  }











  
}
  


//#########################################################################
//# Send the 8 digits
//#########################################################################


void writeDigit(byte address, byte data, int DisplayToUpdate)
{


  
//set digit address
digitalWrite(OutputDA0, B00000001 & address);
digitalWrite(OutputDA1, B00000010 & address);
digitalWrite(OutputDA2, B00000100 & address);

delay(1);
if (DisplayToUpdate == 1)
{
  digitalWrite(OutputDEN1, LOW);
}
if (DisplayToUpdate == 2)
{
  digitalWrite(OutputDEN2, LOW);
}

delay(1);

// I'm using CodeB, so I only need the 4 least significant pins
digitalWrite(OutputDD0, B00000001 & data);
digitalWrite(OutputDD1, B00000010 & data);
digitalWrite(OutputDD2, B00000100 & data);
digitalWrite(OutputDD3, B00001000 & data);

delay(1);

if (DisplayToUpdate == 1)
{
  digitalWrite(OutputDEN1, HIGH);
}
if (DisplayToUpdate == 2)
{
  digitalWrite(OutputDEN2, HIGH);
}

delay(1);
}


//##########################################################################################################################################
//# Serial Communications
//##########################################################################################################################################



void serialEvent()
{
  //Parse the incoming data.
   if ( Serial.available() )
   {
    SerialPortBuffer = Serial.readStringUntil('[');
    SerialPortBuffer = "";
    SerialPortBuffer = Serial.readStringUntil(']');
    
    if (SerialPortBuffer ==  "DAPHNE?")    
      {
        Serial.print("[SAVEME!]");
      }

    if (SerialPortBuffer ==  "VERSION?")    
      {
        Serial.print(VersionIdentifier);
      }    
        // UPDATING THE 1ST DISPLAY
        if (SerialPortBuffer[4] == '1')
            {
            LEDDriver1Display = "";
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[5];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[6];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[7];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[8];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[9];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[10];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[11];
            LEDDriver1Display = LEDDriver1Display + SerialPortBuffer[12];
            UpdateDisplay(1);
            }
        
        // UPDATING 2ND DISPLAY
        if ( SerialPortBuffer[4] == '2')
            {
            LEDDriver2Display = "";  
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[5];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[6];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[7];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[8];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[9];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[10];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[11];
            LEDDriver2Display = LEDDriver2Display + SerialPortBuffer[12];
            UpdateDisplay(2);
            }


       // UPDATING SKILL LEVEL LIGHTS     
       if ( SerialPortBuffer[4] == 'L')
            {
              //# Read off Skill Level Being Adjusted
              if (SerialPortBuffer[5] == '1') 
              {
                SkillLevel = 1;
              }
              if (SerialPortBuffer[5] == '2') 
              {
                SkillLevel = 2;
              }
              if (SerialPortBuffer[5] == '3') 
              {
                SkillLevel = 3;
              }

              //# Read off Skill Level Light State
              if (SerialPortBuffer[6] == '0') 
              {
                SkillState = 0;
              }
              if (SerialPortBuffer[6] == '1') 
              {
                SkillState = 1;
              }
              SkillLights(SkillLevel,SkillState);
            }
    SerialPortBuffer = "";
  }
}


//##############################################################################################
//#If you're seeing this then you've spent too much time looking at my code. Go play some games!
//##############################################################################################
