#include "../../include/other/ilslib_resource_manager.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ResourceManager::ResourceManager():
		textures(),
		fonts()
	{
	}
	
	
	ResourceManager::~ResourceManager()
	{
		std::list<Texture*>::iterator texture;
		for(texture = textures.begin(); texture!=textures.end(); ++texture)
			delete *texture;
		
		std::list<Font*>::iterator font;
		for(font = fonts.begin(); font!=fonts.end(); ++font)
			delete *font;
	}
	
	
	const Texture* ResourceManager::getTexture(const std::string& textureID) const
	{
		std::list<Texture*>::const_iterator texture;
		for(texture = textures.begin(); texture!=textures.end(); ++texture)
		{
			if((*texture)->getID() == textureID)
				return *texture;
		}
		
		return nullptr;
	}
	
	
	const Font* ResourceManager::getFont(const std::string& fontID) const
	{
		std::list<Font*>::const_iterator font;
		
		for(font = fonts.begin(); font!=fonts.end(); ++font)
		{
			if((*font)->getID() == fontID)
				return *font;
		}
		
		return nullptr;
	}
	
	
	Texture* ResourceManager::getTexture(const std::string& textureID)
	{
		std::list<Texture*>::iterator texture;
		for(texture = textures.begin(); texture!=textures.end(); ++texture)
		{
			if((*texture)->getID() == textureID)
				return *texture;
		}
		
		return nullptr;
	}
	
	
	Font* ResourceManager::getFont(const std::string& fontID)
	{
		std::list<Font*>::iterator font;
		
		for(font = fonts.begin(); font!=fonts.end(); ++font)
		{
			if((*font)->getID() == fontID)
				return *font;
		}
		
		return nullptr;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





