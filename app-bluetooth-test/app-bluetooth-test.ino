/*
This program is for test Poproaster APP.
Please check your bluetooth pin at Arduino board.
*/

#include "SoftwareSerial.h"
SoftwareSerial blueSerial(9, 10); // RX | TX

unsigned long lastTimer = 0; // 主循环中定时循环计时

#define POPROAST

String recvCmd;

void setup()
{
  blueSerial.begin(9600); // Default Baud for comm, it may be different for your Module.  
  blueSerial.println("Bluetooth device is open.");
  Serial.begin(115200);
  Serial.println("Bluetooth device is open.");
}



void loop()
{
  if (millis() - lastTimer >= 2000)
  {
    lastTimer = millis();
    doTimerLoop();
  }
  readBlueSerial();

}

void readBlueSerial() {
  while (blueSerial.available())
  {
    recvCmd = blueSerial.readString();
    Serial.println("##########Receive Command##########");
    Serial.print(recvCmd);
    Serial.println("###################################");
  }
}

void doTimerLoop()
{
  int rand_val = random(0, 250);

#ifdef POPROAST
  // Serial.write(blueSerial.read());
  blueSerial.print("tp1=111\n");
  blueSerial.print("tp2=");
  blueSerial.print(rand_val);
  blueSerial.print("\n");
  blueSerial.print("expect=95\n");
  blueSerial.print("fan=90\n");
  blueSerial.print("pow=80\n");
  // Send to Serial
  Serial.print("tp1=111\n");
  Serial.print("tp2=");
  Serial.print(rand_val);
  Serial.print("\n");
  Serial.print("fan=90\n");
  Serial.print("pow=80\n");
  // Serial.print(Serial.read());
#endif

}
