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
		equalCellWidth(false),
		equalCellHeight(false),
		offsetX(0),
		offsetY(0),
		mouseEventsMultiLayer(false),
		mouseEventsSubComponentsFirst(true)
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
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




