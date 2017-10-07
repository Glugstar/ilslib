/*----------------------------------------------------------------------------------
							ilslib_flow_container.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_FLOW_CONTAINER_HPP
#define ILSLIB_FLOW_CONTAINER_HPP

#pragma once

#include "ilslib_container.hpp"
#include "settings/ilslib_flow_container_settings.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{


    // extra functions
    int findPrimaryLimit(const FlowContainerSettings* currentSettings);
    void updateRowColumnInfo(Container::SubComponents& blocks, DimensionsMapper& dMapper,
                                    const int primaryRestriction, const Settings::Step step,
                                    const FlowContainerSettings* currentSettings);
    Vector getBlockSize(const BasicBlock* block, const Settings::Step step);
    
    
	/*!---------------------------------------------------------------------------------
										FlowContainer
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class FlowContainer : public Container
	{
	public:
		// constructors & destructor
		FlowContainer(const std::string& containerID);
		virtual ~FlowContainer();


		// functions
			// basic element functions
		virtual const FlowContainerSettings* getFlowContainerSettings() const;
		virtual FlowContainerSettings* getFlowContainerSettings();
		virtual const SubComponents& getBasicBlocks() const;
		virtual SubComponents& getBasicBlocks();
		virtual bool addBasicBlock(BasicBlock* block);
		virtual bool removeBasicBlock(const std::string& blockID);
			// spacing & visibility functions
		virtual Vector getAvailableMaximization() const;
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize();
		virtual void step1C_maximize(const Vector& availableSize);
			// step 2: drawable map generation
		virtual void step2A_determinePositions();
		virtual void step2B_determineCutRectangles(const Rectangle& availableSpace);
	protected:
		// functions
		virtual bool parseSubComponentsEvent(const MouseEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue);
		virtual bool parseSubComponentsEvent(const KeyboardEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue);
		virtual bool parseSubComponentsEvent(const TimeEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue);
		virtual bool parseSubComponentsEvent(const WindowEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue);
        virtual void getMaximizationSpaceList(const FlowContainerSettings* currentSettings,
                                        std::list<int>& finalList,
                                        std::list<int>& maxListSecondary,
                                        std::list<int>& sizeListSecondary,
                                        int availableWidth, int availableHeight);
        virtual void addMaximizationToFinalList(int cellSpacing, int availableSize,
                                        std::list<int>& finalList,
                                        const std::list<int>& sizeList,
                                        const std::list<int>& maxList);
        static void updateAbsolutePositions(Container::SubComponents& basicBlocks, DimensionsMapper& dMapper,
                                     const FlowContainerSettings* currentSettings,
                                     const int absoluteReferencePrimary, const int absoluteReferenceSecondary,
                                     const int basePrimarySpacing, const int baseSecondarySpacing,
                                     const bool equalCellPrimary, const bool equalCellSecondary,
                                     const Settings::Flow primaryFlow, const Settings::Flow secondaryFlow,
                                     const Settings::Alignment primaryAlignment,
                                     const Settings::Alignment secondaryAlignment);


		// variables
		SubComponents basicBlocks;
	};



} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_FLOW_CONTAINER_HPP




