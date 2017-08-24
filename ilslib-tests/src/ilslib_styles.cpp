#include "../include/ilslib_styles.hpp"


std::list<ContainerStyle*> getStyles(const ILSLibSFML::ResourceManager& resourceManager)
{
	// load them from files in the future

	std::list<ContainerStyle*> styles;
	ContainerStyle* style;

	ContainerStyle::BgColorGradient bgGradient;
	Color outlineColor;


	// window style
	style = new ContainerStyle("window");
	styles.push_back(style);

	outlineColor.red = 0;
	outlineColor.green = 0;
	outlineColor.blue = 0;

	bgGradient.topLeftBGColor.red = 64;
	bgGradient.topLeftBGColor.green = 64;
	bgGradient.topLeftBGColor.blue = 64;

	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;

	style->lineBorderThickness = 0;
	style->lineBorderColors.push_back(outlineColor);
	style->backgroundColors.push_back(bgGradient);


	// container style
	style = new ContainerStyle("container");
	styles.push_back(style);

	outlineColor.red = 0;
	outlineColor.green = 0;
	outlineColor.blue = 0;

	bgGradient.topLeftBGColor.red = 128;
	bgGradient.topLeftBGColor.green = 128;
	bgGradient.topLeftBGColor.blue = 128;

	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;

	style->lineBorderThickness = 1;
	style->lineBorderColors.push_back(outlineColor);
	style->backgroundColors.push_back(bgGradient);


	// red style
	style = new ContainerStyle("red");
	styles.push_back(style);

	outlineColor.red = 128;
	outlineColor.green = 0;
	outlineColor.blue = 0;

	bgGradient.topLeftBGColor.red = 192;
	bgGradient.topLeftBGColor.green = 0;
	bgGradient.topLeftBGColor.blue = 0;

	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;

	style->lineBorderThickness = 1;
	style->lineBorderColors.push_back(outlineColor);
	style->backgroundColors.push_back(bgGradient);


	// green style
	style = new ContainerStyle("green");
	styles.push_back(style);

	outlineColor.red = 0;
	outlineColor.green = 96;
	outlineColor.blue = 0;

	bgGradient.topLeftBGColor.red = 0;
	bgGradient.topLeftBGColor.green = 192;
	bgGradient.topLeftBGColor.blue = 0;

	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;

	style->lineBorderThickness = 1;
	style->lineBorderColors.push_back(outlineColor);
	style->backgroundColors.push_back(bgGradient);


	// blue style
	style = new ContainerStyle("blue");
	styles.push_back(style);

	outlineColor.red = 0;
	outlineColor.green = 0;
	outlineColor.blue = 144;

	bgGradient.topLeftBGColor.red = 0;
	bgGradient.topLeftBGColor.green = 0;
	bgGradient.topLeftBGColor.blue = 192;

	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;

	style->lineBorderThickness = 1;
	style->lineBorderColors.push_back(outlineColor);
	style->backgroundColors.push_back(bgGradient);


	// white style
	style = new ContainerStyle("white");
	styles.push_back(style);

	outlineColor.red = 192;
	outlineColor.green = 192;
	outlineColor.blue = 192;

	bgGradient.topLeftBGColor.red = 255;
	bgGradient.topLeftBGColor.green = 255;
	bgGradient.topLeftBGColor.blue = 255;

	bgGradient.topRightBGColor = bgGradient.bottomLeftBGColor =
	bgGradient.bottomRightBGColor = bgGradient.topLeftBGColor;

	style->lineBorderThickness = 1;
	style->lineBorderColors.push_back(outlineColor);
	style->backgroundColors.push_back(bgGradient);


	// return styles
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


