#include "../../include/blocks/ilslib_flow_container.hpp"



/*  ----------------------------------------------------------------------------------
										ILSLib
    ----------------------------------------------------------------------------------*/
namespace ILSLib
{



	FlowContainer::FlowContainer(const std::string& containerID):
		Container(containerID),
		basicBlocks()
	{
		settings = new FlowContainerSettings();
	}
	
	
	FlowContainer::~FlowContainer()
	{
	}
	
	
	const FlowContainerSettings* FlowContainer::getFlowContainerSettings() const
	{
		if(settings == nullptr)
			return nullptr;
			
		return static_cast<const FlowContainerSettings*>(settings);
	}
	
	
	FlowContainerSettings* FlowContainer::getFlowContainerSettings()
	{
		if(settings == nullptr)
			return nullptr;
			
		return static_cast<FlowContainerSettings*>(settings);
	}
	
	
	const Container::SubComponents& FlowContainer::getBasicBlocks() const
	{
		return basicBlocks;
	}
	
	
	Container::SubComponents& FlowContainer::getBasicBlocks()
	{
		return basicBlocks;
	}
	
	
	bool FlowContainer::addBasicBlock(BasicBlock* block)
	{
		if(block == nullptr)
			return false;
			
		bool result = basicBlocks.push_back(block);
		if(result == true)
			block->parent = this;
			
		return result;
	}
	
	
	bool FlowContainer::removeBasicBlock(const std::string& blockID)
	{
		return basicBlocks.erase(blockID);
	}
	
	
	bool FlowContainer::parseSubComponentsEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		SubComponents::Filter filter;
		filter.addFilterFuntion(isSuperPhysical);
		
		for(iterator i=basicBlocks.begin(&filter); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool FlowContainer::parseSubComponentsEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool FlowContainer::parseSubComponentsEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	bool FlowContainer::parseSubComponentsEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
	{
		bool parseFlag = false;
		
		for(iterator i=basicBlocks.begin(); !i.isEnd(); ++i)
		{
			if((*i)->parseEvent(event, blockManager, eventQueue) == true)
				parseFlag = true;
		}
		
		return parseFlag;
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------




