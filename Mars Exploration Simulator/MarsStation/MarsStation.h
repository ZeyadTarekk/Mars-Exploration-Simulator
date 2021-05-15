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
#include"../Events/FormulationEvent.h"
#include"../Events/PromotionEvent.h"
#include"../Events/CancelationEvent.h"
class Event;
class MarsStation
{
	unsigned long long currentDay;
	double avgSpeed;
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
	Queue<Event*> eventList;
	int autoPromot;
public:
	MarsStation();
	~MarsStation();
	void setAutoPromot(int);
	int getAutoPromot();
	unsigned long long getCurDay();
	void setAvgSpeed(double);
	double getAvgSpeed();
	void addMission(Mission*);
	void addRover(Rover*); // used in case of search (class responsibilities)
	void createRover(char type,int speed,int checkCount,int checkDays); // use in case of create (class responsibilities)
	void createFormEvent(char type,int eventDay,int id,int targetLoc,int MDuration,int sig);
	void createCancelEvent(int eventDay, int id);
	void createPromotEvent(int eventDay, int id);
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

	// Completed Mission && Rover
	void addToCompletedMission(int);
	void moveRoverFromExcuetionToCheckUp(int);
	bool isCompleted(int);


	//test functions 
	void PrintMountList();
	void PrintEmergencyList();
	void printPolarList();
	void printInserviceMissions();
	void printCompleteMission();

	void printUnavRovers();
	void printMountRovers();
	void printEmRovers();
	void printPolarRovers();
	void ExecuteEm(Rover*);
	void Executemount(Rover*);
	void ExecutePolar(Rover*);
	void executeEvents();
};

