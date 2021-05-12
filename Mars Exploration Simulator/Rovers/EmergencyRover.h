#pragma once
#include"Rover.h"
class EmergencyRover:public Rover
{
public:
	EmergencyRover(int roverspeed, int checkupCount, int Days);
	~EmergencyRover();
};

