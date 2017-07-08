/*----------------------------------------------------------------------------------
								ilslib_keyboard_listener.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_KEYBOARD_LISTENER_HPP
#define ILSLIB_KEYBOARD_LISTENER_HPP

#pragma once

#include "ilslib_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										KeyboardListener
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class KeyboardListener : public Listener
	{
	public:
		// constructors & destructor
		KeyboardListener(const std::string& newID);
		KeyboardListener(const KeyboardListener& listener, const std::string& newID);
		virtual ~KeyboardListener();
		
		
		// functions
		virtual KeyboardEvent::Type getTypeTrigger() const;
		virtual const std::set<std::string>& getKeyCodesTrigger() const;
		virtual bool allKeyCodesTrigger() const;
		virtual bool triggersOnKeyAction() const;
		virtual bool triggersOn(const std::string& key) const;
		virtual void setTypeTrigger(KeyboardEvent::Type type);
		virtual void setKeyCodesTrigger(const std::set<std::string>& keyCodes);
	protected:
		KeyboardEvent::Type typeTrigger;
		std::set<std::string> keyCodesTrigger;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_KEYBOARD_LISTENER_HPP




