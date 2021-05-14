#pragma once
#include"Event.h"
#include"../MarsStation/MarsStation.h"
class CompletionEvent:public Event
{

public:
	CompletionEvent(int);
	~CompletionEvent();
	void execute(MarsStation*);

};

