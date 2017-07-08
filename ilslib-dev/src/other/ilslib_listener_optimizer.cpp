#include "../../include/other/ilslib_listener_optimizer.hpp"
#include "../../include/blocks/ilslib_container.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	ListenerOptimizer::ListenerOptimizer():
		buttonTriggers(),
		keyTriggers(),
		allButtons(false),
		allKeys(false)
	{
	}
	
	
	ListenerOptimizer::~ListenerOptimizer()
	{
	}
	
	
	const std::set<MouseButton::Button>& ListenerOptimizer::getButtonTriggers() const
	{
		return buttonTriggers;
	}
	
	
	const std::set<std::string>& ListenerOptimizer::getKeyTriggers() const
	{
		return keyTriggers;
	}
	
	
	bool ListenerOptimizer::allButtonsTrigger() const
	{
		return allButtons;
	}
	
	
	bool ListenerOptimizer::allKeysTrigger() const
	{
		return allKeys;
	}
	
	
	void ListenerOptimizer::updateMouseOptimization(const std::list<MouseListener>& mouseListeners)
	{
		buttonTriggers.clear();
		allButtons = false;
		
		std::list<MouseListener>::const_iterator mouseIt;
		for(mouseIt=mouseListeners.begin(); mouseIt!=mouseListeners.end(); ++mouseIt)
		{
			if(mouseIt->isActive() == false)
				continue;
			
			if(mouseIt->getCallbackFunction() == nullptr)
				continue;
			
			if(mouseIt->triggersOnButtonAction() == false)
				continue;
			
			if(mouseIt->allButtonsTrigger() == true)
			{
				buttonTriggers.clear();
				allButtons = true;
				break;
			}
			
			std::set<MouseButton::Button>::const_iterator i;
			const std::set<MouseButton::Button>& buttonTriggerList = mouseIt->getButtonsTrigger();
			for(i=buttonTriggerList.begin(); i!=buttonTriggerList.end(); ++i)
			{
				if(buttonTriggers.find(*i) == buttonTriggers.end())
					buttonTriggers.insert(*i);
			}
		}
	}
	
	
	void ListenerOptimizer::updateKeyboardOptimization(const std::list<KeyboardListener>& keyboardListeners)
	{
		keyTriggers.clear();
		allKeys = false;
		
		std::list<KeyboardListener>::const_iterator keyIt;
		for(keyIt=keyboardListeners.begin(); keyIt!=keyboardListeners.end(); ++keyIt)
		{
			if(keyIt->isActive() == false)
				continue;
			
			if(keyIt->getCallbackFunction() == nullptr)
				continue;
			
			if(keyIt->triggersOnKeyAction() == false)
				continue;
			
			if(keyIt->allKeyCodesTrigger() == true)
			{
				keyTriggers.clear();
				allKeys = true;
				break;
			}
			
			std::set<std::string>::const_iterator i;
			const std::set<std::string>& keyCodesTriggerList = keyIt->getKeyCodesTrigger();
			for(i=keyCodesTriggerList.begin(); i!=keyCodesTriggerList.end(); ++i)
			{
				if(keyTriggers.find(*i) == keyTriggers.end())
					keyTriggers.insert(*i);
			}
		}
	}
	
	
	void ListenerOptimizer::updateMouseOptimization(const BlockCollection<BasicBlock>* blockCollection)
	{
		const Container::SubComponents* subComponents =
			dynamic_cast<const Container::SubComponents*>(blockCollection);
		if(subComponents == nullptr)
			return;
		
		buttonTriggers.clear();
		allButtons = false;
		
		Container::SubComponents::Filter filter;
		filter.addFilterFuntion(Container::isPhysical);
		
		Container::const_iterator blockIt;
		for(blockIt=subComponents->begin(&filter); !blockIt.isEnd(); ++blockIt)
			updateMouseOptimization((*blockIt)->getListenerOptimizer());
	}
	
	
	void ListenerOptimizer::updateKeyboardOptimization(const BlockCollection<BasicBlock>* blockCollection)
	{
		const Container::SubComponents* subComponents =
			dynamic_cast<const Container::SubComponents*>(blockCollection);
		if(subComponents == nullptr)
			return;
		
		keyTriggers.clear();
		allKeys = false;
		
		Container::const_iterator blockIt;
		for(blockIt=subComponents->begin(); !blockIt.isEnd(); ++blockIt)
			updateKeyboardOptimization((*blockIt)->getListenerOptimizer());
	}
	
	
	void ListenerOptimizer::updateMouseOptimization(const ListenerOptimizer& optimizer1,
													const ListenerOptimizer& optimizer2)
	{
		buttonTriggers.clear();
		allButtons = false;
		
		updateMouseOptimization(optimizer1);
		updateMouseOptimization(optimizer2);
	}
	
	
	void ListenerOptimizer::updateKeyboardOptimization(const ListenerOptimizer& optimizer1,
													const ListenerOptimizer& optimizer2)
	{
		keyTriggers.clear();
		allKeys = false;
		
		updateKeyboardOptimization(optimizer1);
		updateKeyboardOptimization(optimizer2);
	}
	
	
	void ListenerOptimizer::updateMouseOptimization(const ListenerOptimizer& optimizer)
	{
		if(allButtons == true)
			return;
		
		if(optimizer.allButtons == true)
		{
			buttonTriggers.clear();
			allButtons = true;
			return;
		}
		
		std::set<MouseButton::Button>::const_iterator buttonIt;
		for(buttonIt=optimizer.buttonTriggers.begin(); buttonIt!=optimizer.buttonTriggers.end(); ++buttonIt)
		{
			if(buttonTriggers.find(*buttonIt) == buttonTriggers.end())
				buttonTriggers.insert(*buttonIt);
		}
	}
	
	
	void ListenerOptimizer::updateKeyboardOptimization(const ListenerOptimizer& optimizer)
	{
		if(allKeys == true)
			return;
		
		if(optimizer.allKeys == true)
		{
			keyTriggers.clear();
			allKeys = true;
			return;
		}
		
		std::set<std::string>::const_iterator keyIt;
		for(keyIt=optimizer.keyTriggers.begin(); keyIt!=optimizer.keyTriggers.end(); ++keyIt)
		{
			if(keyTriggers.find(*keyIt) == keyTriggers.end())
				keyTriggers.insert(*keyIt);
		}
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





