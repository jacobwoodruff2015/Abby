// mySensors.h

#pragma once
#include <NewPing.h>
#include "MovingAverage.h"

class mySensorsClass
{

private:
    int distanceSonar, avgDistanceSonar;
    int distanceIR, avgDistanceIR;
    int distanceRear;
    MovingAverage<unsigned int, 10> averageSonar;
    MovingAverage<unsigned int, 10> averageIR;

public:
    mySensorsClass(int triggerPin, int echoPin, int triggerPinRear);
    NewPing* sonarFront;
    NewPing* sonarRear;
    void update();
    int getDistanceSonar();
    int getDistanceIR();
    int getAvgDistanceSonar();
    int getAvgDistanceIR();
    int getDistanceRear();
    bool checkObstacle();
    bool obstacleSonar;
};
