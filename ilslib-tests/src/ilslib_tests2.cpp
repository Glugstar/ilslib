#include "../include/ilslib_tests2.hpp"



void createAllTestsB(BlockManager& manager, const std::string rootName, const std::string baseAltName)
{
	FlowContainer* root = new FlowContainer(rootName);
	manager.addBasicBlock("", root);
	
	root->setStyle(manager.getContainerStyle("basic"));
	//root->setModelIndex(1, 0, 0.0f);
	root->getFlowContainerSettings()->loadInnerSpacing(root->getStyle());
	
	root->getFlowContainerSettings()->cellSpacingWidth = 4;
	root->getFlowContainerSettings()->cellSpacingHeight = 4;
	root->getFlowContainerSettings()->autoLineWrap = true;
	
	FlowContainerSettings baseSettings;
	
	baseSettings.autoLineWrap = true;
	baseSettings.cellSpacingWidth = 10;
	baseSettings.cellSpacingHeight = 10;
	baseSettings.horizontalAlignment = Settings::Alignment::CenterAlignment;
	baseSettings.verticalAlignment = Settings::Alignment::CenterAlignment;
	
	createTestBGroup1(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(1) + "." + rootName + "Layer");
}


void createTestBGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	
	createTestBSubGroup1(manager, "group1#1", &newSettings, rootLayer);
}


void createTestBSubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.axisPriority = Settings::AxisPriority::HorizontalFirst;
	newSettings.tableNumberOfCells = 0;
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;
	createTestBBlock1(manager, id + "#block1", &newSettings, rootLayer);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = false;
	createTestBBlock1(manager, id + "#block2", &newSettings, rootLayer);
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = true;
	createTestBBlock1(manager, id + "#block3", &newSettings, rootLayer);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = true;
	createTestBBlock1(manager, id + "#block4", &newSettings, rootLayer);
	
	newSettings.axisPriority = Settings::AxisPriority::VerticalFirst;
	newSettings.tableNumberOfCells = 0;
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;
	createTestBBlock1(manager, id + "#block5", &newSettings, rootLayer);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = false;
	createTestBBlock1(manager, id + "#block6", &newSettings, rootLayer);
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = true;
	createTestBBlock1(manager, id + "#block7", &newSettings, rootLayer);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = true;
	createTestBBlock1(manager, id + "#block8", &newSettings, rootLayer);
	
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;
	
	newSettings.axisPriority = Settings::AxisPriority::HorizontalFirst;
	newSettings.tableNumberOfCells = 2;
	createTestBBlock1(manager, id + "#block9", &newSettings, rootLayer);
	newSettings.tableNumberOfCells = 3;
	createTestBBlock1(manager, id + "#block10", &newSettings, rootLayer);
	newSettings.tableNumberOfCells = 4;
	createTestBBlock1(manager, id + "#block11", &newSettings, rootLayer);
	
	newSettings.axisPriority = Settings::AxisPriority::VerticalFirst;
	newSettings.tableNumberOfCells = 2;
	createTestBBlock1(manager, id + "#block12", &newSettings, rootLayer);
	newSettings.tableNumberOfCells = 3;
	createTestBBlock1(manager, id + "#block13", &newSettings, rootLayer);
	newSettings.tableNumberOfCells = 4;
	createTestBBlock1(manager, id + "#block14", &newSettings, rootLayer);
	
	newSettings.axisPriority = Settings::AxisPriority::HorizontalFirst;
	newSettings.tableNumberOfCells = 0;
	newSettings.horizontalSizePolicy = Settings::SizePolicy::Maximize;
	newSettings.verticalSizePolicy = Settings::SizePolicy::Maximize;
	createTestBBlock2(manager, id + "#block15", &newSettings, rootLayer);
	newSettings.verticalSizePolicy = Settings::SizePolicy::Minimize;
	createTestBBlock2(manager, id + "#block16", &newSettings, rootLayer);
}


void createTestBBlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseFlowContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseFlowContainer);
	(*baseFlowContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseFlowContainer->setStyle(manager.getContainerStyle("basic"));
	baseFlowContainer->getFlowContainerSettings()->loadInnerSpacing(baseFlowContainer->getStyle());
	
	baseFlowContainer->getFlowContainerSettings()->minWidth = 40;
	baseFlowContainer->getFlowContainerSettings()->maxWidth = 200;
	baseFlowContainer->getFlowContainerSettings()->minHeight = 160;
	baseFlowContainer->getFlowContainerSettings()->maxHeight = 300;
	
	addTestBlocksB1(manager, id, 12, baseFlowContainer->getPath());
}


void createTestBBlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseFlowContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseFlowContainer);
	(*baseFlowContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseFlowContainer->setStyle(manager.getContainerStyle("basic"));
	baseFlowContainer->getFlowContainerSettings()->loadInnerSpacing(baseFlowContainer->getStyle());
	
	baseFlowContainer->getFlowContainerSettings()->minWidth = 100;
	baseFlowContainer->getFlowContainerSettings()->minHeight = 100;
	
	addTestBlocksB2(manager, id, 12, baseFlowContainer->getPath());
}


void addTestBlocksB1(BlockManager& manager, const std::string id,
					const int total, const std::string rootLayer,
					const int startingX, const int startingY)
{
	FlowContainer* container[100];
	std::string subID;
	
	#define MAX_CONTAINER_VALUES_X 7
	#define MAX_CONTAINER_VALUES_Y 9
	int maxValuesX = MAX_CONTAINER_VALUES_X;
	int maxValuesY = MAX_CONTAINER_VALUES_Y;
	int cWidths[MAX_CONTAINER_VALUES_X] = {20, 10, 50, 30, 40, 20, 30};
	int cHeights[MAX_CONTAINER_VALUES_Y] = {30, 20, 30, 10, 20, 40, 10, 20, 10};
	#undef MAX_CONTAINER_VALUES_X
	#undef MAX_CONTAINER_VALUES_Y
	
	for(int i=0; i<total; ++i)
	{
		subID = id + "#c" + Support::NumberToString(i);
		container[i] = new FlowContainer(subID);
		container[i]->setStyle(manager.getContainerStyle("basic"));
		//container[i]->setModelIndex(i % 4, 0, 0.0f);
		container[i]->getSettings()->minWidth = cWidths[(i + startingX) % maxValuesX];
		container[i]->getSettings()->minHeight = cHeights[(i + startingY) % maxValuesY];
		manager.addBasicBlock(rootLayer, container[i]);
	}
}


void addTestBlocksB2(BlockManager& manager, const std::string id,
					const int total, const std::string rootLayer,
					const int startingX, const int startingY)
{
	FlowContainer* container[100];
	//TextComponent* text;
	std::string subID;
	
	#define MAX_CONTAINER_VALUES_X 7
	#define MAX_CONTAINER_VALUES_Y 9
	int maxValuesX = MAX_CONTAINER_VALUES_X;
	int maxValuesY = MAX_CONTAINER_VALUES_Y;
	int cWidths[MAX_CONTAINER_VALUES_X] = {20, 10, 50, 30, 40, 20, 30};
	int cHeights[MAX_CONTAINER_VALUES_Y] = {30, 20, 30, 10, 20, 40, 10, 20, 10};
	#undef MAX_CONTAINER_VALUES_X
	#undef MAX_CONTAINER_VALUES_Y
	
	int i;
	for(i=0; i<total; ++i)
	{
		subID = id + "#c" + Support::NumberToString(i);
		container[i] = new FlowContainer(subID);
		container[i]->setStyle(manager.getContainerStyle("basic"));
		//container[i]->setModelIndex(i % 4, 0, 0.0f);
		container[i]->getSettings()->minWidth = cWidths[(i + startingX) % maxValuesX];
		container[i]->getSettings()->minHeight = cHeights[(i + startingY) % maxValuesY];
		manager.addBasicBlock(rootLayer, container[i]);
	}
	
	/*subID = id + "#c" + Support::NumberToString(i);
	text = new TextComponent(subID);
	
	text->text = "Hello!";
	text->fontID = "Philosopher";
	text->textSize = 16;
	text->textColor = Color(192, 0, 0);
	
	manager.addBasicBlock(rootLayer, text);*/
}




