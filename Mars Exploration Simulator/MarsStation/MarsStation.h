#pragma once
#include<iostream>
using namespace std;
//data strucures
#include"../DataStructures/Bag.h"
#include"../DataStructures/PriorityQueue.h"
#include"../DataStructures/Queue.h"
#include"../DataStructures/Stack.h"
#include"../DataStructures/List.h"
//missions
#include"../Missions/Mission.h"
#include"../Missions/EmergencyMission.h"
#include"../Missions/MountainousMission.h"
#include"../Missions/PolarMission.h"
//Rovers
#include"../Rovers/Rover.h"
#include"../Rovers/EmergencyRover.h"
#include"../Rovers/MountainousRover.h"
#include"../Rovers/PolarRover.h"
//Events
#include"../Events/Event.h"
class MarsStation
{
	unsigned long long currentDay;
	//Missions :-
	// 1) Waiting
	PriorityQueue<EmergencyMission*> emergencyWaitingMission;
	List<MountainousMission> mountainousWaitingMission;
	Queue<PolarMission*> polarWaitingMission;

	// 2) Completed
	Queue<Mission*> completedMissions;			//Pointers for polymorphism

	// 3) Execution (In-service) missions
	PriorityQueue<Mission*> inServiceMissions;	//Pointers for polymorphism

	//Rovers
	//1) Available rovers
	PriorityQueue<EmergencyRover*> emergencyAvailableRover;
	PriorityQueue<PolarRover*> polarAvailableRover;
	PriorityQueue<MountainousRover*> mountainousAvailableRover;

	//2) Unavailable rovers
	PriorityQueue<Rover*> unavailableRovers;	//Pointers for polymorphism

	//Event List
	//Queue<Event> eventList;
public:
	MarsStation();
	~MarsStation();
	unsigned long long getCurDay();
	void addMission(Mission*);
	void addRover(Rover*);
	void addUnavailableRover(Rover*);
	// Promotion event functions
	int IndexOfMountainousMission(const MountainousMission&);
	MountainousMission getMountainousMission(int);
	void removeMountainousMission(int);


	//Mission Failure functions
	Mission* inserviceRemove(int);
	Rover* UnavailableRemove(int);

	//Assign functions
	bool assignEmergencyMission(int);
	bool assignMountainousMission(int);
	bool assignPolarMission(int);




	//test functions 
	void PrintMountList();
	void PrintEmergencyList();
	void printPolarList();
	void printInserviceMissions();

	void printUnavRovers();
	void printMountRovers();
	void printEmRovers();
	void printPolarRovers();
	void ExecuteEm(Rover*);
	void Executemount(Rover*);
	void ExecutePolar(Rover*);
};

