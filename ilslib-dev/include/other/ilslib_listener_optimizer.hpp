/*----------------------------------------------------------------------------------
							ilslib_listener_optimizer.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_LISTENER_OPTIMIZER_HPP
#define ILSLIB_LISTENER_OPTIMIZER_HPP

#pragma once


#include "../listeners/ilslib_mouse_listener.hpp"
#include "../listeners/ilslib_keyboard_listener.hpp"
#include "../listeners/ilslib_time_listener.hpp"
#include "../listeners/ilslib_window_listener.hpp"
#include "../blocks/collections/ilslib_block_collection.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										ListenerOptimizer
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ListenerOptimizer
	{
	public:
		// constructors & destructor
		ListenerOptimizer();
		virtual ~ListenerOptimizer();
		
		
		// functions
		virtual const std::set<MouseButton::Button>& getButtonTriggers() const;
		virtual const std::set<std::string>& getKeyTriggers() const;
		virtual bool allButtonsTrigger() const;
		virtual bool allKeysTrigger() const;
			// update from listener list
		virtual void updateMouseOptimization(const std::list<MouseListener>& mouseListeners);
		virtual void updateKeyboardOptimization(const std::list<KeyboardListener>& keyboardListeners);
			// update from block collection
		virtual void updateMouseOptimization(const BlockCollection<BasicBlock>* blockCollection);
		virtual void updateKeyboardOptimization(const BlockCollection<BasicBlock>* blockCollection);
			// update from two other optimizers
		virtual void updateMouseOptimization(const ListenerOptimizer& optimizer1,
											const ListenerOptimizer& optimizer2);
		virtual void updateKeyboardOptimization(const ListenerOptimizer& optimizer1,
											const ListenerOptimizer& optimizer2);
	protected:
		// functions
		virtual void updateMouseOptimization(const ListenerOptimizer& optimizer);
		virtual void updateKeyboardOptimization(const ListenerOptimizer& optimizer);
		
		
		// variables
		std::set<MouseButton::Button> buttonTriggers;
		std::set<std::string> keyTriggers;
		bool allButtons;
		bool allKeys;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_LISTENER_OPTIMIZER_HPP





