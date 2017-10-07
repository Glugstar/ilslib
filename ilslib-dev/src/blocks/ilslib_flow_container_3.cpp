#include "../../include/blocks/ilslib_flow_container.hpp"

/*
---- sequential maximization algorithm pseudo-code:

maximize
	getMaximizableSubObjects()
	while(object list is not empty)
		for(objects)
			object maximum share = (object size * remaining maximization potential) / objects total size
			if(object maximum share >= object maximization potential)
				maximize(this object, object maximization potential)
				remove it from the object list
				subtract from remaining maximization potential
				subtract from objects total size
		if(no object was maximized)
			end while
	if(remaining maximization potential > 0)
        // sort according to which object share is closest to its ceiling function
		sortByRoundingNearestCeiling(objects)
		for(objects)
			if(remaining maximization potential > 0)
				object maximum share ++
		for(objects)
			maximize(this object, object maximum share)
*/



/*  ----------------------------------------------------------------------------------
										ILSLib
    ----------------------------------------------------------------------------------*/
namespace ILSLib
{



	void FlowContainer::step1C_maximize(const Vector& availableSize)
	{
		Container::step1C_maximize(availableSize);
		return;
		
		// algorithm needs updating, currently broken
		
		FlowContainerSettings* currentSettings = getFlowContainerSettings();
		Settings::Step currentStep = Settings::Step::s1C_maximize;
		
		dInfoStep1C = dInfoStep1B;
		int availableWidth = availableSize.x;
		int availableHeight = availableSize.y;
		
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
		                         
		bool xIsPrimary = currentSettings->xIsPrimary();
		int secondarySpacing;
		int secondarySize;
		if(xIsPrimary)
		{
			secondarySpacing = currentSettings->cellSpacingHeight;
			secondarySize = availableHeight;
		}
		else
		{
			secondarySpacing = currentSettings->cellSpacingWidth;
			secondarySize = availableWidth;
		}
		
		addMaximizationToFinalList(secondarySpacing, secondarySize,
		                           finalListSecondary, sizeListSecondary, maxListSecondary);
		                           
		DimensionsMapper dMapper(&dInfoStep1C, xIsPrimary);
		std::list<int>::iterator j;
		std::list<unsigned int>::const_iterator blockBreakIndex = dInfoStep1C.newLineBreaks.begin();
		std::vector<int>::iterator lineMaxIt = dMapper.lineMaxSecondary->begin();
		std::list<int>::const_iterator finalListSecondaryIt = finalListSecondary.begin();
		j = finalListPrimary.begin();
		
		unsigned int maxSecondary = 0;
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);
		
		for(iterator i=basicBlocks.begin(&filter); !i.isEnd(); ++i)
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
			
			if(xIsPrimary)
			{
				Vector blockAvailableSize(*j, *finalListSecondaryIt);
				(*i)->step1C_maximize(blockAvailableSize);
				unsigned int secondary = (*i)->getDimensionsInfo(Settings::Step::s1C_maximize).totalHeight;
				maxSecondary = maxSecondary > secondary ? maxSecondary : secondary;
			}
			else
			{
				Vector blockAvailableSize(*finalListSecondaryIt, *j);
				(*i)->step1C_maximize(blockAvailableSize);
				unsigned int secondary = (*i)->getDimensionsInfo(Settings::Step::s1C_maximize).totalWidth;
				maxSecondary = maxSecondary > secondary ? maxSecondary : secondary;
			}
			
			*lineMaxIt = maxSecondary;
			
			++j;
		}
		
		int primaryLimit = findPrimaryLimit(currentSettings);
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
	
	
	
	Vector FlowContainer::getAvailableMaximization() const
	{
		int maxX, maxY;
		maxX = maxY = 0;
		
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);
		
		for(const_iterator i=basicBlocks.begin(&filter); !i.isEnd(); ++i)
		{
			Vector result = (*i)->getAvailableMaximization();
			
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
	
	
	void FlowContainer::getMaximizationSpaceList(const FlowContainerSettings* currentSettings,
	        std::list<int>& finalList,
	        std::list<int>& maxListSecondary,
	        std::list<int>& sizeListSecondary,
	        int availableWidth, int availableHeight)
	{
		std::list<int> sizeList;
		std::list<int> maxListPrimary;
		
		int spacing = 0;
		int availableSize = 0;
		int secondaryMax = 0;
		bool xIsPrimary = currentSettings->xIsPrimary();
		
		std::vector<int>::iterator sizeSecondaryIt;
		DimensionsMapper dMapper(&dInfoStep1C, xIsPrimary);
		sizeSecondaryIt = dMapper.lineMaxSecondary->begin();
		
		if(xIsPrimary)
		{
			spacing = currentSettings->cellSpacingWidth;
			availableSize = availableWidth;
		}
		else
		{
			spacing = currentSettings->cellSpacingHeight;
			availableSize = availableHeight;
		}
		
		std::list<unsigned int>::const_iterator blockBreakIndex = dInfoStep1C.newLineBreaks.begin();
		SubComponents::Filter filter;
		filter.addFilterFuntion(isPhysical);
		
		for(const_iterator block=basicBlocks.begin(&filter); !block.isEnd(); ++block)
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
			Vector result = (*block)->getAvailableMaximization();
			Vector blockSize = getBlockSize(*block, Settings::Step::s1B_adjust);
			
			if(xIsPrimary == false)
			{
				result.swapValues();
				blockSize.swapValues();
			}
			
			sizeList.push_back(blockSize.x);
			maxListPrimary.push_back(result.x);
			blockSecondaryMax = result.y;
			
			if(blockSecondaryMax < 0 || secondaryMax < 0)
				secondaryMax = (secondaryMax < blockSecondaryMax) ? secondaryMax : blockSecondaryMax;
			else
				secondaryMax = (secondaryMax > blockSecondaryMax) ? secondaryMax : blockSecondaryMax;
		}
		
		if(sizeList.size() > 0)
		{
			sizeListSecondary.push_back(*sizeSecondaryIt);
			maxListSecondary.push_back(secondaryMax);
			addMaximizationToFinalList(spacing, availableSize, finalList, sizeList, maxListPrimary);
		}
	}
	
	
	void FlowContainer::addMaximizationToFinalList(int cellSpacing, int availableSize,
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
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




