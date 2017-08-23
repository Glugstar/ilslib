#include "../include/ilslibsfml_font.hpp"



/*----------------------------------------------------------------------------------
										ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	Font::Font(const std::string& uniqueID, void* uniqueRealResource):
		ILSLib::Font(uniqueID, uniqueRealResource)
	{
	}


	Font::~Font()
	{
		if(realResource == nullptr)
			return;

		delete (sf::Font*)realResource;
	}


	ILSLib::Rectangle Font::getTextSize(unsigned int charSize, const std::string& text) const
	{
		ILSLib::Rectangle sizeRectangle;

		if(realResource == nullptr)
			return sizeRectangle;

		sf::FloatRect sizeRect;
		sf::Text sfText(text, *(sf::Font*)realResource, charSize);

		sizeRect = sfText.getLocalBounds();
		sizeRectangle.x = sizeRect.left;
		sizeRectangle.y = sizeRect.top;
		sizeRectangle.width = sizeRect.width;
		sizeRectangle.height = sizeRect.height;

		return sizeRectangle;
	}


	unsigned int Font::getLineSpacing(unsigned int charSize) const
	{
		if(realResource == nullptr)
			return 0;

		return ((sf::Font*)realResource)->getLineSpacing(charSize);
	}



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------





