#include "../../include/other/ilslib_block_manager.hpp"



/*----------------------------------------------------------------------------------
										ILSLib
----------------------------------------------------------------------------------*/
namespace ILSLib
{
	
	
	
	BlockManager::BlockManager():
		containerStyles(),
		roots(),
		eventQueue()
	{
	}
	
	
	BlockManager::~BlockManager()
	{
		clear();
	}
	
	
	void BlockManager::clear()
	{
		std::vector<ContainerStyle*>::iterator style;
		for(style=containerStyles.begin(); style!=containerStyles.end(); ++style)
			delete *style;
		
		std::vector<Container*>::iterator root;
		for(root=roots.begin(); root!=roots.end(); ++root)
			delete *root;
		
		containerStyles.clear();
		roots.clear();
		eventQueue.clear();
	}
	
	
	void BlockManager::calculateDPInfo(const std::string& root, DrawableMap* drawables, const Vector& windowSize)
	{
		Container* rootContainer = getRoot(root);
		if(rootContainer == nullptr)
			return;
		
		drawables->clear();
		
		ContainerSettings* settings = rootContainer->getContainerSettings();
		settings->horizontalSizePolicy = Settings::SizePolicy::Maximize;
		settings->verticalSizePolicy = Settings::SizePolicy::Maximize;
		int maxWidth = windowSize.x - settings->getOutterSpacingHorizontal();
		int maxHeight = windowSize.y - settings->getOutterSpacingVertical();
		if(maxWidth < 0)
			maxWidth = 0;
		if(maxHeight < 0)
			maxHeight = 0;
		
		settings->maxWidth = maxWidth;
		settings->maxHeight = maxHeight;
		
		Rectangle availableSpace;
		availableSpace.width = windowSize.x;
		availableSpace.height = windowSize.y;
		
		rootContainer->step0A_clear();
		rootContainer->step0B_applyTransformations();
		rootContainer->step0C_optimizeListeners();
		
		rootContainer->step1A_minimize();
		rootContainer->step1B_adjust();
		rootContainer->step1C_maximize(windowSize);
		rootContainer->step1D_reAdjust();
		
		rootContainer->step2A_determinePositions();
		rootContainer->step2B_determineCutRectangles(availableSpace);
		rootContainer->step2C_addToDrawableMap(drawables);
	}
	
	
	const ContainerStyle* BlockManager::getContainerStyle(const std::string& id) const
	{
		std::vector<ContainerStyle*>::const_iterator i;
		
		for(i=containerStyles.begin(); i!=containerStyles.end(); ++i)
			if((*i)->getID() == id)
				return *i;
		
		return nullptr;
	}
	
	
	bool BlockManager::addContainerStyle(ContainerStyle* style)
	{
		if(style == nullptr)
			return false;
		
		std::vector<ContainerStyle*>::const_iterator i;
		for(i=containerStyles.begin(); i!=containerStyles.end(); ++i)
			if((*i)->getID() == style->getID())
				return false;
		
		containerStyles.push_back(style);
		
		return true;
	}
	
	
	void BlockManager::parseEvent(const std::string& root, const MouseEvent& event, EventQueue& queue)
	{
		Container* rootContainer = getRoot(root);
		if(rootContainer == nullptr)
			return;
		
		rootContainer->parseEvent(event, this, queue);
	}
	
	
	void BlockManager::parseEvent(const std::string& root, const KeyboardEvent& event, EventQueue& queue)
	{
		Container* rootContainer = getRoot(root);
		if(rootContainer == nullptr)
			return;
		
		rootContainer->parseEvent(event, this, queue);
	}
	
	
	void BlockManager::parseEvent(const std::string& root, const TimeEvent& event, EventQueue& queue)
	{
		Container* rootContainer = getRoot(root);
		if(rootContainer == nullptr)
			return;
		
		rootContainer->parseEvent(event, this, queue);
	}
	
	
	void BlockManager::parseEvent(const std::string& root, const WindowEvent& event, EventQueue& queue)
	{
		Container* rootContainer = getRoot(root);
		if(rootContainer == nullptr)
			return;
		
		rootContainer->parseEvent(event, this, queue);
	}
	
	
	const BasicBlock* BlockManager::operator[] (const std::string& path) const
	{
		PathInfo pathInfo;
		pathParse(path, pathInfo);
		
		return findBasicBlock(pathInfo);
	}
	
	
	BasicBlock* BlockManager::operator[] (const std::string& path)
	{
		const BlockManager* blockManager = const_cast<const BlockManager*>(this);
		return const_cast<BasicBlock*>((*blockManager)[path]);
	}
	
	
	bool BlockManager::addBasicBlock(const std::string& path, BasicBlock* newBasicBlock)
	{
		if(newBasicBlock == nullptr)
			return false;
		
		BasicBlock* block = (*this)[path];
		if(block == nullptr)
			return false;
		
		Container* container = dynamic_cast<Container*>(block);
		if(container == nullptr)
			return false;
		
		return container->addBasicBlock(newBasicBlock);
	}
	
	
	bool BlockManager::addRoot(BasicBlock* newBasicBlock)
	{
		if(newBasicBlock == nullptr)
			return false;
		
		Container* newRoot = dynamic_cast<Container*>(newBasicBlock);
		if(newRoot == nullptr)
			return false;
		
		for(std::vector<Container*>::const_iterator i=roots.begin(); i!=roots.end(); ++i)
			if((*i)->getID() == newBasicBlock->getID())
				return false;
		
		newRoot->parent = nullptr;
		roots.push_back(newRoot);
		return true;
	}
	
	
	void BlockManager::pathParse(const std::string& path, PathInfo& pathInfo)
	{
		std::string nodeSeparators = "/\\";
		
		pathInfo.clear();
		
		PathInfo preliminaryPath1;
		PathInfo preliminaryPath2;
		
		Support::tokenize< PathInfo >(path, preliminaryPath1, nodeSeparators, true);
		
		for(PathInfo::iterator i=preliminaryPath1.begin(); i!=preliminaryPath1.end(); ++i)
			Support::trim(*i);
		
		int lastExplicitValueIndex = -1;
		int counter = 0;
		std::string lastNodeValue = "";
		
		for(PathInfo::iterator i=preliminaryPath1.begin(); i!=preliminaryPath1.end(); ++i, ++counter)
		{
			std::string nodeValue = *i;
			
			if(nodeValue == "")
				continue;
			if(lastNodeValue == "**" && (nodeValue == "*" || nodeValue == "**"))
				continue;
			if(nodeValue != "*" && nodeValue != "**")
				lastExplicitValueIndex = counter;
			
			preliminaryPath2.push_back(nodeValue);
			lastNodeValue = nodeValue;
		}
		
		counter = 0;
		for(PathInfo::iterator i=preliminaryPath2.begin(); i!=preliminaryPath2.end(); ++i, ++counter)
		{
			if(counter > lastExplicitValueIndex)
				break;
			
			std::string nodeValue = *i;
			pathInfo.push_back(*i);
		}
	}
	
	
	void BlockManager::expandOneLevel(std::list<const BasicBlock*>& blocksList)
	{
		unsigned int listSize = blocksList.size();
		
		for(unsigned int i=0; i<listSize; ++i)
		{
			const Container* container = dynamic_cast<const Container*>(blocksList.front());
			blocksList.pop_front();
			
			if(container == nullptr)
				continue;
			
			const Container::SubComponents& subComponents = container->getBasicBlocks();
			
			Container::const_iterator block;
			for(block = subComponents.begin(); !block.isEnd(); ++block)
				blocksList.push_back(*block);
		}
	}
	
	
	void BlockManager::expandBFS(std::list<const BasicBlock*>& blocksList, const std::string& blockID)
	{
		std::list<const BasicBlock*> newBlockList;
		bool idFound = false;
		
		while(idFound == false)
		{
			if(blocksList.size() == 0)
				return;
			
			expandOneLevel(blocksList);
			
			// check the list for explicit id
			std::list<const BasicBlock*>::const_iterator blockIterator;
			for(blockIterator=blocksList.begin(); blockIterator!=blocksList.end(); ++blockIterator)
			{
				if((*blockIterator)->getID() == blockID)
				{
					idFound = true;
					newBlockList.push_back(*blockIterator);
				}
			}
		}
		
		blocksList.clear();
		blocksList = newBlockList;
	}
	
	
	const Container* BlockManager::getRoot(const std::string& path) const
	{
		PathInfo pathInfo;
		pathParse(path, pathInfo);
		if(pathInfo.size() == 0)
			return nullptr;
		
		PathInfo rootPath;
		rootPath.push_back(pathInfo.front());
		
		const BasicBlock* rootBlock = findBasicBlock(rootPath);
		if(rootBlock == nullptr)
			return nullptr;
		
		const Container* rootContainer = dynamic_cast<const Container*>(rootBlock);
		if(rootContainer == nullptr)
			return nullptr;
		
		return rootContainer;
	}
	
	
	Container* BlockManager::getRoot(const std::string& path)
	{
		const BlockManager* blockManager = const_cast<const BlockManager*>(this);
		return const_cast<Container*>(blockManager->getRoot(path));
	}
	
	
	const BasicBlock* BlockManager::findBasicBlock(const PathInfo& pathInfo) const
	{
		std::list<const BasicBlock*> blocksList;
		std::list<const BasicBlock*> newBlockList;
		std::list<const BasicBlock*>::const_iterator blockIterator;
		PathInfo::const_iterator pathIterator;
		
		std::string singleLevelExpansion = "*";
		std::string multiLevelExpansion = "**";
		
		std::vector<Container*>::const_iterator rootIterator;
		for(rootIterator=roots.begin(); rootIterator!=roots.end(); ++rootIterator)
			blocksList.push_back(*rootIterator);
		
		std::string pathNode = "";
		for(pathIterator=pathInfo.begin(); pathIterator!=pathInfo.end(); ++pathIterator)
		{
			if(blocksList.size() == 0)
				return nullptr;
			
			if(pathIterator != pathInfo.begin())
				expandOneLevel(blocksList);
			
			pathNode = *pathIterator;
			
			if(pathNode == "")
				continue;
			
			if(pathNode == singleLevelExpansion)
			{
				expandOneLevel(blocksList);
				continue;
			}
			
			if(pathNode == multiLevelExpansion)
			{
				std::string nextPathNode = "";
				
				++pathIterator;
				
				if(pathIterator == pathInfo.end())
					return nullptr;
				
				nextPathNode = *pathIterator;
				expandBFS(blocksList, nextPathNode);
				
				continue;
			}
			
			// check the list for explicit id
			newBlockList.clear();
			bool pathNodeFound = false;
			
			for(blockIterator=blocksList.begin(); blockIterator!=blocksList.end(); ++blockIterator)
			{
				if((*blockIterator) == nullptr)
				{
					continue;
				}
				
				if((*blockIterator)->getID() == pathNode)
				{
					pathNodeFound = true;
					newBlockList.push_back(*blockIterator);
				}
			}
			
			// explicit id not found on this level
			if(pathNodeFound == false)
				return nullptr;
			
			blocksList.clear();
			
			for(blockIterator=newBlockList.begin(); blockIterator!=newBlockList.end(); ++blockIterator)
				blocksList.push_back(*blockIterator);
		}
		
		if(blocksList.size() == 0)
			return nullptr;
		
		return *blocksList.begin();
	}
	
	
	
} // end namespace ILSLib
//----------------------------------------------------------------------------------





