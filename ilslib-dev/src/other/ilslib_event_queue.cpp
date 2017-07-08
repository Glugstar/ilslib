#include "../../include/other/ilslib_event_queue.hpp"
#include "../../include/other/ilslib_block_manager.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	EventQueue::EventQueue():
		events()
	{
	}
	
	
	EventQueue::~EventQueue()
	{
		clear();
	}
	
	
	bool EventQueue::hasEvents() const
	{
		return !events.empty();
	}
	
	
	void EventQueue::pushEventFront(const std::string& listenerID, const Event* event,
									BlockManager* blockManager, const std::string basicBlockPath)
	{
		if(event == nullptr || blockManager == nullptr)
			return;
		
		EventTuple eventTuple(listenerID, event, blockManager, basicBlockPath);
		events.push_front(eventTuple);
	}
	
	
	void EventQueue::pushEventBack(const std::string& listenerID, const Event* event,
									BlockManager* blockManager, const std::string basicBlockPath)
	{
		if(event == nullptr || blockManager == nullptr)
			return;
		
		EventTuple eventTuple(listenerID, event, blockManager, basicBlockPath);
		events.push_back(eventTuple);
	}
	
	
	void EventQueue::parseNextEvent()
	{
		if(events.empty() == true)
			return;
		
		EventTuple eventTuple = events.front();
		events.pop_front();
		
		Listener* listener = nullptr;
		std::string& listenerID = std::get<0>(eventTuple);
		const Event* event = std::get<1>(eventTuple);
		BlockManager* blockManager = std::get<2>(eventTuple);
		std::string* path = &std::get<3>(eventTuple);
		BasicBlock* basicBlock = blockManager->findBasicBlock(*path);
		
		if(basicBlock != nullptr)
			listener = basicBlock->getListener(listenerID);
		
		if(listener != nullptr && basicBlock != nullptr && event != nullptr && blockManager != nullptr)
			listener->runCallbackFunction(basicBlock, event, blockManager, this);
		
		if(event != nullptr)
			delete event;
	}
	
	
	void EventQueue::clear()
	{
		std::list<EventTuple>::iterator event;
		for(event=events.begin(); event!=events.end(); ++event)
		{
			const Event* e = std::get<1>(*event);
			if(e != nullptr)
				delete e;
		}
		
		events.clear();
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





