#include"Event.h"
//constructor
Event::Event(int e): eventDay(e > 0 ? e : 0)
{}

//destructor
Event::~Event() {}


//geteventDay
int Event::getEventDay()const { return eventDay; }