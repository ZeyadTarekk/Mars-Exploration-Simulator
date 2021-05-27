//#include<iostream>
//#include<fstream>
//#include"..//MarsStation/MarsStation.h"
//#include"CompletionEvent.h"
//#include"../UI/UI.h"
//using namespace std;
//int main()
//{
//	//mission
//	EmergencyMission *me = new EmergencyMission(1,1,1,662,1,1);
//	MountainousMission* M = new MountainousMission(2,2,2,2,2,2);
//	PolarMission* p = new PolarMission(3,3,3,3,3);
//
//	//rovers
//	EmergencyRover* eR = new EmergencyRover(4,4,4);
//	MountainousRover* Mr = new MountainousRover(5, 5, 5);
//	PolarRover* pR = new PolarRover(6, 6, 6);
//
//	//mars-station
//	MarsStation* m = new MarsStation();
//
//	//assign rover to mission
//	eR->assignMission(1, 1, 1, 1); 
//	eR->assignCheckup(2); //checkup day 
//
//	//add emergency in waiting list
//	m->addMission(me);
//	m->addMission(M);
//	m->addMission(p);
//
//	//execution function
//	m->ExecuteEm(eR);
//	m->Executemount(Mr);
//	m->ExecutePolar(pR);
//
//	//complete event has been created
//	CompletionEvent* C = new CompletionEvent(1);
//
//	//execute complete
//	C->execute(m);
//
//	//print unavailable rovers
//	cout << "Unavailable Rovers :" << endl;
//	m->printUnavRovers();
//
//	//print completed mission
//	cout << "====================" << endl;
//	cout << "Completed Mission :" << endl;
//	m->printCompleteMission();
//}
