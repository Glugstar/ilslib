/*----------------------------------------------------------------------------------
								ilslib_time_event.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_TIME_EVENT_HPP
#define ILSLIB_TIME_EVENT_HPP

#pragma once

#include "ilslib_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											TimeEvent
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class TimeEvent : public Event
	{
	public:
		// constructors & destructor
		TimeEvent();
		TimeEvent(const TimeEvent& event);
		virtual ~TimeEvent();
		
		
		// functions
		virtual int getElapsedTime() const;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_TIME_EVENT_HPP




