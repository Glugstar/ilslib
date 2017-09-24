#include "../../include/blocks/ilslib_flow_container.hpp"



/*  ----------------------------------------------------------------------------------
										ILSLib
    ----------------------------------------------------------------------------------*/
namespace ILSLib
{


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
			dInfo.subComponentsMaxWidth = (blockSize.x > dInfo.subComponentsMaxWidth) ?
			                              blockSize.x : dInfo.subComponentsMaxWidth;
			dInfo.subComponentsMaxHeight = (blockSize.y > dInfo.subComponentsMaxHeight) ?
			                               blockSize.y : dInfo.subComponentsMaxHeight;
		}
		
		
		// calculating rows and columns dimensions
		bool xIsPrimary = currentSettings->xIsPrimary();
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
	
	
	/*
	    void FlowContainer::step1C_maximize(const Vector& availableSize)
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
	
			lineMaxIt = maxSecondary;
	
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
	    }
	*/
	
	
	Vector FlowContainer::getAvailableMaximization() const
	{
		/*
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
		*/
		throw std::exception();
	}
	
	
	void FlowContainer::getMaximizationSpaceList(const FlowContainerSettings* currentSettings,
	        std::list<int>& finalList,
	        std::list<int>& maxListSecondary,
	        std::list<int>& sizeListSecondary,
	        int availableWidth, int availableHeight)
	{
		/*  std::list<int> sizeList;
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
		/*  double totalSize = 0.0;
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
						k = *j;
					else
						k = maxPortion;
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
		bool xIsPrimary = currentSettings->xIsPrimary();
		
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
				cellSize.swapValues();
				
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
			
		if(totalPrimary == 0)
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
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




