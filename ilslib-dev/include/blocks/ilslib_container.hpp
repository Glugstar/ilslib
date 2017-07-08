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

#include "ilslib_basic_block.hpp"
#include "ilslib_container_style.hpp"
#include "ilslib_selector.hpp"
#include "settings/ilslib_container_settings.hpp"



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
		
		
		// typedefs
		typedef BlockCollection<BasicBlock> SubComponents;
		typedef SubComponents::iterator iterator;
		typedef SubComponents::const_iterator const_iterator;
		
		
		// constructors & destructor
		Container(const std::string& containerID);
		virtual ~Container();
		
		
		// functions
			// static filter functions
		static bool isPhysical(const BasicBlock* element);
		static bool isVisible(const BasicBlock* element);
		static bool isSuperPhysical(const BasicBlock* element);
		static bool isSuperVisible(const BasicBlock* element);
			// basic element functions
		virtual const ContainerSettings* getContainerSettings() const;
		virtual ContainerSettings* getContainerSettings();
		virtual const ContainerStyle* getStyle() const;
		virtual void setStyle(const ContainerStyle* newStyle);
		virtual const ContainerStyle::Selector& getStyleSelector() const;
		virtual ContainerStyle::Selector& getStyleSelector();
		virtual const ListenerOptimizer& getListenerOptimizer() const;
		virtual const SubComponents& getBasicBlocks() const = 0;
		virtual bool addBasicBlock(BasicBlock* block) = 0;
		virtual bool removeBasicBlock(const std::string& blockID) = 0;
		//virtual SubComponents& getBasicBlocks() = 0;
		virtual const BasicBlock* operator[] (const std::string& blockID) const;
		virtual BasicBlock* operator[] (const std::string& blockID);
			// event functions
		virtual bool parseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
			// step 0: clear previous data (strict order)
		virtual void step0A_clear();
		virtual void step0B_applyTransformations();
		virtual void step0C_optimizeListeners();
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize();
		virtual void step1B_adjust();
		virtual void step1C_maximize(const Vector& availableSize);
		virtual void step1D_reAdjust();
			// step 2: drawable map generation
		virtual void step2A_determinePositions();
		virtual void step2C_addToDrawableMap(DrawableMap* drawables);
	protected:
		// functions
		virtual bool parseSubComponentsEvent(const MouseEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue) = 0;
		virtual bool parseSubComponentsEvent(const KeyboardEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue) = 0;
		virtual bool parseSubComponentsEvent(const TimeEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue) = 0;
		virtual bool parseSubComponentsEvent(const WindowEvent& event, BlockManager* blockManager,
										EventQueue& eventQueue) = 0;
		
		
		// variables
		const ContainerStyle* style;
		ContainerStyle::Selector styleSelector;
		ListenerOptimizer listenerOptimizer;
		ListenerOptimizer subComponentsListenerOptimizer;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_CONTAINER_HPP




