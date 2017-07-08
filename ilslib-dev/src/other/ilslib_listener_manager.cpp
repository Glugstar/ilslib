#include "../../include/other/ilslib_listener_manager.hpp"
#include "../../include/other/ilslib_event_queue.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ListenerManager::ListenerManager():
		mouseListeners(),
		keyboardListeners(),
		timeListeners(),
		windowListeners(),
		listenerOptimizer(),
		mouseHovering(false)
	{
	}
	
	
	ListenerManager::~ListenerManager()
	{
	}
	
	
	const Listener* ListenerManager::getListener(const std::string& listenerID) const
	{
		std::list<MouseListener>::const_iterator mouseIT, mouseEnd;
		mouseIT = mouseListeners.begin();
		mouseEnd = mouseListeners.end();
		for(; mouseIT!=mouseEnd; ++mouseIT)
			if(mouseIT->getID() == listenerID)
				return &(*mouseIT);
		
		std::list<KeyboardListener>::const_iterator keyIT, keyEnd;
		keyIT = keyboardListeners.begin();
		keyEnd = keyboardListeners.end();
		for(; keyIT!=keyEnd; ++keyIT)
			if(keyIT->getID() == listenerID)
				return &(*keyIT);
		
		std::list<TimeListener>::const_iterator timeIT, timeEnd;
		timeIT = timeListeners.begin();
		timeEnd = timeListeners.end();
		for(; timeIT!=timeEnd; ++timeIT)
			if(timeIT->getID() == listenerID)
				return &(*timeIT);
		
		std::list<WindowListener>::const_iterator winIT, winEnd;
		winIT = windowListeners.begin();
		winEnd = windowListeners.end();
		for(; winIT!=winEnd; ++winIT)
			if(winIT->getID() == listenerID)
				return &(*winIT);
		
		return nullptr;
	}
	
	
	Listener* ListenerManager::getListener(const std::string& listenerID)
	{
		const ListenerManager* listenerManager = const_cast<const ListenerManager*>(this);
		const Listener* listener = listenerManager->getListener(listenerID);
		
		if(listener != nullptr)
			return const_cast<Listener*>(listener);
		
		return nullptr;
	}
	
	
	const ListenerOptimizer& ListenerManager::getListenerOptimizer() const
	{
		return listenerOptimizer;
	}
	
	
	void ListenerManager::updateOptimizationData()
	{
		listenerOptimizer.updateMouseOptimization(mouseListeners);
		listenerOptimizer.updateKeyboardOptimization(keyboardListeners);
	}
	
	
	void ListenerManager::addListener(const MouseListener& listener)
	{
		mouseListeners.push_back(listener);
	}
	
	
	void ListenerManager::addListener(const KeyboardListener& listener)
	{
		keyboardListeners.push_back(listener);
	}
	
	
	void ListenerManager::addListener(const TimeListener& listener)
	{
		timeListeners.push_back(listener);
	}
	
	
	void ListenerManager::addListener(const WindowListener& listener)
	{
		windowListeners.push_back(listener);
	}
	
	
	bool ListenerManager::parseEvent(const std::string& basicBlockPath,
								bool interiorMovement, const MouseEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue)
	{
		MouseEvent::Type type = event.getType();
		bool triggersOnButtonAction = event.triggersOnButtonAction();
		
		MouseButton::Button button;
		if(triggersOnButtonAction == true)
			button = event.getButton();
		
		const std::set<MouseButton::Button>& buttonTriggers = listenerOptimizer.getButtonTriggers();
		if(listenerOptimizer.allButtonsTrigger() == false && triggersOnButtonAction == true)
			if(buttonTriggers.find(button) == buttonTriggers.end())
				return false;
		
		bool parseFlag = false;
		
		std::list<MouseListener>::iterator i, end;
		i = mouseListeners.begin();
		end = mouseListeners.end();
		for(; i!=end; ++i)
		{
			if(i->isActive() == false)
				continue;
			
			if(i->getTypeTrigger() != type)
				continue;
			
			if(i->triggersOnButtonAction() == false)
				if(i->triggersOn(button, type) == false)
					continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			MouseEvent* newEvent = new MouseEvent(event);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, basicBlockPath);
		}
		
		if(type == MouseEvent::Type::Hover)
		{
			if(parseMouseHoverInOut(basicBlockPath, interiorMovement, event,
									blockManager, eventQueue) == true)
			{
				parseFlag = true;
			}
		}
		
		return parseFlag;
	}
	
	
	bool ListenerManager::parseEvent(const std::string& basicBlockPath, const KeyboardEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue)
	{
		KeyboardEvent::Type type = event.getType();
		bool triggersOnKeyAction = event.triggersOnKeyAction();
		
		std::string keyCode;
		if(triggersOnKeyAction == true)
			keyCode = event.getKeyCode();
		
		const std::set<std::string>& keyTriggers = listenerOptimizer.getKeyTriggers();
		if(listenerOptimizer.allKeysTrigger() == false && triggersOnKeyAction == true)
			if(keyTriggers.find(keyCode) == keyTriggers.end())
				return false;
		
		bool parseFlag = false;
		
		std::list<KeyboardListener>::iterator i, end;
		i = keyboardListeners.begin();
		end = keyboardListeners.end();
		for(; i!=end; ++i)
		{
			if(i->isActive() == false)
				continue;
			
			if(i->getTypeTrigger() != type)
				continue;
			
			if(i->triggersOnKeyAction() == false)
				if(i->triggersOn(keyCode) == false)
					continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			KeyboardEvent* newEvent = new KeyboardEvent(event);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, basicBlockPath);
		}
		
		return parseFlag;
	}
	
	
	bool ListenerManager::parseEvent(const std::string& basicBlockPath, const TimeEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		std::list<TimeListener>::iterator i, end;
		i = timeListeners.begin();
		end = timeListeners.end();
		for(; i!=end; ++i)
		{
			if(i->isActive() == false)
				continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			TimeEvent* newEvent = new TimeEvent(event);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, basicBlockPath);
		}
		
		return parseFlag;
	}
	
	
	bool ListenerManager::parseEvent(const std::string& basicBlockPath, const WindowEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue)
	{
		WindowEvent::Type type = event.getType();
		
		bool parseFlag = false;
		
		std::list<WindowListener>::iterator i, end;
		i = windowListeners.begin();
		end = windowListeners.end();
		for(; i!=end; ++i)
		{
			if(i->isActive() == false)
				continue;
			
			if(i->getTypeTrigger() != type)
				continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			WindowEvent* newEvent = new WindowEvent(event);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, basicBlockPath);
		}
		
		return parseFlag;
	}
	
	
	bool ListenerManager::parseMouseHoverInOut(const std::string& basicBlockPath,
								bool interiorMovement, const MouseEvent& event,
								BlockManager* blockManager, EventQueue& eventQueue)
	{
		if(interiorMovement == mouseHovering)
			return false;
		
		MouseEvent::Type type;
		if(interiorMovement == true)
			type = MouseEvent::Type::HoverIn;
		else
			type = MouseEvent::Type::HoverOut;
		
		bool parseFlag = false;
		
		std::list<MouseListener>::iterator i, end;
		i = mouseListeners.begin();
		end = mouseListeners.end();
		for(; i!=end; ++i)
		{
			if(i->isActive() == false)
				continue;
			
			if(i->getTypeTrigger() != type)
				continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			MouseEvent* newEvent = new MouseEvent(event);
			newEvent->setType(type);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, basicBlockPath);
		}
		
		mouseHovering = interiorMovement;
		
		return parseFlag;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





