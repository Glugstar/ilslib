#include "../../include/events/ilslib_mouse_event.hpp"
#include "../../include/blocks/dpinfo/ilslib_position_info.hpp"
#include "../../include//blocks/settings/ilslib_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	MouseEvent::MouseEvent():
		Event(),
		eventType(Type::Hover),
		eventButton(MouseButton::Button::Left),
		buttonsHistory(),
		absoluteCoordX(0),
		absoluteCoordY(0),
		wheelQuantity(0)
	{
	}
	
	
	MouseEvent::MouseEvent(const MouseEvent& event):
		Event(event),
		eventType(event.eventType),
		eventButton(event.eventButton),
		buttonsHistory(event.buttonsHistory),
		absoluteCoordX(event.absoluteCoordX),
		absoluteCoordY(event.absoluteCoordY),
		wheelQuantity(event.wheelQuantity)
	{
	}
	
	
	MouseEvent::~MouseEvent()
	{
	}
	
	
	bool MouseEvent::eventApplies(const PositionInfo& positionInfo,
								const Settings* settings) const
	{
		if(eventType == Type::Hover || eventType == Type::WheelUp || eventType == Type::WheelDown ||
			eventType == Type::Drag || eventType == Type::Release || eventType == Type::Hold)
			return true;
		
		return eventInsideCutRectangle(positionInfo, settings);
	}
	
	
	bool MouseEvent::eventInsideCutRectangle(const PositionInfo& positionInfo,
								const Settings* settings) const
	{
		int left = 0;
		int right = 0;
		int top = 0;
		int bottom = 0;
		
		if(settings != nullptr)
		{
			left = settings->outterSpacingLeft;
			right = settings->outterSpacingRight;
			top = settings->outterSpacingTop;
			bottom = settings->outterSpacingBottom;
		}
		
		
		if(absoluteCoordX < positionInfo.intersectionRectangle.x + left)
			return false;
		if(absoluteCoordY < positionInfo.intersectionRectangle.y + top)
			return false;
		if(absoluteCoordX >= positionInfo.intersectionRectangle.x - right + positionInfo.intersectionRectangle.width)
			return false;
		if(absoluteCoordY >= positionInfo.intersectionRectangle.y - bottom + positionInfo.intersectionRectangle.height)
			return false;
		return true;
	}
	
	
	MouseEvent::PressedButtons MouseEvent::getPressedButtons() const
	{
		PressedButtons pressedButtons;
		ButtonsHistory::const_iterator i;
		
		for(i=buttonsHistory.begin(); i!=buttonsHistory.end(); ++i)
			if(i->buttonIsPressed() == true)
				pressedButtons.push_back(i->button);
		
		return pressedButtons;
	}
	
	
	MouseEvent::Type MouseEvent::getType() const
	{
		return eventType;
	}
	
	
	MouseButton::Button MouseEvent::getButton() const
	{
		return eventButton;
	}
	
	
	const MouseEvent::ButtonsHistory& MouseEvent::getButtonsHistory() const
	{
		return buttonsHistory;
	}
	
	
	int MouseEvent::getWheelQuantity() const
	{
		return wheelQuantity;
	}
	
	
	void MouseEvent::setType(Type type)
	{
		eventType = type;
	}
	
	
	void MouseEvent::setButton(MouseButton::Button button)
	{
		eventButton = button;
	}
	
	
	void MouseEvent::setCoords(int coordX, int coordY)
	{
		absoluteCoordX = coordX;
		absoluteCoordY = coordY;
	}
	
	
	void MouseEvent::setButtonsHistory(const ButtonsHistory& buttons)
	{
		buttonsHistory = buttons;
	}
	
	
	void MouseEvent::setWheelQuantity(int quantity)
	{
		wheelQuantity = quantity;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




