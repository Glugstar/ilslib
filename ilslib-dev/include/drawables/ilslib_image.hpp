/*----------------------------------------------------------------------------------
									ilslib_image.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_IMAGE_HPP
#define ILSLIB_IMAGE_HPP

#pragma once

#include "adjustment_results/ilslib_image_ar.hpp"
#include "ilslib_drawable.hpp"
#include "../resources/ilslib_texture.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Image
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Image : public Drawable
	{
	public:
		// constructors & destructor
		Image(const std::string& newTextureID);
		virtual ~Image();
		
		
		// functions
		virtual ImageAR* getImageAR();
		virtual const std::string& getTextureID() const;
	protected:
		// variables
		std::string textureID;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_IMAGE_HPP




