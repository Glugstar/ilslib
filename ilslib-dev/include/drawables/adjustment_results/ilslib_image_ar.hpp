/*----------------------------------------------------------------------------------
						ilslib_image_ar.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_IMAGE_AR_HPP
#define ILSLIB_IMAGE_AR_HPP

#pragma once

#include "ilslib_adjustment_results.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											ImageAR
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	struct ImageAR : public AdjustmentResults
	{
	public:
		// constructors & destructor
		ImageAR();
		virtual ~ImageAR();
		
		
		// variables
		Rectangle textureRectangle;
		
		float textureZoomX;
		float textureZoomY;
		
		bool repeatX;
		bool repeatY;
		bool repeatXFullOnly;
		bool repeatYFullOnly;
		
		bool mirrorX;
		bool mirrorY;
		
		// stretch overrides zoom settings
		bool stretchX;
		bool stretchY;
		
		bool centerX;
		bool centerY;
		
		float transparency; // [0, 1] -> [opaque, trasparent]
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_IMAGE_AR_HPP




