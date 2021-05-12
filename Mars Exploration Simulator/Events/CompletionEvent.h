#pragma once
#include"Event.h"
class CompletionEvent:public Event
{

public:
	CompletionEvent(int);
	~CompletionEvent();
	void execute(MarsStation*);

};

