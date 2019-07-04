#include "motor.h"

void* Motor::keyHandle = 0;
string Motor::deviceName = string("EPOS4");
string Motor::protocolStackName = string("MAXON SERIAL V2");
string Motor::interfaceName = string("USB");
string Motor::portName = string("USB0");
unsigned int Motor::baudrate = 1000000;
unsigned int Motor::timeout = 500;
unsigned int Motor::lResult = MMC_FAILED;
unsigned int* Motor::errorCode = new unsigned int(0);

Motor::Motor(unsigned short driverId){
  id = driverId;
  mode = -1;
  cout << "Connect motor " << id << " successfully." << endl;
}

Motor::~Motor(){
  //cout << "Close motor " << id << " successfully." << endl;
}

// open dirver (EPOS4)
int Motor::openDevice(){
  lResult = MMC_FAILED;
  *errorCode = 0;
	char* pDeviceName = new char[255];
	char* pProtocolStackName = new char[255];
	char* pInterfaceName = new char[255];
	char* pPortName = new char[255];

	strcpy(pDeviceName, deviceName.c_str());
	strcpy(pProtocolStackName, protocolStackName.c_str());
	strcpy(pInterfaceName, interfaceName.c_str());
	strcpy(pPortName, portName.c_str());

	cout << "Open device..." << endl;

	keyHandle = VCS_OpenDevice(pDeviceName, pProtocolStackName, pInterfaceName, pPortName, errorCode);

	if(keyHandle!=0 && *errorCode == 0){
		VCS_SetProtocolStackSettings(keyHandle, baudrate, timeout, errorCode);
  }
	else{
		keyHandle = 0;
	}

	delete []pDeviceName;
	delete []pProtocolStackName;
	delete []pInterfaceName;
	delete []pPortName;

	return lResult;
}

// close driver (EPOS4)
int Motor::closeDevice(){
  lResult = MMC_FAILED;
	*errorCode = 0;

	cout << "Close device" << endl;

	if(VCS_CloseDevice(keyHandle, errorCode)!=0 && *errorCode == 0){
		lResult = MMC_SUCCESS;
	}

	return lResult;
}

// print the information of dirver
int Motor::printDeviceVersion(){
  lResult = MMC_FAILED;

	unsigned short usHardwareVersion = 0;
	unsigned short usSoftwareVersion = 0;
	unsigned short usApplicationNumber = 0;
	unsigned short usApplicationVersion = 0;
	unsigned int ulErrorCode = 0;

	if(VCS_GetVersion(keyHandle, id, &usHardwareVersion, &usSoftwareVersion, &usApplicationNumber, &usApplicationVersion, &ulErrorCode))
	{
		printf("%s Hardware Version    = 0x%04x\n      Software Version    = 0x%04x\n      Application Number  = 0x%04x\n      Application Version = 0x%04x\n",
				deviceName.c_str(), usHardwareVersion, usSoftwareVersion, usApplicationNumber, usApplicationVersion);
		lResult = MMC_SUCCESS;
	}

  return lResult;
}

// enable motor
int Motor::setEnableState(){
  lResult = MMC_FAILED;
  lResult = VCS_SetEnableState(keyHandle, id, errorCode);

  return lResult;
}

// disenable motor
int Motor::setDisableState(){
  lResult = MMC_FAILED;
  lResult = VCS_SetDisableState(keyHandle, id, errorCode);

  return lResult;
}

// set motion mode for motor
// mode type:
// PROFILE_POSITION 1
// PROFILE_VELOCITY 3
// HOMING 6
// CURRENT -3
int Motor::setMode(int motorMode){
  lResult = MMC_FAILED;
  mode = motorMode;
  lResult = VCS_SetOperationMode(keyHandle, id, motorMode, errorCode);
  return lResult;
}

// set current when using current mode
int Motor::setCurrent(short current){
  lResult = MMC_FAILED;
  if(mode == CURRENT){
    cout << "set current value as " << current << endl;
    lResult = VCS_SetCurrentMust(keyHandle, id, current, errorCode);
  }
  else{
    cout << "This function is only for current mode!" << endl;
  }

  return lResult;
}

// set velocity when using velocity mode
int Motor::setVelocity(int velocity){
  lResult = MMC_FAILED;
  if(mode == PROFILE_VELOCITY){
    cout << "set velocity value as " << velocity << endl;
    lResult = VCS_MoveWithVelocity(keyHandle, id, velocity, errorCode);
  }
  else{
    cout << "This function is only for velocity mode!" << endl;
  }

  return lResult;
}

// move motor to a target positionValue
// absolute 1, relative 0
// immediate 1, wait until last finished 0
int Motor::moveToPosition(long position, bool absolute, bool immediate){
  lResult = MMC_FAILED;
  if(mode == PROFILE_POSITION){
    cout << "set position value as " << position << endl;
    lResult = VCS_MoveToPosition(keyHandle, id, position, absolute, immediate, errorCode);
  }
  else{
    cout << "This function is only for position mode!" << endl;
  }

  return lResult;
}

// get the current actual value
short int Motor::getCurrent(){
    short int currentValue = 0;
    short* current = &currentValue;
    VCS_GetCurrentIs(keyHandle, id, current, errorCode);

    return *current;
}

// get the velocity actual value
int Motor::getVelocity(){
  int velocityValue = 0;
  int* velocity = &velocityValue;
  VCS_GetVelocityIs(keyHandle, id, velocity, errorCode);

  return *velocity;
}

// get the position actual value
int Motor::getPosition(){
  int positionValue = 0;
  int* position = &positionValue;
  VCS_GetPositionIs(keyHandle, id, position, errorCode);

  return *position;
}

// stop motor
int Motor::halt(){
  lResult = MMC_FAILED;
  switch (mode) {
    case PROFILE_VELOCITY:
      lResult = VCS_HaltVelocityMovement(keyHandle, id, errorCode);
      break;
    case PROFILE_POSITION:
      lResult = VCS_HaltPositionMovement(keyHandle, id, errorCode);
    default:
      cout << "No halt function for this motor mode!" << endl;
      break;
  }

  return lResult;
}

// immediately stop motot
int Motor::quickHalt(){
  lResult = MMC_FAILED;
  lResult = setDisableState();
  lResult = setEnableState();

  return lResult;
}
