//#include<iostream>
//#include"EmergencyMission.h"
//#include"Mission.h"
//#include"PolarMission.h"
//#include"MountainousMission.h"
//#include"../Rovers/PolarRover.h"
//using namespace std;
//void Print(Mission* m[])
//{
//	for (int i = 0; i < 6; i++)
//	{
//		cout << "Mission Info : " <<i+1<< endl;
//		cout << "Formulation Day: " << m[i]->getFormulationDay() << endl;
//		cout << "TargetLocation: " << m[i]->getTargetLocation() << endl;
//		cout << "Mission Duration: " << m[i]->getMissionDuration() << endl;
//		cout << "Significance: " << m[i]->getSignificance() << endl;
//		cout << "End Day: " << m[i]->getEndDay() << endl;
//		cout << "*********Info is ended************" << endl;
//		cout << endl;
//	}
//}
//int main()
//{
//	// mission testing
//	EmergencyMission E1(3,10000,6,1,5); 
//	EmergencyMission E2(5, 12000, 8, 2,4);
//	PolarMission P1(6,15000,4,3,7);
//	PolarMission P2(8, 18000, 5, 4, 2);
//	MountainousMission Mo1(4, 11000, 5,4, 10);
//	MountainousMission Mo2(9, 13000, 6, 4, 11);
//
//	//assgin rover to mission
//	PolarRover r1(20, 4, 8);
//	P1.assignRover(&r1);
//
//	//printing
//	Mission*M[6] = {&E1,&E2,&P1,&P2,&Mo1,&Mo2};
//	Print(M);
//	
// }