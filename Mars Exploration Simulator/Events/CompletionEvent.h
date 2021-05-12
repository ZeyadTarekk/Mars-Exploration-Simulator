#pragma once
#include"Event.h"
class CompletionEvent:public Event
{

public:
	CompletionEvent(int);
	void execute(MarsStation*);

};

