#include "../include/ilslib_tests1.hpp"



void createAllTestsA(BlockManager& manager, const std::string rootName)
{
	FlowContainer* root = new FlowContainer(rootName);
	manager.addRoot(root);

	root->setStyle(manager.getContainerStyle("window"));
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

	createTestAGroup1(manager, &baseSettings, rootName);
}


void createTestAGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.horizontalGravity = Settings::Gravity::LeftGravity;
	newSettings.verticalGravity = Settings::Gravity::TopGravity;
	newSettings.horizontalFlow = Settings::Flow::LeftToRightFlow;
	newSettings.verticalFlow = Settings::Flow::TopToBottomFlow;

	createTestASubGroup1(manager, "group1#1", &newSettings, rootName);
}


void createTestASubGroup1(BlockManager& manager, const std::string blockName,
					FlowContainerSettings* baseSettings, const std::string rootName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.axisPriority = Settings::AxisPriority::HorizontalFirst;
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;
	createTestABlock1(manager, blockName + "#block1", &newSettings, rootName);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = false;
	createTestABlock1(manager, blockName + "#block2", &newSettings, rootName);
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = true;
	createTestABlock1(manager, blockName + "#block3", &newSettings, rootName);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = true;
	createTestABlock1(manager, blockName + "#block4", &newSettings, rootName);

	newSettings.axisPriority = Settings::AxisPriority::VerticalFirst;
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;
	createTestABlock1(manager, blockName + "#block5", &newSettings, rootName);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = false;
	createTestABlock1(manager, blockName + "#block6", &newSettings, rootName);
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = true;
	createTestABlock1(manager, blockName + "#block7", &newSettings, rootName);
	newSettings.equalCellWidth = true;
	newSettings.equalCellHeight = true;
	createTestABlock1(manager, blockName + "#block8", &newSettings, rootName);

	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;

	newSettings.axisPriority = Settings::AxisPriority::HorizontalFirst;
	newSettings.horizontalSizePolicy = Settings::SizePolicy::Maximize;
	newSettings.verticalSizePolicy = Settings::SizePolicy::Maximize;
	createTestABlock2(manager, blockName + "#block9", &newSettings, rootName);
	newSettings.verticalSizePolicy = Settings::SizePolicy::Minimize;
	createTestABlock2(manager, blockName + "#block10", &newSettings, rootName);
}


void createTestABlock1(BlockManager& manager, const std::string blockName,
					FlowContainerSettings* baseSettings, const std::string rootName)
{
	FlowContainer* baseFlowContainer = new FlowContainer(blockName);
	manager.addBasicBlock(rootName, baseFlowContainer);
	(*baseFlowContainer->getFlowContainerSettings()) = *baseSettings;

	baseFlowContainer->setStyle(manager.getContainerStyle("container"));
	baseFlowContainer->getFlowContainerSettings()->loadInnerSpacing(baseFlowContainer->getStyle());

	baseFlowContainer->getFlowContainerSettings()->minWidth = 40;
	baseFlowContainer->getFlowContainerSettings()->maxWidth = 200;
	baseFlowContainer->getFlowContainerSettings()->minHeight = 160;
	baseFlowContainer->getFlowContainerSettings()->maxHeight = 300;

	addTestBlocksA1(manager, blockName, baseFlowContainer->getPath(), 12);
}


void createTestABlock2(BlockManager& manager, const std::string blockName,
					FlowContainerSettings* baseSettings, const std::string rootName)
{
	FlowContainer* baseFlowContainer = new FlowContainer(blockName);
	manager.addBasicBlock(rootName, baseFlowContainer);
	(*baseFlowContainer->getFlowContainerSettings()) = *baseSettings;

	baseFlowContainer->setStyle(manager.getContainerStyle("container"));
	baseFlowContainer->getFlowContainerSettings()->loadInnerSpacing(baseFlowContainer->getStyle());

	baseFlowContainer->getFlowContainerSettings()->minWidth = 100;
	baseFlowContainer->getFlowContainerSettings()->minHeight = 100;

	addTestBlocksA2(manager, blockName, baseFlowContainer->getPath(), 12);
}


void addTestBlocksA1(BlockManager& manager,
                    const std::string blockName, const std::string blockPath,
					const int total, const int startingX, const int startingY)
{
	FlowContainer* container[100];
	std::string subID;
	std::string style;

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
		subID = blockName + "#c" + Support::NumberToString(i);
		style = "";
		if(i % 4 == 0)
			style = "red";
		else if(i % 4 == 1)
			style = "green";
		else if(i % 4 == 2)
			style = "blue";
		else if(i % 4 == 3)
			style = "white";

		container[i] = new FlowContainer(subID);
		container[i]->setStyle(manager.getContainerStyle(style));
		container[i]->getSettings()->minWidth = cWidths[(i + startingX) % maxValuesX];
		container[i]->getSettings()->minHeight = cHeights[(i + startingY) % maxValuesY];
		manager.addBasicBlock(blockPath, container[i]);
	}
}


void addTestBlocksA2(BlockManager& manager,
                    const std::string blockName, const std::string blockPath,
					const int total, const int startingX, const int startingY)
{
	FlowContainer* container[100];
	//TextComponent* text;
	std::string subID;
	std::string style;

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
		subID = blockName + "#c" + Support::NumberToString(i);
		style = "";
		if(i % 4 == 0)
			style = "red";
		else if(i % 4 == 1)
			style = "green";
		else if(i % 4 == 2)
			style = "blue";
		else if(i % 4 == 3)
			style = "white";

		container[i] = new FlowContainer(subID);
		container[i]->setStyle(manager.getContainerStyle(style));
		container[i]->getSettings()->minWidth = cWidths[(i + startingX) % maxValuesX];
		container[i]->getSettings()->minHeight = cHeights[(i + startingY) % maxValuesY];
		manager.addBasicBlock(blockPath, container[i]);
	}

	/*subID = id + "#c" + Support::NumberToString(i);
	text = new TextComponent(subID);

	text->text = "Hello!";
	text->fontID = "Philosopher";
	text->textSize = 16;
	text->textColor = Color(192, 0, 0);

	manager.addBasicBlock(rootName, text);*/
}




