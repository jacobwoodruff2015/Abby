
//remoteControl.h
#pragma once

#include <PS2X_lib.h>
#include <Servo.h>

class remoteControlClass
{
private:
	Servo Pan;
	Servo Tilt;
	int checkPS2();
	int parseCommand(char input);
	void serial_flush_buffer();
	int  XValueOld, YValueOld, XValueDiff, YValueDiff;
	int xJoy, yJoy, xJoyOld, yJoyOld;
	byte pan, tilt, tiltOld, panOld, panDiff, tiltDiff;

public:
	remoteControlClass();
	PS2X ps2;                  
	void init();              
	void update();
	bool newData;
	int XValue, YValue;
	bool encoderBool;
	//int leftMotor, rightMotor;
};
