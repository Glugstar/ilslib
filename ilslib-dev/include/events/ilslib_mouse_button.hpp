/*----------------------------------------------------------------------------------
								ilslib_mouse_button.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_MOUSE_BUTTON_HPP
#define ILSLIB_MOUSE_BUTTON_HPP

#pragma once

#include "ilslib_event.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										MouseButton
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class MouseButton
	{
	public:
		// typedefs & enums
		enum Button
		{
			Left,
			Right,
			Middle
		};
		struct ButtonAction
		{
			int actionTime;
			int coordX;
			int coordY;
			ButtonAction():
				actionTime(-1),
				coordX(0),
				coordY(0)
			{
			}
		};
		
		
		// constructors & destructor
		MouseButton();
		virtual ~MouseButton();
		
		
		// functions
		virtual bool buttonIsPressed() const;
		virtual bool validClickTiming(int maxClickSpeedMS) const;
		virtual bool validDoubleClickPressTiming(int maxDoubleClickSpeedMS) const;
		virtual bool validDoubleClickReleaseTiming(int maxDoubleClickSpeedMS) const;
		virtual bool validClickArea(int maxClickDistancePixels) const;
		virtual bool validDoubleClickPressArea(int maxClickDistancePixels) const;
		virtual bool validDoubleClickReleaseArea(int maxClickDistancePixels) const;
		virtual void update(const ButtonAction& newAction, bool press);
		
		
		// variables
		Button button;
		ButtonAction latestPressAction;
		ButtonAction previousPressAction;
		ButtonAction latestReleaseAction;
		ButtonAction previousReleaseAction;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_MOUSE_BUTTON_HPP




