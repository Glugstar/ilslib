/*----------------------------------------------------------------------------------
								ilslib_keyboard_event.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_KEYBOARD_EVENT_HPP
#define ILSLIB_KEYBOARD_EVENT_HPP

#pragma once

#include "ilslib_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										KeyboardEvent
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class KeyboardEvent : public Event
	{
	public:
		// typedefs & enums
		enum Type
		{
			Press, // keyboard button pressed
			Release, // release of pressed keyboard button
			Hold, // keyboard button held pressed
			TextEntered // character was entered
		};
		typedef std::pair<std::string, int> KeyDetails;
		typedef std::list<KeyDetails> KeysHistory;
		
		
		// constructors & destructor
		KeyboardEvent();
		KeyboardEvent(const KeyboardEvent& event);
		virtual ~KeyboardEvent();
		
		
		// functions
		virtual Type getType() const;
		virtual wchar_t getTextChar() const;
		virtual std::string getKeyCode() const;
		virtual const KeysHistory& getKeysHistory() const;
		virtual void setType(Type type);
		virtual void setTextChar(wchar_t myChar);
		virtual void setKeyCode(const std::string& code);
		virtual void setKeysHistory(const KeysHistory& keys);
		
		template<class T>
		static std::string generateKeyCode(const T& key);
		
		template<class T>
		static T generateKey(const std::string& keyCode);
	protected:
		Type eventType;
		wchar_t textChar;
		std::string keyCode;
		KeysHistory keysHistory;
	};
	
	
	template<class T>
	std::string KeyboardEvent::generateKeyCode(const T& key)
	{
		return Support::NumberToString(key);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_KEYBOARD_EVENT_HPP




