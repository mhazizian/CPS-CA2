// #include <Arduino.h>




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

// #include <Arduino.h>

// float tempC;
// int reading;
// int tempPin = A1;

// void setup()
// {
// analogReference(INTERNAL);
// Serial.begin(9600);
// }

// void loop()
// {
// reading = analogRead(tempPin);
// tempC = reading / 9.31;
// Serial.println(tempC);
// delay(100);
// }




#include <Arduino.h>

#define END_OF_LINE '$'
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
    Serial.print('#');
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