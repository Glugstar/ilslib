/*----------------------------------------------------------------------------------
								ilslib_event_queue.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_EVENT_QUEUE_HPP
#define ILSLIB_EVENT_QUEUE_HPP

#pragma once

#include "../listeners/ilslib_mouse_listener.hpp"
#include "../listeners/ilslib_keyboard_listener.hpp"
#include "../listeners/ilslib_time_listener.hpp"
#include "../listeners/ilslib_window_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										EventQueue
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class EventQueue
	{
	public:
		// typedefs
		typedef std::tuple<std::string, const Event*, BlockManager*, std::string> EventTuple;
		
		
		// constructors & destructor
		EventQueue();
		virtual ~EventQueue();
		
		
		// functions
		virtual bool hasEvents() const;
		virtual void pushEventFront(const std::string& listenerID, const Event* event,
									BlockManager* blockManager, const std::string basicBlockPath);
		virtual void pushEventBack(const std::string& listenerID, const Event* event,
									BlockManager* blockManager, const std::string basicBlockPath);
		virtual void parseNextEvent();
		virtual void clear();
	protected:
		// variables
		std::list<EventTuple> events;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_EVENT_QUEUE_HPP





