#include "../../../include/blocks/settings/ilslib_container_settings.hpp"
#include "../../../include/blocks/ilslib_container_style.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ContainerSettings::ContainerSettings():
		Settings(),
		innerSpacingLeft(0),
		innerSpacingRight(0),
		innerSpacingTop(0),
		innerSpacingBottom(0),
		cellSpacingWidth(0),
		cellSpacingHeight(0),
		axisPriority(HorizontalFirst),
		horizontalFlow(RightOrLowerFlow),
		verticalFlow(RightOrLowerFlow),
		equalCellWidth(false),
		equalCellHeight(false),
		scrollX(0),
		scrollY(0),
		autoLineWrap(false),
		mouseEventsMultiLayer(false),
		mouseEventsSubComponentsFirst(true),
		tableNumberOfCells(0)
	{
	}
	
	
	ContainerSettings::~ContainerSettings()
	{
	}
	
	
	void ContainerSettings::loadInnerSpacing(const ContainerStyle* containerStyle)
	{
		innerSpacingLeft = containerStyle->leftContentMargin;
		innerSpacingRight = containerStyle->rightContentMargin;
		innerSpacingTop = containerStyle->topContentMargin;
		innerSpacingBottom = containerStyle->bottomContentMargin;
	}
	
	
	unsigned int ContainerSettings::getInnerSpacingHorizontal() const
	{
		return innerSpacingLeft + innerSpacingRight;
	}
	
	
	unsigned int ContainerSettings::getInnerSpacingVertical() const
	{
		return innerSpacingTop + innerSpacingBottom;
	}
	
	
	unsigned int ContainerSettings::getSpacingHorizontal() const
	{
		return getInnerSpacingHorizontal() + getOutterSpacingHorizontal();
	}
	
	
	unsigned int ContainerSettings::getSpacingVertical() const
	{
		return getInnerSpacingVertical() + getOutterSpacingVertical();
	}
	
	
	unsigned int ContainerSettings::getSpacingLeft() const
	{
		return innerSpacingLeft + outterSpacingLeft;
	}
	
	
	unsigned int ContainerSettings::getSpacingRight() const
	{
		return innerSpacingRight + outterSpacingRight;
	}
	
	
	unsigned int ContainerSettings::getSpacingTop() const
	{
		return innerSpacingTop + outterSpacingTop;
	}
	
	
	unsigned int ContainerSettings::getSpacingBottom() const
	{
		return innerSpacingBottom + outterSpacingBottom;
	}
	
	
	bool ContainerSettings::tableMode() const
	{
		return autoLineWrap == true && tableNumberOfCells > 0;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




