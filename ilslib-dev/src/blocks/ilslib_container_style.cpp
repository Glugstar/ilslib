#include "../../include/blocks/ilslib_container_style.hpp"
#include "../../include/blocks/ilslib_container.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ContainerStyle::ContainerStyle(const std::string& styleID):
		leftBGMargin(0),
		rightBGMargin(0),
		topBGMargin(0),
		bottomBGMargin(0),
		leftBorderMargin(0),
		rightBorderMargin(0),
		topBorderMargin(0),
		bottomBorderMargin(0),
		leftContentMargin(0),
		rightContentMargin(0),
		topContentMargin(0),
		bottomContentMargin(0),
		lineBorderThickness(0),
		borderCornerOverlap(0),
		leftBorderType(BorderType::Stretch),
		rightBorderType(BorderType::Stretch),
		topBorderType(BorderType::Stretch),
		bottomBorderType(BorderType::Stretch),
		backgroundColors(),
		lineBorderColors(),
		bordersResourcesID(),
		id(styleID)
	{
	}
	
	
	ContainerStyle::~ContainerStyle()
	{
	}
	
	
	const std::string& ContainerStyle::getID() const
	{
		return id;
	}
	
	
	void ContainerStyle::addBackground(DrawableMap* drawables, const Container* container,
									const Selector& styleSelector) const
	{
		if(backgroundColors.size() == 0)
			return;
		
		Gradient* background = new Gradient();
		GradientAR* ar = background->getGradientAR();
		const PositionInfo& pInfo = container->getPositionInfo();
		const ContainerSettings* settings = container->getContainerSettings();
		
		// check if there is draw space available
		if(pInfo.intersectionRectangle.isValid() == false)
			return;
		
		ar->cutRectangle = pInfo.cutRectangle;
		
		Rectangle posRectangle = pInfo.posRectangle;
		posRectangle.x += settings->outterSpacingLeft;
		posRectangle.y += settings->outterSpacingTop;
		posRectangle.width -= settings->getOutterSpacingHorizontal();
		posRectangle.height -= settings->getOutterSpacingVertical();
		
		ar->coordsRectangle = posRectangle;
		ar->coordsRectangle.x += leftBGMargin;
		ar->coordsRectangle.y += topBGMargin;
		ar->coordsRectangle.width -= (leftBGMargin + rightBGMargin);
		ar->coordsRectangle.height -= (topBGMargin + bottomBGMargin);
		
		if(ar->coordsRectangle.width < 0)
			return;
		if(ar->coordsRectangle.height < 0)
			return;
		
		unsigned int bgVariant1 = styleSelector.getModelBGIndexFirst(backgroundColors.size());
		unsigned int bgVariant2 = styleSelector.getModelBGIndexLast(backgroundColors.size());
		float ratio = styleSelector.getModelBGRatio();
		
		ar->topLeftColor = Color(backgroundColors[bgVariant1].topLeftBGColor,
								backgroundColors[bgVariant2].topLeftBGColor,
								ratio);
		ar->topRightColor = Color(backgroundColors[bgVariant1].topRightBGColor,
								backgroundColors[bgVariant2].topRightBGColor,
								ratio);
		ar->bottomLeftColor = Color(backgroundColors[bgVariant1].bottomLeftBGColor,
								backgroundColors[bgVariant2].bottomLeftBGColor,
								ratio);
		ar->bottomRightColor = Color(backgroundColors[bgVariant1].bottomRightBGColor,
								backgroundColors[bgVariant2].bottomRightBGColor,
								ratio);
		
		drawables->addDrawable(background);
	}
	
	
	void ContainerStyle::addBorder(DrawableMap* drawables, const Container* container,
									const Selector& styleSelector) const
	{
		if(container == nullptr)
			return;
		
		// check if there is draw space available
		if(container->getPositionInfo().intersectionRectangle.isValid() == false)
			return;
		
		if(bordersResourcesID.size() > 0)
			addImageBorder(drawables, container, styleSelector);
		
		if(lineBorderThickness > 0 && lineBorderColors.size() > 0)
			addLineBorder(drawables, container, styleSelector);
	}
	
	
	void ContainerStyle::addImageBorder(DrawableMap* drawables, const Container* container,
										const Selector& styleSelector) const
	{
		const PositionInfo& pInfo = container->getPositionInfo();
		
		Image* image;
		Rectangle coordsRectangle;
		
		
		unsigned int borderVariant1 = styleSelector.getModelBorderIndexFirst(bordersResourcesID.size());
		//unsigned int borderVariant2 = styleSelector.getModelBorderIndexLast(bordersResourcesID.size());
		//float borderRatio = styleSelector.getModelBorderRatio();
		
		std::string resouceID = bordersResourcesID[borderVariant1];
		const ContainerSettings* settings = container->getContainerSettings();
		
		Rectangle posRectangle = pInfo.posRectangle;
		posRectangle.x += settings->outterSpacingLeft;
		posRectangle.y += settings->outterSpacingTop;
		posRectangle.width -= settings->getOutterSpacingHorizontal();
		posRectangle.height -= settings->getOutterSpacingVertical();
		
		
		// left border
		coordsRectangle = posRectangle;
		coordsRectangle.y += (topBorderMargin - borderCornerOverlap);
		coordsRectangle.height += (- topBorderMargin - bottomBorderMargin + 2 * borderCornerOverlap);
		image = getImage(resouceID + "#L", coordsRectangle, pInfo.cutRectangle);
		if(leftBorderType == BorderType::Stretch)
			image->getImageAR()->stretchY = true;
		else if(leftBorderType == BorderType::Repeat)
			image->getImageAR()->repeatY = true;
		drawables->addDrawable(image);
		
		
		// right border
		coordsRectangle = posRectangle;
		coordsRectangle.x += coordsRectangle.width - rightBorderMargin;
		coordsRectangle.y += topBorderMargin - borderCornerOverlap;
		coordsRectangle.height += (- topBorderMargin - bottomBorderMargin + 2 * borderCornerOverlap);
		image = getImage(resouceID + "#R", coordsRectangle, pInfo.cutRectangle);
		if(rightBorderType == BorderType::Stretch)
			image->getImageAR()->stretchY = true;
		else if(rightBorderType == BorderType::Repeat)
			image->getImageAR()->repeatY = true;
		drawables->addDrawable(image);
		
		
		// top border
		coordsRectangle = posRectangle;
		coordsRectangle.x += (leftBorderMargin - borderCornerOverlap);
		coordsRectangle.width += (- leftBorderMargin - rightBorderMargin + 2 * borderCornerOverlap);
		image = getImage(resouceID + "#T", coordsRectangle, pInfo.cutRectangle);
		if(topBorderType == BorderType::Stretch)
			image->getImageAR()->stretchX = true;
		else if(topBorderType == BorderType::Repeat)
			image->getImageAR()->repeatX = true;
		drawables->addDrawable(image);
		
		
		// bottom border
		coordsRectangle = posRectangle;
		coordsRectangle.x += (leftBorderMargin - borderCornerOverlap);
		coordsRectangle.y += coordsRectangle.height - bottomBorderMargin;
		coordsRectangle.width += (- leftBorderMargin - rightBorderMargin + 2 * borderCornerOverlap);
		coordsRectangle.height = bottomBorderMargin;
		image = getImage(resouceID + "#B", coordsRectangle, pInfo.cutRectangle);
		if(bottomBorderType == BorderType::Stretch)
			image->getImageAR()->stretchX = true;
		else if(bottomBorderType == BorderType::Repeat)
			image->getImageAR()->repeatX = true;
		drawables->addDrawable(image);
		
		
		// top left corner
		coordsRectangle = posRectangle;
		coordsRectangle.width = leftBorderMargin;
		coordsRectangle.height = topBorderMargin;
		image = getImage(resouceID + "#TL", coordsRectangle, pInfo.cutRectangle);
		drawables->addDrawable(image);
		
		
		// top right corner
		coordsRectangle = posRectangle;
		coordsRectangle.x += (coordsRectangle.width - rightBorderMargin);
		coordsRectangle.width = rightBorderMargin;
		coordsRectangle.height = topBorderMargin;
		image = getImage(resouceID + "#TR", coordsRectangle, pInfo.cutRectangle);
		drawables->addDrawable(image);
		
		
		// bottom left corner
		coordsRectangle = posRectangle;
		coordsRectangle.y += (coordsRectangle.height - bottomBorderMargin);
		coordsRectangle.width = leftBorderMargin;
		coordsRectangle.height = bottomBorderMargin;
		image = getImage(resouceID + "#BL", coordsRectangle, pInfo.cutRectangle);
		drawables->addDrawable(image);
		
		
		// bottom right corner
		coordsRectangle = posRectangle;
		coordsRectangle.x += (coordsRectangle.width - rightBorderMargin);
		coordsRectangle.y += (coordsRectangle.height - bottomBorderMargin);
		coordsRectangle.width = rightBorderMargin;
		coordsRectangle.height = bottomBorderMargin;
		image = getImage(resouceID + "#BR", coordsRectangle, pInfo.cutRectangle);
		drawables->addDrawable(image);
	}
	
	
	void ContainerStyle::addLineBorder(DrawableMap* drawables, const Container* container,
										const Selector& styleSelector) const
	{
		const PositionInfo& pInfo = container->getPositionInfo();
		
		RectangleColor* border = new RectangleColor();
		RectangleColorAR* ar = border->getRectangleColorAR();
		
		unsigned int borderVariant1 = styleSelector.getModelBorderIndexFirst(lineBorderColors.size());
		//unsigned int borderVariant2 = styleSelector.getModelBorderIndexLast(bordersResourcesID.size());
		//float borderRatio = styleSelector.getModelBorderRatio();
		
		ar->outlineColor = lineBorderColors[borderVariant1];
		ar->outlineThickness = lineBorderThickness;
		
		ar->coordsRectangle = pInfo.posRectangle;
		ar->cutRectangle = pInfo.intersectionRectangle;
		
		ar->fillColor.red = 0;
		ar->fillColor.green = 0;
		ar->fillColor.blue = 0;
		ar->fillColor.alpha = 0;
		
		drawables->addDrawable(border);
	}
	
	
	Image* ContainerStyle::getImage(const std::string& imageID,
								const Rectangle& coordsRectangle,
								const Rectangle& cutRectangle) const
	{
		Image* image = new Image(imageID);
		ImageAR* imageAR = image->getImageAR();
		
		imageAR->coordsRectangle = coordsRectangle;
		imageAR->cutRectangle = cutRectangle;
		
		return image;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





