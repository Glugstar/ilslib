#include "../include/ilslib_tests1.hpp"



bool getBitValue(unsigned int index, unsigned int value);
unsigned int getMaxValue(unsigned int nBits);

void createTestGroupA(BlockManager& manager, FlowContainerSettings* baseSettings,
                      const std::string rootName);


void createTestSubGroupA(BlockManager& manager, const std::string blockName,
                         FlowContainerSettings* baseSettings, const std::string rootName);


void createTestABlock1(BlockManager& manager, const std::string blockName,
                       FlowContainerSettings* baseSettings, const std::string rootName);
void createTestABlock2(BlockManager& manager, const std::string blockName,
                       FlowContainerSettings* baseSettings, const std::string rootName);


void addTestBlocksA1(BlockManager& manager,
                     const std::string blockName, const std::string blockPath,
                     const int total,
                     const int startingX = 0, const int startingY = 0);
void addTestBlocksA2(BlockManager& manager,
                     const std::string blockName, const std::string blockPath,
                     const int total,
                     const int startingX = 0, const int startingY = 0);



bool getBitValue(unsigned int index, unsigned int value)
{
	if(index >= sizeof(unsigned int) * 8)
		return false;
		
	unsigned int bitMask = 1;
	bitMask = bitMask << index;
	
	return (value & bitMask) != 0;
}

unsigned int getMaxValue(unsigned int nBits)
{
	if(nBits >= sizeof(unsigned int) * 8)
		return 0;
		
	unsigned int result = 1;
	for(unsigned int i=0; i<nBits; ++i)
		result *= 2;
		
	return result;
}

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
	//baseSettings.horizontalAlignment = Settings::Alignment::CenterAlignment;
	//baseSettings.verticalAlignment = Settings::Alignment::CenterAlignment;
	//baseSettings.verticalAlignment = Settings::Alignment::BottomAlignment;
	
	createTestGroupA(manager, &baseSettings, rootName);
}


void createTestGroupA(BlockManager& manager, FlowContainerSettings* baseSettings,
                      const std::string rootName)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.horizontalGravity = Settings::Gravity::LeftGravity;
	newSettings.verticalGravity = Settings::Gravity::TopGravity;
	newSettings.horizontalFlow = Settings::Flow::LeftToRightFlow;
	newSettings.verticalFlow = Settings::Flow::TopToBottomFlow;
	
	createTestSubGroupA(manager, "group1#1", &newSettings, rootName);
}


void createTestSubGroupA(BlockManager& manager, const std::string blockName,
                         FlowContainerSettings* baseSettings, const std::string rootName)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	unsigned int maxValue1 = getMaxValue(3);
	
	for(unsigned int i=0; i<maxValue1; ++i)
	{
		newSettings.equalCellWidth = getBitValue(0, i);
		newSettings.equalCellHeight = getBitValue(1, i);
		newSettings.axisPriority = getBitValue(2, i) ?
		                           Settings::AxisPriority::VerticalFirst :
		                           Settings::AxisPriority::HorizontalFirst;
		                           
		createTestABlock1(manager, blockName + "#block" + std::to_string(i+1), &newSettings, rootName);
	}
	
	newSettings.equalCellWidth = false;
	newSettings.equalCellHeight = false;
	newSettings.axisPriority = Settings::AxisPriority::HorizontalFirst;
	unsigned int maxValue2 = getMaxValue(2);
	
	for(unsigned int i=0; i<maxValue2; ++i)
	{
		newSettings.horizontalSizePolicy = getBitValue(0, i) ?
		                                   Settings::SizePolicy::Minimize :
		                                   Settings::SizePolicy::Maximize;
		newSettings.verticalSizePolicy = getBitValue(1, i) ?
		                                 Settings::SizePolicy::Minimize :
		                                 Settings::SizePolicy::Maximize;
		                                 
		createTestABlock2(manager, blockName + "#block" + std::to_string(i+maxValue1+1), &newSettings, rootName);
	}
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




