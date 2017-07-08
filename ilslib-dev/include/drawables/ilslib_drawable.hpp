/*----------------------------------------------------------------------------------
								ilslib_drawable.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_DRAWABLE_HPP
#define ILSLIB_DRAWABLE_HPP

#pragma once

#include "adjustment_results/ilslib_adjustment_results.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										Drawable
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Drawable
	{
	public:
		// constructors & destructor
		Drawable();
		virtual ~Drawable();
	protected:
		// variables
		AdjustmentResults* adjustments;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_DRAWABLE_HPP




