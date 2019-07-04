#include "motor.h"

class Leg{
public:
	Leg(int num1, int num2, int num3);
	~Leg();
  void enable();
  void disenable();
  void moveForwardTest();
	void moveBackwardTest();
	void printTest();
private:
  Motor* motor1;
	Motor* motor2;
	Motor* motor3;
};
