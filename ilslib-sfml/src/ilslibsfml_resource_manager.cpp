#include "../include/ilslibsfml_resource_manager.hpp"



/*----------------------------------------------------------------------------------
										ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	void ResourceManager::loadFont(const std::string& fontID, const std::string& fontPath)
	{
		sf::Font* font = new sf::Font();
		if(font == nullptr)
			return;
		if(font->loadFromFile(fontPath) == true)
		{
			ILSLibSFML::Font* resource = new ILSLibSFML::Font(fontID, font);
			if(resource == nullptr)
			{
				delete font;
				return;
			}
			fonts.push_back(resource);
		}
		else
			delete font;
	}


	void ResourceManager::loadTexture(const std::string& textureID, const std::string& texturePath)
	{
		sf::Texture* texture = new sf::Texture();
		if(texture == nullptr)
			return;
		if(texture->loadFromFile(texturePath) == true)
		{
			ILSLibSFML::Texture* resource = new ILSLibSFML::Texture(textureID, texture);
			if(resource == nullptr)
			{
				delete texture;
				return;
			}
			resource->updateImage();
			textures.push_back(resource);
		}
		else
			delete texture;
	}


	void ResourceManager::loadFrameStyle(const std::string& styleID, const std::string& stylePath,
										unsigned int nBorders, unsigned int nGradients)
	{
		std::list<std::pair<std::string, std::string> > textureList;
		std::string basePath = stylePath;

		if(basePath.size() == 0)
			basePath = "/";
		else if(basePath[basePath.size() - 1] != '/')
			basePath = stylePath + "/";

		for(unsigned int i=0; i<nBorders; ++i)
		{
			std::string tNumber = ILSLib::Support::NumberToString(i);
			std::string path = basePath + "border" + tNumber + "/";
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#TL", path + "border01TL.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#T", path + "border02T.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#TR", path + "border03TR.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#L", path + "border04L.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#R", path + "border05R.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#BL", path + "border06BL.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#B", path + "border07B.png"));
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#BR", path + "border08BR.png"));
		}

		for(unsigned int i=0; i<nGradients; ++i)
		{
			std::string tNumber = ILSLib::Support::NumberToString(i);
			textureList.push_back(std::pair<std::string, std::string>(styleID + tNumber + "#G", basePath + "gradient" + tNumber + ".png"));
		}

		loadTextures(textureList);
	}


	void ResourceManager::loadTextures(std::list<std::pair<std::string, std::string> >& textureList)
	{
		std::list<std::pair<std::string, std::string> >::const_iterator i;

		for(i=textureList.begin(); i!=textureList.end(); ++i)
			loadTexture(i->first, i->second);
	}



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------





