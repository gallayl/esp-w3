#include "Logger.h"
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void Logger::Setup() {
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight
  lcd.setCursor(0, 0);
}

Logger::~Logger() {
}

#include <Arduino.h>
#include "logger.h"

void Logger::Write(String s){
    uint8_t length = s.length()+1;
    char buffer[length];
    s.toCharArray(buffer, length,0);
    Serial.print(s);
    lcd.print(buffer);
}

void Logger::Write(int i){
    Serial.print(i);
    lcd.print(i);
}

void Logger::WriteLine(String s){
    uint8_t length = s.length()+1;
    char buffer[length];
    s.toCharArray(buffer, length ,0);
    Serial.println(s);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(buffer);
}

void Logger::WriteLine(int i){
    Serial.println(i);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(i);
}
