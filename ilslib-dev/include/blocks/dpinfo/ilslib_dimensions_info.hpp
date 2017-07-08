/*----------------------------------------------------------------------------------
								ilslib_dimensions_info.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_DIMENSIONS_INFO_HPP
#define ILSLIB_DIMENSIONS_INFO_HPP

#pragma once

#include "../../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	// pointer forward dependency class list
	class Layer;
	class Alternative;
	class BasicBlock;
	class Container;
	
	
	
	/*!---------------------------------------------------------------------------------
										DimensionsInfo
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct DimensionsInfo
	{
		// constructor
		DimensionsInfo();
		
		
		// functions
		void clear();
		
		
		// variables
		std::list<unsigned int> newLineBreaks;
		std::vector<int> rowsMaxHeight;
		std::vector<int> columnsMaxWidth;
		std::vector<int> rowsTotalWidth;
		std::vector<int> columnsTotalHeight;
		int subComponentsMaxWidth;
		int subComponentsMaxHeight;
		int subComponentsTotalWidth;
		int subComponentsTotalHeight;
		int totalWidth;
		int totalHeight;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_DIMENSIONS_INFO_HPP




