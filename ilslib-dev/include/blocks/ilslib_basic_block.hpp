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
#include "../listeners/ilslib_mouse_listener.hpp"
#include "../listeners/ilslib_keyboard_listener.hpp"
#include "../listeners/ilslib_time_listener.hpp"
#include "../listeners/ilslib_window_listener.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
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
		friend class Layer;
		
		
		// constructors & destructor
		BasicBlock(const std::string& uniqueID);
		virtual ~BasicBlock();
		
		
		// functions
			// basic element functions
		virtual const std::string& getID() const;
		virtual std::string getPath() const;
		virtual bool occupiesSpace(bool tableMode) const;
		virtual Rectangle getDisplayArea() const;
		virtual Settings::Visibility getVisibility() const;
		virtual const Layer* getParentLayer() const;
		virtual Layer* getParentLayer();
		virtual const Settings* getBaseSettings() const;
		virtual Settings* getBaseSettings();
		virtual Vector getAvailableMaximization(Settings::IterationMode mode) const;
		virtual const std::unordered_set<std::string>& getAllKeyCodes() const;
		virtual const DimensionsInfo* getDimensionsInfo(const Settings::Step step) const = 0;
		virtual const PositionInfo* getPositionInfo() const = 0;
			// events
		virtual Listener* getListener(const std::string& listenerID);
		virtual void addMouseListener(const MouseListener& listener);
		virtual void addKeyboardListener(const KeyboardListener& listener);
		virtual void addTimeListener(const TimeListener& listener);
		virtual void addWindowListener(const WindowListener& listener);
		virtual bool parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
			// step 0: clear previous data (strict order)
		virtual void step0A_clear();
		virtual void step0B_applyTransformations() = 0;
		virtual void step0C_findAllKeyCodes();
			// step 1: dimensions and position computations (strict order)
		virtual void step1A_minimize() = 0;
		virtual void step1B_adjust() = 0;
		virtual void step1C_maximize(int availableWidth, int availableHeight) = 0;
		virtual void step1D_reAdjust() = 0;
			// step 2: drawable map generation
		virtual void step2A_determinePositions() = 0;
		virtual void step2B_determineCutRectangles(const Rectangle& availableSpace);
		virtual void step2C_addToDrawableMap(DrawableMap* drawables) = 0;
	protected:
		// functions
		virtual PositionInfo* getPositionInfo() = 0;
		virtual bool parseMouseHoverInOut(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue);
		
		
		// variables
		std::string id;
		Layer* parentLayer;
		Settings* settings;
		bool mouseHovering;
		std::unordered_set<std::string> allKeyCodes;
		std::list<MouseListener> mouseListeners;
		std::list<KeyboardListener> keyboardListeners;
		std::list<TimeListener> timeListeners;
		std::list<WindowListener> windowListeners;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_BASIC_BLOCK_HPP




