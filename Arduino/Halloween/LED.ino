int NUMPIXELS = 15;

void flickerDebugLed(long millisec){
  static long lastLedOnTime = 0;
  static bool state = false;

  if(!state && lastLedOnTime + millisec < millis()){
    digitalWrite(13, HIGH);
    state = true;
    lastLedOnTime = millis();
  }else if(state && lastLedOnTime + millisec < millis()){
    digitalWrite(13, LOW);
    state = false;
    lastLedOnTime = millis();
  }
}

void TurnOnDebugLed(){
  digitalWrite(13, HIGH);
}

void TurnOffDebugLed(){
  digitalWrite(13, LOW);
}

void LEDStripFireEffect(bool blue){
  static long lastTime = 0;
  
  if(lastTime + random(10,300) < millis())
  {
    for(int i=0;i<NUMPIXELS;i++){
      if(i > 4){
        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        if(blue){
          pixels.setPixelColor(i, pixels.Color(0,random(0,20),random(160,225))); // Moderately bright green color.
        }else{
          pixels.setPixelColor(i, pixels.Color(random(120,255),random(70,140),0)); // Moderately bright green color.
        }
      }else{
        pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
      }
  
      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    lastTime = millis();
  }
}

void LEDStripRedEyes(){
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    if(i >= 0 && i <= 3){
      pixels.setPixelColor(i, pixels.Color(255,0,0)); // Moderately bright green color.
    }else{
      pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
    }
    pixels.show(); // This sends the updated pixel color to the hardware.

  }
}

void LEDStripLaughEffect(){
  static long lastTime = 0;
  
  if(lastTime + random(10,300) < millis())
  {
    for(int i=0;i<NUMPIXELS;i++){
  
      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,random(0,255),random(0,100))); // Moderately bright green color.

      pixels.show(); // This sends the updated pixel color to the hardware.
    }
    lastTime = millis();
  }
}

