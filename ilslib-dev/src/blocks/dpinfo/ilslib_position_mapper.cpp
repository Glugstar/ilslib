#include "../../../include/blocks/dpinfo/ilslib_position_mapper.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	PositionMapper::PositionMapper(PositionInfo* pInfo, const bool xIsPrimary):
		coordPrimary(nullptr),
		coordSecondary(nullptr)
	{
		if(xIsPrimary == true)
		{
			// primary = X axis, secondary = Y axis
			
			coordPrimary = &pInfo->posRectangle.x;
			coordSecondary = &pInfo->posRectangle.y;
		}
		else // xIsPrimary == false
		{
			// primary = Y axis, secondary = X axis
			
			coordPrimary = &pInfo->posRectangle.y;
			coordSecondary = &pInfo->posRectangle.x;
		}
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





