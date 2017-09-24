#include "../../include/base/ilslib_vector.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Vector::Vector():
		x(0),
		y(0)
	{
	}
	
	
	Vector::Vector(int newX, int newY):
		x(newX),
		y(newY)
	{
	}
	
	
	void Vector::swapValues()
	{
	    int tmp = x;
	    x = y;
	    y = tmp;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




