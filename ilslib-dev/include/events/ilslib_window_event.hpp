/*----------------------------------------------------------------------------------
								ilslib_window_event.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_WINDOW_EVENT_HPP
#define ILSLIB_WINDOW_EVENT_HPP

#pragma once

#include "ilslib_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										WindowEvent
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class WindowEvent : public Event
	{
	public:
		// typedefs & enums
		enum Type
		{
			LostFocus, // window has lost focus
			GainedFocus, // window has regained focus
			Resized, // window has resized
			Closed // window is closing
		};
		
		
		// constructors & destructor
		WindowEvent();
		WindowEvent(const WindowEvent& event);
		virtual ~WindowEvent();
		
		
		// functions
		virtual Type getType() const;
		virtual int getWindowWidth() const;
		virtual int getWindowHeight() const;
		virtual void setType(Type type);
		virtual void setWindowWidth(int width);
		virtual void setWindowHeight(int height);
	protected:
		Type eventType;
		int windowWidth;
		int windowHeight;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_WINDOW_EVENT_HPP




