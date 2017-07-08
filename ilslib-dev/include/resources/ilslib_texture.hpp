/*----------------------------------------------------------------------------------
								ilslib_texture.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_TEXTURE_HPP
#define ILSLIB_TEXTURE_HPP

#pragma once

#include "ilslib_resource.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Texture
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Texture : public Resource
	{
	public:
		// constructors & destructor
		Texture(const std::string& uniqueID, void* uniqueRealResource);
		virtual ~Texture();
		
		
		// functions
		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;
		virtual Color getColor(unsigned int x, unsigned int y) const = 0;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_TEXTURE_HPP




