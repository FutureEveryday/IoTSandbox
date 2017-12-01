void updateEncoder() {

  encValue = myEnc.read();
  if (encValue != oldPosition) {
    oldPosition = encValue;
  }

//if (encValue < 0){
//  myEnc.write(0);
//  }
//  if (encValue > 255){
//    myEnc.write(255);
//  }

encValue = constrain(encValue, 0, 242);
myEnc.write(encValue);
}
