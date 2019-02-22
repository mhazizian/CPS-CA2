// #include <Arduino.h>
// // #include <LM35.h>
// const int TempPin = A0;


// // LM35 temperature(TempPin);

// void setup() {
//     Serial.begin(9600);
// }

// void loop() {
//     // Serial.println(temperature.cel());
//     int tempValue = analogRead(TempPin);
//     float tempCel = (tempValue / 1024.0) * 500;

//     Serial.print("#");
//     Serial.println(tempValue);

//     Serial.println(tempCel);

//     delay(100);
// }




#include <Arduino.h>
const int UltraSonicPingPin = 7;
const int UltraSonicEchoPin = 6; // Echo Pin of Ultrasonic Sensor

long  inches, cm;

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
    // Serial.print("Distance: ");
    // Serial.print(inches);
    // Serial.print("in, ");
    Serial.print(cm);
    Serial.println("#33");
}

void loop()
{
    createUSPulse();
    detemineDistance();

    printResult();
    delay(100);
}