void blindsControl() { // > 108, < 135

  maxPosLeft = digitalRead(52);               // digitalRead(stopButtonLeft);
  maxPosRight = digitalRead(53);              // digitalRead(stopButtonRight);

  if (valueBlinds < 108 && maxPosRight == 0) {
    reverse = true;
    speed = map(valueBlinds, 108, 0, 50, 255);
//    Serial.print("go right");
//    Serial.print("  ");
  }

  else  if (valueBlinds > 135 && maxPosLeft == 0) {
    reverse = false;
    speed = map(valueBlinds, 135, 255, 50, 255);
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

