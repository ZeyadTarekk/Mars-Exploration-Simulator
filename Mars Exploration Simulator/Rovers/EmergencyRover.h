#pragma once
#include"Rover.h"
class EmergencyRover:public Rover
{
public:
	EmergencyRover(double roverspeed, int checkupCount, int Days);
	~EmergencyRover();
};

