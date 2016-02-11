// Serial communication module
//----------------------------------------------------------------------------------------------------------------

#define   LINE_END              10        // \n
#define   SPLIT                 58        // :

//----------------------------------------------------------------------------------------------------------------

union u_tag {
  byte b[4];
  float fval;
} u; 

//----------------------------------------------------------------------------------------------------------------

void readSerial(){
  if(Serial.available() >= 6)
  {               
    char param = Serial.read(); 
    parameter = param;
    split = Serial.read();
    if(split == SPLIT){
      if(Serial.available() >= 4){
        u.b[0] = Serial.read(); 
        u.b[1] = Serial.read(); 
        u.b[2] = Serial.read(); 
        u.b[3] = Serial.read(); 
        Serial.flush();
        
        switch (param) {
          case '1':
            currentPiState = (int)u.fval;
            break;
        }
      }
    }
  }
} 

//----------------------------------------------------------------------------------------------------------------

void requestStartMusic(){
  // Start music
  Serial.println("1"); 
}

void requestScareSound(){
  Serial.println("2"); 
}

void requestLaughSound(){
  Serial.println("4"); 
}

void requestReset(){
  Serial.println("0"); 
}

void setError_Message(int error){
  
  error_message = error; 
}
