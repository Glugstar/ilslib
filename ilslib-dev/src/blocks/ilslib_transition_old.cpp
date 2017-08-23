//#include "../../include/blocks/ilslib_transition.hpp"
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
//	Transition::Transition(Container* parent):
//		parentContainer(parent),
//		currentAlternative(nullptr)
//	{
//	}
//
//
//	Transition::~Transition()
//	{
//	}
//
//
//	Alternative* Transition::getCurrentAlternative()
//	{
//		return currentAlternative;
//	}
//
//
//	void Transition::transitionTo(Alternative* alt)
//	{
//		if(currentAlternative == nullptr)
//		{
//			currentAlternative = alt;
//			return;
//		}
//		else
//		{
//			// not yet implemented
//			currentAlternative = alt;
//			return;
//		}
//
//		throw std::exception();
//	}
//
//
//	const std::unordered_set<std::string>& Transition::getAllKeyCodes() const
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->getAllKeyCodes();
//	}
//
//
//	const DimensionsInfo* Transition::getDimensionsInfo(const Settings::Step step) const
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->getDimensionsInfo(step);
//	}
//
//
//	const PositionInfo* Transition::getPositionInfo() const
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->getPositionInfo();
//	}
//
//
//	bool Transition::parseMouseEvent(const MouseEvent& event, BlockManager* blockManager, EventQueue& eventQueue, bool multiLayer)
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->parseMouseEvent(event, blockManager, eventQueue, multiLayer);
//	}
//
//
//	bool Transition::parseKeyboardEvent(const KeyboardEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->parseKeyboardEvent(event, blockManager, eventQueue);
//	}
//
//
//	bool Transition::parseTimeEvent(const TimeEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->parseTimeEvent(event, blockManager, eventQueue);
//	}
//
//
//	bool Transition::parseWindowEvent(const WindowEvent& event, BlockManager* blockManager, EventQueue& eventQueue)
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->parseWindowEvent(event, blockManager, eventQueue);
//	}
//
//
//	void Transition::step0A_clear()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step0A_clear();
//	}
//
//
//	void Transition::step0B_applyTransformations()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step0B_applyTransformations();
//	}
//
//
//	void Transition::step0C_findAllKeyCodes()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step0C_findAllKeyCodes();
//	}
//
//
//	void Transition::step1A_minimize()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step1A_minimize(parentContainer->getContainerSettings());
//	}
//
//
//	void Transition::step1B_adjust()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step1B_adjust();
//	}
//
//
//	void Transition::step1C_maximize(int availableWidth, int availableHeight)
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step1C_maximize(parentContainer->getContainerSettings(),
//											availableWidth, availableHeight);
//	}
//
//
//	void Transition::step1D_reAdjust()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step1D_reAdjust();
//	}
//
//
//	void Transition::step2A_determinePositions()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//
//		const ContainerSettings* currentSettings = parentContainer->getContainerSettings();
//		const PositionInfo* pInfo = const_cast<const Container*>(parentContainer)->getPositionInfo();
//		PositionInfo* alternativePInfo = currentAlternative->getPositionInfo();
//
//		alternativePInfo->posRectangle = pInfo->posRectangle;
//		alternativePInfo->posRectangle.x -= parentContainer->getScrollX();
//		alternativePInfo->posRectangle.y -= parentContainer->getScrollY();
//		alternativePInfo->posRectangle.x += currentSettings->getSpacingLeft();
//		alternativePInfo->posRectangle.y += currentSettings->getSpacingTop();
//
//		currentAlternative->step2A_determinePositions(currentSettings);
//	}
//
//
//	void Transition::step2B_determineCutRectangles()
//	{
//		const ContainerSettings* currentSettings = parentContainer->getContainerSettings();
//		const PositionInfo* pInfo = const_cast<const Container*>(parentContainer)->getPositionInfo();
//
//		Rectangle topLeftRect, topLeftAvailableRect;
//		Rectangle bottomRightRect, bottomRightAvailableRect;
//
//		topLeftRect.x = pInfo->posRectangle.x;
//		topLeftRect.y = pInfo->posRectangle.y;
//		topLeftRect.width = currentSettings->getSpacingLeft();
//		topLeftRect.height = currentSettings->getSpacingTop();
//		topLeftAvailableRect = pInfo->intersectionRectangle.intersect(topLeftRect);
//
//		bottomRightRect.x = topLeftRect.x + pInfo->posRectangle.width;
//		bottomRightRect.y = topLeftRect.y + pInfo->posRectangle.height;
//		bottomRightRect.x -= currentSettings->getSpacingRight();
//		bottomRightRect.y -= currentSettings->getSpacingBottom();
//		bottomRightRect.width = currentSettings->getSpacingRight();
//		bottomRightRect.height = currentSettings->getSpacingBottom();
//		bottomRightAvailableRect = pInfo->intersectionRectangle.intersect(bottomRightRect);
//
//		Rectangle availableSpace = pInfo->intersectionRectangle;
//		availableSpace.x += topLeftAvailableRect.width;
//		availableSpace.y += topLeftAvailableRect.height;
//		availableSpace.width -= (topLeftAvailableRect.width + bottomRightAvailableRect.width);
//		availableSpace.height -= (topLeftAvailableRect.height + bottomRightAvailableRect.height);
//
//		currentAlternative->step2B_determineCutRectangles(availableSpace);
//	}
//
//
//	void Transition::step2C_addToDrawableMap(DrawableMap* drawables)
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		currentAlternative->step2C_addToDrawableMap(drawables);
//	}
//
//
//	PositionInfo* Transition::getPositionInfo()
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->getPositionInfo();
//	}
//
//
//	Vector Transition::getAvailableMaximization(Settings::IterationMode mode) const
//	{
//		if(currentAlternative == nullptr)
//			throw std::exception();
//		return currentAlternative->getAvailableMaximization(mode);
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
