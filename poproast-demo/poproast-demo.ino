#include <Adafruit_MAX31855.h>
#include <SoftwareSerial.h>

#define VERSION "0413-1" // version number
#define POPROAST
//#define DEBUG

// Define temperature sensor pin. Use MAX31855, analog pin
int thermoCLK = 3; //analog pin
int thermoCS = 4;  //analog pin
int thermoDO = 5;  //analog pin
// Define Bluetooth module HC-02/HC-05/HC-06 
SoftwareSerial blueSerial(9, 10); // RX | TX

Adafruit_MAX31855 readtp1(thermoCLK, thermoCS, thermoDO);

unsigned long lastTimer = 0; // Timer in main loop
String recvCmd;
int temp; // Temperature in Celsius

void setup()
{
    blueSerial.begin(9600); // Default Baud for comm, it may be different for your Module.
    blueSerial.println("Bluetooth device is open.");
    Serial.begin(115200);
    Serial.println("Bluetooth device is open.");
}

void loop() {
    if (millis() - lastTimer >= 500)
    {
        lastTimer = millis();
        doTimerLoop();
    }
    readBlueSerial();
}

void doTimerLoop() {
    temp = readtp1.readCelsius();
    temp = 101;
    serialSend();
    blueSerialSend();
}

void blueSerialSend()
{
    #ifdef POPROAST
        // send data to app
        blueSerial.print("tp1=");
        blueSerial.println(temp);
    #endif //for POPROAST
}

void serialSend() {
    #ifdef POPROAST
        // send data to app
        Serial.print("tp1=");
        Serial.println(temp);
    #endif //for POPROAST
}

void readBlueSerial()
{
    while (blueSerial.available())
    {
        recvCmd = blueSerial.readString();
        Serial.println("##########Receive Command##########");
        Serial.print(recvCmd);
        Serial.println("###################################");
    }
}