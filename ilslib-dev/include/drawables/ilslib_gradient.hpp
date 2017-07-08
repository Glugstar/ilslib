/*----------------------------------------------------------------------------------
								ilslib_gradient.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_GRADIENT_HPP
#define ILSLIB_GRADIENT_HPP

#pragma once

#include "adjustment_results/ilslib_gradient_ar.hpp"
#include "ilslib_drawable.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Gradient
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Gradient : public Drawable
	{
	public:
		// constructors & destructor
		Gradient();
		virtual ~Gradient();
		
		
		// functions
		virtual GradientAR* getGradientAR();
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_GRADIENT_HPP




