#include "../../include/events/ilslib_window_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	WindowEvent::WindowEvent():
		Event(),
		eventType(Type::LostFocus),
		windowWidth(0),
		windowHeight(0)
	{
	}
	
	
	WindowEvent::WindowEvent(const WindowEvent& event):
		Event(event),
		eventType(event.eventType),
		windowWidth(event.windowWidth),
		windowHeight(event.windowHeight)
	{
	}
	
	
	WindowEvent::~WindowEvent()
	{
	}
	
	
	WindowEvent::Type WindowEvent::getType() const
	{
		return eventType;
	}
	
	
	int WindowEvent::getWindowWidth() const
	{
		return windowWidth;
	}
	
	
	int WindowEvent::getWindowHeight() const
	{
		return windowHeight;
	}
	
	
	void WindowEvent::setType(Type type)
	{
		eventType = type;
	}
	
	
	void WindowEvent::setWindowWidth(int width)
	{
		windowWidth = width;
	}
	
	
	void WindowEvent::setWindowHeight(int height)
	{
		windowHeight = height;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




