#pragma once
//data strucures
#include"../DataStructures/Bag.h"
#include"../DataStructures/PriorityQueue.h"
#include"../DataStructures/Queue.h"
#include"../DataStructures/Stack.h"
//missions
#include"../Missions/Mission.h"
#include"../Missions/EmergencyMission.h"
#include"../Missions/MountainousMission.h"
#include"../Missions/PolarMission.h"
//Rovers
#include"../Rovers/Rover.h"
#include"../Rovers/EmergencyRover.h"
#include"../Missions/MountainousMission.h"
#include"../Missions/PolarMission.h"
class MarsStation
{
	unsigned long long currentDay;
	//Missions :-
	// 1) Waiting
	PriorityQueue<EmergencyMission*> emergencyWaitingMission;
	Queue<MountainousMission*> mountainousWaitingMission;
	Queue<PolarMission*> polarWaitingMission;

	// 2) Completed
	Queue<Mission*> completedMissions;			//Pointers for polymorphism

	// 3) Execution (In-service) missions
	PriorityQueue<Mission*> inServiceMissions;	//Pointers for polymorphism

	//Rovers
	//1) Available rovers
	PriorityQueue<EmergencyRover*> emergencyAvailableRover;
	PriorityQueue<PolarMission*> polarAvailableMission;
	PriorityQueue<MountainousMission*> mountainousAvailableMission;

	//2) Unavailable rovers
	PriorityQueue<Rover*> unavailableRovers;	//Pointers for polymorphism

	//Event List
	//Queue<Event> eventList;
public:
	MarsStation();
	~MarsStation();
};

