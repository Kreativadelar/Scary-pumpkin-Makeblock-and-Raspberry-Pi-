bool debug = false;

// Idle
// Waiting for detection
int State0(){
  static long lastTime = 0;
  static bool detected = false;
  static int detectCount = 0;
  
  if(ReadPIRSendor() && !detected){
     lastTime = millis();
     detected = true;
     detectCount++;
     if(debug) Serial.println("Detekterat rörelse");
  }else if(detectCount > 0){//(lastTime + 2000 < millis() && detected){
     if(debug) Serial.println("requestStartMusic : 1");
     requestStartMusic();
     lastTime = 0;
     detectCount = 0;
    detected = false;
     return 1;
  }else if(!ReadPIRSendor()){
    lastTime = 0;
    detected = false;

    LEDStripFireEffect(false);
  }

  return 0;
}

// Music started
// Waiting for confirmation that music started
int State1(){
  static long lastTime = 0;

  if(lastTime == 0) lastTime = millis();
  // Check that sound started
  if(currentPiState == 1 || lastTime + 20000 < millis()){
    if(debug) Serial.println("Sound started");
    return 2;
  }else{
    LEDStripFireEffect(false);
  }

  return 1;
}

// LED and wait
// Wait that music has played a sertent time and
// turn on LED stripe
int State2(){
  static long lastTime = 0;

  if(lastTime == 0) lastTime = millis();

  if(lastTime + 2000 < millis()){
     if(debug) Serial.println("requestScareSound : 3");
     requestScareSound();
     lastTime = 0;
     return 3;
  }else{
    // LED Strip blue fire effect
    LEDStripFireEffect(true);
    flickerDebugLed(200);
  }
  return 2;
}

// Scare
// Wait for scare sound and then turn on red eyes 
int State3(){
  static long lastTime = 0;

  if(lastTime == 0) lastTime = millis();
  
  if(currentPiState == 3 || lastTime + 20000 < millis()){
    //Turn on red lights
    if(debug) Serial.println("Turn on red lights : 4");
    TurnOnDebugLed();
    LEDStripRedEyes();
    return 4;
  }else{
    // LED Strip blue fire effect
    LEDStripFireEffect(true);
    flickerDebugLed(200);
  }
  
  return 3;
}

// Scare done
// Wait that scare sound ends and start laugh sound
int State4(){
  static long lastTime = 0;

  if(lastTime == 0) lastTime = millis();
  
  if(currentPiState == 4 && lastTime + 3500 < millis()){
    if(debug) Serial.println("requestLaughSound : 5");
    TurnOffDebugLed();
    requestLaughSound();
    return 5;
  }
  return 4;
}

// Laugh done
// Waiting for laugh to be done and turn of led strip
int State5(){
  static long lastTime = 0;

  if(lastTime == 0) lastTime = millis();
  
  if(currentPiState == 5 && lastTime + 15000 < millis()){
    if(debug) Serial.println("requestReset : 0");
    requestReset();
    TurnOffDebugLed();
    return 6;
  }else{
    // LED flicker when laughing 
    LEDStripLaughEffect();
    flickerDebugLed(500);
  }
  return 5;
}

// Reseted
// Wait for the pi to reset
int State6(){
  if(currentPiState == 0){
    return 0;
  }else{
    // LED flicker when laughing 
    LEDStripLaughEffect();
    flickerDebugLed(500);
  }
  return 6;
}

int StateEngine(int state){
  if(state == 0){
    return State0();
  }else if(state == 1){
    return State1();
  }else if(state == 2){
    return State2();
  }else if(state == 3){
    return State3();
  }else if(state == 4){
    return State4();
  }else if(state == 5){
    return State5();
  }else if(state == 6){
    return State6();
  }
}
