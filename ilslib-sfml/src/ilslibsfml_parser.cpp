#include "../include/ilslibsfml_parser.hpp"



/*----------------------------------------------------------------------------------
										ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	Parser::Parser():
		clock(),
		keysHistory(),
		buttonsHistory(),
		lastKeyboardEventTime(),
		lastTimeEventTime(),
		maxDoubleClickSpeedMS(500),
		maxClickDistancePixels(5),
		lastMouseCoordX(0),
		lastMouseCoordY(0)
	{
	}


	Parser::~Parser()
	{
	}


	sf::Time Parser::getTime() const
	{
		return clock.getElapsedTime();
	}


	void Parser::resetEverything()
	{
		clock.restart();
		keysHistory.clear();
		buttonsHistory.clear();
		lastKeyboardEventTime = sf::milliseconds(0);
		lastTimeEventTime = sf::milliseconds(0);
	}


	void Parser::parseSFMLEvent(const std::string& root, const sf::Event* event, sf::Time eventTime,
							ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		if(event == nullptr)
			parseNoEvent(root, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::TextEntered)
			parseTextEntered(root, *event, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::KeyPressed)
			parseKeyPressed(root, *event, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::KeyReleased)
			parseKeyReleased(root, *event, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::MouseMoved)
			parseMouseMoved(root, *event, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::MouseButtonPressed)
			parseMouseButtonPressed(root, *event, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::MouseButtonReleased)
			parseMouseButtonReleased(root, *event, eventTime, blockManager, eventQueue);
		else if(event->type == sf::Event::MouseWheelMoved)
			parseMouseWheelMoved(root, *event, eventTime, blockManager, eventQueue);
		else
			parseWindow(root, *event, eventTime, blockManager, eventQueue);
	}


	void Parser::parseNoEvent(const std::string& root, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		// parse routine elapsed time
		int msEventTime = eventTime.asMilliseconds();
		if(msEventTime > lastTimeEventTime.asMilliseconds())
		{
			ILSLib::TimeEvent ilsEvent;
			ilsEvent.setEventTime(msEventTime);
			ilsEvent.setEventLastTime(lastTimeEventTime.asMilliseconds());
			blockManager.parseEvent(root, ilsEvent, eventQueue);
		}


		// parse mouse hovering
		ILSLib::MouseEvent ilsEvent;
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(lastTimeEventTime.asMilliseconds());
		ilsEvent.setType(ILSLib::MouseEvent::Type::Hover);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);
		blockManager.parseEvent(root, ilsEvent, eventQueue);


		// parse mouse buttons held pressed
		if(buttonsHistory.size() > 0)
		{
			ILSLib::MouseEvent ilsEvent;
			ilsEvent.setEventTime(msEventTime);
			ilsEvent.setEventLastTime(lastTimeEventTime.asMilliseconds());
			ilsEvent.setType(ILSLib::MouseEvent::Type::Hold);
			ilsEvent.setButtonsHistory(buttonsHistory);
			ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);
			blockManager.parseEvent(root, ilsEvent, eventQueue);
		}


		// parse keyboard keys held pressed
		if(keysHistory.size() > 0)
		{
			ILSLib::KeyboardEvent ilsEvent;
			ilsEvent.setEventTime(msEventTime);
			ilsEvent.setEventLastTime(lastKeyboardEventTime.asMilliseconds());
			ilsEvent.setType(ILSLib::KeyboardEvent::Type::Hold);
			ilsEvent.setKeysHistory(keysHistory);
			blockManager.parseEvent(root, ilsEvent, eventQueue);
		}

		lastTimeEventTime = eventTime;
	}


	void Parser::parseWindow(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::WindowEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		ILSLib::WindowEvent::Type type;
		if(event.type == sf::Event::Closed)
			type = ILSLib::WindowEvent::Type::Closed;
		else if(event.type == sf::Event::Resized)
		{
			ilsEvent.setWindowWidth(event.size.width);
			ilsEvent.setWindowHeight(event.size.height);
			type = ILSLib::WindowEvent::Type::Resized;
		}
		else if(event.type == sf::Event::LostFocus)
			type = ILSLib::WindowEvent::Type::LostFocus;
		else if(event.type == sf::Event::GainedFocus)
			type = ILSLib::WindowEvent::Type::GainedFocus;
		else
			return;

		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(lastKeyboardEventTime.asMilliseconds());
		ilsEvent.setType(type);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseTextEntered(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::KeyboardEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		wchar_t textChar = event.text.unicode;

		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(lastKeyboardEventTime.asMilliseconds());
		ilsEvent.setTextChar(textChar);
		ilsEvent.setType(ILSLib::KeyboardEvent::Type::TextEntered);
		ilsEvent.setKeysHistory(keysHistory);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseKeyPressed(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::KeyboardEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		std::string keyCode = ILSLib::KeyboardEvent::generateKeyCode(event.key.code);

		removeKey(keyCode);
		keysHistory.push_back(ILSLib::KeyboardEvent::KeyDetails(keyCode, msEventTime));

		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(lastKeyboardEventTime.asMilliseconds());
		ilsEvent.setKeyCode(keyCode);
		ilsEvent.setType(ILSLib::KeyboardEvent::Type::Press);
		ilsEvent.setKeysHistory(keysHistory);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
		lastKeyboardEventTime = eventTime;
	}


	void Parser::parseKeyReleased(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::KeyboardEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		std::string keyCode = ILSLib::KeyboardEvent::generateKeyCode(event.key.code);

		removeKey(keyCode);

		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(lastKeyboardEventTime.asMilliseconds());
		ilsEvent.setKeyCode(keyCode);
		ilsEvent.setType(ILSLib::KeyboardEvent::Type::Release);
		ilsEvent.setKeysHistory(keysHistory);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseMouseMoved(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		lastMouseCoordX = event.mouseMove.x;
		lastMouseCoordY = event.mouseMove.y;

		ilsEvent.setType(ILSLib::MouseEvent::Type::Move);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		blockManager.parseEvent(root, ilsEvent, eventQueue);

		parseMouseDrag(root, eventTime, blockManager, eventQueue);
	}


	void Parser::parseMouseButtonPressed(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		sf::Mouse::Button sfmlButton = event.mouseButton.button;
		ILSLib::MouseButton::Button ilslibButton;
		if(sfmlButton == sf::Mouse::Button::Left)
			ilslibButton = ILSLib::MouseButton::Button::Left;
		else if(sfmlButton == sf::Mouse::Button::Right)
			ilslibButton = ILSLib::MouseButton::Button::Right;
		else if(sfmlButton == sf::Mouse::Button::Middle)
			ilslibButton = ILSLib::MouseButton::Button::Middle;
		lastMouseCoordX = event.mouseButton.x;
		lastMouseCoordY = event.mouseButton.y;

		ILSLib::MouseButton::ButtonAction latestAction;
		latestAction.actionTime = msEventTime;
		latestAction.coordX = lastMouseCoordX;
		latestAction.coordY = lastMouseCoordY;
		updateButton(ilslibButton, latestAction, ILSLib::MouseEvent::Type::Press);

		ilsEvent.setType(ILSLib::MouseEvent::Type::Press);
		ilsEvent.setButton(ilslibButton);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		blockManager.parseEvent(root, ilsEvent, eventQueue);

		parseMouseDoubleClickPress(root, eventTime, ilslibButton, blockManager, eventQueue);
	}


	void Parser::parseMouseButtonReleased(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		sf::Mouse::Button sfmlButton = event.mouseButton.button;
		ILSLib::MouseButton::Button ilslibButton;
		if(sfmlButton == sf::Mouse::Button::Left)
			ilslibButton = ILSLib::MouseButton::Button::Left;
		else if(sfmlButton == sf::Mouse::Button::Right)
			ilslibButton = ILSLib::MouseButton::Button::Right;
		else if(sfmlButton == sf::Mouse::Button::Middle)
			ilslibButton = ILSLib::MouseButton::Button::Middle;
		lastMouseCoordX = event.mouseButton.x;
		lastMouseCoordY = event.mouseButton.y;

		ILSLib::MouseButton::ButtonAction latestAction;
		latestAction.actionTime = msEventTime;
		latestAction.coordX = lastMouseCoordX;
		latestAction.coordY = lastMouseCoordY;
		updateButton(ilslibButton, latestAction, ILSLib::MouseEvent::Type::Release);

		ilsEvent.setType(ILSLib::MouseEvent::Type::Release);
		ilsEvent.setButton(ilslibButton);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		blockManager.parseEvent(root, ilsEvent, eventQueue);

		parseMouseClick(root, eventTime, ilslibButton, blockManager, eventQueue);
		parseMouseDoubleClickRelease(root, eventTime, ilslibButton, blockManager, eventQueue);
	}


	void Parser::parseMouseWheelMoved(const std::string& root, const sf::Event& event, sf::Time eventTime,
				ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		int wheelTicks = event.mouseWheel.delta;
		lastMouseCoordX = event.mouseWheel.x;
		lastMouseCoordY = event.mouseWheel.y;

		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		if(wheelTicks > 0)
		{
			ilsEvent.setType(ILSLib::MouseEvent::Type::WheelUp);
			ilsEvent.setWheelQuantity(wheelTicks);
		}
		else if(wheelTicks < 0)
		{
			ilsEvent.setType(ILSLib::MouseEvent::Type::WheelDown);
			ilsEvent.setWheelQuantity(-wheelTicks);
		}
		else
			return;

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseMouseDrag(const std::string& root, sf::Time eventTime,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();

		ilsEvent.setType(ILSLib::MouseEvent::Type::Drag);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		if(ilsEvent.getPressedButtons().size() < 1)
			return;

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseMouseClick(const std::string& root, sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		const ILSLib::MouseButton* buttonDetails = getButton(button);

		if(buttonDetails == nullptr)
			return;
		if(buttonDetails->validClickTiming(-1) == false)
			return;
		if(buttonDetails->validClickArea(maxClickDistancePixels) == false)
			return;

		ilsEvent.setType(ILSLib::MouseEvent::Type::Click);
		ilsEvent.setButton(button);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseMouseDoubleClickPress(const std::string& root, sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		const ILSLib::MouseButton* buttonDetails = getButton(button);

		if(buttonDetails == nullptr)
			return;
		if(buttonDetails->validDoubleClickPressTiming(maxDoubleClickSpeedMS) == false)
			return;
		if(buttonDetails->validDoubleClickPressArea(maxClickDistancePixels) == false)
			return;

		ilsEvent.setType(ILSLib::MouseEvent::Type::DoubleClickPress);
		ilsEvent.setButton(button);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::parseMouseDoubleClickRelease(const std::string& root, sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue)
	{
		ILSLib::MouseEvent ilsEvent;
		int msEventTime = eventTime.asMilliseconds();
		const ILSLib::MouseButton* buttonDetails = getButton(button);

		if(buttonDetails == nullptr)
			return;
		if(buttonDetails->validDoubleClickReleaseTiming(maxDoubleClickSpeedMS) == false)
			return;
		if(buttonDetails->validDoubleClickReleaseArea(maxClickDistancePixels) == false)
			return;

		ilsEvent.setType(ILSLib::MouseEvent::Type::DoubleClickRelease);
		ilsEvent.setButton(button);
		ilsEvent.setEventTime(msEventTime);
		ilsEvent.setEventLastTime(0);
		ilsEvent.setButtonsHistory(buttonsHistory);
		ilsEvent.setCoords(lastMouseCoordX, lastMouseCoordY);

		blockManager.parseEvent(root, ilsEvent, eventQueue);
	}


	void Parser::removeKey(const std::string& keyCode)
	{
		ILSLib::KeyboardEvent::KeysHistory::iterator i, tmp;
		for(i=keysHistory.begin(); i!=keysHistory.end();)
		{
			if(i->first == keyCode)
			{
				tmp = i;
				++i;
				keysHistory.erase(tmp);
			}
			else
				++i;
		}
	}


	const ILSLib::MouseButton* Parser::getButton(ILSLib::MouseButton::Button button) const
	{
		ILSLib::MouseEvent::ButtonsHistory::const_iterator i;
		for(i=buttonsHistory.begin(); i!=buttonsHistory.end(); ++i)
			if(i->button == button)
				return &(*i);
		return nullptr;
	}


	void Parser::updateButton(ILSLib::MouseButton::Button button,
					const ILSLib::MouseButton::ButtonAction& latestAction, ILSLib::MouseEvent::Type eventType)
	{
		ILSLib::MouseEvent::ButtonsHistory::iterator i;
		for(i=buttonsHistory.begin(); i!=buttonsHistory.end(); ++i)
		{
			if(i->button == button)
			{
				if(eventType == ILSLib::MouseEvent::Type::Press)
					i->update(latestAction, true);
				else if(eventType == ILSLib::MouseEvent::Type::Release)
					i->update(latestAction, false);
				return;
			}
		}

		ILSLib::MouseButton::ButtonAction newAction;
		ILSLib::MouseButton newButton;

		newButton.button = button;
		newButton.latestPressAction = newAction;
		newButton.latestReleaseAction = newAction;
		newButton.previousPressAction = newAction;
		newButton.previousReleaseAction = newAction;

		if(eventType == ILSLib::MouseEvent::Type::Press)
			newButton.latestPressAction = latestAction;
		else if(eventType == ILSLib::MouseEvent::Type::Release)
			newButton.latestReleaseAction = latestAction;

		buttonsHistory.push_back(newButton);
	}



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------





