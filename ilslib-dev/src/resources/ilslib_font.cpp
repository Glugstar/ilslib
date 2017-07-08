#include "../../include/resources/ilslib_font.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Font::Font(const std::string& uniqueID, void* uniqueRealResource):
		Resource(uniqueID, uniqueRealResource)
	{
	}
	
	
	Font::~Font()
	{
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




