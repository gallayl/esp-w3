
#include "Movement.h"
#include <../Logger/logger.h>
#include <Arduino.h>

Movement::Movement() {
	Logger::WriteLine("Movement constructed.");
}

Movement::~Movement() { }

void Movement::Setup(int latch, int clock, int data) {
	latchPin = latch;
	clockPin = clock;
	dataPin = data;

	Logger::Write("Setting up movement controls...");
	pinMode(this->latchPin, OUTPUT);
	pinMode(this->dataPin, OUTPUT);
	pinMode(this->clockPin, OUTPUT);
	Logger::WriteLine("Done");
}
;

void Movement::Loop() {

	if (this->stepper1goal == 0 && this->stepper1state == 0 && this->stepper2goal == 0 && this->stepper2state == 0){
		return;
	}

	int bitsToSend = 0;

	if (this->stepper1state != this->stepper1goal)
		(this->stepper1state < this->stepper1goal) ?
				this->stepper1state++ : this->stepper1state--;
	else {
		this->stepper1state =0;
		this->stepper1goal = 0;
	}
	if (this->stepper2state != this->stepper2goal)
		(this->stepper2state < this->stepper2goal) ?
				this->stepper2state++ : this->stepper2state--;
	else {
		this->stepper2state = 0;
		this->stepper2goal = 0;
	}

	uint8_t lower = 1 << this->stepper1state % 4; //Motor inverted
	uint8_t higher = 1 << this->stepper2state % 4;
	bitsToSend = lower + (higher << 4);
	digitalWrite(this->latchPin, LOW);
	shiftOut(this->dataPin, this->clockPin, MSBFIRST, bitsToSend);
	digitalWrite(this->latchPin, HIGH);
	delay(3);
};


void Movement::stepper1_forward(int amount) {
	/*direction inverted here*/
	this->stepper1state = amount;
	this->stepper1goal = 0;
}
void Movement::stepper1_back(int amount) {
	/*direction inverted here*/
	this->stepper1state = 0;
	this->stepper1goal = amount;
}

void Movement::stepper2_forward(int amount) {
	this->stepper2state = 0;
	this->stepper2goal = amount;
}

void Movement::stepper2_back(int amount) {
	this->stepper2state = amount;
	this->stepper2goal = 0;
}

void Movement::GoForward(int amount) {
    this->stepper1_forward(amount);
    this->stepper2_forward(amount);
};

void Movement::GoBack(int amount) {
    this->stepper1_back(amount);
    this->stepper2_back(amount);
};
void Movement::TurnLeft(int amount) {
    this->stepper1_back(amount);
    this->stepper2_forward(amount);
		Logger::Write(amount);
    Logger::WriteLine(" Left");
};

void Movement::TurnRight(int amount) {
    this->stepper1_forward(amount);
    this->stepper2_back(amount);
		Logger::Write(amount);
    Logger::WriteLine(" Right");
};
