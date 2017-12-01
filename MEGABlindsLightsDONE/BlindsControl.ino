void blindsControl() { // > 108, < 135

if (valueBlinds < 135 && valueBlinds > 108){
  goBlindsRight = true;
  goBlindsLeft = true;
}

  maxPosLeft = !digitalRead(stopButtonLeft);
  if (maxPosLeft){
    goBlindsLeft = false;
  }
//  Serial.print("left");
//  Serial.print(maxPosLeft);
//  Serial.print(" ");
  maxPosRight = !digitalRead(stopButtonRight);
  if (maxPosRight){
    goBlindsRight = false;
  }
//  Serial.print("right");
//  Serial.println(maxPosRight);

// GO RIGHT
  if (valueBlinds < 108 && maxPosRight == 0 && goBlindsRight == true) {
    reverse = false;
    speed = map(valueBlinds, 108, 0, 150, 255);
//    Serial.print("go right");
//    Serial.print("  ");
  }

  else  if (valueBlinds > 135 && maxPosLeft == 0 && goBlindsLeft == true) {
    reverse = true;
    speed = map(valueBlinds, 135, 255, 150, 255);
//    Serial.print("go left");
//    Serial.print("  ");
  }

  else {
    speed = 0;
//    Serial.print("STOP");
//    Serial.print("  ");
  }

//  Serial.println(speed);
//    Serial.print("  ");
  setMotor(speed, reverse);

}

void setMotor(int speed, boolean reverse) {
  analogWrite(PWMSpeed, speed);
  digitalWrite(motorLeft, !reverse);
  digitalWrite(motorRight, reverse);
}

