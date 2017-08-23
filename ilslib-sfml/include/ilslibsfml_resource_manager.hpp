/*----------------------------------------------------------------------------------
							ilslibsfml_resource_manager.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library - SFML Adapter.
----------------------------------------------------------------------------------*/
#ifndef ILSLIBSFML_RESOURCE_MANAGER_HPP
#define ILSLIBSFML_RESOURCE_MANAGER_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "../../ilslib-dev/include/other/ilslib_resource_manager.hpp"
#include "ilslibsfml_texture.hpp"
#include "ilslibsfml_font.hpp"



/*----------------------------------------------------------------------------------
									ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	/*!---------------------------------------------------------------------------------
										ResourceManager
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ResourceManager : public ILSLib::ResourceManager
	{
	public:
		// functions
		virtual void loadFont(const std::string& fontID, const std::string& fontPath);
		virtual void loadTexture(const std::string& textureID, const std::string& texturePath);
		virtual void loadFrameStyle(const std::string& styleID, const std::string& stylePath,
										unsigned int nBorders, unsigned int nGradients);
	protected:
		// functions
		virtual void loadTextures(std::list<std::pair<std::string, std::string> >& textureList);
	};



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_RESOURCE_MANAGER_HPP




