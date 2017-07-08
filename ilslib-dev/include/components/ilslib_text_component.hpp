/*----------------------------------------------------------------------------------
							ilslib_text_component.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_TEXT_COMPONENT_HPP
#define ILSLIB_TEXT_COMPONENT_HPP

#pragma once

#include "../blocks/ilslib_component.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										TextComponent
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class TextComponent : public Component
	{
	public:
		// constructors & destructor
		TextComponent(const std::string& uniqueID);
		virtual ~TextComponent();
		
		
		// functions
		virtual void step1A_minimize();
		virtual void step2C_addToDrawableMap(DrawableMap* drawables);
		
		
		// variables
		const ResourceManager* resManager;
		std::string text;
		std::string fontID;
		unsigned int textSize;
		unsigned int shadowOffset;
		Color textColor;
		Color shadowColor;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_TEXT_COMPONENT_HPP




