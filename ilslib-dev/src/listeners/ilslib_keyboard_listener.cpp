#include "../../include/listeners/ilslib_keyboard_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	KeyboardListener::KeyboardListener(const std::string& newID):
		Listener(newID),
		typeTrigger(KeyboardEvent::Type::Press),
		keyCodesTrigger()
	{
	}
	
	
	KeyboardListener::KeyboardListener(const KeyboardListener& listener, const std::string& newID):
		Listener(listener, newID),
		typeTrigger(listener.typeTrigger),
		keyCodesTrigger(listener.keyCodesTrigger)
	{
	}
	
	
	KeyboardListener::~KeyboardListener()
	{
	}
	
	
	KeyboardEvent::Type KeyboardListener::getTypeTrigger() const
	{
		return typeTrigger;
	}
	
	
	const std::list<std::string>& KeyboardListener::getKeyCodesTrigger() const
	{
		return keyCodesTrigger;
	}
	
	
	bool KeyboardListener::allKeyCodesTrigger() const
	{
		return keyCodesTrigger.size() == 0;
	}
	
	
	bool KeyboardListener::triggersOn(const std::string& key) const
	{
		if(allKeyCodesTrigger() == true)
			return true;
		
		std::list<std::string>::const_iterator i;
		for(i=keyCodesTrigger.begin(); i!=keyCodesTrigger.end(); ++i)
		{
			if(*i == key)
				return true;
		}
		
		return false;
	}
	
	
	void KeyboardListener::setTypeTrigger(KeyboardEvent::Type type)
	{
		typeTrigger = type;
	}
	
	
	void KeyboardListener::setKeyCodesTrigger(const std::list<std::string>& keyCodes)
	{
		keyCodesTrigger = keyCodes;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




