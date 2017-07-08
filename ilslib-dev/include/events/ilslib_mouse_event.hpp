/*----------------------------------------------------------------------------------
								ilslib_mouse_event.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_MOUSE_EVENT_HPP
#define ILSLIB_MOUSE_EVENT_HPP

#pragma once

#include "ilslib_event.hpp"
#include "ilslib_mouse_button.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	class PositionInfo;
	class Settings;
	
	
	
	/*!---------------------------------------------------------------------------------
											MouseEvent
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class MouseEvent : public Event
	{
	public:
		// typedefs & enums
		enum Type
		{
			Hover, // mouse held over the object
			Move, // mouse move
			HoverIn, // mouse just got over the object
			HoverOut, // mouse just got away from the object
			WheelUp, // mouse wheel up
			WheelDown, // mouse wheel down
			Press, // mouse button pressed
			Drag, // mouse move while mouse button is pressed
			Release, // release of pressed mouse button
			Hold, // mouse button held pressed
			Click, // mouse button clicked (press + release)
			DoubleClickPress, // mouse button double click, triggered on second press
			DoubleClickRelease // mouse button double click, triggered on second release
		};
		typedef std::list<MouseButton> ButtonsHistory;
		typedef std::list<MouseButton::Button> PressedButtons;
		
		
		// constructors & destructor
		MouseEvent();
		MouseEvent(const MouseEvent& event);
		virtual ~MouseEvent();
		
		
		// functions
		virtual bool eventApplies(const PositionInfo& positionInfo,
								const Settings* settings = nullptr) const;
		virtual bool eventInsideCutRectangle(const PositionInfo& positionInfo,
								const Settings* settings) const;
		virtual PressedButtons getPressedButtons() const;
		virtual Type getType() const;
		virtual bool triggersOnButtonAction() const;
		virtual MouseButton::Button getButton() const;
		virtual const ButtonsHistory& getButtonsHistory() const;
		virtual int getWheelQuantity() const;
		virtual void setType(Type type);
		virtual void setButton(MouseButton::Button button);
		virtual void setCoords(int coordX, int coordY);
		virtual void setButtonsHistory(const ButtonsHistory& buttons);
		virtual void setWheelQuantity(int quantity);
	protected:
		Type eventType;
		MouseButton::Button eventButton;
		ButtonsHistory buttonsHistory;
		int absoluteCoordX;
		int absoluteCoordY;
		int wheelQuantity;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_MOUSE_EVENT_HPP




