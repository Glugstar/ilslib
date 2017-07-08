#include "../../include/base/ilslib_rectangle.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Rectangle::Rectangle():
		x(0),
		y(0),
		width(0),
		height(0)
	{
	}
	
	
	bool Rectangle::isValid() const
	{
		if(width > 0 && height > 0)
			return true;
		return false;
	}
	
	
	void Rectangle::clear()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
	
	
	Rectangle Rectangle::intersect(const Rectangle& otherRectangle) const
	{
		int maxX, maxY;
		maxX = x > otherRectangle.x ? x : otherRectangle.x;
		maxY = y > otherRectangle.y ? y : otherRectangle.y;
		
		int w, h;
		w = x + width < otherRectangle.x + otherRectangle.width ?
			x + width : otherRectangle.x + otherRectangle.width;
		h = y + height < otherRectangle.y + otherRectangle.height ?
			y + height : otherRectangle.y + otherRectangle.height;
		
		Rectangle newRectangle;
		
		if(w - maxX > 0 && h - maxY > 0)
		{
			newRectangle.x = maxX;
			newRectangle.y = maxY;
			newRectangle.width = w - maxX;
			newRectangle.height = h - maxY;
		}
		
		return newRectangle;
	}
	
	
	bool Rectangle::isInteriorOf(const Rectangle& biggerRectangle) const
	{
		if(x < biggerRectangle.x)
			return false;
		if(y < biggerRectangle.y)
			return false;
		if(x + width > biggerRectangle.x + biggerRectangle.width)
			return false;
		if(y + height > biggerRectangle.y + biggerRectangle.height)
			return false;
		
		return true;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




