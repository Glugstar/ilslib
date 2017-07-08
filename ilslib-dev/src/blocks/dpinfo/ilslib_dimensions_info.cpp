#include "../../../include/blocks/dpinfo/ilslib_dimensions_info.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	DimensionsInfo::DimensionsInfo():
		newLineBreaks(),
		rowsMaxHeight(),
		columnsMaxWidth(),
		rowsTotalWidth(),
		columnsTotalHeight(),
		subComponentsMaxWidth(0),
		subComponentsMaxHeight(0),
		subComponentsTotalWidth(0),
		subComponentsTotalHeight(0),
		totalWidth(0),
		totalHeight(0)
	{
	}
	
	
	void DimensionsInfo::clear()
	{
		newLineBreaks.clear();
		rowsMaxHeight.clear();
		columnsMaxWidth.clear();
		rowsTotalWidth.clear();
		columnsTotalHeight.clear();
		subComponentsMaxWidth = 0;
		subComponentsMaxHeight = 0;
		subComponentsTotalWidth = 0;
		subComponentsTotalHeight = 0;
		totalWidth = 0;
		totalHeight = 0;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




