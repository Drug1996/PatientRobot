#include "Definitions.h"
#include <list>
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
using namespace std;

// motor mode type
#define PROFILE_POSITION 1
#define PROFILE_VELOCITY 3
#define HOMING 6
#define CURRENT -3

#ifndef MMC_SUCCESS
	#define MMC_SUCCESS 0
#endif

#ifndef MMC_FAILED
	#define MMC_FAILED 1
#endif

class Motor{
public:
  Motor(unsigned short dirverId);
  ~Motor();
  static void* keyHandle;
  static string deviceName;
  static string protocolStackName;
  static string interfaceName;
  static string portName;
  static unsigned int baudrate;
  static unsigned int timeout;
  static unsigned int lResult;
  static unsigned int* errorCode;
  static int openDevice();
  static int closeDevice();
  int printDeviceVersion();
  int setMode(int mode);
  int setEnableState();
  int setDisableState();
	int setCurrent(short current);
  int setVelocity(int velocity);
	int moveToPosition(long position, bool absolute, bool immediate);
	short int getCurrent();
	int getVelocity();
	int getPosition();
	int halt();
	int quickHalt();
private:
  unsigned short id;
	int mode;
};
