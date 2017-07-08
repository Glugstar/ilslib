/*----------------------------------------------------------------------------------
								ilslibsfml_window.hpp
------------------------------------------------------------------------------------
Author: Alexandru Razvan Ghitu
Last modification date: ???
------------------------------------------------------------------------------------
ILS (Interface Layout Scheme) library - SFML Adapter.
----------------------------------------------------------------------------------*/
#ifndef ILSLIBSFML_WINDOW_HPP
#define ILSLIBSFML_WINDOW_HPP

#pragma once

#include "ilslibsfml_draw_wizard.hpp"
#include "ilslibsfml_parser.hpp"
#include "ilslibsfml_resource_manager.hpp"



/*----------------------------------------------------------------------------------
									ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{
	
	
	
	/*!---------------------------------------------------------------------------------
											Window
	------------------------------------------------------------------------------------
	@brief Fill in.
	*//*------------------------------------------------------------------------------*/
	class Window
	{
	public:
		// constructors & destructor
		Window(ILSLib::ResourceManager* resManager);
		virtual ~Window();
		
		
		// functions
		virtual bool isOpen() const;
		virtual void newWindow(const sf::VideoMode& vMode, const std::string& title);
		virtual void close(bool closeOnUpdate = false);
		virtual void pollEvents(unsigned int maxEvents = 0);
		virtual void parseEvents(unsigned int maxEvents = 0);
		virtual void updateDrawableMap();
		virtual void updateView();
		virtual void resetTitle(const std::string& title);
		virtual unsigned int getMinWidth() const;
		virtual unsigned int getMinHeight() const;
		virtual const ILSLib::BlockManager& getBlockManager() const;
		virtual ILSLib::BlockManager& getBlockManager();
		virtual const std::vector<sf::VideoMode>& getVideoModes() const;
		virtual const sf::VideoMode getDesktopVideoMode() const;
		virtual const sf::VideoMode getCurrentVideoMode() const;
	protected:
		// functions
		virtual void finalizeCloseWindow();
		
		
		// variables
		std::string windowTitle;
		sf::VideoMode videoMode;
		int frameUpdateInterval;
		bool closeWindowFlag;
		sf::Clock clock;
		sf::Transform winSizeTransformations;
		Parser parser;
		DrawWizard drawWizard;
		ILSLib::EventQueue eventQueue;
		ILSLib::DrawableMap drawableMap;
		ILSLib::BlockManager blockManager;
		ILSLib::ResourceManager* resourceManager;
		sf::RenderWindow* renderWindow;
	};
	
	
	
} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------



#endif // ILSLIBSFML_WINDOW_HPP




