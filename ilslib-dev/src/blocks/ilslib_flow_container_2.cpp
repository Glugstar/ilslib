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
	
	
	int FlowContainer::findPrimaryLimit(const FlowContainerSettings* currentSettings)
	{
		int primaryLimit = 0;
		bool xIsPrimary = currentSettings->xIsPrimary();
		
		if(xIsPrimary)
		{
			primaryLimit = currentSettings->fixedWidth;
			if(primaryLimit == 0)
				primaryLimit = currentSettings->maxWidth;
			primaryLimit -= currentSettings->getInnerSpacingHorizontal();
			if(primaryLimit < 0)
				primaryLimit = 0;
		}
		else
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
			
		if(primaryCounter == 0)
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




