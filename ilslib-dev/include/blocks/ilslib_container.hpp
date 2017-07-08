/*----------------------------------------------------------------------------------
							ilslib_container.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_CONTAINER_HPP
#define ILSLIB_CONTAINER_HPP

#pragma once

#include "ilslib_transition.hpp"
#include "ilslib_container_style.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										Container
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Container : public BasicBlock
	{
	public:
		// friends
		friend class BlockManager;
		
		
		// constructors & destructor
		Container(const std::string& containerID,
					const std::string& alternativeID = "default",
					const std::string& layerID = "default");
		virtual ~Container();
		
		
		// functions
			// basic element functions
		virtual void setStyle(const ContainerStyle* newStyle);
		virtual const ContainerStyle* getStyle();
		virtual unsigned int getModelIndex1() const;
		virtual unsigned int getModelIndex2() const;
		virtual float getModelIndexRatio() const;
		virtual void setModelIndex1(unsigned int index1);
		virtual void setModelIndex2(unsigned int index2);
		virtual void setModelIndexRatio(float ratio);
		virtual void getBasicBlocks(std::list<BasicBlock*>& blockList);
		virtual Vector getAvailableMaximization(Settings::IterationMode mode) const;
		virtual void addAlternative(Alternative* alt);
		virtual BasicBlock* findBasicBlock(const std::string& blockID);
		virtual Layer* findLayer(const std::string& layerID);
		virtual Alternative* findAlternative(const std::string& alternativeID);
		virtual ContainerSettings* getContainerSettings();
		virtual const ContainerSettings* getContainerSettings() const;
		virtual const DimensionsInfo* getDimensionsInfo(const Settings::Step step) const;
		virtual const PositionInfo* getPositionInfo() const;
		virtual int getScrollX() const;
		virtual int getScrollY() const;
			// events
		virtual bool parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
			// step 0: clear previous data (strict order)
		virtual void step0A_clear();
		virtual void step0B_applyTransformations();
		virtual void step0C_findAllKeyCodes();
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize();
		virtual void step1B_adjust();
		virtual void step1C_maximize(int availableWidth, int availableHeight);
		virtual void step1D_reAdjust();
			// step 2: drawable map generation
		virtual void step2A_determinePositions();
		virtual void step2B_determineCutRectangles(const Rectangle& availableSpace);
		virtual void step2C_addToDrawableMap(DrawableMap* drawables);
	protected:
		// functions
		virtual unsigned int getBGIndex(unsigned int actualIndex) const;
		virtual unsigned int getBorderIndex(unsigned int actualIndex) const;
		virtual PositionInfo* getPositionInfo();
		virtual void createNewContainerSettings();
		virtual void createAlternative(const std::string& alternativeID, const std::string& layerID);
		virtual void updateDInfo(const Settings::Step step);
		
		
		// variables
		std::list<Alternative*> alternatives;
		Transition transition;
		const ContainerStyle* style;
		unsigned int modelIndex1;
		unsigned int modelIndex2;
		float modelIndexRatio;
		DimensionsInfo dInfoStep1A;
		DimensionsInfo dInfoStep1B;
		DimensionsInfo dInfoStep1C;
		DimensionsInfo dInfoStep1D;
		PositionInfo pInfo;
		int scrollX;
		int scrollY;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_CONTAINER_HPP




