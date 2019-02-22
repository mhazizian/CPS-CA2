#include <Arduino.h>
#include <Wire.h>
#include <math.h>

#define ON 1

const int SCLPin = A5;
const int SDAPin = A4;
const int UTSensorAddress = 110;

const byte onOffSensorReg = 0;
const byte xDataReg[] = {10, 11, 12, 13};
const byte yDataReg[] = {40, 41, 42, 43};
char receivedData[4];

double result;


void turnOnSensor() {
    Wire.begin();
    Wire.beginTransmission(UTSensorAddress);
    Wire.write(onOffSensorReg); 
    Wire.write(ON);
    Wire.endTransmission();
}

char readData(int regNum) {
    Wire.beginTransmission(UTSensorAddress);
    Wire.write(regNum);
    Wire.endTransmission();
    Wire.requestFrom(UTSensorAddress, 1);
    return Wire.read();
}

float charToFloat() {
    float f;
    memcpy(&f, &receivedData, sizeof(f));
    return f;
}

void printCoordinateToSerial(float x, float y) {
    Serial.print("Data: "); 
    Serial.print(x); 
    Serial.print(", "); 
    Serial.print(y);
    Serial.print(", current result: "); 
    Serial.println(result);
}

void setup() {
    turnOnSensor();
    result = 0;
    Serial.begin(9600);
}

void loop() {
    for (int i = 0; i < 4; i++)
        receivedData[i] = readData(xDataReg[i]);

    float xData = charToFloat(); 

    for (int i = 0; i < 4; i++)
        receivedData[i] = readData(yDataReg[i]);

    float yData = charToFloat();
    result += pow(2, xData * xData) + yData;

    printCoordinateToSerial(xData, yData);
    delay(100);
}