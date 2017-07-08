/*----------------------------------------------------------------------------------
								ilslib_basic_block.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_BASIC_BLOCK_HPP
#define ILSLIB_BASIC_BLOCK_HPP

#pragma once


#include "collections/ilslib_block_collection.hpp"

#include "settings/ilslib_settings.hpp"
#include "dpinfo/ilslib_dimensions_mapper.hpp"
#include "dpinfo/ilslib_position_mapper.hpp"
#include "../other/ilslib_drawable_map.hpp"
#include "../other/ilslib_listener_manager.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	// forward declaration of class
	class Container;
	
	
	
	/*!---------------------------------------------------------------------------------
										BasicBlock
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class BasicBlock
	{
	public:
		// friends
		friend class BlockManager;
		friend class FlowContainer;
		
		
		// constructors & destructor
		BasicBlock(const std::string& uniqueID);
		virtual ~BasicBlock();
		
		
		// functions
			// identity functions
		virtual const std::string& getID() const;
		virtual std::string getPath() const;
		virtual const Container* getParent() const;
		virtual const Settings* getSettings() const;
		virtual Settings* getSettings();
			// spacing & visibility functions
		virtual const DimensionsInfo& getDimensionsInfo(const Settings::Step step =
														Settings::Step::s1D_reAdjust) const;
		virtual const PositionInfo& getPositionInfo() const;
		virtual Vector getAvailableMaximization() const;
		virtual Rectangle getDisplayArea() const;
		virtual Settings::Visibility getVisibility() const;
		virtual bool occupiesSpace(bool tableMode) const;
			// listener and event functions
		virtual const ListenerManager& getListenerManager() const;
		virtual ListenerManager& getListenerManager();
		virtual const ListenerOptimizer& getListenerOptimizer() const;
		virtual bool parseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
			// step 0: clear previous data (strict order)
		virtual void step0A_clear();
		virtual void step0B_applyTransformations();
		virtual void step0C_optimizeListeners();
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize() = 0;
		virtual void step1B_adjust() = 0;
		virtual void step1C_maximize(const Vector& availableSize) = 0;
		virtual void step1D_reAdjust() = 0;
			// step 2: drawable map generation
		virtual void step2A_determinePositions();
		virtual void step2B_determineCutRectangles(const Rectangle& availableSpace);
		virtual void step2C_addToDrawableMap(DrawableMap* drawables) = 0;
	protected:
		// variables
		std::string id;
		const Container* parent;
		Settings* settings;
		ListenerManager listenerManager;
		DimensionsInfo dInfoStep1A;
		DimensionsInfo dInfoStep1B;
		DimensionsInfo dInfoStep1C;
		DimensionsInfo dInfoStep1D;
		PositionInfo pInfo;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_BASIC_BLOCK_HPP




