/*
 * Enter a morse code using the 3 buttons and enjoy the light from the diode.
 * created: 16.Aug.2019
 * by: Peter Popov /pjs95/
 * 
 * This idea is to train my beginner skills with Arduino.
 */

#include <millisDelay.h> // A library to help me deal with the delays without stopping the program
#include <string.h> // Library to manage the input string

int pos = 0; //Counter for entering digits to the morseCode array and "spelling" the morse code after.
int clickingTime = 300; //Pressumed time for a click of button

int RXLED = 17; // Pin for the built RX LED
int led = 10; //Pin for my led
   
int dot = 7; //Dot button is connected on pin 7
int dash = 6; //Dash button is connected on pin 6
int space = 5; //Space button is connected on pin 5

millisDelay timerDelay; //Variable for the timer from millisDelay.h library

void setup() 
{
  Serial.begin(9600); //
  pinMode(RXLED, OUTPUT); //Turn RXLED for output
  digitalWrite(RXLED, HIGH); //Turn RXLED off

  pinMode(led, OUTPUT); //Turn led for output
  digitalWrite(led, LOW); //Turn led off

  pinMode(dot, INPUT); //Turn dot for input
  digitalWrite(dot, HIGH); //Turn dot with digital 1 which means 5v for SparkFun Pro Micro (Arduino Leonardo Clone). HIGH is pre-defined to be 1
  
  pinMode(dash, INPUT); //Turn dash for input
  digitalWrite(dash, HIGH); //Turn dash HIGH
  
  pinMode(space, INPUT); //Turn space for input
  digitalWrite(space, HIGH); //Turn space HIGH

}

void loop() 
{
  digitalWrite(RXLED, LOW); //Turn RXLED on
  timerDelay.start(5000); //Start the timer for counting 5 seconds
  
  char morseCode[128] = "";//This is was the first code which was running without entering anything. // = { '-', '-', ' '}; //".... . .-.. .-.. --- / .-- --- .-. .-.. -.. -.-.--"; //Hello world!
  bool timerCheck = false; //Variable to check if the timer has stopped/seconds have elapsed.
  
  while(!timerCheck) //have not stopped
  {
    timerCheck = timerDelay.justFinished(); //Check if timer just finished
    Serial.println("Debug"); //Print "Debug" on the serial monitor
    if((digitalRead(dot)&digitalRead(dash)&digitalRead(space)) == 0) //If a button is clicked
    {
      timerDelay.stop(); //Stop the timer
      timerDelay.start(5000); //And start it again
      if (digitalRead(dot) == 0) //Check if the dot button is pressed
      {
        Serial.println('.'); //Print on the serial montor that a dot is entered to the array
        morseCode[pos++] = '.'; //Add a dot to the array
        delay(clickingTime); //Wait the pressumed clickingTime to enter
      }
      else if(digitalRead(dash) == 0) //Check if the dot button is pressed
      {
        Serial.println('-'); //Print on the serial montor that a dash is entered to the array
        morseCode[pos++] = '-'; //Add a dash to the array
        delay(clickingTime); //Wait the pressumed clickingTime to enter
      }
      else if(digitalRead(space) == 0) //Check if the dot button is pressed
      {
        delay(clickingTime); //Wait the pressumed clickingTime to enter
        if(digitalRead(space) == 0) //And now check if the dot button is held for twice the clicking time to enter a doubled space
        {
          Serial.println('/'); //Print on the serial montor that a slash is entered to the array
          morseCode[pos++] = '/'; //Add a slash to the array
          delay(clickingTime); //Wait the pressumed clickingTime to enter
        }
        else //if space button is not held to enter a slash
        {
          Serial.println(' '); //Print on the serial montor that a space is entered to the array
          morseCode[pos++] = ' '; //Add a space to the array
        }
      }
    }
    else
    {
    Serial.println("world"); //Just a debuging word to check if the code runs OK
    }
  }
  
  lightf(morseCode); //Call the light function which will "spell" the collected chars
}

void lightf (char morseCode[128])
{
  short morseUnit = 256; //The speed for the light to flicker
  digitalWrite(RXLED, HIGH); //Turn off the RXLED
  Serial.println(); 
  Serial.println("Morse code:");
  Serial.println();
  
  for (int j = 0; j < pos; j++) //Start a for cycle to print every character added according to pos counter
  {
    if (morseCode[j] == '.')
    {
      Serial.print(morseCode[j]); //Print '.'
      digitalWrite(led, HIGH); //Turn led on
      delay(morseUnit); //Wait ms specified on the top of function
      digitalWrite(led, LOW); //Turn led off
      delay(morseUnit); //Wait ms specified on the top of function
    }
    else if (morseCode[j] == ' ')
    {
      Serial.print(morseCode[j]); //Print ' '
      delay(2*morseUnit); //Wait 2 morse units
    }
    else if (morseCode[j] == '/')
    {
      Serial.print(morseCode[j]); //Print '/'
      delay(3*morseUnit); //Wait 3 morse units
    }
    else if (morseCode[j] == '-')
    {
      Serial.print(morseCode[j]); // Print '-'
      digitalWrite(led, HIGH); //Turn led on
      delay(3*morseUnit); //Wait 3 morse units
      digitalWrite(led, LOW); //Turn led off
      delay(morseUnit); //Wait 1 morse unit
    }
  }
  Serial.println();
  pos = 0; //reset the position counter to begin the new input of morse characters
}
