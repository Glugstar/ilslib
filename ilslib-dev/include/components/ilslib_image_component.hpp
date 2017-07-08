/*----------------------------------------------------------------------------------
							ilslib_image_component.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_IMAGE_COMPONENT_HPP
#define ILSLIB_IMAGE_COMPONENT_HPP

#pragma once

#include "../blocks/ilslib_component.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										ImageComponent
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ImageComponent : public Component
	{
	public:
		// constructors & destructor
		ImageComponent(const std::string& uniqueID);
		virtual ~ImageComponent();
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_IMAGE_COMPONENT_HPP




