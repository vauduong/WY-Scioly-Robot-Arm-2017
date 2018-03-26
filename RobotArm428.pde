import processing.serial.*;

// The serial port:
Serial mySerialPort;       


color fillVal = color(0);

void setup() {
  size(100, 100);
  noStroke();
  background(0);
  printArray(Serial.list()); // do this to find your arduino
  // Open the port you are using at the rate you want:
  mySerialPort = new Serial(this, Serial.list()[2], 115200);
  mySerialPort.clear();
}

void draw() { 
  background(fillVal);
}

//The keyPressed() function is called once every time a key is pressed.
// see https://processing.org/reference/keyCode.html

void keyPressed() {
  if (key == 'q') {
    mySerialPort.write('q');
  } 
  if (key == 'a') {
    mySerialPort.write('a');
  } 
  if (key == 'd') {
    mySerialPort.write('d');
  } 
  if (key == 'w') {
    mySerialPort.write('w');
  } 
  if (key == 's') {
    mySerialPort.write('s');
  } 
  if (key == 'r') {
    mySerialPort.write('r');
  } 
  if (key == 'f') {
    mySerialPort.write('f');
  }
  else{
    mySerialPort.write('q');
  }  
}
void keyReleased(){
  mySerialPort.write('q');
}

void serialEvent(Serial p) {
  switch(p.read()) {
  case 'A':
    fillVal = #FFE5B4;
    break;
  case 'D':
    fillVal = #FFE5B4;
    break;
  case 'W':
    fillVal = #FFFFFF;
    break;
  case 'S':
    fillVal = #FF2400;
    break;
  case 'R':
    fillVal = #FF0000;
    break;
  case 'F':
    fillVal = #FF00FF;
    break;
  case 'B':
    fillVal = #000000;
    break;
  default: 
    fillVal = #000000;
    break;
  }
} 