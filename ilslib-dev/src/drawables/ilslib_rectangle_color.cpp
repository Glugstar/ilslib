#include "../../include/drawables/ilslib_rectangle_color.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	RectangleColor::RectangleColor():
		Drawable()
	{
		adjustments = new RectangleColorAR();
	}
	
	
	RectangleColor::~RectangleColor()
	{
	}
	
	
	RectangleColorAR* RectangleColor::getRectangleColorAR()
	{
		return (RectangleColorAR*)adjustments;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




