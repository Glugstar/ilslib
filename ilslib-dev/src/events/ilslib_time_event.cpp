#include "../../include/events/ilslib_time_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	TimeEvent::TimeEvent():
		Event()
	{
	}
	
	
	TimeEvent::TimeEvent(const TimeEvent& event):
		Event(event)
	{
	}
	
	
	TimeEvent::~TimeEvent()
	{
	}
	
	
	int TimeEvent::getElapsedTime() const
	{
		if(eventTime < 0)
			return 0;
		if(eventLastTime < 0)
			return 0;
		if(eventTime < eventLastTime)
			return 0;
		return eventTime - eventLastTime;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




