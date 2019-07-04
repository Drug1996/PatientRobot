#include "leg.h"

// test for separate motor
void test(){
  // open driver and motor
  Motor::openDevice();
  Motor motor1(1);
  Motor motor2(2);
  Motor motor3(3);

  motor1.printDeviceVersion();
  motor2.printDeviceVersion();
  motor3.printDeviceVersion();

  motor1.setEnableState();
  motor2.setEnableState();
  motor3.setEnableState();

  // test for velocity mode
  motor1.setMode(PROFILE_VELOCITY);
  motor1.setVelocity(1000);
  sleep(10);
  cout << "current: " << motor1.getCurrent() << endl;
  cout << "velocity: " << motor1.getVelocity() << endl;
  cout << "position: " << motor1.getPosition() << endl;
  sleep(2);
  motor1.quickHalt();
  motor1.setVelocity(-1000);
  sleep(10);
  cout << "current: " << motor1.getCurrent() << endl;
  cout << "velocity: " << motor1.getVelocity() << endl;
  cout << "position: " << motor1.getPosition() << endl;
  sleep(2);
  motor1.quickHalt();

  // test for position mode
  motor2.setMode(PROFILE_POSITION);
  motor2.moveToPosition(1000, 0, 1);
  sleep(5);
  motor2.quickHalt();
  motor2.moveToPosition(-1000, 0, 1);
  sleep(5);
  motor2.quickHalt();
  motor2.moveToPosition(1000, 0, 1);
  sleep(5);
  motor2.quickHalt();

  // test for current mode
  motor3.setMode(CURRENT);
  motor3.setCurrent(6000);
  sleep(10);
  motor3.setCurrent(-6000);
  sleep(10);

  // close motor and driver
  motor1.setDisableState();
  motor2.setDisableState();
  motor3.setDisableState();
  Motor::closeDevice();
}

int main(int argc, char const *argv[]) {
  Leg leg(1, 2, 3);
  leg.printTest();
  leg.moveForwardTest();
  sleep(2);
  leg.moveBackwardTest();
  return 0;
}
