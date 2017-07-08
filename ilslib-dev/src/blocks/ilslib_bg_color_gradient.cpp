#include "../../include/blocks/ilslib_bg_color_gradient.hpp"
#include "../../include/resources/ilslib_texture.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ContainerStyle::BgColorGradient::BgColorGradient():
		topLeftBGColor(),
		topRightBGColor(),
		bottomLeftBGColor(),
		bottomRightBGColor()
	{
	}
	
	
	ContainerStyle::BgColorGradient::BgColorGradient(const BgColorGradient& initialGradient,
						const BgColorGradient& finalGradient, float ratio):
		topLeftBGColor(initialGradient.topLeftBGColor, finalGradient.topLeftBGColor, ratio),
		topRightBGColor(initialGradient.topRightBGColor, finalGradient.topRightBGColor, ratio),
		bottomLeftBGColor(initialGradient.bottomLeftBGColor, finalGradient.bottomLeftBGColor, ratio),
		bottomRightBGColor(initialGradient.bottomRightBGColor, finalGradient.bottomRightBGColor, ratio)
	{
	}
	
	
	ContainerStyle::BgColorGradient::~BgColorGradient()
	{
	}
	
	
	void ContainerStyle::BgColorGradient::getFromTexture(const Texture& texture)
	{
		if(texture.getWidth() != 2 && texture.getHeight() != 2)
			return;
		
		topLeftBGColor = texture.getColor(0, 0);
		topRightBGColor = texture.getColor(1, 0);
		bottomLeftBGColor = texture.getColor(0, 1);
		bottomRightBGColor = texture.getColor(1, 1);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





