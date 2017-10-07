#include "../include/ilslib_styles.hpp"
#include "../include/ilslib_tests0.hpp"
#include "../include/ilslib_tests1.hpp"



int main()
{
	std::string rootName = "Root";
	ILSLibSFML::ResourceManager resourceManager;
	ILSLibSFML::Window window(&resourceManager);
	
	std::list<ContainerStyle*> styles = getStyles(resourceManager);
	for(std::list<ContainerStyle*>::iterator i=styles.begin(); i!=styles.end(); ++i)
		window.getBlockManager().addContainerStyle(*i);
		
	createBasicDisplay(window.getBlockManager(), rootName);
	//createAllTestsA(window.getBlockManager(), rootName);
	
	/*  TextComponent* text;
	    text = ((TextComponent*)window.getBlockManager().findBasicBlock("Root/group1#1#block15#c12"));
	    text->resManager = &resourceManager;*/
	
	sf::VideoMode vMode(1200, 900);
	window.newWindow(vMode, "My Window", false);
	window.updateDrawableMap(rootName);
	
	while(window.isOpen() == true)
	{
		window.pollEvents(rootName);
		window.parseEvents(rootName);
		window.updateView();
	}
	
	return 0;
}


