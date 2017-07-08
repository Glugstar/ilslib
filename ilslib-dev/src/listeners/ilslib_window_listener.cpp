#include "../../include/listeners/ilslib_window_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	WindowListener::WindowListener(const std::string& newID):
		Listener(newID),
		typeTrigger(WindowEvent::Type::LostFocus)
	{
	}
	
	
	WindowListener::WindowListener(const WindowListener& listener, const std::string& newID):
		Listener(listener, newID),
		typeTrigger(listener.typeTrigger)
	{
	}
	
	
	WindowListener::~WindowListener()
	{
	}
	
	
	WindowEvent::Type WindowListener::getTypeTrigger() const
	{
		return typeTrigger;
	}
	
	
	void WindowListener::setTypeTrigger(WindowEvent::Type type)
	{
		typeTrigger = type;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




