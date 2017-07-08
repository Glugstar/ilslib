#include "../../include/events/ilslib_keyboard_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	KeyboardEvent::KeyboardEvent():
		Event(),
		eventType(Type::Hold),
		textChar(),
		keyCode(),
		keysHistory()
	{
	}
	
	
	KeyboardEvent::KeyboardEvent(const KeyboardEvent& event):
		Event(event),
		eventType(event.eventType),
		keyCode(event.keyCode),
		keysHistory(event.keysHistory)
	{
	}
	
	
	KeyboardEvent::~KeyboardEvent()
	{
	}
	
	
	KeyboardEvent::Type KeyboardEvent::getType() const
	{
		return eventType;
	}
	
	
	bool KeyboardEvent::triggersOnKeyAction() const
	{
		if(eventType == Type::Press ||
			eventType == Type::Release)
			return true;
		
		return false;
	}
	
	
	wchar_t KeyboardEvent::getTextChar() const
	{
		return textChar;
	}
	
	
	std::string KeyboardEvent::getKeyCode() const
	{
		return keyCode;
	}
	
	
	const KeyboardEvent::KeysHistory& KeyboardEvent::getKeysHistory() const
	{
		return keysHistory;
	}
	
	
	void KeyboardEvent::setType(Type type)
	{
		eventType = type;
	}
	
	
	void KeyboardEvent::setTextChar(wchar_t myChar)
	{
		textChar = myChar;
	}
	
	
	void KeyboardEvent::setKeyCode(const std::string& code)
	{
		keyCode = code;
	}
	
	
	void KeyboardEvent::setKeysHistory(const KeysHistory& keys)
	{
		keysHistory = keys;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




