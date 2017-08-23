//#include "../../include/blocks/ilslib_alternative.hpp"
//#include "../../include/blocks/ilslib_container.hpp"
//
//
//
///*----------------------------------------------------------------------------------
//										ILSLib
//----------------------------------------------------------------------------------*/
//namespace ILSLib
//{
//
//
//
//	Alternative::Alternative(const std::string& alternativeID, const std::string& layerID):
//		id(alternativeID),
//		parentContainer(nullptr),
//		layers(),
//		allKeyCodes(),
//		dInfoStep1A(),
//		dInfoStep1B(),
//		dInfoStep1C(),
//		dInfoStep1D(),
//		pInfo()
//	{
//		createLayer(layerID);
//	}
//
//
//	Alternative::~Alternative()
//	{
//		removeAllLayers();
//	}
//
//
//	const std::string& Alternative::getID() const
//	{
//		return id;
//	}
//
//
//	std::string Alternative::getPath() const
//	{
//		return parentContainer->getPath() + "." + id;
//	}
//
//
//	const Container* Alternative::getParentContainer() const
//	{
//		return parentContainer;
//	}
//
//
//	Container* Alternative::getParentContainer()
//	{
//		return parentContainer;
//	}
//
//
//	void Alternative::getBasicBlocks(std::list<BasicBlock*>& blockList)
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->getBasicBlocks(blockList);
//	}
//
//
//	BasicBlock* Alternative::findBasicBlock(const std::string& blockID)
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			BasicBlock* element = (*i)->findBasicBlock(blockID);
//			if(element != nullptr)
//				return element;
//		}
//
//		return nullptr;
//	}
//
//
//	Layer* Alternative::findLayer(const std::string& layerID)
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if((*i)->getID() == layerID)
//				return *i;
//		}
//
//		return nullptr;
//	}
//
//
//	void Alternative::addLayer(Layer* layer)
//	{
//		if(layer == nullptr)
//			return;
//
//		layer->parentAlternative = this;
//		layers.push_back(layer);
//	}
//
//
//	void Alternative::removeLayer(const std::string& id)
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if((*i)->getID() == id)
//			{
//				delete *i;
//				layers.erase(i);
//				return;
//			}
//		}
//	}
//
//
//	void Alternative::removeAllLayers()
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			delete *i;
//		layers.clear();
//	}
//
//
//	const std::unordered_set<std::string>& Alternative::getAllKeyCodes() const
//	{
//		return allKeyCodes;
//	}
//
//
//	const DimensionsInfo* Alternative::getDimensionsInfo(const Settings::Step step) const
//	{
//		if(step == Settings::Step::s1A_minimize)
//			return &dInfoStep1A;
//		else if(step == Settings::Step::s1B_adjust)
//			return &dInfoStep1B;
//		else if(step == Settings::Step::s1C_maximize)
//			return &dInfoStep1C;
//		else if(step == Settings::Step::s1D_reAdjust)
//			return &dInfoStep1D;
//
//		throw std::exception();
//	}
//
//
//	const PositionInfo* Alternative::getPositionInfo() const
//	{
//		return &pInfo;
//	}
//
//
//	bool Alternative::parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue, bool multiLayer)
//	{
//		if(event.eventApplies(*getPositionInfo()) == false)
//			return false;
//
//		bool parseFlag = false;
//
//		std::list<Layer*>::reverse_iterator i;
//		for(i=layers.rbegin(); i!=layers.rend(); ++i)
//		{
//			bool flag = (*i)->parseMouseEvent(event, blockManager, eventQueue);
//			if(flag == true)
//				parseFlag = true;
//			if(flag == true && multiLayer == false)
//				return true;
//		}
//
//		return parseFlag;
//	}
//
//
//	bool Alternative::parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
//	{
//		bool parseFlag = false;
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if((*i)->parseKeyboardEvent(event, blockManager, eventQueue) == true)
//				parseFlag = true;
//		}
//
//		return parseFlag;
//	}
//
//
//	bool Alternative::parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
//	{
//		bool parseFlag = false;
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if((*i)->parseTimeEvent(event, blockManager, eventQueue) == true)
//				parseFlag = true;
//		}
//
//		return parseFlag;
//	}
//
//
//	bool Alternative::parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
//	{
//		bool parseFlag = false;
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if((*i)->parseWindowEvent(event, blockManager, eventQueue) == true)
//				parseFlag = true;
//		}
//
//		return parseFlag;
//	}
//
//
//	void Alternative::step0A_clear()
//	{
//		dInfoStep1A.clear();
//		dInfoStep1B.clear();
//		dInfoStep1C.clear();
//		dInfoStep1D.clear();
//
//		pInfo.clear();
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->step0A_clear();
//	}
//
//
//	void Alternative::step0B_applyTransformations()
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->step0B_applyTransformations();
//	}
//
//
//	void Alternative::step0C_findAllKeyCodes()
//	{
//		allKeyCodes.clear();
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			(*i)->step0C_findAllKeyCodes();
//			const std::unordered_set<std::string>& keyCodes = (*i)->getAllKeyCodes();
//
//			std::unordered_set<std::string>::const_iterator j;
//			for(j=keyCodes.begin(); j!=keyCodes.end(); ++j)
//			{
//				if(allKeyCodes.find(*j) == allKeyCodes.end())
//					allKeyCodes.insert(*j);
//			}
//		}
//	}
//
//
//	void Alternative::step1A_minimize(const ContainerSettings* currentSettings)
//	{
//		Settings::Step currentStep = Settings::Step::s1A_minimize;
//
//
//		// recursive minimization first
//		std::list<Layer*>::iterator i;
//		int maxX = 0;
//		int maxY = 0;
//
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if(*i == nullptr)
//				throw std::exception();
//			(*i)->step1A_minimize(currentSettings);
//
//			const DimensionsInfo* dInfo = (*i)->getDimensionsInfo(currentStep);
//			maxX = dInfo->totalWidth > maxX ? dInfo->totalWidth : maxX;
//			maxY = dInfo->totalHeight > maxY ? dInfo->totalHeight : maxY;
//		}
//
//
//		// adjust for min, max, fixed settings
//		if(currentSettings->fixedWidth > 0)
//			maxX = (int)currentSettings->fixedWidth;
//		else
//		{
//			if(currentSettings->minWidth > 0)
//				maxX = maxX > (int)currentSettings->minWidth ? maxX : (int)currentSettings->minWidth;
//			if(currentSettings->maxWidth > 0)
//				maxX = maxX < (int)currentSettings->maxWidth ? maxX : (int)currentSettings->maxWidth;
//		}
//
//		if(currentSettings->fixedHeight > 0)
//			maxY = (int)currentSettings->fixedHeight;
//		else
//		{
//			if(currentSettings->minHeight > 0)
//				maxY = maxY > (int)currentSettings->minHeight ? maxY : (int)currentSettings->minHeight;
//			if(currentSettings->maxHeight > 0)
//				maxY = maxY < (int)currentSettings->maxHeight ? maxY : (int)currentSettings->maxHeight;
//		}
//
//
//		// add outter spacing
//		maxX += currentSettings->getOutterSpacingHorizontal();
//		maxY += currentSettings->getOutterSpacingVertical();
//
//
//		// commit computations to minimization step info
//		dInfoStep1A.totalWidth = maxX;
//		dInfoStep1A.totalHeight = maxY;
//	}
//
//
//	void Alternative::step1B_adjust()
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->step1B_adjust();
//
//		dInfoStep1B = dInfoStep1A;
//	}
//
//
//	void Alternative::step1C_maximize(const ContainerSettings* currentSettings,
//									int availableWidth, int availableHeight)
//	{
//		dInfoStep1C = dInfoStep1B;
//
//		dInfoStep1C.totalWidth = availableWidth;
//		dInfoStep1C.totalHeight = availableHeight;
//
//		availableWidth -= currentSettings->getOutterSpacingHorizontal();
//		availableHeight -= currentSettings->getOutterSpacingVertical();
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->step1C_maximize(currentSettings, availableWidth, availableHeight);
//	}
//
//
//	void Alternative::step1D_reAdjust()
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->step1D_reAdjust();
//
//		dInfoStep1D = dInfoStep1C;
//		pInfo.posRectangle.width = dInfoStep1D.totalWidth;
//		pInfo.posRectangle.height = dInfoStep1D.totalHeight;
//	}
//
//
//	void Alternative::step2A_determinePositions(const ContainerSettings* currentSettings)
//	{
//		// recursive minimization first
//		std::list<Layer*>::iterator i;
//
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			if(*i == nullptr)
//				throw std::exception();
//
//			PositionInfo* layerPInfo = (*i)->getPositionInfo();
//			layerPInfo->posRectangle = pInfo.posRectangle;
//			layerPInfo->posRectangle.x += (*i)->getLayerOffsetX();
//			layerPInfo->posRectangle.y += (*i)->getLayerOffsetY();
//
//			(*i)->step2A_determinePositions(currentSettings);
//		}
//	}
//
//
//	void Alternative::step2B_determineCutRectangles(const Rectangle& availableSpace)
//	{
//		PositionInfo* pInfo = getPositionInfo();
//
//		pInfo->cutRectangle = availableSpace;
//		pInfo->intersectionRectangle = pInfo->posRectangle.intersect(pInfo->cutRectangle);
//
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			(*i)->step2B_determineCutRectangles(pInfo->intersectionRectangle);
//		}
//	}
//
//
//	void Alternative::step2C_addToDrawableMap(DrawableMap* drawables)
//	{
//		std::list<Layer*>::iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//			(*i)->step2C_addToDrawableMap(drawables);
//	}
//
//
//	PositionInfo* Alternative::getPositionInfo()
//	{
//		return &pInfo;
//	}
//
//
//	Vector Alternative::getAvailableMaximization(Settings::IterationMode mode) const
//	{
//		int maxX, maxY;
//		maxX = maxY = 0;
//
//		std::list<Layer*>::const_iterator i;
//		for(i=layers.begin(); i!=layers.end(); ++i)
//		{
//			Vector result = (*i)->getAvailableMaximization(mode);
//
//			if(result.x > 0 && maxX >= 0)
//				maxX = maxX > result.x ? maxX : result.x;
//
//			if(result.y > 0 && maxY >= 0)
//				maxY = maxY > result.y ? maxY : result.y;
//
//			if(result.x < 0)
//				maxX = maxX < result.x ? maxX : result.x;
//
//			if(result.y < 0)
//				maxY = maxY < result.y ? maxY : result.y;
//
//			if(maxX < 0 && maxY < 0)
//				return Vector(maxX, maxY);
//		}
//
//		return Vector(maxX, maxY);
//	}
//
//
//	void Alternative::createLayer(const std::string& layerID)
//	{
//		Layer* l = new Layer(layerID);
//		layers.push_back(l);
//		l->parentAlternative = this;
//	}
//
//
//
//} // end namespace ILSLib
////----------------------------------------------------------------------------------
//
//
//
//
