#include "../include/ilslibsfml_window.hpp"



/*----------------------------------------------------------------------------------
										ILSLibSFML
----------------------------------------------------------------------------------*/
namespace ILSLibSFML
{



	Window::Window(ILSLib::ResourceManager* resManager):
		windowTitle(),
		videoMode(),
		frameUpdateInterval(100),
		closeWindowFlag(false),
		clock(),
		winSizeTransformations(),
		parser(),
		drawWizard(),
		eventQueue(),
		drawableMap(),
		blockManager(),
		resourceManager(resManager),
		renderWindow(nullptr)
	{
		if(resourceManager == nullptr)
			throw std::exception();
	}


	Window::~Window()
	{
		close();
	}


	bool Window::isOpen() const
	{
		if(renderWindow == nullptr)
			return false;
		if(renderWindow->isOpen() == false)
			return false;
		return true;
	}


	void Window::newWindow(const sf::VideoMode& vMode, const std::string& title, const bool fullScreen)
	{
		close();

		videoMode = vMode;
		windowTitle = title;

		closeWindowFlag = false;
		clock.restart();
		winSizeTransformations.scale(1.0f, 1.0f);
		parser.resetEverything();
		eventQueue.clear();
		drawableMap.clear();

		if(fullScreen == true)
			renderWindow = new sf::RenderWindow(videoMode, windowTitle, sf::Style::Fullscreen);
		else
			renderWindow = new sf::RenderWindow(videoMode, windowTitle);
	}


	void Window::close(bool closeOnUpdate)
	{
		closeWindowFlag = true;
		if(closeOnUpdate == false)
			finalizeCloseWindow();
	}


	void Window::pollEvents(const std::string& root, unsigned int maxEvents)
	{
		if(isOpen() == false)
			return;

		sf::Time eventTime = parser.getTime();

		// parse routine events
		parser.parseSFMLEvent(root, nullptr, eventTime, blockManager, eventQueue);

		// parse new events
		unsigned int eventCounter = 0;
        while(true)
        {
			sf::Event event;
        	if(maxEvents < 1)
			{
				if(renderWindow->pollEvent(event) == false)
					break;
			}
			else if(eventCounter < maxEvents)
			{
				if(renderWindow->pollEvent(event) == false)
					break;
			}

			parser.parseSFMLEvent(root, &event, eventTime, blockManager, eventQueue);

			// check the type of the event
			switch (event.type)
			{
				// window closed
				case sf::Event::Closed:
					closeWindowFlag = true;
				break;

				// window resized
				case sf::Event::Resized:
					/*winSizeTransformations.scale(((double)windowWidth) / ((double)event.size.width),
								((double)windowHeight) / ((double)event.size.height));*/

					videoMode = sf::VideoMode(event.size.width, event.size.height);
					renderWindow->setView(sf::View(sf::FloatRect(0, 0, videoMode.width, videoMode.height)));
					updateDrawableMap(root);
				break;

				default:
				break;
			}

			if(maxEvents > 0)
				++eventCounter;
        }
	}


	void Window::parseEvents(const std::string& root, unsigned int maxEvents)
	{
		unsigned int eventCounter = 0;
        while(true)
        {
			if(maxEvents < 1)
			{
				if(eventQueue.hasEvents() == false)
					break;
			}
			else if(eventCounter < maxEvents)
			{
				if(eventQueue.hasEvents() == false)
					break;
			}

			eventQueue.parseNextEvent();
			updateDrawableMap(root);

			if(maxEvents > 0)
				++eventCounter;
		}
	}


	void Window::updateDrawableMap(const std::string& root)
	{
		if(isOpen() == false)
			return;

		ILSLib::Vector videoModeSize(videoMode.width, videoMode.height);
		blockManager.calculateDPInfo(root, &drawableMap, videoModeSize);
	}


	void Window::updateView()
	{
		if(isOpen() == false)
			return;
		if(closeWindowFlag == true)
		{
			finalizeCloseWindow();
			return;
		}

		sf::Time elapsedTime = clock.getElapsedTime();
		if(elapsedTime.asMilliseconds() > frameUpdateInterval)
		{
			clock.restart();
			renderWindow->clear();

			std::pair<sf::RenderWindow*, sf::Transform*> renderPair(renderWindow, &winSizeTransformations);

			drawableMap.drawAll(&drawWizard, resourceManager, &renderPair);
			renderWindow->display();
		}
	}


	void Window::resetTitle(const std::string& title)
	{
		if(isOpen() == false)
			return;

		windowTitle = title;
		renderWindow->setTitle(title);
	}


	unsigned int Window::getMinWidth() const
	{
		return 640;
	}


	unsigned int Window::getMinHeight() const
	{
		return 480;
	}


	const ILSLib::BlockManager& Window::getBlockManager() const
	{
		return blockManager;
	}


	ILSLib::BlockManager& Window::getBlockManager()
	{
		return blockManager;
	}


	const std::vector<sf::VideoMode>& Window::getVideoModes() const
	{
		return sf::VideoMode::getFullscreenModes();
	}


	const sf::VideoMode Window::getDesktopVideoMode() const
	{
		return sf::VideoMode::getDesktopMode();
	}


	const sf::VideoMode Window::getCurrentVideoMode() const
	{
		return videoMode;
	}


	void Window::finalizeCloseWindow()
	{
		if(closeWindowFlag == false)
			return;

		closeWindowFlag = false;

		if(isOpen() == false)
			return;

		renderWindow->close();
		delete renderWindow;
		renderWindow = nullptr;
	}



} // end namespace ILSLibSFML
//----------------------------------------------------------------------------------





