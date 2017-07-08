/*----------------------------------------------------------------------------------
								ilslib_listener.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_LISTENER_HPP
#define ILSLIB_LISTENER_HPP

#pragma once

#include "../events/ilslib_keyboard_event.hpp"
#include "../events/ilslib_mouse_event.hpp"
#include "../events/ilslib_time_event.hpp"
#include "../events/ilslib_window_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Listener
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Listener
	{
	public:
		// constructors & destructor
		Listener(const std::string& newID);
		Listener(const Listener& listener, const std::string& newID);
		virtual ~Listener();
		
		
		// functions
		virtual std::string getID() const;
		virtual bool isActive() const;
		virtual Event::CallbackFunction getCallbackFunction() const;
		virtual void activate();
		virtual void deactivate();
		virtual void setCallbackFunction(Event::CallbackFunction func);
		virtual void runCallbackFunction(BasicBlock* block, const Event* eventInfo,
								BlockManager* blockManager, EventQueue* eventQueue);
	protected:
		std::string id;
		bool active;
		Event::CallbackFunction callbackFunction;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_LISTENER_HPP




