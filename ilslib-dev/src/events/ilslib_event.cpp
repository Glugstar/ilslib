#include "../../include/events/ilslib_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Event::Event():
		eventTime(0),
		eventLastTime(0)
	{
	}
	
	
	Event::Event(const Event& event):
		eventTime(event.eventTime),
		eventLastTime(event.eventLastTime)
	{
	}
	
	
	Event::~Event()
	{
	}
	
	
	void Event::setEventTime(int eTime)
	{
		eventTime = eTime;
	}
	
	
	void Event::setEventLastTime(int eTime)
	{
		eventLastTime = eTime;
	}
	
	
	int Event::getEventTime() const
	{
		return eventTime;
	}
	
	
	int Event::getEventLastTime() const
	{
		return eventLastTime;
	}
	
	
	int Event::getElapsedTime() const
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




