#include "../../../include/blocks/settings/ilslib_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{



	Settings::Settings():
		fixedWidth(0),
		fixedHeight(0),
		minWidth(0),
		minHeight(0),
		maxWidth(0),
		maxHeight(0),
		outterSpacingLeft(0),
		outterSpacingRight(0),
		outterSpacingTop(0),
		outterSpacingBottom(0),
		horizontalGravity(LeftGravity),
		verticalGravity(TopGravity),
		horizontalAlignment(LeftAlignment),
		verticalAlignment(TopAlignment),
		horizontalSizePolicy(Minimize),
		verticalSizePolicy(Minimize),
		visibility(Visible),
		preNewLine(false),
		postNewLine(false),
		ignoreDisplayCuts(false)
	{
	}


	Settings::~Settings()
	{
	}


	unsigned int Settings::getMinAppliedInnerWidth() const
	{
		if(fixedWidth > 0)
			return fixedWidth;
		if(minWidth > 0)
			return minWidth;
		return 0;
	}


	unsigned int Settings::getMinAppliedInnerHeight() const
	{
		if(fixedHeight > 0)
			return fixedHeight;
		if(minHeight > 0)
			return minHeight;
		return 0;
	}


	unsigned int Settings::getMaxAppliedInnerWidth() const
	{
		if(fixedWidth > 0)
			return fixedWidth;
		if(maxWidth > 0)
			return maxWidth;
		return 0;
	}


	unsigned int Settings::getMaxAppliedInnerHeight() const
	{
		if(fixedHeight > 0)
			return fixedHeight;
		if(maxHeight > 0)
			return maxHeight;
		return 0;
	}


	unsigned int Settings::getOutterSpacingHorizontal() const
	{
		return outterSpacingLeft + outterSpacingRight;
	}


	unsigned int Settings::getOutterSpacingVertical() const
	{
		return outterSpacingTop + outterSpacingBottom;
	}



} // end namespace ILSLib
//----------------------------------------------------------------------------------




