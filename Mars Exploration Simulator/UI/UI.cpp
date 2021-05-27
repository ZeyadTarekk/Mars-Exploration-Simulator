#include "UI.h"

void UI::calcAvgSpeed()
{
	for (int i = 0; i < mountRoverCount; i++)
		avgSpeed += mountSpeed[i];
	for (int i = 0; i < polRoverCount; i++)
		avgSpeed += polSpeed[i];
	for (int i = 0; i < emRoverCount; i++)
		avgSpeed += emSpeed[i];
	avgSpeed /= (mountRoverCount + emRoverCount + polRoverCount);
}

void UI::read()
{
	string Filename;
	cout << "Please enter the name of the input file without the extention: ";
	cin >> Filename;

	ifstream in;
	in.open("InputFiles/"+Filename+".txt");
	if (!in.is_open())
	{
		cout << Filename+".txt not found" << endl;
		exit(1);
	}
	int ModeOfOperation;
	cout << "Please choose mode of operation : -" << endl;
	cout << "For interactive mode press 1 :" << endl;
	cout << "For step-by-step mode press 2 :" << endl;
	cout << "For silent mode press any other key :" << endl;
	cin >> ModeOfOperation;
	MStation->setModeOperation(ModeOfOperation);

	in >> mountRoverCount >> polRoverCount >> emRoverCount;
	MStation->setEmRoverCount(emRoverCount);
	MStation->setMountRoverCount(mountRoverCount);
	MStation->setPolRoverCount(polRoverCount);
	mountSpeed = new int[mountRoverCount];
	polSpeed = new int[polRoverCount];
	emSpeed = new int[emRoverCount];
	for (int i = 0; i < mountRoverCount; i++)
		in >> mountSpeed[i];
	for (int i = 0; i < polRoverCount; i++)
		in >> polSpeed[i];
	for (int i = 0; i < emRoverCount; i++)
		in >> emSpeed[i];
	in >> checkCount >> mountCheck >> polCheck >> emCheck;

	createRovers();
	calcAvgSpeed();
	MStation->setAvgSpeed(avgSpeed);
	in >> autoPromLimit;
	MStation->setAutoPromot(autoPromLimit);

	in >> NoEvents;
	MStation->setEventCount(NoEvents);
	for (int i = 0; i < NoEvents; i++)
	{
		in >> eventType;
		//cout << eventType << endl;
		switch (eventType)
		{
		case 'F':
		{
			in >> missionType >> eventDay >> ID >> location >> duration >> signifiance;
			//cout << missionType << " " << eventDay << " " << ID << " " << location << " " << duration << " " << signifiance << endl;
			MStation->createFormEvent(missionType, eventDay, ID, location, duration, signifiance);
			break;
		}
		case 'X':
		{
			in >> eventDay >> ID;
			MStation->createCancelEvent(eventDay, ID);
			break;
		}
		case 'P':
		{
			in >> eventDay >> ID;
			MStation->createPromotEvent(eventDay, ID);
			break;
		}
		}
	}
	in.close();
}



void UI::createRovers()
{
	for (int i = 0; i < mountRoverCount; i++)
		MStation->createRover('M', mountSpeed[i], checkCount, mountCheck);
	for (int i = 0; i < polRoverCount; i++)
		MStation->createRover('P', polSpeed[i], checkCount, polCheck);
	for (int i = 0; i < emRoverCount; i++)
		MStation->createRover('E', emSpeed[i], checkCount, emCheck);
}


void UI::TestPrint()
{
	cout << mountRoverCount << " " << polRoverCount << " " << emRoverCount << endl;
	for (int i = 0; i < mountRoverCount; i++)
		cout << mountSpeed[i] << " ";
	cout << endl;
	for (int i = 0; i < polRoverCount; i++)
		cout << polSpeed[i] << " ";
	cout << endl;
	for (int i = 0; i < emRoverCount; i++)
		cout << emSpeed[i] << " ";
	cout << endl;
	cout << checkCount << " " << mountCheck << " " << polCheck << " " << emCheck << endl;
	cout << autoPromLimit << endl;
	cout << NoEvents << endl;
}

UI::UI(MarsStation* MS) :MStation(MS)
{
	read();
}

void UI::outputStart()
{
	ofstream out;
	out.open("OutputFiles/Output.txt");
	if (out.is_open())
		MStation->printOutput(out);
	//out << "zeyad";
}

UI::~UI() {}
