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
	void addMission(Mission*);

	// Promotion event functions
	int IndexOfMountainousMission(const MountainousMission&);
	MountainousMission getMountainousMission(int);
	void removeMountainousMission(int);

	//test functions for Promotion event
	void PrintMountList();
	void PrintEmergencyList();
};

