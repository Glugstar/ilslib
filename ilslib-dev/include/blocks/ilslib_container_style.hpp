/*----------------------------------------------------------------------------------
								ilslib_container_style.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_CONTAINER_STYLE_HPP
#define ILSLIB_CONTAINER_STYLE_HPP

#pragma once

#include "../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	class Image;
	class DrawableMap;
	class Container;
	class GradientAR;
	
	
	
	/*!---------------------------------------------------------------------------------
										ContainerStyle
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ContainerStyle
	{
	public:
		// classes
		class BgColorGradient;
		class Selector;
		
		
		// enums
		enum BorderType
		{
			Stretch,
			Repeat
		};
		
		
		// constructors & destructor
		ContainerStyle(const std::string& styleID);
		virtual ~ContainerStyle();
		
		
		// functions
		virtual const std::string& getID() const;
		virtual void addBackground(DrawableMap* drawables, const Container* container,
									const Selector& styleSelector) const;
		virtual void addBorder(DrawableMap* drawables, const Container* container,
									const Selector& styleSelector) const;
		
		
		// variables
		int leftBGMargin;
		int rightBGMargin;
		int topBGMargin;
		int bottomBGMargin;
		
		int leftBorderMargin;
		int rightBorderMargin;
		int topBorderMargin;
		int bottomBorderMargin;
		
		int leftContentMargin;
		int rightContentMargin;
		int topContentMargin;
		int bottomContentMargin;
		
		int lineBorderThickness;
		int borderCornerOverlap;
		
		BorderType leftBorderType;
		BorderType rightBorderType;
		BorderType topBorderType;
		BorderType bottomBorderType;
		
		std::vector<BgColorGradient> backgroundColors;
		std::vector<Color> lineBorderColors;
		std::vector<std::string> bordersResourcesID;
	protected:
		// variables
		std::string id;
		
		
		// functions
		virtual void addImageBorder(DrawableMap* drawables, const Container* container,
									const Selector& styleSelector) const;
		virtual void addLineBorder(DrawableMap* drawables, const Container* container,
									const Selector& styleSelector) const;
		virtual Image* getImage(const std::string& imageID,
								const Rectangle& coordsRectangle,
								const Rectangle& cutRectangle) const;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#include "ilslib_bg_color_gradient.hpp"



#endif // ILSLIB_CONTAINER_STYLE_HPP




