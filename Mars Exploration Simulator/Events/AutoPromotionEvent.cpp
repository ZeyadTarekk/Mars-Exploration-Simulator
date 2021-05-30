#include "AutoPromotionEvent.h"

AutoPromotionEvent::AutoPromotionEvent(int ed):Event(ed)
{
}

void AutoPromotionEvent::execute(MarsStation* mStation)
{
	mStation->promoteMountainousToEmergencyMission(getEventDay());

}

AutoPromotionEvent::~AutoPromotionEvent()
{
}
