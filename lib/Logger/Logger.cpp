#include "Logger.h"

Logger::Logger() {
}

Logger::~Logger() {
}

#include <Arduino.h>
#include "logger.h"

void Logger::Write(String s){
    Serial.print(s);
}

void Logger::Write(int i){
    Serial.print(i);
}

void Logger::WriteLine(String s){
    Serial.println(s);
}

void Logger::WriteLine(int i){
    Serial.println(i);
}
