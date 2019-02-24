#include <Arduino.h>
#include <LiquidCrystal.h>
#include <AltSoftSerial.h>

#define DISTANCE_MAX_CHAR 10
#define TEMPERATURE_MAX_CHAR 10
#define COORDINATE_MAX_CHAR 10
#define END_OF_LINE '$'
#define SENSOR_DATA_DELIMITER '#'

AltSoftSerial altSerial;

char distance[DISTANCE_MAX_CHAR + 1];
char temperature[TEMPERATURE_MAX_CHAR + 1];
char coordinate[COORDINATE_MAX_CHAR + 1];

bool gettingDistanceData;
int distanceIndex, temperatureIndex, utBoardDataIndex;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void readDistanceData()
{
    char c = altSerial.read();
    if (c == SENSOR_DATA_DELIMITER)
    {
        gettingDistanceData = false;
        distance[distanceIndex] = '\0';
        lcd.setCursor(0, 1);
        lcd.print(distance);
        distanceIndex = 0;
    }
    else
    {
        distance[distanceIndex++] = c;
    }
}

void readTemperatureData()
{
    char c = altSerial.read();
    if (c == END_OF_LINE)
    {
        gettingDistanceData = true;
        temperature[temperatureIndex] = '\0';
        lcd.setCursor(0, 2);
        lcd.print(temperature);
        temperatureIndex = 0;
    }
    else
    {
        temperature[temperatureIndex++] = c;
    }
}

void readUTBoardData()
{
    char c = Serial.read();
    if (c == END_OF_LINE)
    {
        coordinate[utBoardDataIndex] = '\0';
        lcd.setCursor(0, 0);
        lcd.print(coordinate);
        utBoardDataIndex = 0;
    }
    else
    {
        coordinate[utBoardDataIndex++] = c;
    }
}

void setup()
{
    lcd.begin(20, 4);
    Serial.begin(9600);
    altSerial.begin(9600);
    gettingDistanceData = true;
    distanceIndex = 0;
    utBoardDataIndex = 0;
    temperatureIndex = 0;
}

void loop()
{
    if (altSerial.available())
    {
        if (gettingDistanceData)
            readDistanceData();
        else
            readTemperatureData();
    }

    if (Serial.available())
        readUTBoardData();
}