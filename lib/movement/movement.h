#ifndef MOVEMENT_H_
#define MOVEMENT_H_

class Movement {
public:
	Movement();
	virtual ~Movement();
	void GoForward(int amount);
	void GoBack(int amount);
	void TurnLeft(int amount);
	void TurnRight(int amount);

	// Task functions
	void Setup(int latch, int clock, int data);
	void Loop();

private:
	// PIN variables for 74HC595
	int latchPin = 0;
	int clockPin = 0;
	int dataPin = 0;

	int stepper1state = 0;
	int stepper1goal = 0;
	int stepper2state = 0;
	int stepper2goal = 0;

	int stepper_min = 0;

	void stepper1_forward(int amount);
	void stepper1_back(int amount);

	void stepper2_forward(int amount);
	void stepper2_back(int amount);

};

#endif /* MOVEMENT_H_ */
