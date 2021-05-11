#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int i, int day):Event(i,day)
{}

PromotionEvent::~PromotionEvent()
{
}

void PromotionEvent::execute(MarsStation* MStation)
{
	EmergencyMission tempEmMission(0, 0, 0, id, 0);

}
