PImage bg;

import processing.serial.*;

// The Serial ports
Serial Interface1;
//Serial Interface2;
//Serial Interface3;
Serial House;

byte[] inBuffer;

String totalInputs[] = {"Interface1", "Interface2", "Interface3"};
String output[] = {"House"};
int connections[] = {-1, -1, -1};

int windowWidth = 480;
int windowHeight = 320;

int buttonSizeX = 70;
int buttonSizeY = 50;
int buttonOriginInterfaceX = windowWidth/5;
int buttonOriginInterfaceY = windowHeight/4;
int buttonOriginHouseX = windowWidth/5*4;
int buttonOriginHouseY = windowHeight/2;
int buttonDistance = (windowHeight - 2 * buttonOriginInterfaceY)/2;

int mouseOrigin = 4;
boolean mouseIn = true;
boolean firstTime = true;
boolean interface1Over = false;
boolean interface2Over = false;
boolean interface3Over = false;
boolean overbutton = false;
boolean houseOver = false;

void setup() {
  size(480, 320);
  noStroke();
  bg = loadImage("GreyBackground.jpg");
  frameRate(60);
  printArray(Serial.list());

  Interface1 = new Serial(this, Serial.list()[0], 115200);
  //Interface2 = new Serial(this, Serial.list()[1], 115200);
  //Interface3 = new Serial(this, Serial.list()[2], 115200);
  //House = new Serial(this, Serial.list()[3], 115200);
}

void draw() {
  background(bg); // set a background for the application (image is also 480x320 pixels)

  inBuffer = new byte[20];
  if (connections[0] == 1){
    inBuffer = Interface1.readBytes();
    Interface1.readBytes(inBuffer);
    }
    //if (connections[1] == 1){
    //inBuffer = Interface2.readBytes();
    //Interface2.readBytes(inBuffer);
    //}
    //if (connections[2] == 1){
    //inBuffer = Interface3.readBytes();
    //Interface3.readBytes(inBuffer);
    //}
    if (inBuffer != null) {
      String myString = new String(inBuffer);
      println(myString);
      //House.write(myString);
  }

  // drawing of the input buttons
  for (int i = 0; i < totalInputs.length; i++) {
    noStroke();
    //if (interface1Over || connections[0] == 1) {
    if (connections[0] == 1 || mouseOrigin == 0) {
      fill(100);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
      fill(200);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+i*buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
    }
    //if (interface2Over || connections[1] == 1) {
    if (connections[1] == 1 || mouseOrigin == 1) {
      fill(100);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
      fill(200);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+i*buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
    }
    //if (interface3Over || connections[2] == 1) {
    if (connections[2] == 1 || mouseOrigin == 2) {
      fill(100);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+2*buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
      fill(200);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
    } else {
      fill(200);
      rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+i*buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
    }
    //else if (overbutton == false) {
    //  fill(200);
    //  rect(buttonOriginInterfaceX-buttonSizeX/2, buttonOriginInterfaceY+i*buttonDistance-buttonSizeY/2, buttonSizeX, buttonSizeY, 5);
    //}
  }

  // text displayed at each interface
  noStroke();
  fill(200);
  textSize(15);
  textAlign(CENTER);
  text("INTERFACE1", buttonOriginInterfaceX, buttonOriginInterfaceY-30);
  text("INTERFACE2", buttonOriginInterfaceX, buttonOriginInterfaceY-30+(windowHeight/4));
  text("INTERFACE3", buttonOriginInterfaceX, buttonOriginInterfaceY-30+(windowHeight/2));

  // output button
  noStroke();
  if (connections[0] == 1 || connections[1] == 1 || connections[2] == 1) {
    fill(100);
  } else {
    fill(200);
  }
  ellipse(buttonOriginHouseX, buttonOriginHouseY, 50, 50);

  noStroke();
  fill(200);
  textSize(15);
  textAlign(CENTER);
  text("HOUSE", buttonOriginHouseX, buttonOriginHouseY-30);

  //reset button
  noStroke();
  fill(255, 0, 0);
  ellipse(windowWidth/2, (windowHeight/15)*14, 24, 24);
  noStroke();
  fill(255, 0, 0);
  textSize(15);
  textAlign(CENTER);
  text("RESET", windowWidth/2, (windowHeight/15)*13);

  // when a connection has been made, this piece displays the line
  for (int i = 0; i<connections.length; i ++) {
    //draw line from input to output
    if (connections[i] != -1) {
      stroke(255);
      line(buttonOriginInterfaceX, buttonOriginInterfaceY+i*buttonDistance, buttonOriginHouseX, buttonOriginHouseY);
    } else {
      fill(0);
    }
  }

  for (int i = 0; i<totalInputs.length; i++) {
    if (mouseX < buttonOriginInterfaceX-buttonSizeX/2 && mouseX > buttonOriginInterfaceX+buttonSizeX/2 && mouseY > buttonOriginInterfaceY+buttonSizeY/2+i*buttonDistance && mouseY < buttonOriginInterfaceY-buttonSizeY/2+i*buttonDistance) {
      println("I can feel you inside of me");
    }
  }
}

void mouseMoved() {
  for (int i = 0; i<totalInputs.length; i++) {
    if (mouseX > buttonOriginInterfaceX-buttonSizeX/2 && mouseX < buttonOriginInterfaceX+buttonSizeX/2 && mouseY < buttonOriginInterfaceY+buttonSizeY/2+i*buttonDistance && mouseY>buttonOriginInterfaceY-buttonSizeY/2+i*buttonDistance) {
      println("hover is true");
    } else {
      println("hover is false");
      overbutton = false;
      interface1Over = false;
      interface2Over = false;
      interface3Over = false;
    }
  } // 540 = windowWidth/3-halfButtonSize
  if (mouseX > buttonOriginInterfaceX-buttonSizeX/2 && mouseX < buttonOriginInterfaceX+buttonSizeX/2 && mouseY < buttonOriginInterfaceY+buttonSizeY/2 && mouseY>buttonOriginInterfaceY-buttonSizeY/2) {
    overbutton = true;
    interface1Over = true;
    interface2Over = false;
    interface3Over = false;
    println("1 over");
  }
  if (mouseX > buttonOriginInterfaceX-buttonSizeX/2 && mouseX < buttonOriginInterfaceX+buttonSizeX/2 && mouseY < buttonOriginInterfaceY+buttonSizeY/2+buttonDistance && mouseY>buttonOriginInterfaceY-buttonSizeY/2+buttonDistance) {
    overbutton = true;
    interface1Over = false;
    interface2Over = true;
    interface3Over = false;
    println("2 over");
  }
  if (mouseX > buttonOriginInterfaceX-buttonSizeX/2 && mouseX < buttonOriginInterfaceX+buttonSizeX/2 && mouseY < buttonOriginInterfaceY+buttonSizeY/2+2*buttonDistance && mouseY>buttonOriginInterfaceY-buttonSizeY/2+2*buttonDistance) {
    overbutton = true;
    interface1Over = false;
    interface2Over = false;
    interface3Over = true;
    println("3 over");
  }
  if (mouseX > buttonOriginHouseX-buttonSizeX/2 && mouseX < buttonOriginHouseX+buttonSizeX/2 && mouseY< buttonOriginHouseY+buttonSizeY/2 && mouseY > buttonOriginHouseY-buttonSizeY/2) {
    houseOver = true;
  } else {
    houseOver = false;
  }
}

void mousePressed() {
  for (int i = 0; i<totalInputs.length; i++) {
    if (mouseX > buttonOriginInterfaceX-buttonSizeX/2 && mouseX < buttonOriginInterfaceX+buttonSizeX/2 && mouseY < buttonOriginInterfaceY+buttonSizeY/2+i*buttonDistance && mouseY>buttonOriginInterfaceY-buttonSizeY/2+i*buttonDistance) {
      reset();
      mouseOrigin = i;
      mouseIn = true;
      println("stop TOUCHING ME!");
    }
  }
  for (int i = 0; i<totalInputs.length; i++) {
    if (mouseX > (windowWidth/2-12) && mouseX < (windowWidth/2+12) && mouseY > ((windowHeight/15*14)-12) && mouseY < ((windowHeight/15*14)+12) ) {
      //reset lines
      reset();
      println("reset true");
    }
  }
}

void mouseDragged() {
  if (mouseIn) {
    //drag a line
    for (int i = 0; i < totalInputs.length; i++) {
      if (i == mouseOrigin) {
        strokeWeight(4);
        line(buttonOriginInterfaceX, buttonOriginInterfaceY+i*buttonDistance, mouseX, mouseY);
        println("they see me rollin im dragging, them bitches think I am to white and nerdy");
      }
    }
  }
}

void mouseReleased() {
  for (int i = 0; i< output.length; i++) {
    if (mouseX > buttonOriginHouseX-buttonSizeX/2 && mouseX < buttonOriginHouseX+buttonSizeX/2 && mouseY< buttonOriginHouseY+buttonSizeY/2+i*buttonDistance && mouseY > buttonOriginHouseY-buttonSizeY/2+i*buttonDistance) {
      //connections[mouseOrigin][i] = 1;
      connections[mouseOrigin] = 1;
      println("think I'm just too white and nerdy");
    }
  }
  mouseIn = false;
}

void reset() {
  for (int i = 0; i < connections.length; i++) {
    //for (int j = 0; j < connections.length; j ++) {
    connections[i] = -1;
  }
  mouseOrigin = 4;
  //}
  println("Reset Press");
}