/*----------------------------------------------------------------------------------
							ilslib_rectangle_color.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_RECTANGLE_COLOR_HPP
#define ILSLIB_RECTANGLE_COLOR_HPP

#pragma once

#include "adjustment_results/ilslib_rectangle_color_ar.hpp"
#include "ilslib_drawable.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										RectangleColor
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class RectangleColor : public Drawable
	{
	public:
		// constructors & destructor
		RectangleColor();
		virtual ~RectangleColor();
		
		
		// functions
		virtual RectangleColorAR* getRectangleColorAR();
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_RECTANGLE_COLOR_HPP




