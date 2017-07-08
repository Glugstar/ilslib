/*----------------------------------------------------------------------------------
						ilslib_text_ar.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_TEXT_AR_HPP
#define ILSLIB_TEXT_AR_HPP

#pragma once

#include "ilslib_adjustment_results.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											TextAR
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct TextAR : public AdjustmentResults
	{
	public:
		// constructors & destructor
		TextAR();
		virtual ~TextAR();
		
		
		// variables
		bool bold;
		bool italic;
		bool underline;
		
		float fontSize;
		Color fontColor;
		
		// enabled only if highlightColor.alpha < 0.999
		Color highlightColor;
		
		// enabled only if firstShadowColor.alpha < 0.999
		int firstShadowOffsetX;
		int firstShadowOffsetY;
		Color firstShadowColor;
		
		// enabled only if secondShadowColor.alpha < 0.999
		int secondShadowOffsetX;
		int secondShadowOffsetY;
		Color secondShadowColor;
		
		bool mirrorX;
		bool mirrorY;
		
		bool stretchX;
		bool stretchY;
		
		bool horizontalPriority;
		bool leftToRight;
		bool topToBottom;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_TEXT_AR_HPP




