#include "../../include/blocks/ilslib_layer.hpp"
#include "../../include/blocks/ilslib_alternative.hpp"
#include "../../include/blocks/ilslib_container.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	Layer::Layer(const std::string& layerID):
		id(layerID),
		parentAlternative(nullptr),
		basicBlocks(),
		allKeyCodes(),
		dInfoStep1A(),
		dInfoStep1B(),
		dInfoStep1C(),
		dInfoStep1D(),
		pInfo(),
		layerOffsetX(0),
		layerOffsetY(0)
	{
	}
	
	
	Layer::~Layer()
	{
	}
	
	
	const std::string& Layer::getID() const
	{
		return id;
	}
	
	
	std::string Layer::getPath() const
	{
		return parentAlternative->getPath() + "." + id;
	}
	
	
	const Alternative* Layer::getParentAlternative() const
	{
		return parentAlternative;
	}
	
	
	Alternative* Layer::getParentAlternative()
	{
		return parentAlternative;
	}
	
	
	void Layer::getBasicBlocks(std::list<BasicBlock*>& blockList)
	{
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
			blockList.push_back(*i);
	}
	
	
	BasicBlock* Layer::findBasicBlock(const std::string& blockID)
	{
		return basicBlocks[blockID];
	}
	
	
	void Layer::addBasicBlock(BasicBlock* block)
	{
		if(block == nullptr)
			return;
		
		block->parentLayer = this;
		basicBlocks.push_back(block);
	}
	
	
	void Layer::removeBasicBlock(const std::string& id)
	{
		basicBlocks.erase(id);
	}
	
	
	void Layer::removeAllBasicBlocks()
	{
		basicBlocks.clear();
	}
	
	
	const std::unordered_set<std::string>& Layer::getAllKeyCodes() const
	{
		return allKeyCodes;
	}
	
	
	const DimensionsInfo* Layer::getDimensionsInfo(const Settings::Step step) const
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
	
	
	const PositionInfo* Layer::getPositionInfo() const
	{
		return &pInfo;
	}
	
	
	void Layer::setLayerOffsetX(int offset)
	{
		layerOffsetX = offset;
	}
	
	
	void Layer::setLayerOffsetY(int offset)
	{
		layerOffsetY = offset;
	}
	
	
	int Layer::getLayerOffsetX() const
	{
		return layerOffsetX;
	}
	
	
	int Layer::getLayerOffsetY() const
	{
		return layerOffsetY;
	}
	
	
	bool Layer::parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		if(event.eventApplies(*getPositionInfo()) == false)
			return false;
		
		bool parseFlag = false;
		
		const Container* container = getParentAlternative()->getParentContainer();
		bool tableMode = container->getContainerSettings()->tableMode();
		
		for(iterator i=basicBlocks.begin(Settings::IterationMode::SuperPhysical, tableMode); !i.isEnd(); ++i)
		{
			if((*i)->parseMouseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool Layer::parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseKeyboardEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool Layer::parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseTimeEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool Layer::parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseWindowEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	void Layer::step0A_clear()
	{
		dInfoStep1A.clear();
		dInfoStep1B.clear();
		dInfoStep1C.clear();
		dInfoStep1D.clear();
		
		pInfo.clear();
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
			(*i)->step0A_clear();
	}
	
	
	void Layer::step0B_applyTransformations()
	{
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
			(*i)->step0B_applyTransformations();
	}
	
	
	void Layer::step0C_findAllKeyCodes()
	{
		allKeyCodes.clear();
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
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
	
	
	void Layer::step1A_minimize(const ContainerSettings* currentSettings)
	{
		Settings::Step currentStep = Settings::Step::s1A_minimize;
		DimensionsInfo& dInfo = dInfoStep1A;
		
		
		// recursive minimization first
		// and finding the max dimensions of cells
		for(iterator i=basicBlocks.begin(Settings::IterationMode::Physical, currentSettings->tableMode());
			!i.isEnd(); ++i)
		{
			if(*i == nullptr)
				throw std::exception();
			(*i)->step1A_minimize();
			
			int x = getDPData(*i, currentStep, true);
			int y = getDPData(*i, currentStep, false);
			dInfo.subComponentsMaxWidth = x > dInfo.subComponentsMaxWidth ? x : dInfo.subComponentsMaxWidth;
			dInfo.subComponentsMaxHeight = y > dInfo.subComponentsMaxHeight ? y : dInfo.subComponentsMaxHeight;
		}
		
		
		// calculating rows and columns dimensions
		bool xIsPrimary = (currentSettings->axisPriority ==
							ContainerSettings::AxisPriority::HorizontalFirst);
		int primaryLimit = findPrimaryLimit(currentSettings, currentStep);
		DimensionsMapper dMapper(&dInfo, xIsPrimary);
		
		updateRowColumnInfo(basicBlocks, dMapper,
							primaryLimit, currentStep,
							currentSettings);
		
		
		// commit computations to minimization step info
		dInfo.totalWidth = dInfo.subComponentsTotalWidth;
		dInfo.totalWidth += currentSettings->getInnerSpacingHorizontal();
		if(dInfo.totalWidth < 0)
			dInfo.totalWidth = 0;
		
		dInfo.totalHeight = dInfo.subComponentsTotalHeight;
		dInfo.totalHeight += currentSettings->getInnerSpacingVertical();
		if(dInfo.totalHeight < 0)
			dInfo.totalHeight = 0;
		
		
		// do not include outter spacing at this stage
		// do that in the Alternative's function
	}
	
	
	void Layer::step1B_adjust()
	{
		const Container* container = getParentAlternative()->getParentContainer();
		bool tableMode = container->getContainerSettings()->tableMode();
		
		for(iterator i=basicBlocks.begin(Settings::IterationMode::Physical, tableMode); !i.isEnd(); ++i)
			(*i)->step1B_adjust();
		
		dInfoStep1B = dInfoStep1A;
	}
	
	
	void Layer::step1C_maximize(const ContainerSettings* currentSettings,
								int availableWidth, int availableHeight)
	{
		Settings::Step currentStep = Settings::Step::s1C_maximize;
		
		dInfoStep1C = dInfoStep1B;
		
		dInfoStep1C.totalWidth = availableWidth;
		dInfoStep1C.totalHeight = availableHeight;
		
		availableWidth -= currentSettings->getInnerSpacingHorizontal();
		availableHeight -= currentSettings->getInnerSpacingVertical();
		
		std::list<int> finalListPrimary;
		std::list<int> finalListSecondary;
		std::list<int> maxListSecondary;
		std::list<int> sizeListSecondary;
		
		getMaximizationSpaceList(currentSettings, finalListPrimary,
				maxListSecondary, sizeListSecondary, availableWidth, availableHeight);
		
		int secondarySpacing;
		int secondarySize;
		if(currentSettings->axisPriority == Settings::AxisPriority::HorizontalFirst)
		{
			secondarySpacing = currentSettings->cellSpacingHeight;
			secondarySize = availableHeight;
		}
		else //currentSettings->axisPriority == Settings::AxisPriority::VerticalFirst
		{
			secondarySpacing = currentSettings->cellSpacingWidth;
			secondarySize = availableWidth;
		}
		
		addMaximizationToFinalList(secondarySpacing, secondarySize,
				finalListSecondary, sizeListSecondary, maxListSecondary);
		
		bool tableMode = currentSettings->tableMode();
		
		DimensionsMapper dMapper(&dInfoStep1C, currentSettings->axisPriority ==
												Settings::AxisPriority::HorizontalFirst);
		std::list<int>::iterator j;
		std::list<unsigned int>::const_iterator blockBreakIndex = dInfoStep1C.newLineBreaks.begin();
		std::vector<int>::iterator lineMaxIt = dMapper.lineMaxSecondary->begin();
		std::list<int>::const_iterator finalListSecondaryIt = finalListSecondary.begin();
		j = finalListPrimary.begin();
		
		unsigned int maxSecondary = 0;
		
		for(iterator i=basicBlocks.begin(Settings::IterationMode::Physical, tableMode); !i.isEnd(); ++i)
		{
			if(blockBreakIndex != dInfoStep1C.newLineBreaks.end())
			{
				if(i.getCounter() == (int)*blockBreakIndex)
				{
					maxSecondary = 0;
					++blockBreakIndex;
					++finalListSecondaryIt;
					++lineMaxIt;
				}
			}
			
			if(currentSettings->axisPriority == Settings::AxisPriority::HorizontalFirst)
			{
				(*i)->step1C_maximize(*j, *finalListSecondaryIt);
				unsigned int secondary = (*i)->getDimensionsInfo(Settings::Step::s1C_maximize)->totalHeight;
				maxSecondary = maxSecondary > secondary ? maxSecondary : secondary;
			}
			else //currentSettings->axisPriority == Settings::AxisPriority::VerticalFirst
			{
				(*i)->step1C_maximize(*finalListSecondaryIt, *j);
				unsigned int secondary = (*i)->getDimensionsInfo(Settings::Step::s1C_maximize)->totalWidth;
				maxSecondary = maxSecondary > secondary ? maxSecondary : secondary;
			}
			
			*lineMaxIt = maxSecondary;
			
			++j;
		}
		
		int primaryLimit = findPrimaryLimit(currentSettings, currentStep);
		updateRowColumnInfo(basicBlocks, dMapper,
							primaryLimit, currentStep,
							currentSettings);
		
		
		// commit computations to minimization step info
		dInfoStep1C.totalWidth = dInfoStep1C.subComponentsTotalWidth;
		dInfoStep1C.totalWidth += currentSettings->getInnerSpacingHorizontal();
		if(dInfoStep1C.totalWidth < 0)
			dInfoStep1C.totalWidth = 0;
		
		dInfoStep1C.totalHeight = dInfoStep1C.subComponentsTotalHeight;
		dInfoStep1C.totalHeight += currentSettings->getInnerSpacingVertical();
		if(dInfoStep1C.totalHeight < 0)
			dInfoStep1C.totalHeight = 0;
		
		
		// do not include outter spacing at this stage
		// do that in the Alternative's function
	}
	
	
	void Layer::step1D_reAdjust()
	{
		const Container* container = getParentAlternative()->getParentContainer();
		bool tableMode = container->getContainerSettings()->tableMode();
		
		for(iterator i=basicBlocks.begin(Settings::IterationMode::Physical, tableMode); !i.isEnd(); ++i)
			(*i)->step1D_reAdjust();
		
		dInfoStep1D = dInfoStep1C;
		pInfo.posRectangle.width = dInfoStep1D.totalWidth;
		pInfo.posRectangle.height = dInfoStep1D.totalHeight;
	}
	
	
	void Layer::step2A_determinePositions(const ContainerSettings* currentSettings)
	{
		int containerInnerWidth = 0;
		int containerInnerHeight = 0;
		int centerDisplacementX = 0;
		int centerDisplacementY = 0;
		int absRefX = 0;
		int absRefY = 0;
		int absoluteReferencePrimary = 0;
		int absoluteReferenceSecondary = 0;
		int basePrimarySpacing = 0;
		int baseSecondarySpacing = 0;
		bool equalCellPrimary = false;
		bool equalCellSecondary = false;
		Settings::Flow primaryFlow;
		Settings::Flow secondaryFlow;
		Settings::Alignment primaryAlignment;
		Settings::Alignment secondaryAlignment;
		
		bool xIsPrimary = (currentSettings->axisPriority ==
							ContainerSettings::AxisPriority::HorizontalFirst);
		
		Settings::Step dataStep = Settings::Step::s1D_reAdjust;
		const DimensionsInfo* dInfo = getDimensionsInfo(dataStep);
		DimensionsMapper dMapper(&dInfoStep1D, xIsPrimary);
		
		
		containerInnerWidth = getParentAlternative()->getDimensionsInfo(dataStep)->totalWidth;
		containerInnerWidth -= currentSettings->getSpacingHorizontal();
		
		if(containerInnerWidth > dInfo->subComponentsTotalWidth)
			centerDisplacementX = (containerInnerWidth - dInfo->subComponentsTotalWidth) / 2;
		
		absRefX = getPositionInfo()->posRectangle.x;
		
		if(currentSettings->horizontalFlow == Settings::Flow::RightOrLowerFlow)
		{
			if(currentSettings->horizontalGravity == Settings::Gravity::RightOrLowerGravity)
			{
				if(containerInnerWidth > dInfo->subComponentsTotalWidth)
				{
					absRefX += containerInnerWidth;
					absRefX -= dInfo->subComponentsTotalWidth;
				}
			}
			else if(currentSettings->horizontalGravity == Settings::Gravity::CenterGravity)
			{
				if(containerInnerWidth > dInfo->subComponentsTotalWidth)
					absRefX += centerDisplacementX;
			}
		}
		else // currentSettings->horizontalFlow == Settings::Flow::LeftOrUpperFlow
		{
			if(currentSettings->horizontalGravity == Settings::Gravity::LeftOrUpperGravity)
				absRefX += dInfo->subComponentsTotalWidth;
			else if(currentSettings->horizontalGravity == Settings::Gravity::RightOrLowerGravity)
			{
				if(containerInnerWidth > dInfo->subComponentsTotalWidth)
					absRefX += containerInnerWidth;
				else
					absRefX += dInfo->subComponentsTotalWidth;
			}
			else // currentSettings->horizontalGravity == Settings::Gravity::CenterGravity
			{
				absRefX += dInfo->subComponentsTotalWidth;
				if(containerInnerWidth > dInfo->subComponentsTotalWidth)
					absRefX += centerDisplacementX;
			}
		}
		
		
		containerInnerHeight = getParentAlternative()->getDimensionsInfo(dataStep)->totalHeight;
		containerInnerHeight -= currentSettings->getSpacingVertical();
		
		if(containerInnerHeight > dInfo->subComponentsTotalHeight)
			centerDisplacementY = (containerInnerHeight - dInfo->subComponentsTotalHeight) / 2;
		
		absRefY = getPositionInfo()->posRectangle.y;
		
		if(currentSettings->verticalFlow == Settings::Flow::RightOrLowerFlow)
		{
			if(currentSettings->verticalGravity == Settings::Gravity::RightOrLowerGravity)
			{
				if(containerInnerHeight > dInfo->subComponentsTotalHeight)
				{
					absRefY += containerInnerHeight;
					absRefY -= dInfo->subComponentsTotalHeight;
				}
			}
			else if(currentSettings->verticalGravity == Settings::Gravity::CenterGravity)
			{
				if(containerInnerHeight > dInfo->subComponentsTotalHeight)
					absRefY += centerDisplacementY;
			}
		}
		else // currentSettings->verticalFlow == Settings::Flow::LeftOrUpperFlow
		{
			if(currentSettings->verticalGravity == Settings::Gravity::LeftOrUpperGravity)
				absRefY += dInfo->subComponentsTotalHeight;
			else if(currentSettings->verticalGravity == Settings::Gravity::RightOrLowerGravity)
			{
				if(containerInnerHeight > dInfo->subComponentsTotalHeight)
					absRefY += containerInnerHeight;
				else
					absRefY += dInfo->subComponentsTotalHeight;
			}
			else // currentSettings->verticalGravity == Settings::Gravity::CenterGravity
			{
				absRefY += dInfo->subComponentsTotalHeight;
				if(containerInnerHeight > dInfo->subComponentsTotalHeight)
					absRefY += centerDisplacementY;
			}
		}
		
		
		if(xIsPrimary == true)
		{
			absoluteReferencePrimary = absRefX;
			absoluteReferenceSecondary = absRefY;
			equalCellPrimary = currentSettings->equalCellWidth;
			equalCellSecondary = currentSettings->equalCellHeight;
			basePrimarySpacing = currentSettings->cellSpacingWidth;
			baseSecondarySpacing = currentSettings->cellSpacingHeight;
			primaryFlow = currentSettings->horizontalFlow;
			secondaryFlow = currentSettings->verticalFlow;
			primaryAlignment = currentSettings->horizontalAlignment;
			secondaryAlignment = currentSettings->verticalAlignment;
		}
		else // xIsPrimary == false
		{
			absoluteReferencePrimary = absRefY;
			absoluteReferenceSecondary = absRefX;
			equalCellPrimary = currentSettings->equalCellHeight;
			equalCellSecondary = currentSettings->equalCellWidth;
			basePrimarySpacing = currentSettings->cellSpacingHeight;
			baseSecondarySpacing = currentSettings->cellSpacingWidth;
			primaryFlow = currentSettings->verticalFlow;
			secondaryFlow = currentSettings->horizontalFlow;
			primaryAlignment = currentSettings->verticalAlignment;
			secondaryAlignment = currentSettings->horizontalAlignment;
		}
		
		updateAbsolutePositions(basicBlocks, dMapper, currentSettings,
								absoluteReferencePrimary, absoluteReferenceSecondary,
								basePrimarySpacing, baseSecondarySpacing,
								equalCellPrimary, equalCellSecondary,
								primaryFlow, secondaryFlow,
								primaryAlignment, secondaryAlignment);
	}
	
	
	void Layer::step2B_determineCutRectangles(const Rectangle& availableSpace)
	{
		PositionInfo* pInfo = getPositionInfo();
		
		Rectangle requiredSpace;
		requiredSpace = pInfo->posRectangle;
		
		if(requiredSpace.width < availableSpace.width)
			requiredSpace.width = availableSpace.width;
		if(requiredSpace.height < availableSpace.height)
			requiredSpace.height = availableSpace.height;
		
		pInfo->cutRectangle = requiredSpace.intersect(availableSpace);
		pInfo->intersectionRectangle = pInfo->posRectangle.intersect(pInfo->cutRectangle);
		
		const Container* container = getParentAlternative()->getParentContainer();
		bool tableMode = container->getContainerSettings()->tableMode();
		
		for(iterator i=basicBlocks.begin(Settings::IterationMode::Physical, tableMode); !i.isEnd(); ++i)
			(*i)->step2B_determineCutRectangles(pInfo->intersectionRectangle);
	}
	
	
	void Layer::step2C_addToDrawableMap(DrawableMap* drawables)
	{
		const Container* container = getParentAlternative()->getParentContainer();
		bool tableMode = container->getContainerSettings()->tableMode();
		
		for(iterator i=basicBlocks.begin(Settings::IterationMode::SuperVisible, tableMode); !i.isEnd(); ++i)
			(*i)->step2C_addToDrawableMap(drawables);
	}
	
	
	PositionInfo* Layer::getPositionInfo()
	{
		return &pInfo;
	}
	
	
	Vector Layer::getAvailableMaximization(Settings::IterationMode mode) const
	{
		const Container* container = getParentAlternative()->getParentContainer();
		bool tableMode = container->getContainerSettings()->tableMode();
		
		int maxX, maxY;
		maxX = maxY = 0;
		
		for(const_iterator i=basicBlocks.begin(Settings::IterationMode::Physical, tableMode); !i.isEnd(); ++i)
		{
			Vector result = (*i)->getAvailableMaximization(mode);
			
			if(result.x > 0 && maxX >= 0)
				maxX = maxX > result.x ? maxX : result.x;
			
			if(result.y > 0 && maxY >= 0)
				maxY = maxY > result.y ? maxY : result.y;
			
			if(result.x < 0)
				maxX = maxX < result.x ? maxX : result.x;
			
			if(result.y < 0)
				maxY = maxY < result.y ? maxY : result.y;
			
			if(maxX < 0 && maxY < 0)
				return Vector(maxX, maxY);
		}
		
		return Vector(maxX, maxY);
	}
	
	
	void Layer::getMaximizationSpaceList(const ContainerSettings* currentSettings,
									std::list<int>& finalList,
									std::list<int>& maxListSecondary,
									std::list<int>& sizeListSecondary,
									int availableWidth, int availableHeight)
	{
		std::list<int> sizeList;
		std::list<int> maxListPrimary;
		
		bool tableMode = currentSettings->tableMode();
		
		int spacing = 0;
		int availableSize = 0;
		int secondaryMax = 0;
		std::vector<int>::iterator sizeSecondaryIt;
		DimensionsMapper dMapper(&dInfoStep1C, currentSettings->axisPriority ==
												Settings::AxisPriority::HorizontalFirst);
		sizeSecondaryIt = dMapper.lineMaxSecondary->begin();
		
		if(currentSettings->axisPriority == Settings::AxisPriority::HorizontalFirst)
		{
			spacing = currentSettings->cellSpacingWidth;
			availableSize = availableWidth;
		}
		else //currentSettings->axisPriority == Settings::AxisPriority::VerticalFirst
		{
			spacing = currentSettings->cellSpacingHeight;
			availableSize = availableHeight;
		}
		
		std::list<unsigned int>::const_iterator blockBreakIndex = dInfoStep1C.newLineBreaks.begin();
		
		for(const_iterator block=basicBlocks.begin(Settings::IterationMode::Physical, tableMode);
			!block.isEnd(); ++block)
		{
			if(blockBreakIndex != dInfoStep1C.newLineBreaks.end())
			{
				if(block.getCounter() == (int)*blockBreakIndex)
				{
					sizeListSecondary.push_back(*sizeSecondaryIt);
					maxListSecondary.push_back(secondaryMax);
					addMaximizationToFinalList(spacing, availableSize, finalList, sizeList, maxListPrimary);
					sizeList.clear();
					maxListPrimary.clear();
					++blockBreakIndex;
					++sizeSecondaryIt;
					secondaryMax = 0;
				}
			}
			
			int blockSecondaryMax;
			Vector result = (*block)->getAvailableMaximization(Settings::IterationMode::Physical);
			if(currentSettings->axisPriority == Settings::AxisPriority::HorizontalFirst)
			{
				sizeList.push_back(getDPData(*block, Settings::Step::s1B_adjust, true));
				maxListPrimary.push_back(result.x);
				blockSecondaryMax = result.y;
			}
			else //currentSettings->axisPriority == Settings::AxisPriority::VerticalFirst
			{
				sizeList.push_back(getDPData(*block, Settings::Step::s1B_adjust, false));
				maxListPrimary.push_back(result.y);
				blockSecondaryMax = result.x;
			}
			
			if(blockSecondaryMax < 0 || secondaryMax < 0)
				secondaryMax = secondaryMax < blockSecondaryMax ? secondaryMax : blockSecondaryMax;
			else
				secondaryMax = secondaryMax > blockSecondaryMax ? secondaryMax : blockSecondaryMax;
		}
		
		if(sizeList.size() > 0)
		{
			sizeListSecondary.push_back(*sizeSecondaryIt);
			maxListSecondary.push_back(secondaryMax);
			addMaximizationToFinalList(spacing, availableSize, finalList, sizeList, maxListPrimary);
		}
	}
	
	
	void Layer::addMaximizationToFinalList(int cellSpacing, int availableSize,
									std::list<int>& finalList,
									const std::list<int>& sizeList,
									const std::list<int>& maxList)
	{
		double totalSize = 0.0;
		int totalExtraLast = 0;
		int totalExtraCurrent = 0;
		int availableIncrement = availableSize;
		
		std::list<int> extraList;
		
		std::list<int>::const_iterator i, j;
		std::list<int>::iterator k;
		
		bool first = true;
		for(i=sizeList.begin(); i!=sizeList.end(); ++i)
		{
			extraList.push_back(0);
			availableIncrement -= *i;
			if(first == true)
				first = false;
			else
				availableIncrement -= cellSpacing;
		}
		
		do
		{
			totalExtraLast = totalExtraCurrent;
			
			i = sizeList.begin();
			j = maxList.begin();
			k = extraList.begin();
			
			totalSize = 0.0;
			totalExtraCurrent = 0;
			for(; i!=sizeList.end(); ++i, ++j, ++k)
			{
				if(*k < *j || *j < 0)
					totalSize += *i;
				else
					totalExtraCurrent += *k;
			}
			
			if(totalSize < 1)
				totalSize = 1.0;
			
			i = sizeList.begin();
			j = maxList.begin();
			k = extraList.begin();
			
			for(; i!=sizeList.end(); ++i, ++j, ++k)
			{
				if(*k < *j || *j < 0)
				{
					double sizeRatio = ((double)*i) / totalSize;
					double maxPortion = sizeRatio * (availableIncrement - totalExtraCurrent);
					
					if(maxPortion > ((double)*j) && *j >= 0)
						*k = *j;
					else
						*k = maxPortion;
				}
			}
		}
		while(totalExtraCurrent > totalExtraLast);
		
		i = sizeList.begin();
		k = extraList.begin();
		
		for(; i!=sizeList.end(); ++i, ++k)
			finalList.push_back(*i + *k);
	}
	
	
	int Layer::findPrimaryLimit(const ContainerSettings* currentSettings, const Settings::Step step)
	{
		(void)step; // remove unused parameter warning
		
		int primaryLimit = 0;
		
		if(currentSettings->axisPriority == ContainerSettings::AxisPriority::HorizontalFirst)
		{
			primaryLimit = currentSettings->fixedWidth;
			if(primaryLimit == 0)
				primaryLimit = currentSettings->maxWidth;
			primaryLimit -= currentSettings->getInnerSpacingHorizontal();
			if(primaryLimit < 0)
				primaryLimit = 0;
		}
		else // currentSettings->axisPriority == ContainerSettings::AxisPriority::VerticalFirst
		{
			primaryLimit = currentSettings->fixedHeight;
			if(primaryLimit == 0)
				primaryLimit = currentSettings->maxHeight;
			primaryLimit -= currentSettings->getInnerSpacingVertical();
			if(primaryLimit < 0)
				primaryLimit = 0;
		}
		
		return primaryLimit;
	}
	
	
	void Layer::updateRowColumnInfo(BasicBlocks& basicBlocks, DimensionsMapper& dMapper,
									const int primaryRestriction, const Settings::Step step,
									const ContainerSettings* currentSettings)
	{
		int primaryCounter = 0;
		int secondaryCounter = 0;
		int cellPrimary = 0;
		int cellSecondary = 0;
		int primaryCurrentTotal = 0;
		int secondaryCurrentMax = 0;
		int primarySpacing = 0;
		bool tableMode = currentSettings->tableMode();
		bool postNewLine = false;
		bool equalCellPrimary = false;
		bool equalCellSecondary = false;
		bool xIsPrimary = (currentSettings->axisPriority ==
							ContainerSettings::AxisPriority::HorizontalFirst);
		
		if(xIsPrimary == true)
		{
			equalCellPrimary = currentSettings->equalCellWidth;
			equalCellSecondary = currentSettings->equalCellHeight;
			primarySpacing = currentSettings->cellSpacingWidth;
		}
		else
		{
			equalCellPrimary = currentSettings->equalCellHeight;
			equalCellSecondary = currentSettings->equalCellWidth;
			primarySpacing = currentSettings->cellSpacingHeight;
		}
		
		dMapper.lineMaxPrimary->clear();
		dMapper.lineMaxSecondary->clear();
		dMapper.lineTotalPrimary->clear();
		dMapper.lineTotalSecondary->clear();
		dMapper.newLineBreaks->clear();
		
		const_iterator block;
		for(block = basicBlocks.begin(Settings::IterationMode::Physical, tableMode);
			!block.isEnd(); ++block, ++primaryCounter)
		{
			cellPrimary = getDPData(*block, step, xIsPrimary);
			cellSecondary = getDPData(*block, step, !xIsPrimary);
			
			if(equalCellPrimary == true)
			{
				cellPrimary = cellPrimary > *dMapper.subComponentsMaxPrimary ?
								cellPrimary : *dMapper.subComponentsMaxPrimary;
			}
			
			if(equalCellSecondary == true)
			{
				cellSecondary = cellSecondary > *dMapper.subComponentsMaxSecondary ?
								cellSecondary : *dMapper.subComponentsMaxSecondary;
			}
			
			if(primaryCounter > 0)
			{
				bool newLineRequired = (*block)->getBaseSettings()->preNewLine;
				
				if(newLineRequired == false)
					newLineRequired = postNewLine;
				
				if(newLineRequired == false)
				{
					newLineRequired = determineNewLine(
										currentSettings, tableMode,
										primaryCounter, block.getCounter(),
										primaryCurrentTotal,
										cellPrimary + (primaryCounter > 0 ? primarySpacing : 0),
										primaryRestriction, primaryRestriction > 0);
				}
				
				if(newLineRequired == true)
				{
					commitNewLine(dMapper, block.getCounter(), cellSecondary,
									primaryCounter, secondaryCounter,
									primaryCurrentTotal, secondaryCurrentMax);
				}
			}
			
			postNewLine = (*block)->getBaseSettings()->postNewLine;
			
			primaryCurrentTotal += cellPrimary;
			if(primaryCounter > 0)
				primaryCurrentTotal += primarySpacing;
			
			secondaryCurrentMax = secondaryCurrentMax > cellSecondary ?
									secondaryCurrentMax : cellSecondary;
			
			commitLineMaxPrimary(dMapper, primaryCounter, cellPrimary);
		}
		
		if(primaryCounter > 0)
		{
			commitNewLine(dMapper, block.getCounter(), cellSecondary,
							primaryCounter, secondaryCounter,
							primaryCurrentTotal, secondaryCurrentMax);
		}
		
		calculateSubComponentTotals(dMapper, currentSettings);
	}
	
	
	int Layer::getDPData(const BasicBlock* block,
						const Settings::Step step,
						const bool xIsPrimary)
	{
		if(xIsPrimary == true)
			return block->getDimensionsInfo(step)->totalWidth;
		return block->getDimensionsInfo(step)->totalHeight;
	}
	
	
	bool Layer::determineNewLine(const ContainerSettings* currentSettings, const bool tableMode,
								const int primaryCounter, const int blockCounter,
								const int totalPrimary, const int cellPrimary,
								const int limitPrimary, const bool limitEnabled)
	{
		if(currentSettings->autoLineWrap == false)
			return false;
		
		if(blockCounter == 0)
			return false;
		
		if(tableMode == true)
		{
			if(primaryCounter >= currentSettings->tableNumberOfCells)
				return true;
		}
		else
		{
			if(limitEnabled == false)
				return false;
			if(totalPrimary + cellPrimary > limitPrimary)
				return true;
		}
		
		return false;
	}
	
	
	void Layer::commitNewLine(DimensionsMapper& dMapper, const int blockCounter, const int cellSecondary,
								int& primaryCounter, int& secondaryCounter,
								int& primaryCurrentTotal, int& secondaryCurrentMax)
	{
		if(dMapper.lineTotalSecondary->size() <= (unsigned int)primaryCounter)
			dMapper.lineTotalSecondary->resize(primaryCounter + 1, 0);
		
		(*dMapper.lineTotalSecondary)[primaryCounter] += cellSecondary;
		dMapper.lineTotalPrimary->push_back(primaryCurrentTotal);
		dMapper.lineMaxSecondary->push_back(secondaryCurrentMax);
		dMapper.newLineBreaks->push_back(blockCounter);
		primaryCurrentTotal = 0;
		secondaryCurrentMax = 0;
		primaryCounter = 0;
		++secondaryCounter;
	}
	
	
	void Layer::commitLineMaxPrimary(DimensionsMapper& dMapper, const int primaryCounter,
								const int cellPrimary)
	{
		if(dMapper.lineMaxPrimary->size() <= (unsigned int)primaryCounter)
			dMapper.lineMaxPrimary->resize(primaryCounter + 1, 0);
		
		int value = (*dMapper.lineMaxPrimary)[primaryCounter];
		value = value > cellPrimary ? value : cellPrimary;
		(*dMapper.lineMaxPrimary)[primaryCounter] = value;
	}
	
	
	void Layer::calculateSubComponentTotals(DimensionsMapper& dMapper,
								const ContainerSettings* currentSettings)
	{
		int max, total;
		bool tableMode = currentSettings->tableMode();
		std::vector<int>::iterator i;
		
		
		// total primary is the same on every row in table mode
		if(tableMode == true)
		{
			int totalPrimary = 0;
			bool first = true;
			for(i = dMapper.lineMaxPrimary->begin();
				i != dMapper.lineMaxPrimary->end();
				++i)
			{
				totalPrimary += *i;
				if(first == true)
					first = false;
				else
					totalPrimary += currentSettings->cellSpacingWidth;
			}
			
			for(i = dMapper.lineTotalPrimary->begin();
				i != dMapper.lineTotalPrimary->end();
				++i)
			{
				*i = totalPrimary;
			}
		}
		
		
		// primary
		max = 0;
		
		for(i = dMapper.lineTotalPrimary->begin();
			i != dMapper.lineTotalPrimary->end();
			++i)
		{
			max = max > *i ? max : *i;
		}
		
		*dMapper.subComponentsTotalPrimary = max;
		
		// secondary
		total = 0;
		
		for(i = dMapper.lineMaxSecondary->begin();
			i != dMapper.lineMaxSecondary->end();
			++i)
		{
			// add row spacing
			if(i != dMapper.lineMaxSecondary->begin())
			{
				if(currentSettings->axisPriority ==
					ContainerSettings::AxisPriority::HorizontalFirst)
					total += currentSettings->cellSpacingHeight;
				else
					total += currentSettings->cellSpacingWidth;
			}
			
			total += *i;
		}
		
		*dMapper.subComponentsTotalSecondary = total;
	}
	
	
	void Layer::updateAbsolutePositions(BasicBlocks& basicBlocks, DimensionsMapper& dMapper,
									const ContainerSettings* currentSettings,
									const int absoluteReferencePrimary, const int absoluteReferenceSecondary,
									const int basePrimarySpacing, const int baseSecondarySpacing,
									const bool equalCellPrimary, const bool equalCellSecondary,
									const Settings::Flow primaryFlow, const Settings::Flow secondaryFlow,
									const Settings::Alignment primaryAlignment,
									const Settings::Alignment secondaryAlignment)
	{
		Settings::Step dataStep = Settings::Step::s1D_reAdjust;
		
		int nextNewLineIndex = -1;
		int posPrimary = 0;
		int posSecondary = 0;
		int primaryIndex = 0;
		int secondaryIndex = 0;
		int primarySpacing = 0;
		int secondarySpacing = 0;
		int primaryAlignOffset = 0;
		int secondaryAlignOffset = 0;
		bool xIsPrimary = (currentSettings->axisPriority ==
							ContainerSettings::AxisPriority::HorizontalFirst);
		bool tableMode = currentSettings->tableMode();
		
		std::list<unsigned int>::const_iterator lineBreakIterator;
		
		lineBreakIterator = dMapper.newLineBreaks->begin();
		if(lineBreakIterator != dMapper.newLineBreaks->end())
			nextNewLineIndex = (int)*lineBreakIterator;
		
		
		for(iterator block = basicBlocks.begin(Settings::IterationMode::Physical, tableMode);
			!block.isEnd(); ++block, ++primaryIndex)
		{
			if(*block == nullptr)
				throw std::exception();
			
			if(nextNewLineIndex == block.getCounter())
			{
				posPrimary = 0;
				
				posSecondary += (*dMapper.lineMaxSecondary)[secondaryIndex];
				posSecondary += secondarySpacing;
				
				primaryIndex = 0;
				++secondaryIndex;
				
				++lineBreakIterator;
				if(lineBreakIterator != dMapper.newLineBreaks->end())
					nextNewLineIndex = (int)*lineBreakIterator;
				else
					nextNewLineIndex = -1;
			}
			
			int primary;
			if(equalCellPrimary == true)
				primary = *dMapper.subComponentsMaxPrimary;
			else if(tableMode == true)
				primary = (*dMapper.lineMaxPrimary)[primaryIndex];
			else
				primary = getDPData(*block, dataStep, xIsPrimary);
			
			int secondary;
			if(equalCellSecondary == true)
				secondary = *dMapper.subComponentsMaxSecondary;
			else if(tableMode == true)
				secondary = (*dMapper.lineMaxSecondary)[secondaryIndex];
			else
				secondary = getDPData(*block, dataStep, !xIsPrimary);
			
			
			PositionInfo* blockPInfo = (*block)->getPositionInfo();
			PositionMapper pMapper(blockPInfo, xIsPrimary);
			
			*pMapper.coordPrimary = absoluteReferencePrimary;
			*pMapper.coordSecondary = absoluteReferenceSecondary;
			
			primaryAlignOffset = *dMapper.subComponentsTotalPrimary -
								(*dMapper.lineTotalPrimary)[secondaryIndex];
			if(primaryFlow == Settings::Flow::RightOrLowerFlow)
			{
				*pMapper.coordPrimary += posPrimary;
				if(primaryAlignment == Settings::Alignment::RightOrLowerAlignment)
					*pMapper.coordPrimary += primaryAlignOffset;
				else if(primaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordPrimary += primaryAlignOffset / 2;
			}
			else // primaryFlow == Settings::Flow::LeftOrUpperFlow
			{
				*pMapper.coordPrimary -= posPrimary;
				*pMapper.coordPrimary -= primary;
				if(primaryAlignment == Settings::Alignment::LeftOrUpperAlignment)
					*pMapper.coordPrimary -= primaryAlignOffset;
				else if(primaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordPrimary -= primaryAlignOffset / 2;
			}
			
			
			secondaryAlignOffset = (*dMapper.lineMaxSecondary)[secondaryIndex] -
									getDPData(*block, dataStep, !xIsPrimary);
			if(secondaryFlow == Settings::Flow::RightOrLowerFlow)
			{
				*pMapper.coordSecondary += posSecondary;
				if(secondaryAlignment == Settings::Alignment::RightOrLowerAlignment)
					*pMapper.coordSecondary += secondaryAlignOffset;
				else if(secondaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordSecondary += secondaryAlignOffset / 2;
			}
			else // secondaryFlow == Settings::Flow::LeftOrUpperFlow
			{
				*pMapper.coordSecondary -= posSecondary;
				*pMapper.coordSecondary -= secondary;
				if(secondaryAlignment == Settings::Alignment::LeftOrUpperAlignment)
					*pMapper.coordSecondary -= secondaryAlignOffset;
				else if(secondaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordSecondary -= secondaryAlignOffset / 2;
			}
			
			(*block)->step2A_determinePositions();
			
			primarySpacing = basePrimarySpacing;
			secondarySpacing = baseSecondarySpacing;
			/*if(xIsPrimary == true)
			{
				primarySpacing = basePrimarySpacing + ???; // add to spacing if elements are spread out
				secondarySpacing = baseSecondarySpacing + ???; // add to spacing if elements are spread out
			}
			else
			{
				primarySpacing = basePrimarySpacing + ???; // add to spacing if elements are spread out
				secondarySpacing = baseSecondarySpacing + ???; // add to spacing if elements are spread out
			}*/
			
			posPrimary += primary;
			posPrimary += primarySpacing;
		}
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




