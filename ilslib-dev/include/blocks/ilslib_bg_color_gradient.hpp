/*----------------------------------------------------------------------------------
							ilslib_bg_color_gradient.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_BG_COLOR_GRADIENT_HPP
#define ILSLIB_BG_COLOR_GRADIENT_HPP

#pragma once

#include "ilslib_container_style.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	class Texture;
	
	
	
	/*!---------------------------------------------------------------------------------
									BgColorGradient
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ContainerStyle::BgColorGradient
	{
	public:
		// constructors & destructor
		BgColorGradient();
		BgColorGradient(const BgColorGradient& initialGradient,
						const BgColorGradient& finalGradient, float ratio);
		virtual ~BgColorGradient();
		
		
		// functions
		virtual void getFromTexture(const Texture& texture);
		
		
		// variables
		Color topLeftBGColor;
		Color topRightBGColor;
		Color bottomLeftBGColor;
		Color bottomRightBGColor;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_BG_COLOR_GRADIENT_HPP




