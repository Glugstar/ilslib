#include "../../include/drawables/ilslib_image.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Image::Image(const std::string& newTextureID):
		Drawable(),
		textureID(newTextureID)
	{
		adjustments = new ImageAR();
	}
	
	
	Image::~Image()
	{
	}
	
	
	ImageAR* Image::getImageAR()
	{
		return (ImageAR*)adjustments;
	}
	
	
	const std::string& Image::getTextureID() const
	{
		return textureID;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




