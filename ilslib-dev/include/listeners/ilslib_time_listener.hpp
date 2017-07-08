/*----------------------------------------------------------------------------------
								ilslib_time_listener.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_TIME_LISTENER_HPP
#define ILSLIB_TIME_LISTENER_HPP

#pragma once

#include "ilslib_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										TimeListener
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class TimeListener : public Listener
	{
	public:
		// enums
		enum TimerType
		{
			None,
			Reset,
			ModFrequency
		};
		
		
		// constructors & destructor
		TimeListener(const std::string& newID);
		TimeListener(const TimeListener& listener, const std::string& newID);
		virtual ~TimeListener();
		
		
		// functions
		virtual void setPeriodicTimer(TimerType type, int interval);
		virtual void runCallbackFunction(BasicBlock* block, const Event* eventInfo,
								BlockManager* blockManager, EventQueue* eventQueue);
	protected:
		// variables
		int timerAccumulated;
		int timerInterval;
		TimerType timerType;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_TIME_LISTENER_HPP




