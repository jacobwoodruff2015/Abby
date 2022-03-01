// myMotors.h

#pragma once

#include <Arduino.h>
#include <Servo.h>


class myMotorsClass
{

private:
    Servo motorsL; 
    Servo motorsR;
    int  speedDiffL, speedDiffR;
    bool atTarget(int speedL, int speedR);
    int increment;
    long now, lastSpeedUpdate, speedUpdateInterval;
    int encoderL, encoderR;
       
public:
    myMotorsClass(); 
    void resetEncoders();
    void estop();
    void update(int speedL1, int speedR1);  
    void init(int servoPinA, int servoPinB);
    void writeData(int s1, int s2);
    void checkData();
    bool atTargetSpeed;
    int actSpeedL, actSpeedR;
    int getEncoderL();
    int getEncoderR();    
    void odometerL();
    void odometerR();
    
    
  };
