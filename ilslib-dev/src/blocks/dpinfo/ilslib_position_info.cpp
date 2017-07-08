#include "../../../include/blocks/dpinfo/ilslib_position_info.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	PositionInfo::PositionInfo():
		posRectangle(),
		cutRectangle(),
		intersectionRectangle()
	{
	}
	
	
	void PositionInfo::clear()
	{
		posRectangle.clear();
		cutRectangle.clear();
		intersectionRectangle.clear();
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





