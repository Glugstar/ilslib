/*----------------------------------------------------------------------------------
							ilslib_position_mapper.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_POSITION_MAPPER_HPP
#define ILSLIB_POSITION_MAPPER_HPP

#pragma once

#include "ilslib_position_info.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										PositionMapper
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct PositionMapper
	{
		// constructor
		PositionMapper(PositionInfo* pInfo, const bool xIsPrimary);
		
		
		// variables
		int* coordPrimary;
		int* coordSecondary;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_POSITION_MAPPER_HPP






