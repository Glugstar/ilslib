/*----------------------------------------------------------------------------------
								ilslibsfml_texture.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library - SFML Adapter.
----------------------------------------------------------------------------------*/
#ifndef ILSLIBSFML_TEXTURE_HPP
#define ILSLIBSFML_TEXTURE_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "../../include/resources/ilslib_texture.hpp"



/*----------------------------------------------------------------------------------
									ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{
	
	
	
	/*!---------------------------------------------------------------------------------
										Texture
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Texture : public ILSLib::Texture
	{
	public:
		// constructors & destructor
		Texture(const std::string& uniqueID, void* uniqueRealResource);
		virtual ~Texture();
		
		
		// functions
		virtual void removeResource();
		virtual unsigned int getWidth() const;
		virtual unsigned int getHeight() const;
		virtual ILSLib::Color getColor(unsigned int x, unsigned int y) const;
		virtual void updateImage();
	protected:
		// variables
		sf::Texture* imageRef;
		sf::Image image;
	};
	
	
	
} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_TEXTURE_HPP




