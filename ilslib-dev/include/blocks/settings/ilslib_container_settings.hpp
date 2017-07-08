/*----------------------------------------------------------------------------------
						ilslib_container_settings.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_CONTAINER_SETTINGS_HPP
#define ILSLIB_CONTAINER_SETTINGS_HPP

#pragma once

#include "ilslib_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	class ContainerStyle;
	
	
	
	/*!---------------------------------------------------------------------------------
										ContainerSettings
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ContainerSettings : public Settings
	{
	public:
		// constructors & destructor
		ContainerSettings();
		virtual ~ContainerSettings();
		
		
		// functions
		virtual void loadInnerSpacing(const ContainerStyle* containerStyle);
		unsigned int getInnerSpacingHorizontal() const;
		unsigned int getInnerSpacingVertical() const;
		unsigned int getSpacingHorizontal() const;
		unsigned int getSpacingVertical() const;
		unsigned int getSpacingLeft() const;
		unsigned int getSpacingRight() const;
		unsigned int getSpacingTop() const;
		unsigned int getSpacingBottom() const;
		
		
		// variables
			// empty space inside the container (but outside the contained elements)
		unsigned int innerSpacingLeft;
		unsigned int innerSpacingRight;
		unsigned int innerSpacingTop;
		unsigned int innerSpacingBottom;
			// equal cell width or height and squares for sub-components
			// can cause conflict with sub-component fixed or max sizes
		bool equalCellWidth;
		bool equalCellHeight;
			// offset
		int offsetX;
		int offsetY;
			// other stuff
		bool mouseEventsMultiLayer; // allow mouse events to reach lower layers
		bool mouseEventsSubComponentsFirst; // allow mouse events to run on subcomponents first
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_CONTAINER_SETTINGS_HPP




