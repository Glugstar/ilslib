/*----------------------------------------------------------------------------------
								ilslibsfml_parser.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library.
----------------------------------------------------------------------------------*/
#ifndef ILSLIBSFML_PARSER_HPP
#define ILSLIBSFML_PARSER_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include "../ilslib.hpp"



/*----------------------------------------------------------------------------------
									ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Parser
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Parser
	{
	public:
		// constructors & destructor
		Parser();
		virtual ~Parser();
		
		
		// functions
		virtual sf::Time getTime() const;
		virtual void resetEverything();
		virtual void parseSFMLEvent(const sf::Event* event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
	protected:
		// variables
		sf::Clock clock;
		ILSLib::KeyboardEvent::KeysHistory keysHistory;
		ILSLib::MouseEvent::ButtonsHistory buttonsHistory;
		sf::Time lastKeyboardEventTime;
		sf::Time lastTimeEventTime;
		int maxDoubleClickSpeedMS;
		int maxClickDistancePixels;
		int lastMouseCoordX;
		int lastMouseCoordY;
		
		
		// functions
		virtual void parseNoEvent(sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseWindow(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseTextEntered(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseKeyPressed(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseKeyReleased(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseMoved(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseButtonPressed(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseButtonReleased(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseWheelMoved(const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		
		virtual void parseMouseDrag(sf::Time eventTime,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseClick(sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseDoubleClickPress(sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseDoubleClickRelease(sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		
		virtual void removeKey(const std::string& keyCode);
		virtual const ILSLib::MouseButton* getButton(ILSLib::MouseButton::Button button) const;
		virtual void updateButton(ILSLib::MouseButton::Button button,
					const ILSLib::MouseButton::ButtonAction& latestAction, ILSLib::MouseEvent::Type eventType);
	};
	
	
	
} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_PARSER_HPP




