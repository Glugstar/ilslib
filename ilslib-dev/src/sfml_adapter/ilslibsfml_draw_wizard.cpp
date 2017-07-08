#include "../../include/sfml_adapter/ilslibsfml_draw_wizard.hpp"



/*----------------------------------------------------------------------------------
										ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{
	
	
	
	DrawWizard::DrawWizard()
	{
	}
	
	
	DrawWizard::~DrawWizard()
	{
	}
	
	
	void DrawWizard::draw(ILSLib::Drawable* nextDrawable,
						ILSLib::ResourceManager* resourceManager, void* renderSurface)
	{
		if(ILSLib::Gradient* gradient = dynamic_cast<ILSLib::Gradient*>(nextDrawable))
			drawGradient(gradient, resourceManager, renderSurface);
		if(ILSLib::Image* image = dynamic_cast<ILSLib::Image*>(nextDrawable))
			drawImage(image, resourceManager, renderSurface);
		if(ILSLib::RectangleColor* rectangleColor = dynamic_cast<ILSLib::RectangleColor*>(nextDrawable))
			drawRectangleColor(rectangleColor, resourceManager, renderSurface);
		if(ILSLib::Text* text = dynamic_cast<ILSLib::Text*>(nextDrawable))
			drawText(text, resourceManager, renderSurface);
	}
	
	
	void DrawWizard::drawGradient(ILSLib::Gradient* gradient,
						ILSLib::ResourceManager* resourceManager, void* renderSurface)
	{
		(void)resourceManager;
		
		const ILSLib::GradientAR* ar = gradient->getGradientAR();
		
		ILSLib::Rectangle intersection = ar->coordsRectangle.intersect(ar->cutRectangle);
		if(intersection.isValid() == false)
			return;
		
		bool cropView = ! ar->coordsRectangle.isInteriorOf(ar->cutRectangle);
		
		sf::Vertex rectangle[] =
		{
			sf::Vertex(sf::Vector2f(ar->coordsRectangle.x, ar->coordsRectangle.y),
						sf::Color(ar->topLeftColor.red, ar->topLeftColor.green,
								ar->topLeftColor.blue, ar->topLeftColor.alpha)),
			sf::Vertex(sf::Vector2f(ar->coordsRectangle.x + ar->coordsRectangle.width,
									ar->coordsRectangle.y),
						sf::Color(ar->topRightColor.red, ar->topRightColor.green,
								ar->topRightColor.blue, ar->topRightColor.alpha)),
			sf::Vertex(sf::Vector2f(ar->coordsRectangle.x + ar->coordsRectangle.width,
									ar->coordsRectangle.y + ar->coordsRectangle.height),
						sf::Color(ar->bottomRightColor.red, ar->bottomRightColor.green,
								ar->bottomRightColor.blue, ar->bottomRightColor.alpha)),
			sf::Vertex(sf::Vector2f(ar->coordsRectangle.x,
									ar->coordsRectangle.y + ar->coordsRectangle.height),
						sf::Color(ar->bottomLeftColor.red, ar->bottomLeftColor.green,
								ar->bottomLeftColor.blue, ar->bottomLeftColor.alpha))
		};
		
		std::pair<sf::RenderWindow*, sf::Transform*>* renderPair =
			(std::pair<sf::RenderWindow*, sf::Transform*>*)renderSurface;
		sf::RenderWindow* renderWindow = renderPair->first;
		
		sf::View oldView;
		if(cropView == true)
			oldView = limitView(renderWindow, intersection);
		
		renderWindow->draw(rectangle, 4, sf::Quads, *renderPair->second);
		
		if(cropView == true)
			restoreView(renderWindow, oldView);
	}
	
	
	void DrawWizard::drawImage(ILSLib::Image* image,
						ILSLib::ResourceManager* resourceManager, void* renderSurface)
	{
		const ILSLib::ImageAR* ar = image->getImageAR();
		
		ILSLib::Rectangle intersection = ar->coordsRectangle.intersect(ar->cutRectangle);
		if(intersection.isValid() == false)
			return;
		
		bool cropView = ! ar->coordsRectangle.isInteriorOf(ar->cutRectangle);
		
		ILSLib::Texture* resource = resourceManager->getTexture(image->getTextureID());
		if(resource == nullptr)
			return;
		
		sf::Texture* texture = (sf::Texture*)(resource->getResource());
		if(texture == nullptr)
			return;
		
		sf::Sprite sprite;
		sprite.setTexture(*texture);
		
		double scaleX, scaleY;
		scaleX = ((double)ar->coordsRectangle.width) / ((double)sprite.getTextureRect().width);
		scaleY = ((double)ar->coordsRectangle.height) / ((double)sprite.getTextureRect().height);
		
		std::pair<sf::RenderWindow*, sf::Transform*>* renderPair =
			(std::pair<sf::RenderWindow*, sf::Transform*>*)renderSurface;
		sf::RenderWindow* renderWindow = renderPair->first;
		
		sf::View oldView;
		if(cropView == true)
			oldView = limitView(renderWindow, intersection);
		
		if(ar->repeatX == true)
		{
			if(ar->repeatY == true)
			{
				for(int i=0; i<ar->coordsRectangle.width; i+=sprite.getTextureRect().width)
				{
					for(int j=0; j<ar->coordsRectangle.height; j+=sprite.getTextureRect().height)
					{
						sprite.setPosition(ar->coordsRectangle.x + i, ar->coordsRectangle.y + j);
						renderWindow->draw(sprite, *renderPair->second);
					}
				}
			}
			else if(ar->stretchY)
			{
				sprite.scale(1.0f, scaleY);
				for(int i=0; i<ar->coordsRectangle.width; i+=sprite.getTextureRect().width)
				{
					sprite.setPosition(ar->coordsRectangle.x + i, ar->coordsRectangle.y);
					renderWindow->draw(sprite, *renderPair->second);
				}
			}
			else // single Y image draw
			{
				for(int i=0; i<ar->coordsRectangle.width; i+=sprite.getTextureRect().width)
				{
					sprite.setPosition(ar->coordsRectangle.x + i, ar->coordsRectangle.y);
					renderWindow->draw(sprite, *renderPair->second);
				}
			}
		}
		else if(ar->stretchX)
		{
			if(ar->repeatY == true)
			{
				sprite.scale(scaleX, 1.0f);
				for(int j=0; j<ar->coordsRectangle.height; j+=sprite.getTextureRect().height)
				{
					sprite.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y + j);
					renderWindow->draw(sprite, *renderPair->second);
				}
			}
			else if(ar->stretchY)
			{
				sprite.scale(scaleX, scaleY);
				sprite.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y);
				renderWindow->draw(sprite, *renderPair->second);
			}
			else // single Y image draw
			{
				sprite.scale(scaleX, 1.0f);
				sprite.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y);
				renderWindow->draw(sprite, *renderPair->second);
			}
		}
		else // single X image draw
		{
			if(ar->repeatY == true)
			{
				for(int j=0; j<ar->coordsRectangle.height; j+=sprite.getTextureRect().height)
				{
					sprite.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y + j);
					renderWindow->draw(sprite, *renderPair->second);
				}
			}
			else if(ar->stretchY)
			{
				sprite.scale(1.0f, scaleY);
				sprite.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y);
				renderWindow->draw(sprite, *renderPair->second);
			}
			else // single Y image draw
			{
				sprite.scale(1.0f, 1.0f);
				sprite.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y);
				renderWindow->draw(sprite, *renderPair->second);
			}
		}
		
		if(cropView == true)
			restoreView(renderWindow, oldView);
	}
	
	
	void DrawWizard::drawRectangleColor(ILSLib::RectangleColor* rectangleColor,
						ILSLib::ResourceManager* resourceManager, void* renderSurface)
	{
		(void)resourceManager;
		
		const ILSLib::RectangleColorAR* ar = rectangleColor->getRectangleColorAR();
		
		ILSLib::Rectangle intersection = ar->coordsRectangle.intersect(ar->cutRectangle);
		if(intersection.isValid() == false)
			return;
		
		bool cropView = ! ar->coordsRectangle.isInteriorOf(ar->cutRectangle);
		
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(ar->coordsRectangle.width - 2 * ar->outlineThickness,
										ar->coordsRectangle.height - 2 * ar->outlineThickness));
		rectangle.setFillColor(sf::Color(ar->fillColor.red, ar->fillColor.green,
										ar->fillColor.blue, ar->fillColor.alpha));
		rectangle.setOutlineColor(sf::Color(ar->outlineColor.red, ar->outlineColor.green,
										ar->outlineColor.blue, ar->outlineColor.alpha));
		rectangle.setOutlineThickness(ar->outlineThickness);
		rectangle.setPosition(ar->coordsRectangle.x + ar->outlineThickness,
								ar->coordsRectangle.y + ar->outlineThickness);
		
		
		std::pair<sf::RenderWindow*, sf::Transform*>* renderPair =
			(std::pair<sf::RenderWindow*, sf::Transform*>*)renderSurface;
		sf::RenderWindow* renderWindow = renderPair->first;
		
		sf::View oldView;
		if(cropView == true)
			oldView = limitView(renderWindow, intersection);
		
		renderWindow->draw(rectangle, *renderPair->second);
		
		if(cropView == true)
			restoreView(renderWindow, oldView);
	}
	
	
	void DrawWizard::drawText(ILSLib::Text* text,
						ILSLib::ResourceManager* resourceManager, void* renderSurface)
	{
		const ILSLib::TextAR* ar = text->getTextAR();
		
		ILSLib::Rectangle intersection = ar->coordsRectangle.intersect(ar->cutRectangle);
		if(intersection.isValid() == false)
			return;
		
		bool cropView = ! ar->coordsRectangle.isInteriorOf(ar->cutRectangle);
		
		ILSLib::Font* resource = resourceManager->getFont(text->getFontID());
		if(resource == nullptr)
			return;
		
		sf::Font* font = (sf::Font*)(resource->getResource());
		if(font == nullptr)
			return;
		
		sf::Text message1;
		
		message1.setFont(*font);
		message1.setString(text->getMessage());
		message1.setCharacterSize(ar->fontSize);
		
		sf::Color firstShadowColor;
		firstShadowColor.r = ar->firstShadowColor.red;
		firstShadowColor.g = ar->firstShadowColor.green;
		firstShadowColor.b = ar->firstShadowColor.blue;
		firstShadowColor.a = ar->firstShadowColor.alpha;
		message1.setColor(firstShadowColor);
		//message1.setStyle(sf::Text::Bold | sf::Text::Underlined);
		message1.setPosition(ar->coordsRectangle.x + ar->firstShadowOffsetX,
							ar->coordsRectangle.y + ar->firstShadowOffsetY);
		
		sf::Text message2;
		
		message2.setFont(*font);
		message2.setString(text->getMessage());
		message2.setCharacterSize(ar->fontSize);
		
		sf::Color fontColor;
		fontColor.r = ar->fontColor.red;
		fontColor.g = ar->fontColor.green;
		fontColor.b = ar->fontColor.blue;
		fontColor.a = ar->fontColor.alpha;
		message2.setColor(fontColor);
		//message2.setStyle(sf::Text::Bold | sf::Text::Underlined);
		message2.setPosition(ar->coordsRectangle.x, ar->coordsRectangle.y);
		
		
		std::pair<sf::RenderWindow*, sf::Transform*>* renderPair =
			(std::pair<sf::RenderWindow*, sf::Transform*>*)renderSurface;
		sf::RenderWindow* renderWindow = renderPair->first;
		
		sf::View oldView;
		if(cropView == true)
			oldView = limitView(renderWindow, intersection);
		
		if(ar->firstShadowOffsetX != 0 && ar->firstShadowOffsetY != 0)
			renderWindow->draw(message1, *renderPair->second);
		renderWindow->draw(message2, *renderPair->second);
		
		if(cropView == true)
			restoreView(renderWindow, oldView);
	}
	
	
	sf::View DrawWizard::limitView(sf::RenderWindow* renderWindow,
								const ILSLib::Rectangle& cutRectangle)
	{
		sf::View oldView = renderWindow->getView();
		
		double viewportL = oldView.getViewport().left;
		double viewportT = oldView.getViewport().top;
		double viewportW = oldView.getSize().x;
		double viewportH = oldView.getSize().y;
		
		double spaceRectL = cutRectangle.x;
		double spaceRectT = cutRectangle.y;
		double spaceRectW = cutRectangle.width;
		double spaceRectH = cutRectangle.height;
		
		double leftRatio = (spaceRectL - viewportL) / viewportW;
		double topRatio = (spaceRectT - viewportT) / viewportH;
		double widthRatio = spaceRectW / viewportW;
		double heightRatio = spaceRectH / viewportH;
		
		sf::FloatRect newRatios(leftRatio, topRatio, widthRatio, heightRatio);
		
		sf::View newView(sf::FloatRect(spaceRectL, spaceRectT, spaceRectW, spaceRectH));
		
		newView.setViewport(newRatios);
		
		renderWindow->setView(newView);
		
		return oldView;
	}
	
	
	void DrawWizard::restoreView(sf::RenderWindow* renderWindow,
								 const sf::View& oldView)
	{
		renderWindow->setView(oldView);
	}
	
	
	
} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------





