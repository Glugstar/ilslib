/*----------------------------------------------------------------------------------
								ilslib_event.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_EVENT_HPP
#define ILSLIB_EVENT_HPP

#pragma once

#include "../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	class BasicBlock;
	class BlockManager;
	class EventQueue;
	class Listener;
	
	
	
	/*!---------------------------------------------------------------------------------
											Event
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Event
	{
	public:
		// typedefs
		typedef void (*CallbackFunction) (Listener* listener, BasicBlock* block, const Event* eventInfo,
											BlockManager* blockManager, EventQueue* eventQueue);
		
		
		// constructors & destructor
		Event();
		Event(const Event& event);
		virtual ~Event();
		
		
		// functions
		virtual void setEventTime(int eTime);
		virtual void setEventLastTime(int eTime);
		virtual int getEventTime() const;
		virtual int getEventLastTime() const;
		virtual int getElapsedTime() const;
	protected:
		// variables
		int eventTime;
		int eventLastTime;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_EVENT_HPP




