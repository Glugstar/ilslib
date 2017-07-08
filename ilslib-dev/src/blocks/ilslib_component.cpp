#include "../../include/blocks/ilslib_component.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Component::Component(const std::string& uniqueID):
		BasicBlock(uniqueID),
		dInfoStep1A(),
		dInfoStep1B(),
		dInfoStep1C(),
		dInfoStep1D(),
		pInfo()
	{
		settings = new ComponentSettings();
	}
	
	
	Component::~Component()
	{
	}
	
	
	const DimensionsInfo* Component::getDimensionsInfo(const Settings::Step step) const
	{
		if(step == Settings::Step::s1A_minimize)
			return &dInfoStep1A;
		else if(step == Settings::Step::s1B_adjust)
			return &dInfoStep1B;
		else if(step == Settings::Step::s1C_maximize)
			return &dInfoStep1C;
		else if(step == Settings::Step::s1D_reAdjust)
			return &dInfoStep1D;
		
		throw std::exception();
	}
	
	
	const PositionInfo* Component::getPositionInfo() const
	{
		return &pInfo;
	}
	
	
	void Component::step0A_clear()
	{
		dInfoStep1A.clear();
		dInfoStep1B.clear();
		dInfoStep1C.clear();
		dInfoStep1D.clear();
		
		pInfo.clear();
	}
	
	
	void Component::step0B_applyTransformations()
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
	
	
	void Component::step1C_maximize(int availableWidth, int availableHeight)
	{
		dInfoStep1C = dInfoStep1B;
		
		int width = settings->getMaxAppliedInnerWidth() + settings->getOutterSpacingHorizontal();
		int height = settings->getMaxAppliedInnerHeight() + settings->getOutterSpacingVertical();
		
		if(width > availableWidth)
			width = availableWidth;
		if(height > availableHeight)
			height = availableHeight;
		
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
	
	
	void Component::step2A_determinePositions()
	{
	}
	
	
	PositionInfo* Component::getPositionInfo()
	{
		return &pInfo;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




