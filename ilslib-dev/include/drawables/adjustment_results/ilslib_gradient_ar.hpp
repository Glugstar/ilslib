/*----------------------------------------------------------------------------------
						ilslib_gradient_ar.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_GRADIENT_AR_HPP
#define ILSLIB_GRADIENT_AR_HPP

#pragma once

#include "ilslib_adjustment_results.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										GradientAR
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct GradientAR : public AdjustmentResults
	{
	public:
		// constructors & destructor
		GradientAR();
		virtual ~GradientAR();
		
		
		// variables
		Color topLeftColor;
		Color topRightColor;
		Color bottomLeftColor;
		Color bottomRightColor;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_GRADIENT_AR_HPP




