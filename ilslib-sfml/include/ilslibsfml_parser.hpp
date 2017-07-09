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
		virtual void parseSFMLEvent(const std::string& root, const sf::Event* event, sf::Time eventTime,
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
		virtual void parseNoEvent(const std::string& root, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseWindow(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseTextEntered(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseKeyPressed(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseKeyReleased(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseMoved(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseButtonPressed(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseButtonReleased(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseWheelMoved(const std::string& root, const sf::Event& event, sf::Time eventTime,
					ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		
		virtual void parseMouseDrag(const std::string& root, sf::Time eventTime,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseClick(const std::string& root, sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseDoubleClickPress(const std::string& root, sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		virtual void parseMouseDoubleClickRelease(const std::string& root, sf::Time eventTime, ILSLib::MouseButton::Button button,
								ILSLib::BlockManager& blockManager, ILSLib::EventQueue& eventQueue);
		
		virtual void removeKey(const std::string& keyCode);
		virtual const ILSLib::MouseButton* getButton(ILSLib::MouseButton::Button button) const;
		virtual void updateButton(ILSLib::MouseButton::Button button,
					const ILSLib::MouseButton::ButtonAction& latestAction, ILSLib::MouseEvent::Type eventType);
	};
	
	
	
} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_PARSER_HPP




