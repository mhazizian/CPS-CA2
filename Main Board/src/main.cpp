#include <Arduino.h>
#include <LiquidCrystal.h>

char distance[10 + 1];
char temperature[10 + 1];
char coordinate[10 + 1]; 

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
    int i = 0;
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    // print the number of seconds since reset:
    if (Serial.available()) {
        delay(100); //allows all serial sent to be received together
        while(Serial.available() && i < 10) {
            char c = Serial.read();
            if (c == '#')
                break;
            distance[i++] = c;

        }
        distance[i] = '\0';
        i = 0;
        while(Serial.available() && i < 10)
            temperature[i++] = Serial.read();

        temperature[i] = '\0';
    }
    lcd.setCursor(0, 0);
    lcd.print(distance);
    lcd.setCursor(0, 1);
    lcd.print(temperature);
}