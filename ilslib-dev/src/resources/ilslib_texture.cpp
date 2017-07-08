#include "../../include/resources/ilslib_texture.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Texture::Texture(const std::string& uniqueID, void* uniqueRealResource):
		Resource(uniqueID, uniqueRealResource)
	{
	}
	
	
	Texture::~Texture()
	{
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




