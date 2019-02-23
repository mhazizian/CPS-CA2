#include <Arduino.h>
#include <LiquidCrystal.h>

#define DISTANCE_MAX_CHAR 10
#define TEMPERATURE_MAX_CHAR 10
#define COORDINATE_MAX_CHAR 10

char distance[DISTANCE_MAX_CHAR + 1];
char temperature[TEMPERATURE_MAX_CHAR + 1];
char coordinate[COORDINATE_MAX_CHAR + 1]; 

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
        // delay(100); //allows all serial sent to be received together
        while(i < DISTANCE_MAX_CHAR) {
            if (Serial.available()) {
                char c = Serial.read();
                if (c == '#')
                    break;
                distance[i++] = c;
            }
        }
        distance[i] = '\0';
        i = 0;
        while(i < TEMPERATURE_MAX_CHAR) {
            if (Serial.available()) {
                char c = Serial.read();
                if (c == '$')
                    break;
                temperature[i++] = c;
            }
        }
        temperature[i] = '\0';
        lcd.setCursor(0, 2);
        lcd.print(distance);
        lcd.setCursor(0, 3);
        lcd.print(temperature);
    }
}