/*
**   _   __               _   _                _      _            
**  | | / /              | | (_)              | |    | |           
**  | |/ / _ __ ___  __ _| |_ ___   ____ _  __| | ___| | __ _ _ __ 
**  |    \| '__/ _ \/ _` | __| \ \ / / _` |/ _` |/ _ \ |/ _` | '__|
**  | |\  \ | |  __/ (_| | |_| |\ V / (_| | (_| |  __/ | (_| | |   
**  \_| \_/_|  \___|\__,_|\__|_| \_/ \__,_|\__,_|\___|_|\__,_|_|   
**                                                                 
**
**  Scary pumpkin using Makeblock modules
**  from Kreativadelar.se, Sweden
**
**  This code is written "quick & dirty" and should not be as a guide
**  in how to program an Arduino. Feel free to change code as you like
**  and share with your friends.
**
**  If you want to share your code changes, please e-mail them to
**  info@kreativadelar.se and we will put them on our web for other
**  customers to download.
**
**  (C) Kreativadelar.se 2015, Sweden, Patrik
**  http://www.kreativadelar.se
**
**  To use this code you need the following libraries: 
**  
**  Adafruit NeoPixel which can be
**  downloaded free from https://github.com/adafruit/Adafruit_NeoPixel
**
**  Version 1.0, Initial public release, July 2015
**
**  This example code is in the public domain.
**
*/

#include <Adafruit_NeoPixel.h>

char parameter = ' ';
byte split = 0;
int serialCount = 0;
int currentState = 0; // 0:Idle, 1:Music started, 2:LED and wait, 3:Scare, 4: Scare done, 5: Laugh done 6: Reseted
int currentPiState = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(15, 3, NEO_GRB + NEO_KHZ800);

/********************************************
 * Setup 
 ********************************************/
void setup() {
  Serial.begin(9600); 
  setError_Message(1);  
  //Started up messge to the GUI
  Serial.println("start");
  pinMode(A1, INPUT);
  pinMode(13, OUTPUT);

  // Reset state engine
  currentState = 0;
  requestReset();

  pixels.begin(); // This initializes the NeoPixel library.
}

/********************************************
 * Loop
 ********************************************/
void loop() {
  
  // ********************* print Debug info *******************************
  readSerial();

  currentState = StateEngine(currentState);
}
