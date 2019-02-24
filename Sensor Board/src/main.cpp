#include <Arduino.h>

#define END_OF_LINE '$'
#define DATA_DELIMITER '#'

const int TempPin = A1;
const int UltraSonicPingPin = 7;
const int UltraSonicEchoPin = 6;

long  inches, cm;
float tempC;

long microsecondsToInches(long microseconds)
{
    return microseconds / 74.0 / 2.0 + 0.5;
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds / 29.0 / 2.0 + 0.5;
}

void setup()
{
    pinMode(UltraSonicEchoPin, INPUT);
    pinMode(UltraSonicPingPin, OUTPUT);
    analogReference(INTERNAL);
    Serial.begin(9600);
    
}

void createUSPulse() {
    digitalWrite(UltraSonicPingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(UltraSonicPingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(UltraSonicPingPin, LOW);
}

void detemineDistance() {
    long duration = pulseIn(UltraSonicEchoPin, HIGH);
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
}

void printResult() {
    Serial.print(cm);
    Serial.print(DATA_DELIMITER);
    Serial.print(tempC);
    Serial.print(END_OF_LINE);
}

void calculateTemp() {
    tempC = analogRead(TempPin) / 9.31;
}

void loop()
{
    createUSPulse();
    detemineDistance();
    calculateTemp();

    printResult();
    delay(100);
}