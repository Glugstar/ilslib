#include "../../include/blocks/ilslib_basic_block.hpp"
#include "../../include/blocks/ilslib_container.hpp"
#include "../../include/other/ilslib_event_queue.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	BasicBlock::BasicBlock(const std::string& uniqueID):
		id(uniqueID),
		parent(nullptr),
		settings(nullptr),
		listenerManager(),
		dInfoStep1A(),
		dInfoStep1B(),
		dInfoStep1C(),
		dInfoStep1D(),
		pInfo()
	{
	}
	
	
	BasicBlock::~BasicBlock()
	{
		delete settings;
	}
	
	
	const std::string& BasicBlock::getID() const
	{
		return id;
	}
	
	
	std::string BasicBlock::getPath() const
	{
		if(parent != nullptr)
			return parent->getPath() + "/" + id;
		
		return id;
	}
	
	
	const Container* BasicBlock::getParent() const
	{
		return parent;
	}
	
	
	const Settings* BasicBlock::getSettings() const
	{
		return settings;
	}
	
	
	Settings* BasicBlock::getSettings()
	{
		return settings;
	}
	
	
	const DimensionsInfo& BasicBlock::getDimensionsInfo(const Settings::Step step) const
	{
		if(step == Settings::Step::s1A_minimize)
			return dInfoStep1A;
		else if(step == Settings::Step::s1B_adjust)
			return dInfoStep1B;
		else if(step == Settings::Step::s1C_maximize)
			return dInfoStep1C;
		else if(step == Settings::Step::s1D_reAdjust)
			return dInfoStep1D;
		
		throw std::exception();
	}
	
	
	const PositionInfo& BasicBlock::getPositionInfo() const
	{
		return pInfo;
	}
	
	
	Vector BasicBlock::getAvailableMaximization() const
	{
		int limitX, limitY;
		limitX = settings->getMaxAppliedInnerWidth();
		limitY = settings->getMaxAppliedInnerHeight();
		
		int remainingX, remainingY;
		remainingX = remainingY = 0;
		
		const DimensionsInfo& dInfo = getDimensionsInfo(Settings::Step::s1B_adjust);
		
		if(settings->horizontalSizePolicy != Settings::SizePolicy::Minimize)
		{
			if(limitX == 0)
				remainingX = -1;
			if(limitX > dInfo.totalWidth)
				remainingX = limitX - dInfo.totalWidth;
		}
		if(settings->verticalSizePolicy != Settings::SizePolicy::Minimize)
		{
			if(limitY == 0)
				remainingY = -1;
			if(limitY > dInfo.totalHeight)
				remainingY = limitY - dInfo.totalHeight;
		}
		
		return Vector(remainingX, remainingY);
	}
	
	
	Rectangle BasicBlock::getDisplayArea() const
	{
		return getPositionInfo().posRectangle;
	}
	
	
	Settings::Visibility BasicBlock::getVisibility() const
	{
		return settings->visibility;
	}
	
	
	bool BasicBlock::occupiesSpace(bool tableMode) const
	{
		if(settings->visibility == Settings::Visibility::IgnoreBlock)
			return false;
		
		if(settings->visibility == Settings::Visibility::Collapse &&
			tableMode == false)
			return false;
		
		return true;
	}
	
	
	const ListenerManager& BasicBlock::getListenerManager() const
	{
		return listenerManager;
	}
	
	
	ListenerManager& BasicBlock::getListenerManager()
	{
		return listenerManager;
	}
	
	
	const ListenerOptimizer& BasicBlock::getListenerOptimizer() const
	{
		return listenerManager.getListenerOptimizer();
	}
	
	
	bool BasicBlock::parseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		if(event.eventApplies(getPositionInfo(), settings) == false)
			return false;
		
		bool interiorMovement = event.eventInsideCutRectangle(getPositionInfo(), settings);
		
		return listenerManager.parseEvent(getPath(), interiorMovement, event, blockManager, eventQueue);
	}
	
	
	bool BasicBlock::parseEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		return listenerManager.parseEvent(getPath(), event, blockManager, eventQueue);
	}
	
	
	bool BasicBlock::parseEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		return listenerManager.parseEvent(getPath(), event, blockManager, eventQueue);
	}
	
	
	bool BasicBlock::parseEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		return listenerManager.parseEvent(getPath(), event, blockManager, eventQueue);
	}
	
	
	void BasicBlock::step0A_clear()
	{
		dInfoStep1A.clear();
		dInfoStep1B.clear();
		dInfoStep1C.clear();
		dInfoStep1D.clear();
		pInfo.clear();
	}
	
	
	void BasicBlock::step0B_applyTransformations()
	{
	}
	
	
	void BasicBlock::step0C_optimizeListeners()
	{
		listenerManager.updateOptimizationData();
	}
	
	
	void BasicBlock::step2A_determinePositions()
	{
		/*if(currentAlternative == nullptr)
			throw std::exception();
		
		const ContainerSettings* currentSettings = getContainerSettings();
		
		alternativePInfo->posRectangle = pInfo.posRectangle;
		alternativePInfo->posRectangle.x -= parentContainer->getScrollX();
		alternativePInfo->posRectangle.y -= parentContainer->getScrollY();
		alternativePInfo->posRectangle.x += currentSettings->getSpacingLeft();
		alternativePInfo->posRectangle.y += currentSettings->getSpacingTop();
		*/
		
		
		
		/*std::list<Layer*>::iterator i;
		
		for(i=layers.begin(); i!=layers.end(); ++i)
		{
			if(*i == nullptr)
				throw std::exception();
			
			PositionInfo* layerPInfo = (*i)->getPositionInfo();
			layerPInfo->posRectangle = pInfo.posRectangle;
			layerPInfo->posRectangle.x += (*i)->getLayerOffsetX();
			layerPInfo->posRectangle.y += (*i)->getLayerOffsetY();
			
			(*i)->step2A_determinePositions(currentSettings);
		}*/
	}
	
	
	void BasicBlock::step2B_determineCutRectangles(const Rectangle& availableSpace)
	{
		pInfo.cutRectangle = availableSpace;
		pInfo.intersectionRectangle = pInfo.posRectangle.intersect(pInfo.cutRectangle);
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




