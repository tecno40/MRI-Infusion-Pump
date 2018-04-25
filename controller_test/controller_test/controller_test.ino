#include <SoftwareSerial.h>

SoftwareSerial mriController(4, 5); // RX, TX

int flowRate=0;
String movementCode;
boolean pumpStart=false;

void setup() {
  //start communications with USB serial to check for errors
  Serial.begin(57600);
  while (!Serial) {}
  Serial.println("Starting MRI Test");

  // set the data rate for the SoftwareSerial port
  mriController.begin(115200);
  pinMode(3, OUTPUT); 

  //unpark the motor
  digitalWrite(3, HIGH);
  delay(500);
  mriController.print("XM2\r");
  Serial.print("XM2\r");
  delay(500);
  digitalWrite(3, LOW);

}

void createMovementCode()
{
  double stepsPerSecond=0;
  
  stepsPerSecond=(double)flowRate*9.696277
  movementCode="XJ"+String(stepsPerSecond)+",0,"+String(stepsPerSecond)+"\r";
}

void movePump()
{
    digitalWrite(3, HIGH);
    delay(50);
    mriController.print(movementCode);
    Serial.print(movementCode);
    delay(50);
    digitalWrite(3, LOW);
}

void loop() 
{
  if (pumpStart)
  {
    movePump();
    delay(900);
  }
  else
  {
    
  }
}



/*
  // send data only when you receive data:
        if (mriController.available() > 0) {
                // read the incoming byte:
                incomingByte = mriController.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        }*/
