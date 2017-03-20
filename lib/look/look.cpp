#include "look.h"

void Look::Setup(int pwmPin){
    Logger::Write("Setting up Look...");

    this->verticalAngle = 90;
    this->verticalMin = 60;
    this->verticalMax = 120;

    this->headVertical = Servo();

    this->headVertical.attach(pwmPin);
};

void Look::SetAngle(byte newAngle){
  Logger::Write("Look angle ");
  Logger::Write(newAngle);
  this->verticalAngle = newAngle;
}

byte Look::GetAngle(){
  return this->verticalAngle;
}

void Look::Left(byte amount){
  this->verticalAngle += amount;
  if (this->verticalAngle > this->verticalMax)
    this->verticalAngle = this->verticalMax;
}

void Look::Right(byte amount){
  this->verticalAngle -= amount;
  if (this->verticalAngle < this->verticalMin)
    this->verticalAngle = this->verticalMin;
}

void Look::Think(){
  // Logger::Write(this->verticalAngle);
  this->headVertical.write(this->verticalAngle);
}
