#include "CompletionEvent.h"

CompletionEvent::CompletionEvent(int eV):Event(eV)
{

}

CompletionEvent::~CompletionEvent()
{
}

void CompletionEvent::execute(MarsStation*m)
{
	if (m->isCompleted(getEventDay()))
	{
		m->addToCompletedMission(getEventDay());
		m->moveRoverFromExcuetionToCheckUp(getEventDay());
	}

}
