#include "../../include/other/ilslib_block_manager.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	BlockManager::BlockManager():
		root(nullptr),
		containerStyles()
	{
	}
	
	
	BlockManager::~BlockManager()
	{
		delete root;
		
		std::vector<ContainerStyle*>::iterator i;
		for(i=containerStyles.begin(); i!=containerStyles.end(); ++i)
			delete *i;
	}
	
	
	void BlockManager::addContainerStyle(ContainerStyle* style)
	{
		if(style != nullptr)
			containerStyles.push_back(style);
	}
	
	
	const ContainerStyle* BlockManager::getContainerStyle(const std::string& id) const
	{
		std::vector<ContainerStyle*>::const_iterator i;
		
		for(i=containerStyles.begin(); i!=containerStyles.end(); ++i)
		{
			if((*i)->getID() == id)
				return *i;
		}
		
		return nullptr;
	}
	
	
	void BlockManager::setRoot(Container* newRoot)
	{
		delete root;
		root = newRoot;
	}
	
	
	void BlockManager::calculateDPInfo(DrawableMap* drawables, const int windowWidth, const int windowHeight)
	{
		if(root == nullptr)
			return;
		
		drawables->clear();
		
		ContainerSettings* settings = root->getContainerSettings();
		settings->horizontalSizePolicy = Settings::SizePolicy::Maximize;
		settings->verticalSizePolicy = Settings::SizePolicy::Maximize;
		int maxWidth = windowWidth - settings->getOutterSpacingHorizontal();
		int maxHeight = windowHeight - settings->getOutterSpacingVertical();
		if(maxWidth < 0)
			maxWidth = 0;
		if(maxHeight < 0)
			maxHeight = 0;
		settings->maxWidth = maxWidth;
		settings->maxHeight = maxHeight;
		
		Rectangle availableSpace;
		availableSpace.width = windowWidth;
		availableSpace.height = windowHeight;
		
		root->step0A_clear();
		root->step0B_applyTransformations();
		root->step0C_findAllKeyCodes();
		
		root->step1A_minimize();
		root->step1B_adjust();
		root->step1C_maximize(windowWidth, windowHeight);
		root->step1D_reAdjust();
		
		root->step2A_determinePositions();
		root->step2B_determineCutRectangles(availableSpace);
		root->step2C_addToDrawableMap(drawables);
	}
	
	
	void BlockManager::transitionToAlternative(const std::string& path)
	{
		std::list<PathInfo> pathInfo;
		pathParse(path, pathInfo);
		
		if(pathInfo.size() < 1)
			throw std::exception();
		if(root->getID() != pathInfo.begin()->blockName)
			throw std::exception();
		
		BasicBlock* currentBlock = findBasicBlock(pathInfo, root);
		
		Container* currentContainer = dynamic_cast<Container*>(currentBlock);
		if(currentContainer == nullptr)
			throw std::exception();
		
		PathInfo& lastNodeInfo = *(--pathInfo.end());
		Alternative* currentAlternative = currentContainer->findAlternative(lastNodeInfo.alternativeName);
		
		currentContainer->transition.transitionTo(currentAlternative);
	}
	
	
	void BlockManager::parseMouseEvent(const MouseEvent& event, EventQueue& queue)
	{
		if(root != nullptr)
			root->parseMouseEvent(event, this, queue);
	}
	
	
	void BlockManager::parseKeyboardEvent(const KeyboardEvent& event, EventQueue& queue)
	{
		if(root != nullptr)
			root->parseKeyboardEvent(event, this, queue);
	}
	
	
	void BlockManager::parseTimeEvent(const TimeEvent& event, EventQueue& queue)
	{
		if(root != nullptr)
			root->parseTimeEvent(event, this, queue);
	}
	
	
	void BlockManager::parseWindowEvent(const WindowEvent& event, EventQueue& queue)
	{
		if(root != nullptr)
			root->parseWindowEvent(event, this, queue);
	}
	
	
	BasicBlock* BlockManager::findBasicBlock(const std::string& path)
	{
		std::list<PathInfo> pathInfo;
		pathParse(path, pathInfo);
		
		if(pathInfo.size() < 1)
			throw std::exception();
		if(root->getID() != pathInfo.begin()->blockName)
			throw std::exception();
		
		return findBasicBlock(pathInfo, root);
	}
	
	
	Alternative* BlockManager::findAlternative(const std::string& path)
	{
		std::list<PathInfo> pathInfo;
		pathParse(path, pathInfo);
		
		if(pathInfo.size() < 1)
			throw std::exception();
		if(root->getID() != pathInfo.begin()->blockName)
			throw std::exception();
		
		BasicBlock* currentBlock = findBasicBlock(pathInfo, root);
		if(currentBlock == nullptr)
			throw std::exception();
		
		Container* currentContainer = dynamic_cast<Container*>(currentBlock);
		if(currentContainer == nullptr)
			throw std::exception();
		
		PathInfo& lastNodeInfo = *(--pathInfo.end());
		return currentContainer->findAlternative(lastNodeInfo.alternativeName);
	}
	
	
	Layer* BlockManager::findLayer(const std::string& path)
	{
		std::list<PathInfo> pathInfo;
		pathParse(path, pathInfo);
		
		if(pathInfo.size() < 1)
			throw std::exception();
		if(root->getID() != pathInfo.begin()->blockName)
			throw std::exception();
		
		BasicBlock* currentBlock = findBasicBlock(pathInfo, root);
		if(currentBlock == nullptr)
			throw std::exception();
		
		Container* currentContainer = dynamic_cast<Container*>(currentBlock);
		if(currentContainer == nullptr)
			throw std::exception();
		
		PathInfo& lastNodeInfo = *(--pathInfo.end());
		Alternative* currentAlternative = currentContainer->findAlternative(lastNodeInfo.alternativeName);
		
		return currentAlternative->findLayer(lastNodeInfo.layerName);
	}
	
	
	void BlockManager::addBasicBlock(const std::string& path, BasicBlock* newBasicBlock)
	{
		Layer* currentLayer = findLayer(path);
		if(currentLayer == nullptr)
			throw std::exception();
		
		currentLayer->addBasicBlock(newBasicBlock);
	}
	
	
	void BlockManager::addAlternative(const std::string& path, Alternative* newAlternative)
	{
		BasicBlock* currentBlock = findBasicBlock(path);
		if(currentBlock == nullptr)
			throw std::exception();
		
		Container* currentContainer = dynamic_cast<Container*>(currentBlock);
		if(currentContainer == nullptr)
			throw std::exception();
		
		currentContainer->addAlternative(newAlternative);
	}
	
	
	void BlockManager::addLayer(const std::string& path, Layer* newLayer)
	{
		Alternative* currentAlternative = findAlternative(path);
		if(currentAlternative == nullptr)
			throw std::exception();
		
		currentAlternative->addLayer(newLayer);
	}
	
	
	void BlockManager::pathParse(const std::string& path, std::list<PathInfo>& pathInfo)
	{
		std::string nodeSeparators = "/\\";
		std::string alternativeSeparators = ".";
		
		std::list<std::string> nodes;
		Support::tokenize< std::list<std::string> >(path, nodes, nodeSeparators, true);
		
		std::list<std::string>::const_iterator node;
		for(node = nodes.begin(); node != nodes.end(); ++node)
		{
			std::vector<std::string> infoTokens;
			Support::tokenize< std::vector<std::string> >(*node, infoTokens, alternativeSeparators, false);
			
			PathInfo info;
			if(infoTokens.size() > 0)
				info.blockName = infoTokens[0];
			if(infoTokens.size() > 1)
				info.alternativeName = infoTokens[1];
			if(infoTokens.size() > 2)
				info.layerName = infoTokens[2];
			
			pathInfo.push_back(info);
		}
	}
	
	
	BasicBlock* BlockManager::findBasicBlock(const std::list<PathInfo>& pathInfo, BasicBlock* root)
	{
		BasicBlock* currentBlock = root;
		std::list<PathInfo>::const_iterator i;
		std::list<PathInfo>::const_iterator startingBlock = pathInfo.begin();
		
		for(i=pathInfo.begin(); i!=pathInfo.end(); ++i)
		{
			std::list<PathInfo>::const_iterator nextElement = i;
			++nextElement;
			if(nextElement == pathInfo.end())
				break;
			
			Container* currentContainer = dynamic_cast<Container*>(currentBlock);
			if(currentContainer == nullptr)
				return nullptr;
			
			PathInfo newPathInfo;
			newPathInfo.blockName = nextElement->blockName;
			newPathInfo.alternativeName = i->alternativeName;
			newPathInfo.layerName = i->layerName;
			
			BasicBlock* newBlock;
			
			// plan A: look for immediate connection
			newBlock = getBasicBlock(currentContainer, newPathInfo);
			if(newBlock != nullptr)
			{
				currentBlock = newBlock;
				continue;
			}
			
			// plan B: use breath first search
			std::list<BasicBlock*> breathFirstSearchList;
			
			Layer* currentLayer = getLayer(currentContainer, newPathInfo);
			if(currentLayer != nullptr)
			{
				currentLayer->getBasicBlocks(breathFirstSearchList);
			}
			else
			{
				Alternative* currentAlternative = getAlternative(currentContainer, newPathInfo);
				if(currentAlternative != nullptr)
					currentAlternative->getBasicBlocks(breathFirstSearchList);
				else
					currentContainer->getBasicBlocks(breathFirstSearchList);
			}
			
			newBlock = findBasicBlockBFS(breathFirstSearchList, newPathInfo.blockName);
			if(newBlock != nullptr)
				currentBlock = newBlock;
			else
				return nullptr;
			continue;
		}
		
		return currentBlock;
	}
	
	
	BasicBlock* BlockManager::findBasicBlockBFS(std::list<BasicBlock*> blocksList, const std::string& blockID)
	{
		while(blocksList.size() > 0)
		{
			BasicBlock* currentBlock = (*blocksList.begin());
			if(currentBlock == nullptr)
				continue;
			if(currentBlock->getID() == blockID)
				return currentBlock;
			
			blocksList.pop_front();
			
			Container* currentContainer = dynamic_cast<Container*>(currentBlock);
			if(currentContainer == nullptr)
				continue;
			
			currentContainer->getBasicBlocks(blocksList);
		}
		
		return nullptr;
	}
	
	
	Alternative* BlockManager::getAlternative(Container* container, const PathInfo& pathInfo)
	{
		return container->findAlternative(pathInfo.alternativeName);
	}
	
	
	Layer* BlockManager::getLayer(Container* container, const PathInfo& pathInfo)
	{
		if(pathInfo.layerName == "")
			return nullptr;
		
		Alternative* alt = getAlternative(container, pathInfo);
		if(alt != nullptr)
			return alt->findLayer(pathInfo.layerName);
		
		return nullptr;
	}
	
	
	BasicBlock* BlockManager::getBasicBlock(Container* container, const PathInfo& pathInfo)
	{
		if(pathInfo.blockName == "")
			return nullptr;
		
		if(pathInfo.layerName != "")
		{
			Layer* layer = getLayer(container, pathInfo);
			if(layer != nullptr)
				return layer->findBasicBlock(pathInfo.blockName);
		}
		else
		{
			Alternative* alt = getAlternative(container, pathInfo);
			if(alt != nullptr)
				return alt->findBasicBlock(pathInfo.blockName);
			else
				return container->findBasicBlock(pathInfo.blockName);
		}
		
		return nullptr;
	}
	
	
	BlockManager::PathInfo::PathInfo():
		blockName(),
		alternativeName(),
		layerName(),
		layerNumber(0)
	{
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





