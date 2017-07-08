#include "../../include/drawables/ilslib_gradient.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Gradient::Gradient():
		Drawable()
	{
		adjustments = new GradientAR();
	}
	
	
	Gradient::~Gradient()
	{
	}
	
	
	GradientAR* Gradient::getGradientAR()
	{
		return (GradientAR*)adjustments;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




