#include"Event.h"
//constructor
Event::Event(int e) :eventDay(e > 0 ? e : 0)
{}

//destructor
Event::~Event() {}


//getId
//int Event::getId()const { return id; }


//geteventDay
int Event::getEventDay()const { return eventDay; }