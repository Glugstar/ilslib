#include "../../../include/drawables/adjustment_results/ilslib_text_ar.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	TextAR::TextAR():
		AdjustmentResults(),
		bold(false),
		italic(false),
		underline(false),
		fontSize(1.0f),
		fontColor(),
		highlightColor(),
		firstShadowOffsetX(0),
		firstShadowOffsetY(0),
		firstShadowColor(),
		secondShadowOffsetX(0),
		secondShadowOffsetY(0),
		secondShadowColor(),
		mirrorX(false),
		mirrorY(false),
		stretchX(false),
		stretchY(false),
		horizontalPriority(true),
		leftToRight(true),
		topToBottom(true)
	{
	}
	
	
	TextAR::~TextAR()
	{
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




