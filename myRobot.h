#pragma once

#include "myMotors.h"
#include "myRemote.h"
#include "mySensors.h"
#include <SSD1306AsciiWire.h>
#include "DifferentialSteering.h"

class myRobotClass
{
 private:         
     DifferentialSteering diffSteer;
     void diffSteerData();
     long lastMeasurement;
     char fromPI;
    
 public:
    myRobotClass(); 
    SSD1306AsciiWire myDisplay;
#ifndef debugMotors
    myMotorsClass myMotors;
#endif
    remoteControlClass myRemote;
    mySensorsClass mySensors;
    void initialize();
    void update();
    void stop();
    int speedL, speedR, mappedL, mappedR;
    bool obstacle; 
};
