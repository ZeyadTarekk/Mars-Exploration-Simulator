#include "CompletionEvent.h"

CompletionEvent::CompletionEvent(int eV):Event(eV)
{

}

CompletionEvent::~CompletionEvent()
{
}

void CompletionEvent::execute(MarsStation*m)
{
	while (m->isCompleted(getEventDay()))
	{
		m->addToCompletedMission(getEventDay());
	}
	m->moveRoverFromExcuetionToCheckUp(getEventDay());
}
