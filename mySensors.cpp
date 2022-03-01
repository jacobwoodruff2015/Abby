#include "mySensors.h"
#include "myDefinitions.h"



mySensorsClass::mySensorsClass(int trigFront, int echoFront, int trigRear)
{
	sonarFront = new NewPing(trigFront, echoFront, maxDistance);
	sonarRear = new NewPing(trigRear, maxDistance);
	distanceSonar = maxDistance;
	obstacleSonar = 0;
	pinMode(IRPin, INPUT);
}

//void mySensorsClass::init() {pinMode(A2, OUTPUT);}

void mySensorsClass::update()
{
	distanceSonar = sonarFront->ping_cm();
	distanceRear = sonarRear->ping_cm();
	
	avgDistanceSonar = averageSonar.add(distanceSonar);
	distanceIR = 2076 / (analogRead(IRPin) - 11);
	avgDistanceIR = averageIR.add(distanceIR);
	obstacleSonar = checkObstacle();
}

int mySensorsClass::getAvgDistanceSonar()
{
	//if (avgDistanceSonar > 300) return 301;
	//else if (avgDistanceSonar < 4) return 3;
	//else 
	return avgDistanceSonar;
}

int mySensorsClass::getDistanceSonar()
{
	//if (distanceSonar > 300) return 301;
	//else if (distanceSonar < 4) return 3;
	//else 
	return distanceSonar;
}

bool mySensorsClass::checkObstacle()
{
	if ((avgDistanceSonar > 20) || (avgDistanceSonar == 0)) return 0;  
	return 1;  //1 is obstacle present
}

int mySensorsClass::getAvgDistanceIR()
{
	//if (avgDistanceIR > 300) return 302;
	//else if (avgDistanceIR < 4) return 2;
	//else 
	return avgDistanceIR;
}

int mySensorsClass::getDistanceIR()
{
	//if (distanceIR > 300) return 302;
	//else if (distanceIR < 4) return 2;
	//else 
	return distanceIR;
}

int mySensorsClass::getDistanceRear()
{
	//if (distanceRear > 300) return 302;
	//else if (distanceRear < 4) return 2;
	//else
	return distanceRear;
}
