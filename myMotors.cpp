
#include "myMotors.h"
#include "mySensors.h"
#include "myDefinitions.h"


myMotorsClass::myMotorsClass():motorsL(), motorsR()
{
    actSpeedL = 90;
    actSpeedR = 90; 
    increment = 5;
    int encoderL = 0;
    int encoderR = 0;
    pinMode(encoderLInt, INPUT);
    pinMode(encoderRInt, INPUT);
}

void  myMotorsClass::init(int servoPinA, int servoPinB)
{
    motorsL.attach(servoPinA);
    motorsR.attach(servoPinB);
    delay(50);
    lastSpeedUpdate = millis();
    atTargetSpeed = false;
    writeData(90, 90);
 }

void myMotorsClass::writeData(int s1, int s2)
{
    motorsL.write(s1); delay(50); motorsR.write(s2);
}

bool myMotorsClass::atTarget(int speedL2, int speedR2)
{
    //absolute value
    speedDiffL = actSpeedL > speedL2 ? actSpeedL - speedL2 : speedL2 - actSpeedL;
    speedDiffR = actSpeedR > speedR2 ? actSpeedR - speedR2 : speedR2 - actSpeedR;
    if ((speedDiffL < 2) || (speedDiffR < 2)) return true;
    else return false;
}

void myMotorsClass::update(int speedL1, int speedR1)
{
    now = millis();
    atTargetSpeed = atTarget(speedL1, speedR1);
   
        if ((now - lastSpeedUpdate > acceleration) && (!atTargetSpeed))
        {
            (actSpeedL < speedL1) ? actSpeedL = actSpeedL + increment : actSpeedL = actSpeedL;
            (actSpeedL > speedL1) ? actSpeedL = actSpeedL - increment : actSpeedL = actSpeedL;
            (actSpeedR < speedR1) ? actSpeedR = actSpeedR + increment : actSpeedR = actSpeedR;
            (actSpeedR > speedR1) ? actSpeedR = actSpeedR - increment : actSpeedR = actSpeedR;

            lastSpeedUpdate = now;

            checkData();

                //need to increase this 75 & 105 to prevent stalling
            (actSpeedL <= 80 || actSpeedL >= 100 || actSpeedL == 90) ? motorsL.write(actSpeedL) : motorsL.write(90);
            delay(50);
            (actSpeedR <= 80 || actSpeedR >= 100 || actSpeedR == 90) ? motorsR.write(actSpeedR) : motorsR.write(90);
        }
    //(speedR == 90) ? speedR = 90 : speedR += 0;   //calibration
}

void myMotorsClass::checkData()
{
    if (actSpeedL > 165) actSpeedL = 165;
    if (actSpeedL < 15) actSpeedL = 15;
    if (actSpeedR > 165) actSpeedR = 165;
    if (actSpeedR < 15) actSpeedR = 15;
}

void myMotorsClass::estop()
{
    motorsL.write(90); delay(50); motorsR.write(90);
}

void myMotorsClass::odometerL()
{
    encoderL = encoderL++;
}

void myMotorsClass::odometerR()
{
    encoderR = encoderR++;
}

int myMotorsClass::getEncoderL()
{
    return encoderL;
}

int myMotorsClass::getEncoderR()
{
    return encoderR;
}

void myMotorsClass::resetEncoders()
{
    encoderL = 0;
    encoderR = 0;
}