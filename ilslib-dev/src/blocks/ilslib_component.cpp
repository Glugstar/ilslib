#include "../../include/blocks/ilslib_component.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Component::Component(const std::string& uniqueID):
		BasicBlock(uniqueID)
	{
		settings = new ComponentSettings();
	}
	
	
	Component::~Component()
	{
	}
	
	
	void Component::step1A_minimize()
	{
		dInfoStep1A.totalWidth = settings->getMinAppliedInnerWidth() + settings->getOutterSpacingHorizontal();
		dInfoStep1A.totalHeight = settings->getMinAppliedInnerHeight() + settings->getOutterSpacingVertical();
	}
	
	
	void Component::step1B_adjust()
	{
		dInfoStep1B = dInfoStep1A;
	}
	
	
	void Component::step1C_maximize(const Vector& availableSize)
	{
		dInfoStep1C = dInfoStep1B;
		
		int width = settings->getMaxAppliedInnerWidth() + settings->getOutterSpacingHorizontal();
		int height = settings->getMaxAppliedInnerHeight() + settings->getOutterSpacingVertical();
		
		if(width > availableSize.x)
			width = availableSize.x;
		if(height > availableSize.y)
			height = availableSize.y;
		
		if(dInfoStep1C.totalWidth < width)
			dInfoStep1C.totalWidth = width;
		if(dInfoStep1C.totalHeight < height)
			dInfoStep1C.totalHeight = height;
	}
	
	
	void Component::step1D_reAdjust()
	{
		dInfoStep1D = dInfoStep1C;
		pInfo.posRectangle.width = dInfoStep1D.totalWidth;
		pInfo.posRectangle.height = dInfoStep1D.totalHeight;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




