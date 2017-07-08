/*----------------------------------------------------------------------------------
								ilslib_resource_manager.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_RESOURCE_MANAGER_HPP
#define ILSLIB_RESOURCE_MANAGER_HPP

#pragma once


#include "../resources/ilslib_texture.hpp"
#include "../resources/ilslib_font.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										ResourceManager
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ResourceManager
	{
	public:
		// constructors & destructor
		ResourceManager();
		virtual ~ResourceManager();
		
		
		// functions
		virtual const Texture* getTexture(const std::string& textureID) const;
		virtual const Font* getFont(const std::string& fontID) const;
		virtual Texture* getTexture(const std::string& textureID);
		virtual Font* getFont(const std::string& fontID);
		
		virtual void loadFont(const std::string& fontID, const std::string& fontPath) = 0;
		virtual void loadTexture(const std::string& textureID, const std::string& texturePath) = 0;
		virtual void loadFrameStyle(const std::string& styleID, const std::string& stylePath,
										unsigned int nBorders, unsigned int nGradients) = 0;
	protected:
		// variables
		std::list<Texture*> textures;
		std::list<Font*> fonts;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_RESOURCE_MANAGER_HPP





