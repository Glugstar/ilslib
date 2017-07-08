/*----------------------------------------------------------------------------------
								ilslib_settings.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_SETTINGS_HPP
#define ILSLIB_SETTINGS_HPP

#pragma once

#include "../../base/ilslib_support.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										Settings
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct Settings
	{
		// enums
		/*! @brief The directionality of component flow
		(Latin script paragraphs are HorizontalFirst). */
		enum AxisPriority
		{
			HorizontalFirst,
			VerticalFirst
		};
		/*! @brief How spread out the content is
		(Latin script paragraphs are Minimize). */
		enum SizePolicy
		{
			Minimize,
			Neutral,
			Maximize
		};
		/*! @brief Where are the components located
		(Latin script paragraphs are LeftOrUpperGravity). */
		enum Gravity
		{
			LeftOrUpperGravity,
			RightOrLowerGravity,
			CenterGravity,
			SpreadOut
		};
		/*! @brief Where are the components located (within their block)
		(Latin script paragraphs are LeftOrUpperAlignment). */
		enum Alignment
		{
			LeftOrUpperAlignment,
			RightOrLowerAlignment,
			CenterAlignment
		};
		/*! @brief In which direction are the components displayed
		(Latin script paragraphs are RightOrLowerFlow). */
		enum Flow
		{
			LeftOrUpperFlow,
			RightOrLowerFlow
		};
		/*! @brief How is the block displayed */
		enum Visibility
		{
			Visible,
			Hidden, // takes up space
			Collapse, // takes no space (except in tables, where it reserves a cell), and is invisible
			IgnoreBlock // takes no space (tables included), and is invisible
		};
		/*! @brief Computation step */
		enum Step
		{
			s0A_clear,
			s0B_applyTransformations,
			s0C_optimizeListeners,
			s1A_minimize,
			s1B_adjust,
			s1C_maximize,
			s1D_reAdjust,
			s2A_determinePositions,
			s2B_determineCutRectangles,
			s2C_addToDrawableMap
		};
		
		
		// constructors & destructor
		Settings();
		virtual ~Settings();
		
		
		// functions
		virtual unsigned int getMinAppliedInnerWidth() const;
		virtual unsigned int getMinAppliedInnerHeight() const;
		virtual unsigned int getMaxAppliedInnerWidth() const;
		virtual unsigned int getMaxAppliedInnerHeight() const;
		virtual unsigned int getOutterSpacingHorizontal() const;
		virtual unsigned int getOutterSpacingVertical() const;
		
		
		// variables
			// size specifications; 0 means to be ignored
		unsigned int fixedWidth;
		unsigned int fixedHeight;
		unsigned int minWidth;
		unsigned int minHeight;
		unsigned int maxWidth;
		unsigned int maxHeight;
			// empty space outside the element
		unsigned int outterSpacingLeft;
		unsigned int outterSpacingRight;
		unsigned int outterSpacingTop;
		unsigned int outterSpacingBottom;
			// gravity, alignment and size policy
		Gravity horizontalGravity;
		Gravity verticalGravity;
		Alignment horizontalAlignment;
		Alignment verticalAlignment;
		SizePolicy horizontalSizePolicy;
		SizePolicy verticalSizePolicy;
			// other stuff
		Visibility visibility;
		bool preNewLine;
		bool postNewLine;
		bool ignoreDisplayCuts; // true to display components outside their boundaries if they don't fit
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_SETTINGS_HPP




