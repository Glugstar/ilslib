/*----------------------------------------------------------------------------------
								ilslib_layer.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_LAYER_HPP
#define ILSLIB_LAYER_HPP

#pragma once

#include "ilslib_basic_block.hpp"
#include "settings/ilslib_container_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Layer
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Layer
	{
	public:
		// friends
		friend class BlockManager;
		friend class Alternative;
		
		
		// typedefs
		typedef BlockCollection<BasicBlock> BasicBlocks;
		typedef BlockCollection<BasicBlock>::iterator iterator;
		typedef BlockCollection<BasicBlock>::const_iterator const_iterator;
		
		
		// constructors & destructor
		Layer(const std::string& layerID);
		virtual ~Layer();
		
		
		// functions
			// basic element functions
		virtual const std::string& getID() const;
		virtual std::string getPath() const;
		virtual const Alternative* getParentAlternative() const;
		virtual Alternative* getParentAlternative();
		virtual void getBasicBlocks(std::list<BasicBlock*>& blockList);
		virtual BasicBlock* findBasicBlock(const std::string& blockID);
		virtual void addBasicBlock(BasicBlock* block);
		virtual void removeBasicBlock(const std::string& id);
		virtual void removeAllBasicBlocks();
		virtual const std::unordered_set<std::string>& getAllKeyCodes() const;
		virtual const DimensionsInfo* getDimensionsInfo(const Settings::Step step) const;
		virtual const PositionInfo* getPositionInfo() const;
		virtual void setLayerOffsetX(int offset);
		virtual void setLayerOffsetY(int offset);
		virtual int getLayerOffsetX() const;
		virtual int getLayerOffsetY() const;
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
		virtual void step1A_minimize(const ContainerSettings* currentSettings);
		virtual void step1B_adjust();
		virtual void step1C_maximize(const ContainerSettings* currentSettings,
									int availableWidth, int availableHeight);
		virtual void step1D_reAdjust();
			// step 2: drawable map generation
		virtual void step2A_determinePositions(const ContainerSettings* currentSettings);
		virtual void step2B_determineCutRectangles(const Rectangle& availableSpace);
		virtual void step2C_addToDrawableMap(DrawableMap* drawables);
	protected:
		// functions
		virtual PositionInfo* getPositionInfo();
		virtual Vector getAvailableMaximization(Settings::IterationMode mode) const;
		virtual void getMaximizationSpaceList(const ContainerSettings* currentSettings,
									std::list<int>& finalList,
									std::list<int>& maxListSecondary,
									std::list<int>& sizeListSecondary,
									int availableWidth, int availableHeight);
		virtual void addMaximizationToFinalList(int cellSpacing, int availableSize,
									std::list<int>& finalList,
									const std::list<int>& sizeList,
									const std::list<int>& maxList);
		static int findPrimaryLimit(const ContainerSettings* currentSettings, const Settings::Step step);
		static void updateRowColumnInfo(BasicBlocks& blocks, DimensionsMapper& dMapper,
									const int primaryRestriction, const Settings::Step step,
									const ContainerSettings* currentSettings);
		static int getDPData(const BasicBlock* block,
									const Settings::Step step,
									const bool xIsPrimary);
		static bool determineNewLine(const ContainerSettings* currentSettings, const bool tableMode,
									const int primaryCounter, const int blockCounter,
									const int totalPrimary, const int cellPrimary,
									const int limitPrimary, const bool limitEnabled);
		static void commitNewLine(DimensionsMapper& dMapper, const int blockCounter, const int cellSecondary,
									int& primaryCounter, int& secondaryCounter,
									int& primaryCurrentTotal, int& secondaryCurrentMax);
		static void commitLineMaxPrimary(DimensionsMapper& dMapper, const int primaryCounter,
									const int cellPrimary);
		static void calculateSubComponentTotals(DimensionsMapper& dMapper,
									const ContainerSettings* currentSettings);
		static void updateAbsolutePositions(BasicBlocks& basicBlocks, DimensionsMapper& dMapper,
									const ContainerSettings* currentSettings,
									const int absoluteReferencePrimary, const int absoluteReferenceSecondary,
									const int basePrimarySpacing, const int baseSecondarySpacing,
									const bool equalCellPrimary, const bool equalCellSecondary,
									const Settings::Flow primaryFlow, const Settings::Flow secondaryFlow,
									const Settings::Alignment primaryAlignment,
									const Settings::Alignment secondaryAlignment);
		
		
		// variables
		std::string id;
		Alternative* parentAlternative;
		BasicBlocks basicBlocks;
		std::unordered_set<std::string> allKeyCodes;
		DimensionsInfo dInfoStep1A;
		DimensionsInfo dInfoStep1B;
		DimensionsInfo dInfoStep1C;
		DimensionsInfo dInfoStep1D;
		PositionInfo pInfo;
		int layerOffsetX;
		int layerOffsetY;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_LAYER_HPP




