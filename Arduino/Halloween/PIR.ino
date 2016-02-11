bool ReadPIRSendor(){
  if(digitalRead(A1) == HIGH){
    return true;
  }

  return false;
}

