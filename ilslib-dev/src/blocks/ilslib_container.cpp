#include "../../include/blocks/ilslib_container.hpp"
#include "../../include/blocks/ilslib_flow_container.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Container::Container(const std::string& containerID):
		BasicBlock(containerID),
		style(nullptr),
		styleSelector(),
		listenerOptimizer(),
		subComponentsListenerOptimizer()
	{
	}
	
	
	Container::~Container()
	{
	}
	
	
	bool Container::isPhysical(const BasicBlock* element)
	{
		Settings::Visibility visibility = element->getSettings()->visibility;
		if(visibility == Settings::Visibility::IgnoreBlock)
			return false;
		if(visibility == Settings::Visibility::Collapse)
		{
			const FlowContainer* flowContainer = dynamic_cast<const FlowContainer*>(element);
			if(flowContainer == nullptr)
				return false;
			if(flowContainer->getFlowContainerSettings()->tableMode() == true)
				return true;
		}
		
		return true;
	}
	
	
	bool Container::isVisible(const BasicBlock* element)
	{
		Settings::Visibility visibility = element->getSettings()->visibility;
		if(visibility == Settings::Visibility::Visible)
			return true;
		
		return false;
	}
	
	
	bool Container::isSuperPhysical(const BasicBlock* element)
	{
		if(isPhysical(element) == false)
			return false;
		if(element->getDisplayArea().isValid() == false)
			return false;
		
		return true;
	}
	
	
	bool Container::isSuperVisible(const BasicBlock* element)
	{
		if(isVisible(element) == false)
			return false;
		if(element->getDisplayArea().isValid() == false)
			return false;
		
		return true;
	}
	
	
	const ContainerSettings* Container::getContainerSettings() const
	{
		if(settings == nullptr)
			return nullptr;
		
		return static_cast<const ContainerSettings*>(settings);
	}
	
	
	ContainerSettings* Container::getContainerSettings()
	{
		if(settings == nullptr)
			return nullptr;
		
		return static_cast<ContainerSettings*>(settings);
	}
	
	
	const ContainerStyle* Container::getStyle() const
	{
		return style;
	}
	
	
	void Container::setStyle(const ContainerStyle* newStyle)
	{
		style = newStyle;
	}
	
	
	const ContainerStyle::Selector& Container::getStyleSelector() const
	{
		return styleSelector;
	}
	
	
	ContainerStyle::Selector& Container::getStyleSelector()
	{
		return styleSelector;
	}
	
	
	const ListenerOptimizer& Container::getListenerOptimizer() const
	{
		return listenerOptimizer;
	}
	
	
	const BasicBlock* Container::operator[] (const std::string& blockID) const
	{
		for(const_iterator i = getBasicBlocks().begin(); !i.isEnd(); ++i)
			if((*i)->getID() == blockID)
				return *i;
		
		return nullptr;
	}
	
	
	BasicBlock* Container::operator[] (const std::string& blockID)
	{
		const Container* container = const_cast<const Container*>(this);
		return const_cast<BasicBlock*>((*container)[blockID]);
	}
	
	
	/*Vector Container::getAvailableMaximization() const
	{
		Vector result1 = BasicBlock::getAvailableMaximization();
		Vector result2 = transition.getAvailableMaximization();
		
		if(settings->horizontalSizePolicy == Settings::SizePolicy::Neutral)
		{
			if(result1.x > 0)
			{
				if(result2.x > 0)
					result1.x = result1.x < result2.x ? result1.x : result2.x;
			}
			else if(result1.x < 0)
			{
				result1.x = result2.x;
			}
		}
		
		if(settings->verticalSizePolicy == Settings::SizePolicy::Neutral)
		{
			if(result1.y > 0)
			{
				if(result2.y > 0)
					result1.y = result1.y < result2.y ? result1.y : result2.y;
			}
			else if(result1.y < 0)
			{
				result1.y = result2.y;
			}
		}
		
		return result1;
	}*/
	
	
	/*unsigned int Container::getModelIndex1() const
	{
		return modelIndex1;
	}
	
	
	unsigned int Container::getModelIndex2() const
	{
		return modelIndex2;
	}
	
	
	float Container::getModelIndexRatio() const
	{
		return modelIndexRatio;
	}
	
	
	void Container::setModelIndex1(unsigned int index1)
	{
		modelIndex1 = index1;
	}
	
	
	void Container::setModelIndex2(unsigned int index2)
	{
		modelIndex2 = index2;
	}
	
	
	void Container::setModelIndexRatio(float ratio)
	{
		modelIndexRatio = ratio;
	}*/
	
	
	bool Container::parseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		if(event.eventApplies(getPositionInfo()) == false)
			return false;
		
		Settings::Visibility visibility = getContainerSettings()->visibility;
		
		if(visibility == Settings::Visibility::Collapse ||
			visibility == Settings::Visibility::IgnoreBlock)
		{
			return false;
		}
		
		bool parseFlag = false;
		bool subComponentsFirst = getContainerSettings()->mouseEventsSubComponentsFirst;
		
		if(subComponentsFirst == false)
			if(BasicBlock::parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		
		if(parseSubComponentsEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(subComponentsFirst == true)
			if(BasicBlock::parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		
		return parseFlag;
	}
	
	
	bool Container::parseEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		if(BasicBlock::parseEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(parseSubComponentsEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		return parseFlag;
	}
	
	
	bool Container::parseEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		if(BasicBlock::parseEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(parseSubComponentsEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		return parseFlag;
	}
	
	
	bool Container::parseEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		if(BasicBlock::parseEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(parseSubComponentsEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		return parseFlag;
	}
	
	
	void Container::step0A_clear()
	{
		BasicBlock::step0A_clear();
		
		for(const_iterator i = getBasicBlocks().begin(); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step0A_clear();
		}
	}
	
	
	void Container::step0B_applyTransformations()
	{
		BasicBlock::step0B_applyTransformations();
		
		for(const_iterator i = getBasicBlocks().begin(); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step0B_applyTransformations();
		}
	}
	
	
	void Container::step0C_optimizeListeners()
	{
		BasicBlock::step0C_optimizeListeners();
		
		for(const_iterator i = getBasicBlocks().begin(); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step0C_optimizeListeners();
		}
		
		const SubComponents* subComponents = &getBasicBlocks();
		subComponentsListenerOptimizer.updateMouseOptimization(subComponents);
		subComponentsListenerOptimizer.updateKeyboardOptimization(subComponents);
		
		listenerOptimizer.updateMouseOptimization(subComponentsListenerOptimizer,
													listenerManager.getListenerOptimizer());
		listenerOptimizer.updateKeyboardOptimization(subComponentsListenerOptimizer,
													listenerManager.getListenerOptimizer());
	}
	
	
	void Container::step1A_minimize()
	{
		ContainerSettings* currentSettings = getContainerSettings();
		
		// add inner spacing
		dInfoStep1A.totalWidth += currentSettings->getInnerSpacingHorizontal();
		dInfoStep1A.totalHeight += currentSettings->getInnerSpacingVertical();
		
		
		// adjust for min, max, fixed settings
		if(currentSettings->fixedWidth > 0)
			dInfoStep1A.totalWidth = (int)currentSettings->fixedWidth;
		else
		{
			if(currentSettings->minWidth > 0 && dInfoStep1A.totalWidth < (int)currentSettings->minWidth)
				dInfoStep1A.totalWidth = (int)currentSettings->minWidth;
			if(currentSettings->maxWidth > 0 && dInfoStep1A.totalWidth > (int)currentSettings->maxWidth)
				dInfoStep1A.totalWidth = (int)currentSettings->maxWidth;
		}
		
		if(currentSettings->fixedHeight > 0)
			dInfoStep1A.totalHeight = (int)currentSettings->fixedHeight;
		else
		{
			if(currentSettings->minHeight > 0 && dInfoStep1A.totalHeight < (int)currentSettings->minHeight)
				dInfoStep1A.totalHeight = (int)currentSettings->minHeight;
			if(currentSettings->maxHeight > 0 && dInfoStep1A.totalHeight > (int)currentSettings->maxHeight)
				dInfoStep1A.totalHeight = (int)currentSettings->maxHeight;
		}
		
		// add outter spacing
		dInfoStep1A.totalWidth += currentSettings->getOutterSpacingHorizontal();
		dInfoStep1A.totalHeight += currentSettings->getOutterSpacingVertical();
	}
	
	
	void Container::step1B_adjust()
	{
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);
		
		for(const_iterator i=getBasicBlocks().begin(&filter); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step1B_adjust();
		}
		
		dInfoStep1B = dInfoStep1A;
	}
	
	
	void Container::step1C_maximize(const Vector& availableSize)
	{
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);
		
		for(const_iterator i=getBasicBlocks().begin(&filter); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step1C_maximize(availableSize);
		}
		
		dInfoStep1C = dInfoStep1B;
		
		/*Vector maxIncrementSpace = getAvailableMaximization(Settings::IterationMode::Physical);
		
		const DimensionsInfo* dInfo = getDimensionsInfo(Settings::Step::s1B_adjust);
		int newWidth = dInfo->totalWidth;
		int newHeight = dInfo->totalHeight;
		
		if(availableSize.x > newWidth)
		{
			if(maxIncrementSpace.x < 0)
				newWidth = availableSize.x;
			else if(maxIncrementSpace.x > 0)
			{
				int availableIncrement = availableSize.x - newWidth;
				newWidth += (availableIncrement < maxIncrementSpace.x ?
							availableIncrement : maxIncrementSpace.x);
			}
		}
		
		if(availableSize.y > newHeight)
		{
			if(maxIncrementSpace.y < 0)
				newHeight = availableSize.y;
			else if(maxIncrementSpace.y > 0)
			{
				int availableIncrement = availableSize.y - newHeight;
				newHeight += (availableIncrement < maxIncrementSpace.y ?
							availableIncrement : maxIncrementSpace.y);
			}
		}
		
		transition.step1C_maximize(newWidth, newHeight);
		updateDInfo(Settings::Step::s1C_maximize);*/
	}
	
	
	void Container::step1D_reAdjust()
	{
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);
		
		for(const_iterator i=getBasicBlocks().begin(&filter); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step1D_reAdjust();
		}
		
		dInfoStep1D = dInfoStep1C;
		
		pInfo.posRectangle.width = dInfoStep1D.totalWidth;
		pInfo.posRectangle.height = dInfoStep1D.totalHeight;
	}
	
	
	void Container::step2C_addToDrawableMap(DrawableMap* drawables)
	{
		if(style != nullptr)
			style->addBackground(drawables, this, styleSelector);
		
		SubComponents::Filter filter;
		filter.addFilterFuntion(isSuperVisible);
		
		for(const_iterator i=getBasicBlocks().begin(&filter); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step2C_addToDrawableMap(drawables);
		}
		
		if(style != nullptr)
			style->addBorder(drawables, this, styleSelector);
	}
	
	
	void Container::step2A_determinePositions()
	{
		SubComponents::Filter filter;
		filter.addFilterFuntion(isSuperVisible);
		
		for(const_iterator i=getBasicBlocks().begin(&filter); !i.isEnd(); ++i)
		{
			BasicBlock* block = const_cast<BasicBlock*>(*i);
			block->step2A_determinePositions();
		}
	}
	
	
	/*unsigned int Container::getBGIndex(unsigned int actualIndex) const
	{
		if(style == nullptr)
			return 0;
		if(style->backgroundColors.size() == 0)
			return 0;
		if(actualIndex >= style->backgroundColors.size())
			return style->backgroundColors.size() - 1;
		return actualIndex;
	}*/
	
	
	/*unsigned int Container::getBorderIndex(unsigned int actualIndex) const
	{
		if(style == nullptr)
			return 0;
		if(style->bordersResourcesID.size() == 0)
			return 0;
		if(actualIndex >= style->bordersResourcesID.size())
			return style->bordersResourcesID.size() - 1;
		return actualIndex;
	}*/
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




