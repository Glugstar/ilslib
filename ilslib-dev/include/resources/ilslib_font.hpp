/*----------------------------------------------------------------------------------
									ilslib_font.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_FONT_HPP
#define ILSLIB_FONT_HPP

#pragma once

#include "ilslib_resource.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Font
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Font : public Resource
	{
	public:
		// constructors & destructor
		Font(const std::string& uniqueID, void* uniqueRealResource);
		virtual ~Font();
		
		
		// functions
		virtual Rectangle getTextSize(unsigned int charSize, const std::string& text) const = 0;
		virtual unsigned int getLineSpacing(unsigned int charSize) const = 0;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_FONT_HPP




