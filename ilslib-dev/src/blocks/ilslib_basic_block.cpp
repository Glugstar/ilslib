#include "../../include/blocks/ilslib_basic_block.hpp"
#include "../../include/blocks/ilslib_layer.hpp"
#include "../../include/other/ilslib_event_queue.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	BasicBlock::BasicBlock(const std::string& uniqueID):
		id(uniqueID),
		parentLayer(nullptr),
		settings(nullptr),
		mouseHovering(false),
		allKeyCodes(),
		mouseListeners(),
		keyboardListeners(),
		timeListeners(),
		windowListeners()
	{
	}
	
	
	BasicBlock::~BasicBlock()
	{
		delete settings;
	}
	
	
	const std::string& BasicBlock::getID() const
	{
		return id;
	}
	
	
	std::string BasicBlock::getPath() const
	{
		if(parentLayer != nullptr)
			return parentLayer->getPath() + "/" + id;
		else
			return id;
	}
	
	
	bool BasicBlock::occupiesSpace(bool tableMode) const
	{
		if(settings->visibility == Settings::Visibility::IgnoreBlock)
			return false;
		if(settings->visibility == Settings::Visibility::Collapse &&
			tableMode == false)
			return false;
		
		return true;
	}
	
	
	Rectangle BasicBlock::getDisplayArea() const
	{
		return getPositionInfo()->posRectangle;
	}
	
	
	Settings::Visibility BasicBlock::getVisibility() const
	{
		return settings->visibility;
	}
	
	
	const Layer* BasicBlock::getParentLayer() const
	{
		return parentLayer;
	}
	
	
	Layer* BasicBlock::getParentLayer()
	{
		return parentLayer;
	}
	
	
	const Settings* BasicBlock::getBaseSettings() const
	{
		return settings;
	}
	
	
	Settings* BasicBlock::getBaseSettings()
	{
		return settings;
	}
	
	
	const std::unordered_set<std::string>& BasicBlock::getAllKeyCodes() const
	{
		return allKeyCodes;
	}
	
	
	Listener* BasicBlock::getListener(const std::string& listenerID)
	{
		std::list<MouseListener>::iterator mouseIT, mouseEnd;
		mouseIT = mouseListeners.begin();
		mouseEnd = mouseListeners.end();
		for(; mouseIT!=mouseEnd; ++mouseIT)
			if(mouseIT->getID() == listenerID)
				return &(*mouseIT);
		
		std::list<KeyboardListener>::iterator keyIT, keyEnd;
		keyIT = keyboardListeners.begin();
		keyEnd = keyboardListeners.end();
		for(; keyIT!=keyEnd; ++keyIT)
			if(keyIT->getID() == listenerID)
				return &(*keyIT);
		
		std::list<TimeListener>::iterator timeIT, timeEnd;
		timeIT = timeListeners.begin();
		timeEnd = timeListeners.end();
		for(; timeIT!=timeEnd; ++timeIT)
			if(timeIT->getID() == listenerID)
				return &(*timeIT);
		
		std::list<WindowListener>::iterator winIT, winEnd;
		winIT = windowListeners.begin();
		winEnd = windowListeners.end();
		for(; winIT!=winEnd; ++winIT)
			if(winIT->getID() == listenerID)
				return &(*winIT);
		
		return nullptr;
	}
	
	
	void BasicBlock::addMouseListener(const MouseListener& listener)
	{
		mouseListeners.push_back(listener);
	}
	
	
	void BasicBlock::addKeyboardListener(const KeyboardListener& listener)
	{
		keyboardListeners.push_back(listener);
	}
	
	
	void BasicBlock::addTimeListener(const TimeListener& listener)
	{
		timeListeners.push_back(listener);
	}
	
	
	void BasicBlock::addWindowListener(const WindowListener& listener)
	{
		windowListeners.push_back(listener);
	}
	
	
	bool BasicBlock::parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		if(event.eventApplies(*getPositionInfo(), settings) == false)
		{
			return false;
		}
		
		MouseEvent::Type type = event.getType();
		MouseButton::Button button = event.getButton();
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
			
			if(i->triggersOn(button, type) == false)
				continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			MouseEvent* newEvent = new MouseEvent(event);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, getPath());
		}
		
		if(type == MouseEvent::Type::Hover)
		{
			if(parseMouseHoverInOut(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool BasicBlock::parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		KeyboardEvent::Type type = event.getType();
		std::string keyCode = event.getKeyCode();
		
		if(type == KeyboardEvent::Type::Press || type == KeyboardEvent::Type::Release)
			if(allKeyCodes.find(event.getKeyCode()) == allKeyCodes.end())
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
			
			if(i->triggersOn(keyCode) == false)
				continue;
			
			if(i->getCallbackFunction() == nullptr)
				continue;
			
			parseFlag = true;
			KeyboardEvent* newEvent = new KeyboardEvent(event);
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, getPath());
		}
		
		return parseFlag;
	}
	
	
	bool BasicBlock::parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
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
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, getPath());
		}
		
		return parseFlag;
	}
	
	
	bool BasicBlock::parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
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
			eventQueue.pushEventBack(i->getID(), newEvent, blockManager, getPath());
		}
		
		return parseFlag;
	}
	
	
	void BasicBlock::step0A_clear()
	{
	}
	
	
	void BasicBlock::step0C_findAllKeyCodes()
	{
		allKeyCodes.clear();
		
		std::list<KeyboardListener>::const_iterator keyIt;
		
		for(keyIt=keyboardListeners.begin(); keyIt!=keyboardListeners.end(); ++keyIt)
		{
			if(keyIt->isActive() == false)
				continue;
			
			if(keyIt->getCallbackFunction() == nullptr)
				continue;
			
			std::list<std::string>::const_iterator i;
			const std::list<std::string> keyCodesTrigger = keyIt->getKeyCodesTrigger();
			for(i=keyCodesTrigger.begin(); i!=keyCodesTrigger.end(); ++i)
			{
				if(allKeyCodes.find(*i) == allKeyCodes.end())
					allKeyCodes.insert(*i);
			}
		}
	}
	
	
	void BasicBlock::step2B_determineCutRectangles(const Rectangle& availableSpace)
	{
		PositionInfo* pInfo = getPositionInfo();
		
		pInfo->cutRectangle = availableSpace;
		pInfo->intersectionRectangle = pInfo->posRectangle.intersect(pInfo->cutRectangle);
	}
	
	
	Vector BasicBlock::getAvailableMaximization(Settings::IterationMode mode) const
	{
		(void)mode;
		
		int limitX, limitY;
		limitX = settings->getMaxAppliedInnerWidth();
		limitY = settings->getMaxAppliedInnerHeight();
		
		int remainingX, remainingY;
		remainingX = remainingY = 0;
		
		const DimensionsInfo* dInfo = getDimensionsInfo(Settings::Step::s1B_adjust);
		
		if(settings->horizontalSizePolicy != Settings::SizePolicy::Minimize)
		{
			if(limitX == 0)
				remainingX = -1;
			if(limitX > dInfo->totalWidth)
				remainingX = limitX - dInfo->totalWidth;
		}
		if(settings->verticalSizePolicy != Settings::SizePolicy::Minimize)
		{
			if(limitY == 0)
				remainingY = -1;
			if(limitY > dInfo->totalHeight)
				remainingY = limitY - dInfo->totalHeight;
		}
		
		return Vector(remainingX, remainingY);
	}
	
	
	bool BasicBlock::parseMouseHoverInOut(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool interior = event.eventInsideCutRectangle(*getPositionInfo(), settings);
		if(interior == mouseHovering)
			return false;
		
		MouseEvent::Type type;
		if(interior == true)
			type = MouseEvent::Type::HoverIn;
		else
			type = MouseEvent::Type::HoverOut;
		
		bool parseFlag = false;
		
		std::list<MouseListener>::iterator i, end;
		i = mouseListeners.begin();
		end = mouseListeners.end();
		for(; i!=end; ++i)
		{
			if(i->getTypeTrigger() == type)
			{
				if(i->getCallbackFunction() != nullptr)
				{
					parseFlag = true;
					MouseEvent* newEvent = new MouseEvent(event);
					newEvent->setType(type);
					eventQueue.pushEventBack(i->getID(), newEvent, blockManager, getPath());
				}
			}
		}
		
		mouseHovering = interior;
		
		return parseFlag;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




