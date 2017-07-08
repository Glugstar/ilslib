/*----------------------------------------------------------------------------------
							ilslib_listener_manager.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIB_LISTENER_MANAGER_HPP
#define ILSLIB_LISTENER_MANAGER_HPP

#pragma once


#include "ilslib_listener_optimizer.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	/*!---------------------------------------------------------------------------------
										ListenerManager
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class ListenerManager
	{
	public:
		// constructors & destructor
		ListenerManager();
		virtual ~ListenerManager();
		
		
		// functions
			// search functions
		virtual const Listener* getListener(const std::string& listenerID) const;
		virtual Listener* getListener(const std::string& listenerID);
			// optimization functions
		virtual const ListenerOptimizer& getListenerOptimizer() const;
		virtual void updateOptimizationData();
			// add functions
		virtual void addListener(const MouseListener& listener);
		virtual void addListener(const KeyboardListener& listener);
		virtual void addListener(const TimeListener& listener);
		virtual void addListener(const WindowListener& listener);
			// parse functions
		virtual bool parseEvent(const std::string& basicBlockPath,
								bool interiorMovement, const MouseEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const std::string& basicBlockPath, const KeyboardEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const std::string& basicBlockPath, const TimeEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue);
		virtual bool parseEvent(const std::string& basicBlockPath, const WindowEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue);
	protected:
		// functions
		virtual bool parseMouseHoverInOut(const std::string& basicBlockPath,
								bool interiorMovement, const MouseEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue);
		
		
		// variables
		std::list<MouseListener> mouseListeners;
		std::list<KeyboardListener> keyboardListeners;
		std::list<TimeListener> timeListeners;
		std::list<WindowListener> windowListeners;
		ListenerOptimizer listenerOptimizer;
		bool mouseHovering;
	};
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------



#endif // ILSLIB_LISTENER_MANAGER_HPP





