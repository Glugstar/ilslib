/*----------------------------------------------------------------------------------
								ilslib_mouse_listener.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_MOUSE_LISTENER_HPP
#define ILSLIB_MOUSE_LISTENER_HPP

#pragma once

#include "ilslib_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										MouseListener
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class MouseListener : public Listener
	{
	public:
		// constructors & destructor
		MouseListener(const std::string& newID);
		MouseListener(const MouseListener& listener, const std::string& newID);
		virtual ~MouseListener();
		
		
		// functions
		virtual MouseEvent::Type getTypeTrigger() const;
		virtual const std::set<MouseButton::Button>& getButtonsTrigger() const;
		virtual bool allButtonsTrigger() const;
		virtual bool triggersOnButtonAction() const;
		virtual bool triggersOn(MouseButton::Button button, MouseEvent::Type type) const;
		virtual void setTypeTrigger(MouseEvent::Type type);
		virtual void setButtonsTrigger(const std::set<MouseButton::Button>& buttons);
	protected:
		MouseEvent::Type typeTrigger;
		std::set<MouseButton::Button> buttonsTrigger;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_MOUSE_LISTENER_HPP




