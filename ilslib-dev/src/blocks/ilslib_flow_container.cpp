#include "../../include/blocks/ilslib_flow_container.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{



	FlowContainer::FlowContainer(const std::string& containerID):
		Container(containerID),
		basicBlocks()
	{
		settings = new FlowContainerSettings();
	}


	FlowContainer::~FlowContainer()
	{
	}


	const FlowContainerSettings* FlowContainer::getFlowContainerSettings() const
	{
		if(settings == nullptr)
			return nullptr;

		return static_cast<const FlowContainerSettings*>(settings);
	}


	FlowContainerSettings* FlowContainer::getFlowContainerSettings()
	{
		if(settings == nullptr)
			return nullptr;

		return static_cast<FlowContainerSettings*>(settings);
	}


	const Container::SubComponents& FlowContainer::getBasicBlocks() const
	{
		return basicBlocks;
	}


	Container::SubComponents& FlowContainer::getBasicBlocks()
	{
		return basicBlocks;
	}


	bool FlowContainer::addBasicBlock(BasicBlock* block)
	{
		if(block == nullptr)
			return false;

		bool result = basicBlocks.push_back(block);
		if(result == true)
			block->parent = this;

		return result;
	}


	bool FlowContainer::removeBasicBlock(const std::string& blockID)
	{
		return basicBlocks.erase(blockID);
	}


	void FlowContainer::step1A_minimize()
	{
		FlowContainerSettings* currentSettings = getFlowContainerSettings();

		Settings::Step currentStep = Settings::Step::s1A_minimize;
		DimensionsInfo& dInfo = dInfoStep1A;


		// recursive minimization first
		// and finding the max dimensions of cells
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);

		for(iterator i=basicBlocks.begin(&filter); !i.isEnd(); ++i)
		{
			(*i)->step1A_minimize();

			Vector blockSize = getBlockSize(*i, currentStep);
			dInfo.subComponentsMaxWidth = blockSize.x > dInfo.subComponentsMaxWidth ?
											blockSize.x : dInfo.subComponentsMaxWidth;
			dInfo.subComponentsMaxHeight = blockSize.y > dInfo.subComponentsMaxHeight ?
											blockSize.y : dInfo.subComponentsMaxHeight;
		}


		// calculating rows and columns dimensions
		bool xIsPrimary = (currentSettings->axisPriority ==
							ContainerSettings::AxisPriority::HorizontalFirst);
		int primaryLimit = findPrimaryLimit(currentSettings);
		DimensionsMapper dMapper(&dInfo, xIsPrimary);

		updateRowColumnInfo(basicBlocks, dMapper,
							primaryLimit, currentStep,
							currentSettings);


		if(dInfo.subComponentsTotalWidth < 0)
			dInfo.subComponentsTotalWidth = 0;
		if(dInfo.subComponentsTotalHeight < 0)
			dInfo.subComponentsTotalHeight = 0;

		// commit computations to minimization step info
		dInfo.totalWidth = dInfo.subComponentsTotalWidth;
		dInfo.totalHeight = dInfo.subComponentsTotalHeight;


		Container::step1A_minimize();
	}


	/*void FlowContainer::step1C_maximize(const Vector& availableSize)
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

		//Container::step1C_maximize();
	}*/


	void FlowContainer::step2A_determinePositions()
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
		int subComponentsWidth = 0;
		int subComponentsHeight = 0;
		bool equalCellPrimary = false;
		bool equalCellSecondary = false;
		Settings::Flow primaryFlow;
		Settings::Flow secondaryFlow;
		Settings::Alignment primaryAlignment;
		Settings::Alignment secondaryAlignment;

		FlowContainerSettings* currentSettings = getFlowContainerSettings();

		bool xIsPrimary = (currentSettings->axisPriority ==
							ContainerSettings::AxisPriority::HorizontalFirst);

		//Settings::Step dataStep = Settings::Step::s1D_reAdjust;
		const DimensionsInfo& dInfo = getDimensionsInfo();
		DimensionsMapper dMapper(&dInfoStep1D, xIsPrimary);

		subComponentsWidth = dInfo.subComponentsTotalWidth;
		subComponentsHeight = dInfo.subComponentsTotalHeight;


		//containerInnerWidth = getParentAlternative()->getDimensionsInfo(dataStep)->totalWidth;
		containerInnerWidth = dInfo.totalWidth;
		containerInnerWidth -= currentSettings->getSpacingHorizontal();

		if(containerInnerWidth > subComponentsWidth)
			centerDisplacementX = (containerInnerWidth - subComponentsWidth) / 2;

		absRefX = getPositionInfo().posRectangle.x + currentSettings->getSpacingLeft();

		if(currentSettings->horizontalFlow == Settings::Flow::LeftToRightFlow)
		{
			if(currentSettings->horizontalGravity == Settings::Gravity::RightGravity)
			{
				if(containerInnerWidth > subComponentsWidth)
				{
					absRefX += containerInnerWidth;
					absRefX -= subComponentsWidth;
				}
			}
			else if(currentSettings->horizontalGravity == Settings::Gravity::CenterGravity)
			{
				if(containerInnerWidth > subComponentsWidth)
					absRefX += centerDisplacementX;
			}
		}
		else // currentSettings->horizontalFlow == Settings::Flow::RightToLeftFlow
		{
			if(currentSettings->horizontalGravity == Settings::Gravity::LeftGravity)
				absRefX += subComponentsWidth;
			else if(currentSettings->horizontalGravity == Settings::Gravity::RightGravity)
			{
				if(containerInnerWidth > subComponentsWidth)
					absRefX += containerInnerWidth;
				else
					absRefX += subComponentsWidth;
			}
			else // currentSettings->horizontalGravity == Settings::Gravity::CenterGravity
			{
				absRefX += subComponentsWidth;
				if(containerInnerWidth > subComponentsWidth)
					absRefX += centerDisplacementX;
			}
		}


		//containerInnerHeight = getParentAlternative()->getDimensionsInfo(dataStep)->totalHeight;
		containerInnerHeight = dInfo.totalHeight;
		containerInnerHeight -= currentSettings->getSpacingVertical();

		if(containerInnerHeight > subComponentsHeight)
			centerDisplacementY = (containerInnerHeight - subComponentsHeight) / 2;

		absRefY = getPositionInfo().posRectangle.y + currentSettings->getSpacingTop();

		if(currentSettings->verticalFlow == Settings::Flow::TopToBottomFlow)
		{
			if(currentSettings->verticalGravity == Settings::Gravity::BottomGravity)
			{
				if(containerInnerHeight > subComponentsHeight)
				{
					absRefY += containerInnerHeight;
					absRefY -= subComponentsHeight;
				}
			}
			else if(currentSettings->verticalGravity == Settings::Gravity::CenterGravity)
			{
				if(containerInnerHeight > subComponentsHeight)
					absRefY += centerDisplacementY;
			}
		}
		else // currentSettings->verticalFlow == Settings::Flow::BottomToTopFlow
		{
			if(currentSettings->verticalGravity == Settings::Gravity::TopGravity)
				absRefY += subComponentsHeight;
			else if(currentSettings->verticalGravity == Settings::Gravity::BottomGravity)
			{
				if(containerInnerHeight > subComponentsHeight)
					absRefY += containerInnerHeight;
				else
					absRefY += subComponentsHeight;
			}
			else // currentSettings->verticalGravity == Settings::Gravity::CenterGravity
			{
				absRefY += subComponentsHeight;
				if(containerInnerHeight > subComponentsHeight)
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


	void FlowContainer::step2B_determineCutRectangles(const Rectangle& availableSpace)
	{
		Rectangle requiredSpace;
		requiredSpace = pInfo.posRectangle;

		if(requiredSpace.width < availableSpace.width)
			requiredSpace.width = availableSpace.width;
		if(requiredSpace.height < availableSpace.height)
			requiredSpace.height = availableSpace.height;

		pInfo.cutRectangle = requiredSpace.intersect(availableSpace);
		pInfo.intersectionRectangle = pInfo.posRectangle.intersect(pInfo.cutRectangle);

		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);

		for(iterator i=basicBlocks.begin(&filter); !i.isEnd(); ++i)
			(*i)->step2B_determineCutRectangles(pInfo.intersectionRectangle);
	}


	bool FlowContainer::parseSubComponentsEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;

		SubComponents::Filter filter;
		filter.addFilterFuntion(isSuperPhysical);

		for(iterator i=basicBlocks.begin(&filter); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}

		return parseFlag;
	}


	bool FlowContainer::parseSubComponentsEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;

		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}

		return parseFlag;
	}


	bool FlowContainer::parseSubComponentsEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;

		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}

		return parseFlag;
	}


	bool FlowContainer::parseSubComponentsEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;

		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}

		return parseFlag;
	}


	Vector FlowContainer::getAvailableMaximization() const
	{
		/*const Container* container = getParentAlternative()->getParentContainer();
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

		return Vector(maxX, maxY);*/
		throw std::exception();
	}


	void FlowContainer::getMaximizationSpaceList(const FlowContainerSettings* currentSettings,
									std::list<int>& finalList,
									std::list<int>& maxListSecondary,
									std::list<int>& sizeListSecondary,
									int availableWidth, int availableHeight)
	{
		/*std::list<int> sizeList;
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
		}*/
	}


	void FlowContainer::addMaximizationToFinalList(int cellSpacing, int availableSize,
									std::list<int>& finalList,
									const std::list<int>& sizeList,
									const std::list<int>& maxList)
	{
		/*double totalSize = 0.0;
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
			finalList.push_back(*i + *k);*/
	}


	int FlowContainer::findPrimaryLimit(const FlowContainerSettings* currentSettings)
	{
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


	void FlowContainer::updateRowColumnInfo(SubComponents& basicBlocks, DimensionsMapper& dMapper,
									const int primaryRestriction, const Settings::Step step,
									const FlowContainerSettings* currentSettings)
	{
		int primaryCounter = 0;
		int secondaryCounter = 0;
		Vector cellSize;
		int primaryCurrentTotal = 0;
		int secondaryCurrentMax = 0;
		int primarySpacing = 0;
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

		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);

		const_iterator block;
		for(block = basicBlocks.begin(&filter);
			!block.isEnd(); ++block, ++primaryCounter)
		{
			cellSize = getBlockSize(*block, step);
			if(xIsPrimary == false)
			{
				int tmp = cellSize.x;
				cellSize.x = cellSize.y;
				cellSize.y = tmp;
			}

			if(equalCellPrimary == true)
			{
				cellSize.x = cellSize.x > *dMapper.subComponentsMaxPrimary ?
								cellSize.x : *dMapper.subComponentsMaxPrimary;
			}

			if(equalCellSecondary == true)
			{
				cellSize.y = cellSize.y > *dMapper.subComponentsMaxSecondary ?
								cellSize.y : *dMapper.subComponentsMaxSecondary;
			}

			if(primaryCounter > 0)
			{
				bool newLineRequired = (*block)->getSettings()->preNewLine;

				if(newLineRequired == false)
					newLineRequired = postNewLine;

				if(newLineRequired == false)
				{
					newLineRequired = determineNewLine(
										currentSettings,
										primaryCounter, block.getCounter(),
										primaryCurrentTotal,
										cellSize.x + (primaryCounter > 0 ? primarySpacing : 0),
										primaryRestriction, primaryRestriction > 0);
				}

				if(newLineRequired == true)
				{
					commitNewLine(dMapper, block.getCounter(), cellSize.y,
									primaryCounter, secondaryCounter,
									primaryCurrentTotal, secondaryCurrentMax);
				}
			}

			postNewLine = (*block)->getSettings()->postNewLine;

			primaryCurrentTotal += cellSize.x;
			if(primaryCounter > 0)
				primaryCurrentTotal += primarySpacing;

			secondaryCurrentMax = secondaryCurrentMax > cellSize.y ?
									secondaryCurrentMax : cellSize.y;

			commitLineMaxPrimary(dMapper, primaryCounter, cellSize.x);
		}

		if(primaryCounter > 0)
		{
			commitNewLine(dMapper, block.getCounter(), cellSize.y,
							primaryCounter, secondaryCounter,
							primaryCurrentTotal, secondaryCurrentMax);
		}

		calculateSubComponentTotals(dMapper, currentSettings);
	}


	Vector FlowContainer::getBlockSize(const BasicBlock* block, const Settings::Step step)
	{
		const DimensionsInfo& blockDInfo = block->getDimensionsInfo(step);

		Vector blockSize(blockDInfo.totalWidth, blockDInfo.totalHeight);
		return blockSize;
	}


	bool FlowContainer::determineNewLine(const FlowContainerSettings* currentSettings,
								const int primaryCounter, const int blockCounter,
								const int totalPrimary, const int cellPrimary,
								const int limitPrimary, const bool limitEnabled)
	{
		if(currentSettings->autoLineWrap == false)
			return false;

		if(blockCounter == 0)
			return false;

        if(limitEnabled == false)
            return false;

        if(totalPrimary + cellPrimary > limitPrimary)
            return true;

		return false;
	}


	void FlowContainer::commitNewLine(DimensionsMapper& dMapper, const int blockCounter, const int cellSecondary,
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


	void FlowContainer::commitLineMaxPrimary(DimensionsMapper& dMapper, const int primaryCounter,
								const int cellPrimary)
	{
		if(dMapper.lineMaxPrimary->size() <= (unsigned int)primaryCounter)
			dMapper.lineMaxPrimary->resize(primaryCounter + 1, 0);

		int value = (*dMapper.lineMaxPrimary)[primaryCounter];
		value = value > cellPrimary ? value : cellPrimary;
		(*dMapper.lineMaxPrimary)[primaryCounter] = value;
	}


	void FlowContainer::calculateSubComponentTotals(DimensionsMapper& dMapper,
								const FlowContainerSettings* currentSettings)
	{
		int max, total;
		std::vector<int>::iterator i;

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


	void FlowContainer::updateAbsolutePositions(SubComponents& basicBlocks, DimensionsMapper& dMapper,
									const FlowContainerSettings* currentSettings,
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

		std::list<unsigned int>::const_iterator lineBreakIterator;

		lineBreakIterator = dMapper.newLineBreaks->begin();
		if(lineBreakIterator != dMapper.newLineBreaks->end())
			nextNewLineIndex = (int)*lineBreakIterator;

		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);

		for(iterator block = basicBlocks.begin(&filter); !block.isEnd(); ++block, ++primaryIndex)
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

			Vector blockSize = getBlockSize(*block, dataStep);

			int primary;
			if(equalCellPrimary == true)
				primary = *dMapper.subComponentsMaxPrimary;
			else
				primary = xIsPrimary ? blockSize.x : blockSize.y;

			int secondary;
			if(equalCellSecondary == true)
				secondary = *dMapper.subComponentsMaxSecondary;
			else
				secondary = !xIsPrimary ? blockSize.x : blockSize.y;


			PositionInfo* blockPInfo = &(*block)->pInfo;
			PositionMapper pMapper(blockPInfo, xIsPrimary);

			*pMapper.coordPrimary = absoluteReferencePrimary;
			*pMapper.coordSecondary = absoluteReferenceSecondary;

			primaryAlignOffset = *dMapper.subComponentsTotalPrimary -
								(*dMapper.lineTotalPrimary)[secondaryIndex];

            bool primaryFlowFlag = false;
            if(xIsPrimary == true)
                primaryFlowFlag = (primaryFlow == Settings::Flow::LeftToRightFlow);
            else
                primaryFlowFlag = (primaryFlow == Settings::Flow::TopToBottomFlow);

			if(primaryFlowFlag == true)
			{
			    bool primaryAlignmentFlag = false;
                if(xIsPrimary == true)
                    primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::RightAlignment);
                else
                    primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::BottomAlignment);

				*pMapper.coordPrimary += posPrimary;
				if(primaryAlignmentFlag == true)
					*pMapper.coordPrimary += primaryAlignOffset;
				else if(primaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordPrimary += primaryAlignOffset / 2;
			}
			else
			{
			    bool primaryAlignmentFlag = false;
                if(xIsPrimary == true)
                    primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::LeftAlignment);
                else
                    primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::TopAlignment);

				*pMapper.coordPrimary -= posPrimary;
				*pMapper.coordPrimary -= primary;
				if(primaryAlignmentFlag == true)
					*pMapper.coordPrimary -= primaryAlignOffset;
				else if(primaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordPrimary -= primaryAlignOffset / 2;
			}


			secondaryAlignOffset = (*dMapper.lineMaxSecondary)[secondaryIndex] -
									!xIsPrimary ? blockSize.x : blockSize.y;


            bool secondaryFlowFlag = false;
            if(xIsPrimary == false)
                secondaryFlowFlag = (secondaryFlow == Settings::Flow::LeftToRightFlow);
            else
                secondaryFlowFlag = (secondaryFlow == Settings::Flow::TopToBottomFlow);

			if(secondaryFlowFlag == true)
			{
			    bool secondaryAlignmentFlag = false;
                if(xIsPrimary == false)
                    secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::RightAlignment);
                else
                    secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::BottomAlignment);

				*pMapper.coordSecondary += posSecondary;
				if(secondaryAlignmentFlag == true)
					*pMapper.coordSecondary += secondaryAlignOffset;
				else if(secondaryAlignment == Settings::Alignment::CenterAlignment)
					*pMapper.coordSecondary += secondaryAlignOffset / 2;
			}
			else
			{
			    bool secondaryAlignmentFlag = false;
                if(xIsPrimary == false)
                    secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::LeftAlignment);
                else
                    secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::TopAlignment);

				*pMapper.coordSecondary -= posSecondary;
				*pMapper.coordSecondary -= secondary;
				if(secondaryAlignmentFlag == true)
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




