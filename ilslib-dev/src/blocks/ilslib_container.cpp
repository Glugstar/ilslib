#include "../../include/blocks/ilslib_container.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Container::Container(const std::string& containerID,
						const std::string& alternativeID,
						const std::string& layerID):
		BasicBlock(containerID),
		alternatives(),
		transition(this),
		style(nullptr),
		modelIndex1(0),
		modelIndex2(0),
		modelIndexRatio(0.0f),
		dInfoStep1A(),
		dInfoStep1B(),
		dInfoStep1C(),
		dInfoStep1D(),
		pInfo(),
		scrollX(0),
		scrollY(0)
	{
		createNewContainerSettings();
		createAlternative(alternativeID, layerID);
	}
	
	
	Container::~Container()
	{
		std::list<Alternative*>::iterator i;
		for(i=alternatives.begin(); i!=alternatives.end(); ++i)
			delete *i;
	}
	
	
	void Container::setStyle(const ContainerStyle* newStyle)
	{
		style = newStyle;
	}
	
	
	const ContainerStyle* Container::getStyle()
	{
		return style;
	}
	
	
	unsigned int Container::getModelIndex1() const
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
	}
	
	
	void Container::getBasicBlocks(std::list<BasicBlock*>& blockList)
	{
		std::list<Alternative*>::iterator i;
		for(i=alternatives.begin(); i!=alternatives.end(); ++i)
			(*i)->getBasicBlocks(blockList);
	}
	
	
	void Container::addAlternative(Alternative* alt)
	{
		if(alt == nullptr)
			return;
		
		alt->parentContainer = this;
		alternatives.push_back(alt);
	}
	
	
	BasicBlock* Container::findBasicBlock(const std::string& blockID)
	{
		if(blockID == "")
			return nullptr;
		
		std::list<Alternative*>::iterator i;
		for(i=alternatives.begin(); i!=alternatives.end(); ++i)
		{
			BasicBlock* element = (*i)->findBasicBlock(blockID);
			if(element != nullptr)
				return element;
		}
		
		return nullptr;
	}
	
	
	Layer* Container::findLayer(const std::string& layerID)
	{
		if(layerID == "")
			return nullptr;
		
		// search current alternative first
		Alternative* currentAlt = transition.getCurrentAlternative();
		Layer* element = currentAlt->findLayer(layerID);
		if(element != nullptr)
			return element;
		
		// search other alternatives second
		std::list<Alternative*>::iterator i;
		for(i=alternatives.begin(); i!=alternatives.end(); ++i)
		{
			if((*i) == currentAlt) // skip current alternative, already searched there
				continue;
			Layer* element = (*i)->findLayer(layerID);
			if(element != nullptr)
				return element;
		}
		
		return nullptr;
	}
	
	
	Alternative* Container::findAlternative(const std::string& alternativeID)
	{
		if(alternativeID == "")
			return transition.getCurrentAlternative();
		
		std::list<Alternative*>::iterator i;
		for(i=alternatives.begin(); i!=alternatives.end(); ++i)
		{
			if((*i)->getID() == alternativeID)
				return *i;
		}
		
		return nullptr;
	}
	
	
	ContainerSettings* Container::getContainerSettings()
	{
		if(settings == nullptr)
			throw std::exception();
		return (ContainerSettings*)settings;
	}
	
	
	const ContainerSettings* Container::getContainerSettings() const
	{
		if(settings == nullptr)
			throw std::exception();
		return (ContainerSettings*)settings;
	}
	
	
	const DimensionsInfo* Container::getDimensionsInfo(const Settings::Step step) const
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
	
	
	const PositionInfo* Container::getPositionInfo() const
	{
		return &pInfo;
	}
	
	
	int Container::getScrollX() const
	{
		return scrollX;
	}
	
	
	int Container::getScrollY() const
	{
		return scrollY;
	}
	
	
	bool Container::parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		if(event.eventApplies(*getPositionInfo()) == false)
			return false;
		
		if(getContainerSettings()->visibility == Settings::Visibility::Collapse)
			return false;
		
		if(getContainerSettings()->visibility == Settings::Visibility::IgnoreBlock)
			return false;
		
		bool parseFlag = false;
		
		if(getContainerSettings()->mouseEventsSubComponentsFirst == true)
		{
			if(transition.parseMouseEvent(event, blockManager, eventQueue,
											getContainerSettings()->mouseEventsMultiLayer) == true)
				parseFlag = true;
			
			if(BasicBlock::parseMouseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		else
		{
			if(BasicBlock::parseMouseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
			
			if(transition.parseMouseEvent(event, blockManager, eventQueue,
											getContainerSettings()->mouseEventsMultiLayer) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool Container::parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		if(BasicBlock::parseKeyboardEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(transition.parseKeyboardEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		return parseFlag;
	}
	
	
	bool Container::parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		if(BasicBlock::parseTimeEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(transition.parseTimeEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		return parseFlag;
	}
	
	
	bool Container::parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		if(BasicBlock::parseWindowEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		if(transition.parseWindowEvent(event, blockManager, eventQueue) == true)
			parseFlag = true;
		
		return parseFlag;
	}
	
	
	void Container::step0A_clear()
	{
		dInfoStep1A.clear();
		dInfoStep1B.clear();
		dInfoStep1C.clear();
		dInfoStep1D.clear();
		
		pInfo.clear();
		
		transition.step0A_clear();
	}
	
	
	void Container::step0B_applyTransformations()
	{
		transition.step0B_applyTransformations();
	}
	
	
	void Container::step0C_findAllKeyCodes()
	{
		BasicBlock::step0C_findAllKeyCodes();
		
		std::list<Alternative*>::iterator i;
		for(i=alternatives.begin(); i!=alternatives.end(); ++i)
		{
			(*i)->step0C_findAllKeyCodes();
			const std::unordered_set<std::string>& keyCodes = (*i)->getAllKeyCodes();
			
			std::unordered_set<std::string>::const_iterator j;
			for(j=keyCodes.begin(); j!=keyCodes.end(); ++j)
			{
				if(allKeyCodes.find(*j) == allKeyCodes.end())
					allKeyCodes.insert(*j);
			}
		}
	}
	
	
	void Container::step1A_minimize()
	{
		transition.step1A_minimize();
		updateDInfo(Settings::Step::s1A_minimize);
	}
	
	
	void Container::step1B_adjust()
	{
		transition.step1B_adjust();
		updateDInfo(Settings::Step::s1B_adjust);
	}
	
	
	void Container::step1C_maximize(int availableWidth, int availableHeight)
	{
		Vector maxIncrementSpace = getAvailableMaximization(Settings::IterationMode::Physical);
		
		const DimensionsInfo* dInfo = getDimensionsInfo(Settings::Step::s1B_adjust);
		int newWidth = dInfo->totalWidth;
		int newHeight = dInfo->totalHeight;
		
		if(availableWidth > newWidth)
		{
			if(maxIncrementSpace.x < 0)
				newWidth = availableWidth;
			else if(maxIncrementSpace.x > 0)
			{
				int availableIncrement = availableWidth - newWidth;
				newWidth += (availableIncrement < maxIncrementSpace.x ?
							availableIncrement : maxIncrementSpace.x);
			}
		}
		
		if(availableHeight > newHeight)
		{
			if(maxIncrementSpace.y < 0)
				newHeight = availableHeight;
			else if(maxIncrementSpace.y > 0)
			{
				int availableIncrement = availableHeight - newHeight;
				newHeight += (availableIncrement < maxIncrementSpace.y ?
							availableIncrement : maxIncrementSpace.y);
			}
		}
		
		transition.step1C_maximize(newWidth, newHeight);
		updateDInfo(Settings::Step::s1C_maximize);
	}
	
	
	void Container::step1D_reAdjust()
	{
		transition.step1D_reAdjust();
		updateDInfo(Settings::Step::s1D_reAdjust);
		pInfo.posRectangle.width = dInfoStep1D.totalWidth;
		pInfo.posRectangle.height = dInfoStep1D.totalHeight;
	}
	
	
	void Container::step2A_determinePositions()
	{
		transition.step2A_determinePositions();
	}
	
	
	void Container::step2B_determineCutRectangles(const Rectangle& availableSpace)
	{
		BasicBlock::step2B_determineCutRectangles(availableSpace);
		transition.step2B_determineCutRectangles();
	}
	
	
	void Container::step2C_addToDrawableMap(DrawableMap* drawables)
	{
		if(style != nullptr)
			style->addBackground(drawables, this, getBGIndex(modelIndex1), getBGIndex(modelIndex2), modelIndexRatio);
		
		transition.step2C_addToDrawableMap(drawables);
		
		if(style != nullptr)
			style->addBorder(drawables, this, getBorderIndex(modelIndex1));
	}
	
	
	unsigned int Container::getBGIndex(unsigned int actualIndex) const
	{
		if(style == nullptr)
			return 0;
		if(style->backgroundColors.size() == 0)
			return 0;
		if(actualIndex >= style->backgroundColors.size())
			return style->backgroundColors.size() - 1;
		return actualIndex;
	}
	
	
	unsigned int Container::getBorderIndex(unsigned int actualIndex) const
	{
		if(style == nullptr)
			return 0;
		if(style->bordersResourcesID.size() == 0)
			return 0;
		if(actualIndex >= style->bordersResourcesID.size())
			return style->bordersResourcesID.size() - 1;
		return actualIndex;
	}
	
	
	PositionInfo* Container::getPositionInfo()
	{
		return &pInfo;
	}
	
	
	Vector Container::getAvailableMaximization(Settings::IterationMode mode) const
	{
		Vector result1 = BasicBlock::getAvailableMaximization(mode);
		Vector result2 = transition.getAvailableMaximization(mode);
		
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
	}
	
	
	void Container::createNewContainerSettings()
	{
		delete settings;
		settings = new ContainerSettings();
	}
	
	
	void Container::createAlternative(const std::string& alternativeID, const std::string& layerID)
	{
		Alternative* alt = new Alternative(alternativeID, layerID);
		alternatives.push_back(alt);
		alt->parentContainer = this;
		
		transition.transitionTo(alt);
	}
	
	
	void Container::updateDInfo(const Settings::Step step)
	{
		if(step == Settings::Step::s1A_minimize)
			dInfoStep1A = *transition.getDimensionsInfo(step);
		else if(step == Settings::Step::s1B_adjust)
			dInfoStep1B = *transition.getDimensionsInfo(step);
		else if(step == Settings::Step::s1C_maximize)
			dInfoStep1C = *transition.getDimensionsInfo(step);
		else if(step == Settings::Step::s1D_reAdjust)
			dInfoStep1D = *transition.getDimensionsInfo(step);
		else
			throw std::exception();
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




