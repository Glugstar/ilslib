/*----------------------------------------------------------------------------------
									ilslib_text.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_TEXT_HPP
#define ILSLIB_TEXT_HPP

#pragma once

#include "adjustment_results/ilslib_text_ar.hpp"
#include "ilslib_drawable.hpp"
#include "../resources/ilslib_font.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Text
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Text : public Drawable
	{
	public:
		// constructors & destructor
		Text(const std::string& newFontID, const std::string& newMessage);
		virtual ~Text();
		
		
		// functions
		virtual TextAR* getTextAR();
		virtual const std::string& getFontID() const;
		virtual const std::string& getMessage() const;
	protected:
		// variables
		std::string fontID;
		std::string message;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_TEXT_HPP




