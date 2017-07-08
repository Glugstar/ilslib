#include "../../../include/blocks/dpinfo/ilslib_dimensions_mapper.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	DimensionsMapper::DimensionsMapper(DimensionsInfo* dInfo, const bool xIsPrimary):
		newLineBreaks(nullptr),
		lineMaxPrimary(nullptr),
		lineMaxSecondary(nullptr),
		lineTotalPrimary(nullptr),
		lineTotalSecondary(nullptr),
		subComponentsMaxPrimary(nullptr),
		subComponentsMaxSecondary(nullptr),
		subComponentsTotalPrimary(nullptr),
		subComponentsTotalSecondary(nullptr),
		totalPrimary(nullptr),
		totalSecondary(nullptr)
	{
		if(xIsPrimary == true)
		{
			// primary = X axis, secondary = Y axis
			
			newLineBreaks = &dInfo->newLineBreaks;
			
			lineMaxPrimary = &dInfo->columnsMaxWidth;
			lineMaxSecondary = &dInfo->rowsMaxHeight;
			lineTotalPrimary = &dInfo->rowsTotalWidth;
			lineTotalSecondary = &dInfo->columnsTotalHeight;
			
			subComponentsMaxPrimary = &dInfo->subComponentsMaxWidth;
			subComponentsMaxSecondary = &dInfo->subComponentsMaxHeight;
			subComponentsTotalPrimary = &dInfo->subComponentsTotalWidth;
			subComponentsTotalSecondary = &dInfo->subComponentsTotalHeight;
			
			totalPrimary = &dInfo->totalWidth;
			totalSecondary = &dInfo->totalHeight;
		}
		else // xIsPrimary == false
		{
			// primary = Y axis, secondary = X axis
			
			newLineBreaks = &dInfo->newLineBreaks;
			
			lineMaxPrimary = &dInfo->rowsMaxHeight;
			lineMaxSecondary = &dInfo->columnsMaxWidth;
			lineTotalPrimary = &dInfo->columnsTotalHeight;
			lineTotalSecondary = &dInfo->rowsTotalWidth;
			
			subComponentsMaxPrimary = &dInfo->subComponentsMaxHeight;
			subComponentsMaxSecondary = &dInfo->subComponentsMaxWidth;
			subComponentsTotalPrimary = &dInfo->subComponentsTotalHeight;
			subComponentsTotalSecondary = &dInfo->subComponentsTotalWidth;
			
			totalPrimary = &dInfo->totalHeight;
			totalSecondary = &dInfo->totalWidth;
		}
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





