/*----------------------------------------------------------------------------------
					ilslib_rectangle_color_ar.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_RECTANGLE_COLOR_AR_HPP
#define ILSLIB_RECTANGLE_COLOR_AR_HPP

#pragma once

#include "ilslib_adjustment_results.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
									RectangleColorAR
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct RectangleColorAR : public AdjustmentResults
	{
	public:
		// constructors & destructor
		RectangleColorAR();
		virtual ~RectangleColorAR();
		
		
		// variables
		Color fillColor;
		Color outlineColor;
		int outlineThickness;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_RECTANGLE_COLOR_AR_HPP




