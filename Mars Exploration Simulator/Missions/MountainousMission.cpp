#include"MountainousMission.h"

MountainousMission::MountainousMission(int fD, int tL, int mD, int iD, double sig,int autoProm):Mission(fD, tL, mD, iD, sig),autoPromot(autoProm)
{}

MountainousMission::~MountainousMission()
{
}

int MountainousMission::getAutoProm()
{
	return autoPromot;
}

bool MountainousMission::needAutoProm(int curDay)
{
	return (autoPromot >= (curDay - getFormulationDay()));
}
