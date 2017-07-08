#include "../../include/components/ilslib_text_component.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	TextComponent::TextComponent(const std::string& uniqueID):
		Component(uniqueID),
		resManager(nullptr),
		text(),
		fontID(),
		textSize(16),
		shadowOffset(0),
		textColor(),
		shadowColor()
	{
	}
	
	
	TextComponent::~TextComponent()
	{
	}
	
	
	void TextComponent::step1A_minimize()
	{
		if(resManager != nullptr)
		{
			const Font* font = resManager->getFont(fontID);
			Rectangle sizeRectangle = font->getTextSize(textSize, text);
			settings->fixedWidth = sizeRectangle.width + 2 * sizeRectangle.x + shadowOffset;
			settings->fixedHeight = sizeRectangle.height + 2 * sizeRectangle.y + shadowOffset;
			//settings->fixedHeight = font->getLineSpacing(textSize) + shadowOffset;
		}
		
		Component::step1A_minimize();
	}
	
	
	void TextComponent::step2C_addToDrawableMap(DrawableMap* drawables)
	{
		Text* textResource;
		Rectangle coordsRectangle;
		
		/*const Font* font = resManager->getFont(fontID);
		Rectangle sizeRectangle = font->getTextSize(textSize, text);*/
		
		coordsRectangle = pInfo.posRectangle;
		//coordsRectangle.y -= sizeRectangle.y;
		/*coordsRectangle.y -= ((float)coordsRectangle.height) * 0.1f;
		coordsRectangle.height += ((float)coordsRectangle.height) * 0.1f;*/
		
		textResource = new Text(fontID, text);
		TextAR* textAR = textResource->getTextAR();
		textAR->coordsRectangle = coordsRectangle;
		textAR->cutRectangle = pInfo.cutRectangle;
		textAR->fontSize = textSize;
		textAR->fontColor = textColor;
		
		textAR->firstShadowOffsetX = shadowOffset;
		textAR->firstShadowOffsetY = shadowOffset;
		textAR->firstShadowColor = shadowColor;
		
		drawables->addDrawable(textResource);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




