/*----------------------------------------------------------------------------------
								ilslibsfml_font.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library - SFML Adapter.
----------------------------------------------------------------------------------*/
#ifndef ILSLIBSFML_FONT_HPP
#define ILSLIBSFML_FONT_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "../../include/resources/ilslib_font.hpp"



/*----------------------------------------------------------------------------------
									ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Font
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Font : public ILSLib::Font
	{
	public:
		// constructors & destructor
		Font(const std::string& uniqueID, void* uniqueRealResource);
		virtual ~Font();
		
		
		// functions
		virtual ILSLib::Rectangle getTextSize(unsigned int charSize, const std::string& text) const;
		virtual unsigned int getLineSpacing(unsigned int charSize) const;
	};
	
	
	
} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_FONT_HPP




