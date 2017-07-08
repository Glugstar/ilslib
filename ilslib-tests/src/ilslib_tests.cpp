#include "../include/ilslib_tests.hpp"


void arrowCallbackFunc(Listener* listener, BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue)
{
	(void)listener;
	(void)block;
	(void)eventQueue;
	
	const KeyboardEvent* event = (const KeyboardEvent*)eventInfo;
	
	std::string actualKeyCode = event->getKeyCode();
	std::string leftKeyCode, rightKeyCode;
	
	leftKeyCode = KeyboardEvent::generateKeyCode<sf::Keyboard::Key>(sf::Keyboard::Left);
	rightKeyCode = KeyboardEvent::generateKeyCode<sf::Keyboard::Key>(sf::Keyboard::Right);
	
	if(actualKeyCode == leftKeyCode)
		changeTestGroup(blockManager, -1);
	else if(actualKeyCode == rightKeyCode)
		changeTestGroup(blockManager, 1);
}


void ctrlADCallbackFunc(Listener* listener, BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue)
{
	(void)listener;
	(void)block;
	(void)eventQueue;
	
	static int lastTime = 0;
	int pressTime;
	int changeInterval = 250;
	
	const KeyboardEvent* event = (const KeyboardEvent*)eventInfo;
	if(event == nullptr)
		return;
	if(event->getType() != KeyboardEvent::Type::Hold)
		return;
	pressTime = event->getEventTime();
	if(pressTime - lastTime <= changeInterval)
		return;
	
	const KeyboardEvent::KeysHistory& keys = event->getKeysHistory();
	if(keys.size() != 2)
		return;
	
	std::string aKeyCode, dKeyCode, ctrlKeyCode;
	bool aPressed, dPressed, ctrlPressed;
	aPressed = dPressed = ctrlPressed = false;
	
	aKeyCode = KeyboardEvent::generateKeyCode<sf::Keyboard::Key>(sf::Keyboard::Key::A);
	dKeyCode = KeyboardEvent::generateKeyCode<sf::Keyboard::Key>(sf::Keyboard::Key::D);
	ctrlKeyCode = KeyboardEvent::generateKeyCode<sf::Keyboard::Key>(sf::Keyboard::Key::LControl);
	
	KeyboardEvent::KeysHistory::const_iterator i;
	for(i=keys.begin(); i!=keys.end(); ++i)
	{
		if(i->first == aKeyCode)
			aPressed = true;
		else if(i->first == dKeyCode)
			dPressed = true;
		else if(i->first == ctrlKeyCode)
			ctrlPressed = true;
	}
	
	if(ctrlPressed == false)
		return;
	
	lastTime = event->getEventTime();
	
	if(aPressed == true)
		changeTestGroup(blockManager, -1);
	else if(dPressed == true)
		changeTestGroup(blockManager, 1);
}


int changeTestGroup(BlockManager* blockManager, int offset)
{
	static int currentAlternative = 0;
	
	if(offset == 0)
		return currentAlternative;
	
	std::string rootName = "Root";
	std::string baseAltName = "TestGroup";
	int totalAlts = 18;
	
	currentAlternative += offset;
	currentAlternative += totalAlts;
	currentAlternative %= totalAlts;
	
	std::string altID = rootName + "." + baseAltName + Support::NumberToString(currentAlternative + 1);
	//blockManager->transitionToAlternative(altID);
	
	return currentAlternative;
}


void createAllTestsA(BlockManager& manager, const std::string rootName, const std::string baseAltName)
{
	FlowContainer* root = new FlowContainer(rootName);
	manager.addBasicBlock("", root);
	
	/*for(int i=1; i<19; ++i)
		manager.addAlternative(rootName, new Alternative(baseAltName + Support::NumberToString(i),
														rootName + "Layer"));*/
	
	root->setStyle(manager.getContainerStyle("basic"));
	//root->setModelIndex(1, 0, 0.0f);
	root->getFlowContainerSettings()->loadInnerSpacing(root->getStyle());
	
	root->getFlowContainerSettings()->cellSpacingWidth = 2;
	root->getFlowContainerSettings()->cellSpacingHeight = 2;
	root->getFlowContainerSettings()->autoLineWrap = true;
	
	std::set<std::string> arrowKeyCodes;
	std::set<std::string> ctrlADKeyCodes;
	arrowKeyCodes.insert(KeyboardEvent::generateKeyCode<>(sf::Keyboard::Key::Left));
	arrowKeyCodes.insert(KeyboardEvent::generateKeyCode<>(sf::Keyboard::Key::Right));
	ctrlADKeyCodes.insert(KeyboardEvent::generateKeyCode<>(sf::Keyboard::Key::A));
	ctrlADKeyCodes.insert(KeyboardEvent::generateKeyCode<>(sf::Keyboard::Key::D));
	ctrlADKeyCodes.insert(KeyboardEvent::generateKeyCode<>(sf::Keyboard::Key::LControl));
	
	KeyboardListener arrowListener("arrowListener");
	KeyboardListener ctrlADListener("ctrlADListener");
	arrowListener.setTypeTrigger(KeyboardEvent::Type::Release);
	arrowListener.setKeyCodesTrigger(arrowKeyCodes);
	arrowListener.setCallbackFunction(arrowCallbackFunc);
	ctrlADListener.setTypeTrigger(KeyboardEvent::Type::Hold);
	ctrlADListener.setKeyCodesTrigger(ctrlADKeyCodes);
	ctrlADListener.setCallbackFunction(ctrlADCallbackFunc);
	
	root->getListenerManager().addListener(arrowListener);
	root->getListenerManager().addListener(ctrlADListener);
	
	FlowContainerSettings baseSettings;
	
	baseSettings.autoLineWrap = true;
	baseSettings.cellSpacingWidth = 10;
	baseSettings.cellSpacingHeight = 10;
	baseSettings.horizontalAlignment = Settings::Alignment::CenterAlignment;
	baseSettings.verticalAlignment = Settings::Alignment::CenterAlignment;
	
	createTestAGroup1(manager, &baseSettings, rootName);
	/*createTestAGroup2(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(2) + "." + rootName + "Layer");
	createTestAGroup3(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(3) + "." + rootName + "Layer");
	createTestAGroup4(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(4) + "." + rootName + "Layer");
	createTestAGroup5(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(5) + "." + rootName + "Layer");
	createTestAGroup6(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(6) + "." + rootName + "Layer");
	createTestAGroup7(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(7) + "." + rootName + "Layer");
	createTestAGroup8(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(8) + "." + rootName + "Layer");
	createTestAGroup9(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(9) + "." + rootName + "Layer");
	createTestAGroup10(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(10) + "." + rootName + "Layer");
	createTestAGroup11(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(11) + "." + rootName + "Layer");
	createTestAGroup12(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(12) + "." + rootName + "Layer");
	createTestAGroup13(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(13) + "." + rootName + "Layer");
	createTestAGroup14(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(14) + "." + rootName + "Layer");
	createTestAGroup15(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(15) + "." + rootName + "Layer");
	createTestAGroup16(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(16) + "." + rootName + "Layer");
	createTestAGroup17(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(17) + "." + rootName + "Layer");
	createTestAGroup18(manager, &baseSettings, rootName + "." + baseAltName + Support::NumberToString(18) + "." + rootName + "Layer");*/
}


void createTestAGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group1#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group1#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group1#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group1#4", &newSettings, rootLayer);
}


void createTestAGroup2(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group2#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group2#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group2#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group2#4", &newSettings, rootLayer);
}


void createTestAGroup3(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group3#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group3#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group3#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group3#4", &newSettings, rootLayer);
}


void createTestAGroup4(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group4#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group4#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group4#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group4#4", &newSettings, rootLayer);
}


void createTestAGroup5(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group5#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group5#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group5#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group5#4", &newSettings, rootLayer);
}


void createTestAGroup6(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group6#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group6#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group6#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group6#4", &newSettings, rootLayer);
}


void createTestAGroup7(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group7#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group7#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group7#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group7#4", &newSettings, rootLayer);
}


void createTestAGroup8(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group8#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group8#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group8#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group8#4", &newSettings, rootLayer);
}


void createTestAGroup9(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group9#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group9#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group9#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group9#4", &newSettings, rootLayer);
}


void createTestAGroup10(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group10#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group10#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group10#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group10#4", &newSettings, rootLayer);
}


void createTestAGroup11(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group11#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group11#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group11#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group11#4", &newSettings, rootLayer);
}


void createTestAGroup12(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group12#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group12#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group12#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group12#4", &newSettings, rootLayer);
}


void createTestAGroup13(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group13#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group13#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group13#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group13#4", &newSettings, rootLayer);
}


void createTestAGroup14(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group14#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group14#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group14#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group14#4", &newSettings, rootLayer);
}


void createTestAGroup15(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group15#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group15#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group15#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group15#4", &newSettings, rootLayer);
}


void createTestAGroup16(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group16#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group16#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group16#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group16#4", &newSettings, rootLayer);
}


void createTestAGroup17(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group17#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group17#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group17#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group17#4", &newSettings, rootLayer);
}


void createTestAGroup18(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;
	
	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestASubGroup1(manager, "group18#1", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group18#2", &newSettings, rootLayer);
	
	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestASubGroup1(manager, "group18#3", &newSettings, rootLayer);
	createTestASubGroup2(manager, "group18#4", &newSettings, rootLayer);
}


void createTestASubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	createTestABlock1(manager, id + "#block1", &newSettings, rootLayer);
	createTestABlock2(manager, id + "#block2", &newSettings, rootLayer);
	createTestABlock3(manager, id + "#block3", &newSettings, rootLayer);
	createTestABlock4(manager, id + "#block4", &newSettings, rootLayer);
	createTestABlock5(manager, id + "#block5", &newSettings, rootLayer);
	createTestABlock6(manager, id + "#block6", &newSettings, rootLayer);
	createTestABlock7(manager, id + "#block7", &newSettings, rootLayer);
	createTestABlock8(manager, id + "#block8", &newSettings, rootLayer);
	createTestABlock9(manager, id + "#block9", &newSettings, rootLayer);
	createTestABlock10(manager, id + "#block10", &newSettings, rootLayer);
	createTestABlock11(manager, id + "#block11", &newSettings, rootLayer);
	createTestABlock12(manager, id + "#block12", &newSettings, rootLayer);
}


void createTestASubGroup2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainerSettings newSettings = *baseSettings;
	
	newSettings.axisPriority = Settings::AxisPriority::VerticalFirst;
	
	createTestABlock1(manager, id + "#block1", &newSettings, rootLayer);
	createTestABlock2(manager, id + "#block2", &newSettings, rootLayer);
	createTestABlock3(manager, id + "#block3", &newSettings, rootLayer);
	createTestABlock4(manager, id + "#block4", &newSettings, rootLayer);
	createTestABlock5(manager, id + "#block5", &newSettings, rootLayer);
	createTestABlock6(manager, id + "#block6", &newSettings, rootLayer);
	createTestABlock7(manager, id + "#block7", &newSettings, rootLayer);
	createTestABlock8(manager, id + "#block8", &newSettings, rootLayer);
	createTestABlock9(manager, id + "#block9", &newSettings, rootLayer);
	createTestABlock10(manager, id + "#block10", &newSettings, rootLayer);
	createTestABlock11(manager, id + "#block11", &newSettings, rootLayer);
	createTestABlock12(manager, id + "#block12", &newSettings, rootLayer);
}


void createTestABlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 160;
	baseContainer->getFlowContainerSettings()->minHeight = 160;
	baseContainer->getFlowContainerSettings()->maxHeight = 300;
	
	addTestBlocksA(manager, id, 4, baseContainer->getPath());
}


void createTestABlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 190;
	baseContainer->getFlowContainerSettings()->fixedHeight = 190;
	
	addTestBlocksA(manager, id, 12, baseContainer->getPath());
}


void createTestABlock3(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->cellSpacingHeight = 4;
	baseContainer->getFlowContainerSettings()->fixedWidth = 200;
	baseContainer->getFlowContainerSettings()->fixedHeight = 200;
	
	addTestBlocksA(manager, id, 24, baseContainer->getPath());
}


void createTestABlock4(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 200;
	baseContainer->getFlowContainerSettings()->minHeight = 200;
	baseContainer->getFlowContainerSettings()->maxHeight = 240;
	
	addTestBlocksA(manager, id, 24, baseContainer->getPath());
}


void createTestABlock5(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 200;
	baseContainer->getFlowContainerSettings()->fixedHeight = 200;
	
	addTestBlocksA(manager, id, 24, baseContainer->getPath());
}


void createTestABlock6(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 40;
	baseContainer->getFlowContainerSettings()->fixedHeight = 100;
	
	addTestBlocksA(manager, id, 1, baseContainer->getPath());
}


void createTestABlock7(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 30;
	baseContainer->getFlowContainerSettings()->fixedHeight = 100;
}


void createTestABlock8(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->autoLineWrap = false;
	baseContainer->getFlowContainerSettings()->fixedWidth = 80;
	baseContainer->getFlowContainerSettings()->fixedHeight = 80;
	
	addTestBlocksA(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestABlock9(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->autoLineWrap = false;
	baseContainer->getFlowContainerSettings()->fixedWidth = 80;
	baseContainer->getFlowContainerSettings()->fixedHeight = 20;
	
	addTestBlocksA(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestABlock10(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 10;
	baseContainer->getFlowContainerSettings()->fixedHeight = 100;
	
	addTestBlocksA(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestABlock11(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 20;
	baseContainer->getFlowContainerSettings()->fixedHeight = 10;
	
	addTestBlocksA(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestABlock12(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(rootLayer, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;
	
	baseContainer->setStyle(manager.getContainerStyle("basic"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());
	
	baseContainer->getFlowContainerSettings()->fixedWidth = 10;
	baseContainer->getFlowContainerSettings()->fixedHeight = 10;
	
	baseContainer->getFlowContainerSettings()->postNewLine = true;
	
	addTestBlocksA(manager, id, 3, baseContainer->getPath(), 5);
}


void addTestBlocksA(BlockManager& manager, const std::string id,
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





