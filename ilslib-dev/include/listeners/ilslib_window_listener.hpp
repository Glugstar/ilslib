/*----------------------------------------------------------------------------------
								ilslib_window_listener.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_WINDOW_LISTENER_HPP
#define ILSLIB_WINDOW_LISTENER_HPP

#pragma once

#include "ilslib_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										WindowListener
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class WindowListener : public Listener
	{
	public:
		// constructors & destructor
		WindowListener(const std::string& newID);
		WindowListener(const WindowListener& listener, const std::string& newID);
		virtual ~WindowListener();
		
		
		// functions
		virtual WindowEvent::Type getTypeTrigger() const;
		virtual void setTypeTrigger(WindowEvent::Type type);
	protected:
		WindowEvent::Type typeTrigger;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_WINDOW_LISTENER_HPP




