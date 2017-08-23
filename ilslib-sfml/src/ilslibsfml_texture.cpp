#include "../include/ilslibsfml_texture.hpp"



/*----------------------------------------------------------------------------------
										ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	Texture::Texture(const std::string& uniqueID, void* uniqueRealResource):
		ILSLib::Texture(uniqueID, uniqueRealResource)
	{
	}


	Texture::~Texture()
	{
		if(realResource == nullptr)
			return;

		delete (sf::Texture*)realResource;
	}


	void Texture::removeResource()
	{
		ILSLib::Texture::removeResource();
		imageRef = nullptr;
	}


	unsigned int Texture::getWidth() const
	{
		if(realResource == nullptr)
			return 0;

		return ((sf::Texture*)realResource)->getSize().x;
	}


	unsigned int Texture::getHeight() const
	{
		if(realResource == nullptr)
			return 0;

		return ((sf::Texture*)realResource)->getSize().y;
	}


	ILSLib::Color Texture::getColor(unsigned int x, unsigned int y) const
	{
		if(imageRef == nullptr)
			return ILSLib::Color();
		if((sf::Texture*)realResource != imageRef)
			return ILSLib::Color();

		sf::Color sfColor = image.getPixel(x, y);

		ILSLib::Color myColor;
		myColor.red = sfColor.r;
		myColor.green = sfColor.g;
		myColor.blue = sfColor.b;
		myColor.alpha = sfColor.a;

		return myColor;
	}


	void Texture::updateImage()
	{
		if((sf::Texture*)realResource == imageRef)
			return;

		imageRef = (sf::Texture*)realResource;
		if(imageRef == nullptr)
			return;

		image = imageRef->copyToImage();
	}



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------





