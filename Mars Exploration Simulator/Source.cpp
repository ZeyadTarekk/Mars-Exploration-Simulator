#include"MarsStation/MarsStation.h"
int main()
{
	MarsStation* mStation = new MarsStation();
	mStation->simulate();
	delete mStation;
	return 0;
}