/*----------------------------------------------------------------------------------
								ilslib_position_info.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_POSITION_INFO_HPP
#define ILSLIB_POSITION_INFO_HPP

#pragma once

#include "../../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										PositionInfo
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct PositionInfo
	{
		// constructor
		PositionInfo();
		
		
		// functions
		void clear();
		
		
		// variables
		Rectangle posRectangle;
		Rectangle cutRectangle;
		Rectangle intersectionRectangle;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_POSITION_INFO_HPP





