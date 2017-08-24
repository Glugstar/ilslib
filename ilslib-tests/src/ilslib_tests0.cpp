#include "../include/ilslib_tests0.hpp"



void createBasicDisplay(BlockManager& manager, const std::string rootName)
{
	FlowContainer* root = new FlowContainer(rootName);
	manager.addRoot(root);

	root->setStyle(manager.getContainerStyle("window"));
	root->getFlowContainerSettings()->loadInnerSpacing(root->getStyle());

	root->getFlowContainerSettings()->autoLineWrap = true;
	root->getFlowContainerSettings()->innerSpacingLeft = 50;
	root->getFlowContainerSettings()->innerSpacingRight = 50;
	root->getFlowContainerSettings()->innerSpacingTop = 50;
	root->getFlowContainerSettings()->innerSpacingBottom = 50;
	root->getFlowContainerSettings()->cellSpacingWidth = 50;
	root->getFlowContainerSettings()->cellSpacingHeight = 50;

	FlowContainer* container;

	container = new FlowContainer("c1");
    container->setStyle(manager.getContainerStyle("red"));
    container->getSettings()->minWidth = 50;
    container->getSettings()->minHeight = 50;
    manager.addBasicBlock(rootName, container);

	container = new FlowContainer("c2");
    container->setStyle(manager.getContainerStyle("green"));
    container->getSettings()->minWidth = 100;
    container->getSettings()->minHeight = 100;
    manager.addBasicBlock(rootName, container);

	container = new FlowContainer("c3");
    container->setStyle(manager.getContainerStyle("blue"));
    container->getSettings()->minWidth = 150;
    container->getSettings()->minHeight = 150;
    manager.addBasicBlock(rootName, container);
}
