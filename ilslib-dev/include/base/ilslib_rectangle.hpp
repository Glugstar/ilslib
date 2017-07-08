/*----------------------------------------------------------------------------------
								ilslib_rectangle.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_RECTANGLE_HPP
#define ILSLIB_RECTANGLE_HPP

#pragma once



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Rectangle
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct Rectangle
	{
		// constructor
		Rectangle();
		
		
		// functions
		bool isValid() const;
		void clear();
		Rectangle intersect(const Rectangle& otherRectangle) const;
		bool isInteriorOf(const Rectangle& biggerRectangle) const;
		
		
		// variables
		int x;
		int y;
		int width;
		int height;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_RECTANGLE_HPP





