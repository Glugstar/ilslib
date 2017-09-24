#include "../../include/blocks/ilslib_flow_container.hpp"



/*  ----------------------------------------------------------------------------------
										ILSLib
    ----------------------------------------------------------------------------------*/
namespace ILSLib
{



	void FlowContainer::step2A_determinePositions()
	{
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
		
		FlowContainerSettings* currentSettings = getFlowContainerSettings();
		
		bool xIsPrimary = currentSettings->xIsPrimary();
		
		//Settings::Step dataStep = Settings::Step::s1D_reAdjust;
		const DimensionsInfo& dInfo = getDimensionsInfo();
		DimensionsMapper dMapper(&dInfoStep1D, xIsPrimary);
		
		absRefX = determineAbsoluteRefX(currentSettings, dInfo, getPositionInfo().posRectangle.x);
		absRefY = determineAbsoluteRefY(currentSettings, dInfo, getPositionInfo().posRectangle.y);
		
		
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
	
	
	int FlowContainer::determineAbsoluteRefX(const FlowContainerSettings* currentSettings,
	        const DimensionsInfo& dInfo, int posInfoX)
	{
		int containerInnerWidth = 0;
		int centerDisplacementX = 0;
		int subComponentsWidth = 0;
		
		subComponentsWidth = dInfo.subComponentsTotalWidth;
		//containerInnerWidth = getParentAlternative()->getDimensionsInfo(dataStep)->totalWidth;
		containerInnerWidth = dInfo.totalWidth;
		containerInnerWidth -= currentSettings->getSpacingHorizontal();
		
		if(containerInnerWidth > subComponentsWidth)
			centerDisplacementX = (containerInnerWidth - subComponentsWidth) / 2;
			
		int absRefX = posInfoX + currentSettings->getSpacingLeft();
		
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
		
		return absRefX;
	}
	
	
	int FlowContainer::determineAbsoluteRefY(const FlowContainerSettings* currentSettings,
	        const DimensionsInfo& dInfo, int posInfoY)
	{
		int containerInnerHeight = 0;
		int centerDisplacementY = 0;
		int subComponentsHeight = 0;
		
		subComponentsHeight = dInfo.subComponentsTotalHeight;
		//containerInnerHeight = getParentAlternative()->getDimensionsInfo(dataStep)->totalHeight;
		containerInnerHeight = dInfo.totalHeight;
		containerInnerHeight -= currentSettings->getSpacingVertical();
		
		if(containerInnerHeight > subComponentsHeight)
			centerDisplacementY = (containerInnerHeight - subComponentsHeight) / 2;
			
		int absRefY = posInfoY + currentSettings->getSpacingTop();
		
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
		
		return absRefY;
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
		bool xIsPrimary = currentSettings->xIsPrimary();
		
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
			if(xIsPrimary == false)
				blockSize.swapValues();
				
			int primarySize;
			if(equalCellPrimary == true)
				primarySize = *dMapper.subComponentsMaxPrimary;
			else
				primarySize = blockSize.x;
				
			int secondarySize;
			if(equalCellSecondary == true)
				secondarySize = *dMapper.subComponentsMaxSecondary;
			else
				secondarySize = blockSize.y;
				
				
			PositionInfo* blockPInfo = &(*block)->pInfo;
			PositionMapper pMapper(blockPInfo, xIsPrimary);
			
			*pMapper.coordPrimary = determinePrimaryCoord(dMapper, xIsPrimary,
                                            secondaryIndex, posPrimary, primarySize,
                                            absoluteReferencePrimary, primaryFlow, primaryAlignment);
			*pMapper.coordSecondary = determineSecondaryCoord(dMapper, xIsPrimary,
                                            secondaryIndex, posSecondary, secondarySize, blockSize.y,
                                            absoluteReferenceSecondary, secondaryFlow, secondaryAlignment);
			
			(*block)->step2A_determinePositions();
			
			primarySpacing = basePrimarySpacing;
			secondarySpacing = baseSecondarySpacing;
			
			/*
			    if(xIsPrimary == true)
			    {
			    primarySpacing = basePrimarySpacing + ???; // add to spacing if elements are spread out
			    secondarySpacing = baseSecondarySpacing + ???; // add to spacing if elements are spread out
			    }
			    else
			    {
			    primarySpacing = basePrimarySpacing + ???; // add to spacing if elements are spread out
			    secondarySpacing = baseSecondarySpacing + ???; // add to spacing if elements are spread out
			    }
			*/
			
			posPrimary += primarySize;
			posPrimary += primarySpacing;
		}
	}
	
	
	int FlowContainer::determinePrimaryCoord(DimensionsMapper& dMapper, bool xIsPrimary,
            int secondaryIndex, int posPrimary, int primarySize,
	        const int absoluteReferencePrimary,
	        const Settings::Flow primaryFlow,
	        const Settings::Alignment primaryAlignment)
	{
		int coordPrimary = absoluteReferencePrimary;
		int primaryAlignOffset = 0;
		bool primaryFlowFlag = false;
		bool primaryAlignmentFlag = false;
		
		primaryAlignOffset = *dMapper.subComponentsTotalPrimary;
		primaryAlignOffset -= (*dMapper.lineTotalPrimary)[secondaryIndex];
		
		if(xIsPrimary == true)
			primaryFlowFlag = (primaryFlow == Settings::Flow::LeftToRightFlow);
		else
			primaryFlowFlag = (primaryFlow == Settings::Flow::TopToBottomFlow);
			
		if(primaryFlowFlag == true)
		{
			if(xIsPrimary == true)
				primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::RightAlignment);
			else
				primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::BottomAlignment);
				
			coordPrimary += posPrimary;
			if(primaryAlignmentFlag == true)
				coordPrimary += primaryAlignOffset;
			else if(primaryAlignment == Settings::Alignment::CenterAlignment)
				coordPrimary += primaryAlignOffset / 2;
		}
		else
		{
			if(xIsPrimary == true)
				primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::LeftAlignment);
			else
				primaryAlignmentFlag = (primaryAlignment == Settings::Alignment::TopAlignment);
				
			coordPrimary -= posPrimary;
			coordPrimary -= primarySize;
			if(primaryAlignmentFlag == true)
				coordPrimary -= primaryAlignOffset;
			else if(primaryAlignment == Settings::Alignment::CenterAlignment)
				coordPrimary -= primaryAlignOffset / 2;
		}
		
		return coordPrimary;
	}
	
	
	int FlowContainer::determineSecondaryCoord(DimensionsMapper& dMapper, bool xIsPrimary,
            int secondaryIndex, int posSecondary, int secondarySize, int blockSizeY,
	        const int absoluteReferenceSecondary,
	        const Settings::Flow secondaryFlow,
	        const Settings::Alignment secondaryAlignment)
	{
		int coordSecondary = absoluteReferenceSecondary;
		int secondaryAlignOffset = 0;
		bool secondaryFlowFlag = false;
		bool secondaryAlignmentFlag = false;
		
		secondaryAlignOffset = (*dMapper.lineMaxSecondary)[secondaryIndex];
		secondaryAlignOffset -= blockSizeY;
		
		if(xIsPrimary == false)
			secondaryFlowFlag = (secondaryFlow == Settings::Flow::LeftToRightFlow);
		else
			secondaryFlowFlag = (secondaryFlow == Settings::Flow::TopToBottomFlow);
			
		if(secondaryFlowFlag == true)
		{
			if(xIsPrimary == false)
				secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::RightAlignment);
			else
				secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::BottomAlignment);
				
			coordSecondary += posSecondary;
			if(secondaryAlignmentFlag == true)
				coordSecondary += secondaryAlignOffset;
			else if(secondaryAlignment == Settings::Alignment::CenterAlignment)
				coordSecondary += secondaryAlignOffset / 2;
		}
		else
		{
			if(xIsPrimary == false)
				secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::LeftAlignment);
			else
				secondaryAlignmentFlag = (secondaryAlignment == Settings::Alignment::TopAlignment);
				
			coordSecondary -= posSecondary;
			coordSecondary -= secondarySize;
			if(secondaryAlignmentFlag == true)
				coordSecondary -= secondaryAlignOffset;
			else if(secondaryAlignment == Settings::Alignment::CenterAlignment)
				coordSecondary -= secondaryAlignOffset / 2;
		}
		
		return coordSecondary;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




