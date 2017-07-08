#include "../../include/base/ilslib_color.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Color::Color():
		red(0),
		green(0),
		blue(0),
		alpha(255)
	{
	}
	
	
	Color::Color(int r, int g, int b, int a):
		red(r),
		green(g),
		blue(b),
		alpha(a)
	{
		if(red < 0)
			red = 0;
		if(green < 0)
			green = 0;
		if(blue < 0)
			blue = 0;
		if(alpha < 0)
			alpha = 0;
		
		if(red > 255)
			red = 255;
		if(green > 255)
			green = 255;
		if(blue > 255)
			blue = 255;
		if(alpha > 255)
			alpha = 255;
	}
	
	
	Color::Color(const Color& initialColor, const Color& finalColor, float ratio):
		red(0),
		green(0),
		blue(0),
		alpha(255)
	{
		if(ratio < 0.0f)
			ratio = 0.0f;
		if(ratio > 1.0f)
			ratio = 1.0f;
		
		float ratio2 = 1.0f - ratio;
		
		red = ((float)finalColor.red) * ratio + ((float)initialColor.red) * ratio2;
		green = ((float)finalColor.green) * ratio + ((float)initialColor.green) * ratio2;
		blue = ((float)finalColor.blue) * ratio + ((float)initialColor.blue) * ratio2;
		alpha = ((float)finalColor.alpha) * ratio + ((float)initialColor.alpha) * ratio2;
		
		if(red < 0)
			red = 0;
		if(green < 0)
			green = 0;
		if(blue < 0)
			blue = 0;
		if(alpha < 0)
			alpha = 0;
		
		if(red > 255)
			red = 255;
		if(green > 255)
			green = 255;
		if(blue > 255)
			blue = 255;
		if(alpha > 255)
			alpha = 255;
	}
	
	
	Color::~Color()
	{
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




