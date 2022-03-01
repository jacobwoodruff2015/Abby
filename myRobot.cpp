#pragma once
#include "myRobot.h"
#include "myDefinitions.h"

#define sensorUpdateInterval 100


#ifndef debugMotors
myRobotClass::myRobotClass() : myDisplay(), mySensors(DISTANCE_SENSORS), myRemote(), diffSteer()
{
    speedL = 90;
    speedR = 90;
    initialize();
    obstacle = false;
    lastMeasurement = millis();
}
#endif

#ifdef debugMotors
RobotClass::RobotClass() : myDisplay(), myMotors(), mySensors(DISTANCE_SENSORS), myRemote(), diffSteer()
{
    speedL = 90;
    speedR = 90;
    initialize();
    obstacle = false;
    lastMeasurement = millis();
}
#endif

void myRobotClass::initialize()
{
    myDisplay.println("What up  "); myDisplay.println(" Bri B");
}

void myRobotClass::diffSteerData()
{
    mappedL = map(myRemote.XValue, 0, 255, -127, 127);
    mappedR = map(myRemote.YValue, 255, 0, -127, 127);
    diffSteer.computeMotors(mappedL, mappedR);
    speedL = diffSteer.computedLeftMotor();
    speedR = diffSteer.computedRightMotor();
    speedL = map(speedL, -127, 127, 30, 150);
    speedR = map(speedR, -127, 127, 30, 150);
}

void myRobotClass::update()
{
#ifdef raspberryPI
    if (Serial.available())
    {
        fromPI = Serial.read(); 
        if (fromPI == 1) {speedL = 110; speedR = 130;}
        if (fromPI == 2) {speedL = 120; speedR = 120;}
        if (fromPI == 3) {speedL = 130; speedR = 110;}
        if (fromPI == 4) {speedL = 60; speedR = 60;}
        if (fromPI == 5) {speedL = 90; speedR = 90;}
        while (Serial.read() >= 0) {}
        //delay(50);
        //parseCommand(val); // parse the input
    }
#endif
    if (millis() - lastMeasurement > sensorUpdateInterval)
    {
        #ifndef debugSensors
        mySensors.update();
        obstacle = mySensors.obstacleSonar;   //1 is obstacle present
        lastMeasurement = millis();
        #endif
    }

    myRemote.update();
    if (myRemote.newData)
    {
        diffSteerData();
        if (myRemote.encoderBool) myMotors.resetEncoders();
        myRemote.newData = false;
    }
   
    speedL = (obstacle && speedL >= 90) ? 90 : speedL;
    speedR = (obstacle && speedR >= 90) ? 90 : speedR;

#ifndef debugMotors
    myMotors.update(speedL, speedR);
#endif

}

void myRobotClass::stop()
{
#ifndef debugMotors
  myMotors.estop();
#endif
  speedR = 90;
}
