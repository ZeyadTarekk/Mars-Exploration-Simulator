#include "AutoPromotionEvent.h"

AutoPromotionEvent::AutoPromotionEvent(int id):Event(id)
{
}

void AutoPromotionEvent::execute(MarsStation* mStation)
{
	mStation->promoteMountainousToEmergencyMission(getEventDay());

}

AutoPromotionEvent::~AutoPromotionEvent()
{
}
