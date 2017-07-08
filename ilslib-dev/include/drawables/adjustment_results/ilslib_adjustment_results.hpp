/*----------------------------------------------------------------------------------
							ilslib_adjustment_results.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_ADJUSTMENT_RESULTS_HPP
#define ILSLIB_ADJUSTMENT_RESULTS_HPP

#pragma once


#include "../../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										AdjustmentResults
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct AdjustmentResults
	{
	public:
		// constructors & destructor
		AdjustmentResults();
		virtual ~AdjustmentResults();
		
		
		// variables
		Rectangle coordsRectangle;
		Rectangle cutRectangle;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_ADJUSTMENT_RESULTS_HPP




