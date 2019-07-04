#include "leg.h"

Leg::Leg(int num1, int num2, int num3){
  Motor::openDevice();
  motor1 = new Motor(num1);
  motor2 = new Motor(num2);
  motor3 = new Motor(num3);
}

Leg::~Leg(){
  delete motor1;
  delete motor2;
  delete motor3;
  Motor::closeDevice();
}

void Leg::enable(){
  motor1->setEnableState();
  motor2->setEnableState();
  motor3->setEnableState();
}

void Leg::disenable(){
  motor1->setDisableState();
  motor2->setDisableState();
  motor3->setDisableState();
}

void Leg::printTest(){
  enable();
  motor1->printDeviceVersion();
  motor2->printDeviceVersion();
  motor3->printDeviceVersion();
}

void Leg::moveForwardTest(){
  enable();
  motor1->setMode(PROFILE_VELOCITY);
  motor2->setMode(PROFILE_VELOCITY);
  motor3->setMode(PROFILE_VELOCITY);
  motor1->setVelocity(-200);
  motor2->setVelocity(200);
  motor3->setVelocity(-200);
  sleep(3);
  motor1->setVelocity(200);
  motor2->setVelocity(-200);
  motor3->setVelocity(200);
  sleep(3);
  disenable();
}

void Leg::moveBackwardTest(){
  enable();
  motor1->setMode(PROFILE_VELOCITY);
  motor2->setMode(PROFILE_VELOCITY);
  motor3->setMode(PROFILE_VELOCITY);
  motor1->setVelocity(200);
  motor2->setVelocity(-200);
  motor3->setVelocity(200);
  sleep(3);
  motor1->setVelocity(-200);
  motor2->setVelocity(200);
  motor3->setVelocity(-200);
  sleep(3);
  disenable();
}
