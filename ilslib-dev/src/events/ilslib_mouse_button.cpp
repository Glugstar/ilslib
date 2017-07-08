#include "../../include/events/ilslib_mouse_button.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	MouseButton::MouseButton():
		button(Button::Left),
		latestPressAction(),
		previousPressAction(),
		latestReleaseAction(),
		previousReleaseAction()
	{
	}
	
	
	MouseButton::~MouseButton()
	{
	}
	
	
	bool MouseButton::buttonIsPressed() const
	{
		if(latestPressAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < 0)
			return true;
		if(latestReleaseAction.actionTime < latestPressAction.actionTime)
			return true;
		
		return false;
	}
	
	
	bool MouseButton::validClickTiming(int maxClickSpeedMS) const
	{
		if(latestPressAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < latestPressAction.actionTime)
			return false;
		
		if(maxClickSpeedMS < 1)
			return true;
		
		int timeDifferential = latestReleaseAction.actionTime -
								latestPressAction.actionTime;
		if(timeDifferential > maxClickSpeedMS)
			return false;
		
		return true;
	}
	
	
	bool MouseButton::validDoubleClickPressTiming(int maxDoubleClickSpeedMS) const
	{
		if(latestPressAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < 0)
			return false;
		if(previousPressAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < previousPressAction.actionTime)
			return false;
		if(latestPressAction.actionTime < latestReleaseAction.actionTime)
			return false;
		
		if(maxDoubleClickSpeedMS < 1)
			return true;
		
		int timeDifferential = latestPressAction.actionTime -
								previousPressAction.actionTime;
		if(timeDifferential > maxDoubleClickSpeedMS)
			return false;
		
		return true;
	}
	
	
	bool MouseButton::validDoubleClickReleaseTiming(int maxDoubleClickSpeedMS) const
	{
		if(latestPressAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < 0)
			return false;
		if(previousPressAction.actionTime < 0)
			return false;
		if(previousReleaseAction.actionTime < 0)
			return false;
		if(latestReleaseAction.actionTime < latestPressAction.actionTime)
			return false;
		if(previousReleaseAction.actionTime < previousPressAction.actionTime)
			return false;
		if(latestPressAction.actionTime < previousReleaseAction.actionTime)
			return false;
		
		if(maxDoubleClickSpeedMS < 1)
			return true;
		
		int timeDifferential = latestReleaseAction.actionTime -
								previousPressAction.actionTime;
		if(timeDifferential > maxDoubleClickSpeedMS)
			return false;
		
		return true;
	}
	
	
	bool MouseButton::validClickArea(int maxClickDistancePixels) const
	{
		if(maxClickDistancePixels < 0)
			return true;
		
		int minX, minY, maxX, maxY;
		maxX = minX = latestPressAction.coordX;
		maxY = minY = latestPressAction.coordY;
		
		minX = latestReleaseAction.coordX < minX ?
				latestReleaseAction.coordX : minX;
		minY = latestReleaseAction.coordY < minY ?
				latestReleaseAction.coordY : minY;
		maxX = latestReleaseAction.coordX > maxX ?
				latestReleaseAction.coordX : maxX;
		maxY = latestReleaseAction.coordY > maxY ?
				latestReleaseAction.coordY : maxY;
		
		if(maxX - minX > maxClickDistancePixels)
			return false;
		if(maxY - minY > maxClickDistancePixels)
			return false;
		
		return true;
	}
	
	
	bool MouseButton::validDoubleClickPressArea(int maxClickDistancePixels) const
	{
		if(maxClickDistancePixels < 0)
			return true;
		
		int minX, minY, maxX, maxY;
		maxX = minX = latestPressAction.coordX;
		maxY = minY = latestPressAction.coordY;
		
		minX = latestReleaseAction.coordX < minX ?
				latestReleaseAction.coordX : minX;
		minY = latestReleaseAction.coordY < minY ?
				latestReleaseAction.coordY : minY;
		maxX = latestReleaseAction.coordX > maxX ?
				latestReleaseAction.coordX : maxX;
		maxY = latestReleaseAction.coordY > maxY ?
				latestReleaseAction.coordY : maxY;
		
		minX = previousPressAction.coordX < minX ?
				previousPressAction.coordX : minX;
		minY = previousPressAction.coordY < minY ?
				previousPressAction.coordY : minY;
		maxX = previousPressAction.coordX > maxX ?
				previousPressAction.coordX : maxX;
		maxY = previousPressAction.coordY > maxY ?
				previousPressAction.coordY : maxY;
		
		if(maxX - minX > maxClickDistancePixels)
			return false;
		if(maxY - minY > maxClickDistancePixels)
			return false;
		
		return true;
	}
	
	
	bool MouseButton::validDoubleClickReleaseArea(int maxClickDistancePixels) const
	{
		if(maxClickDistancePixels < 0)
			return true;
		
		int minX, minY, maxX, maxY;
		maxX = minX = latestPressAction.coordX;
		maxY = minY = latestPressAction.coordY;
		
		minX = latestReleaseAction.coordX < minX ?
				latestReleaseAction.coordX : minX;
		minY = latestReleaseAction.coordY < minY ?
				latestReleaseAction.coordY : minY;
		maxX = latestReleaseAction.coordX > maxX ?
				latestReleaseAction.coordX : maxX;
		maxY = latestReleaseAction.coordY > maxY ?
				latestReleaseAction.coordY : maxY;
		
		minX = previousPressAction.coordX < minX ?
				previousPressAction.coordX : minX;
		minY = previousPressAction.coordY < minY ?
				previousPressAction.coordY : minY;
		maxX = previousPressAction.coordX > maxX ?
				previousPressAction.coordX : maxX;
		maxY = previousPressAction.coordY > maxY ?
				previousPressAction.coordY : maxY;
		
		minX = previousReleaseAction.coordX < minX ?
				previousReleaseAction.coordX : minX;
		minY = previousReleaseAction.coordY < minY ?
				previousReleaseAction.coordY : minY;
		maxX = previousReleaseAction.coordX > maxX ?
				previousReleaseAction.coordX : maxX;
		maxY = previousReleaseAction.coordY > maxY ?
				previousReleaseAction.coordY : maxY;
		
		if(maxX - minX > maxClickDistancePixels)
			return false;
		if(maxY - minY > maxClickDistancePixels)
			return false;
		
		return true;
	}
	
	
	void MouseButton::update(const ButtonAction& newAction, bool press)
	{
		if(press == true)
		{
			previousPressAction = latestPressAction;
			latestPressAction = newAction;
		}
		else
		{
			previousReleaseAction = latestReleaseAction;
			latestReleaseAction = newAction;
		}
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




