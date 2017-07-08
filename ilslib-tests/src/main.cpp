#include "../include/ilslib_tests2.hpp"


std::list<ContainerStyle*> getStyles(const ILSLibSFML::ResourceManager& resourceManager);
ContainerStyle* getStyle(const ILSLibSFML::ResourceManager& resourceManager,
						const std::string& id, int nBackgrounds);


int main()
{
	std::string rootName = "Root";
	std::string baseAltName = "TestGroup";
	ILSLibSFML::ResourceManager resourceManager;
	ILSLibSFML::Window window(&resourceManager);
	
	std::list<ContainerStyle*> styles = getStyles(resourceManager);
	for(std::list<ContainerStyle*>::iterator i=styles.begin(); i!=styles.end(); ++i)
		window.getBlockManager().addContainerStyle(*i);
	
	createAllTestsA(window.getBlockManager(), rootName, baseAltName);
	
	/*TextComponent* text;
	text = ((TextComponent*)window.getBlockManager().findBasicBlock("Root/group1#1#block15#c12"));
	text->resManager = &resourceManager;*/
	
	sf::VideoMode vMode(1200, 900);
	window.newWindow(vMode, "My Window");
	window.updateDrawableMap(rootName);
	
	while(window.isOpen() == true)
    {
    	window.pollEvents(rootName);
    	window.parseEvents(rootName);
    	window.updateView();
    }
	
	return 0;
}


std::list<ContainerStyle*> getStyles(const ILSLibSFML::ResourceManager& resourceManager)
{
	// load them from files in the future
	
	std::list<ContainerStyle*> styles;
	ContainerStyle* style;
	
	ContainerStyle::BgColorGradient bgGradient;
	bgGradient.topLeftBGColor.alpha = 128;
	bgGradient.bottomLeftBGColor.alpha = 128;
	bgGradient.bottomRightBGColor.alpha = 128;
	bgGradient.topRightBGColor.alpha = 128;
	
	Color outlineColor;
	outlineColor.alpha = 255;
	
	
	// first style
	style = new ContainerStyle("basic");
	styles.push_back(style);
	
	
	
	outlineColor.red = 0;
	outlineColor.green = 0;
	outlineColor.blue = 0;
	style->lineBorderColors.push_back(outlineColor);
	
	bgGradient.topLeftBGColor.red = 64;
	bgGradient.topLeftBGColor.green = 64;
	bgGradient.topLeftBGColor.blue = 64;
	
	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;
	
	style->backgroundColors.push_back(bgGradient);
	
	
	
	outlineColor.red = 128;
	outlineColor.green = 0;
	outlineColor.blue = 0;
	style->lineBorderColors.push_back(outlineColor);
	
	bgGradient.topLeftBGColor.red = 192;
	bgGradient.topLeftBGColor.green = 0;
	bgGradient.topLeftBGColor.blue = 0;
	
	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;
	
	style->backgroundColors.push_back(bgGradient);
	
	
	
	outlineColor.red = 0;
	outlineColor.green = 0;
	outlineColor.blue = 144;
	style->lineBorderColors.push_back(outlineColor);
	
	bgGradient.topLeftBGColor.red = 0;
	bgGradient.topLeftBGColor.green = 0;
	bgGradient.topLeftBGColor.blue = 192;
	
	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;
	
	style->backgroundColors.push_back(bgGradient);
	
	
	
	outlineColor.red = 0;
	outlineColor.green = 96;
	outlineColor.blue = 0;
	style->lineBorderColors.push_back(outlineColor);
	
	bgGradient.topLeftBGColor.red = 0;
	bgGradient.topLeftBGColor.green = 192;
	bgGradient.topLeftBGColor.blue = 0;
	
	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;
	
	style->backgroundColors.push_back(bgGradient);
	
	style->lineBorderThickness = 1;
	
	
	return styles;
}


ContainerStyle* getStyle(const ILSLibSFML::ResourceManager& resourceManager,
						const std::string& id, int nBackgrounds)
{
	ContainerStyle::BgColorGradient bgGradient;
	int maxBorder, currentBorder;
	
	ContainerStyle* style = new ContainerStyle(id);
	if(style == nullptr)
		return nullptr;
	
	style->bordersResourcesID.push_back(id);
	
	for(int i=0; i<nBackgrounds; ++i)
	{
		std::string textureID = id + "#F" + Support::NumberToString(i + 1);
		const Texture* texture = resourceManager.getTexture(textureID);
		if(texture != nullptr)
		{
			bgGradient.getFromTexture(*texture);
			style->backgroundColors.push_back(bgGradient);
		}
	}
	
	maxBorder = 0;
	currentBorder = resourceManager.getTexture(id + "#L")->getWidth();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#TL")->getWidth();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#BL")->getWidth();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	style->leftBorderMargin = maxBorder;
	
	maxBorder = 0;
	currentBorder = resourceManager.getTexture(id + "#R")->getWidth();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#TR")->getWidth();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#BR")->getWidth();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	style->rightBorderMargin = maxBorder;
	
	maxBorder = 0;
	currentBorder = resourceManager.getTexture(id + "#T")->getHeight();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#TL")->getHeight();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#TR")->getHeight();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	style->topBorderMargin = maxBorder;
	
	maxBorder = 0;
	currentBorder = resourceManager.getTexture(id + "#B")->getHeight();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#BL")->getHeight();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	currentBorder = resourceManager.getTexture(id + "#BR")->getHeight();
	maxBorder = maxBorder > currentBorder ? maxBorder : currentBorder;
	style->bottomBorderMargin = maxBorder;
	
	style->leftContentMargin = style->leftBorderMargin;
	style->rightContentMargin = style->rightBorderMargin;
	style->topContentMargin = style->topBorderMargin;
	style->bottomContentMargin = style->bottomBorderMargin;
	
	return style;
}




