#include "../../include/drawables/ilslib_drawable.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Drawable::Drawable():
		adjustments(nullptr)
	{
	}
	
	
	Drawable::~Drawable()
	{
		delete adjustments;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




