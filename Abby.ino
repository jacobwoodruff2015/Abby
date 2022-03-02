
#include <NewPing.h>
#include <PS2X_lib.h>
#include <Servo.h>
#include <Wire.h>

//#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\libraries\Wire\"
#include <SSD1306AsciiWire.h>
#include "myRobot.h"
#include "myDefinitions.h"

//#define debugMotors      //define to turn off
//#define raspberryPI    //define to check serial for pi

myRobotClass myRobot;

long now, lastTime;

void odometerL_ISR()
{
    myRobot.myMotors.odometerL();
}

void odometerR_ISR()
{
    myRobot.myMotors.odometerR();
}

void setup()
{
    Serial.begin(57600);
    Wire.begin();  Wire.setClock(400000L);
    myRobot.myDisplay.begin(&Adafruit128x64, 0x3C);  myRobot.myDisplay.setFont(Adafruit5x7);
    myRobot.myDisplay.clear(); myRobot.myDisplay.set2X();
    myRobot.initialize();
#ifndef debugMotors
    myRobot.myMotors.init(S1Pin, S2Pin);
    myRobot.myRemote.init();
    attachInterrupt(digitalPinToInterrupt(encoderLInt), odometerL_ISR, RISING);
    attachInterrupt(digitalPinToInterrupt(encoderRInt), odometerR_ISR, RISING);
#endif
    lastTime = millis();
}


void loop()
{
    static int displayDelay = 0;

    if (millis() - lastTime > 10)
    {
        myRobot.update();
        lastTime = millis();
        displayDelay++;
    }

    if (displayDelay == 3)
    {
        //myRobot.update();
        displayDelay = 0;

        myRobot.myDisplay.setCursor(0, 0); myRobot.myDisplay.clearToEOL();
        if (myRobot.mySensors.getDistanceSonar() < 10) myRobot.myDisplay.setCursor(12, 0);
   
        myRobot.myDisplay.print(myRobot.mySensors.getDistanceSonar());
        myRobot.myDisplay.print("   "); myRobot.myDisplay.print(myRobot.mySensors.getDistanceRear());

        myRobot.myDisplay.setCursor(0, 2); myRobot.myDisplay.clearToEOL(); myRobot.myDisplay.print(myRobot.mySensors.checkObstacle()); 
        myRobot.myDisplay.print(" "); myRobot.myDisplay.println(String("IR ") + myRobot.mySensors.getDistanceIR());

        myRobot.myDisplay.setCursor(0, 4); myRobot.myDisplay.clearToEOL(); myRobot.myDisplay.print(myRobot.myMotors.actSpeedL);
        myRobot.myDisplay.print(" "); myRobot.myDisplay.println(myRobot.myMotors.actSpeedR);
#ifndef debugMotors
        myRobot.myDisplay.setCursor(0, 6); myRobot.myDisplay.clearToEOL(); myRobot.myDisplay.print(myRobot.myMotors.getEncoderL());
        myRobot.myDisplay.print(" "); myRobot.myDisplay.print(myRobot.myMotors.getEncoderR());
#endif
    }
}
