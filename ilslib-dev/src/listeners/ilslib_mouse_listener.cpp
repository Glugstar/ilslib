#include "../../include/listeners/ilslib_mouse_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	MouseListener::MouseListener(const std::string& newID):
		Listener(newID),
		typeTrigger(MouseEvent::Type::Hover),
		buttonsTrigger()
	{
	}
	
	
	MouseListener::MouseListener(const MouseListener& listener, const std::string& newID):
		Listener(listener, newID),
		typeTrigger(listener.typeTrigger),
		buttonsTrigger(listener.buttonsTrigger)
	{
	}
	
	
	MouseListener::~MouseListener()
	{
	}
	
	
	MouseEvent::Type MouseListener::getTypeTrigger() const
	{
		return typeTrigger;
	}
	
	
	const std::list<MouseButton::Button>& MouseListener::getButtonsTrigger() const
	{
		return buttonsTrigger;
	}
	
	
	bool MouseListener::allButtonsTrigger() const
	{
		return buttonsTrigger.size() == 0;
	}
	
	
	bool MouseListener::triggersOn(MouseButton::Button button, MouseEvent::Type type) const
	{
		if(type == MouseEvent::Type::Drag || type == MouseEvent::Type::Hold ||
			type == MouseEvent::Type::Hover || type == MouseEvent::Type::HoverIn ||
			type == MouseEvent::Type::HoverOut || type == MouseEvent::Type::Move ||
			type == MouseEvent::Type::WheelDown || type == MouseEvent::Type::WheelUp)
			return true;
		
		if(allButtonsTrigger() == true)
			return true;
		
		std::list<MouseButton::Button>::const_iterator i;
		for(i=buttonsTrigger.begin(); i!=buttonsTrigger.end(); ++i)
		{
			if(*i == button)
				return true;
		}
		
		return false;
	}
	
	
	void MouseListener::setTypeTrigger(MouseEvent::Type type)
	{
		typeTrigger = type;
	}
	
	
	void MouseListener::setButtonsTrigger(const std::list<MouseButton::Button>& buttons)
	{
		buttonsTrigger = buttons;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




