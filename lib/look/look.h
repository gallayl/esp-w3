#ifndef LOOK_H_
#define LOOK_H_

#include <Servo.h>
#include <logger.h>

class Look {
public:
  void Setup(int pwmPin);
  void Think();
  void SetAngle(byte newAngle);
  void Left(byte amount);
  void Right(byte amount);
  byte GetAngle();

private:
  Servo headVertical;
  byte verticalAngle;
  byte verticalMin;
  byte verticalMax;
};


#endif /* LOGGER_H_ */
