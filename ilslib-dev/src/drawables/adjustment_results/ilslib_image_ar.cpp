#include "../../../include/drawables/adjustment_results/ilslib_image_ar.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ImageAR::ImageAR():
		AdjustmentResults(),
		textureRectangle(),
		textureZoomX(0.0f),
		textureZoomY(0.0f),
		repeatX(false),
		repeatY(false),
		repeatXFullOnly(false),
		repeatYFullOnly(false),
		mirrorX(false),
		mirrorY(false),
		stretchX(false),
		stretchY(false),
		centerX(false),
		centerY(false),
		transparency(0.0f)
	{
	}
	
	
	ImageAR::~ImageAR()
	{
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




