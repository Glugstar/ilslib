/*----------------------------------------------------------------------------------
							ilslib_dimensions_mapper.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_DIMENSIONS_MAPPER_HPP
#define ILSLIB_DIMENSIONS_MAPPER_HPP

#pragma once

#include "ilslib_dimensions_info.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										DimensionsMapper
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct DimensionsMapper
	{
		// constructor
		DimensionsMapper(DimensionsInfo* dInfo, const bool xIsPrimary);
		
		
		// variables
		std::list<unsigned int>* newLineBreaks;
		std::vector<int>* lineMaxPrimary;
		std::vector<int>* lineMaxSecondary;
		std::vector<int>* lineTotalPrimary;
		std::vector<int>* lineTotalSecondary;
		int* subComponentsMaxPrimary;
		int* subComponentsMaxSecondary;
		int* subComponentsTotalPrimary;
		int* subComponentsTotalSecondary;
		int* totalPrimary;
		int* totalSecondary;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_DIMENSIONS_MAPPER_HPP





