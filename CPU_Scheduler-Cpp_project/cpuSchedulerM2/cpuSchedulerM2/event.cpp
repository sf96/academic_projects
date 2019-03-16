#include "event.h"

int Event::GetEventTime()
{
	return event_time;
};

Event::Event(int etime) : event_time(etime)
{
};

Event::~Event() 
{

};
