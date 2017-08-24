#include "../include/ilslib_tests2.hpp"


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

	std::string parentContainerName = "Root";
	std::string baseAltName = "TestGroup";
	int totalAlts = 18;

	currentAlternative += offset;
	currentAlternative += totalAlts;
	currentAlternative %= totalAlts;

	std::string altID = parentContainerName + "." + baseAltName + Support::NumberToString(currentAlternative + 1);
	//blockManager->transitionToAlternative(altID);

	return currentAlternative;
}


void createAllTestsB(BlockManager& manager, const std::string parentContainerName)
{
	FlowContainer* root = new FlowContainer(parentContainerName);
	manager.addRoot(root);

	/*for(int i=1; i<19; ++i)
		manager.addAlternative(parentContainerName, new Alternative(baseAltName + Support::NumberToString(i),
														parentContainerName + "Layer"));*/

	root->setStyle(manager.getContainerStyle("window"));
	root->getFlowContainerSettings()->loadInnerSpacing(root->getStyle());

	root->getFlowContainerSettings()->cellSpacingWidth = 2;
	root->getFlowContainerSettings()->cellSpacingHeight = 2;
	root->getFlowContainerSettings()->autoLineWrap = true;

	/*std::set<std::string> arrowKeyCodes;
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
	root->getListenerManager().addListener(ctrlADListener);*/

	FlowContainerSettings baseSettings;

	baseSettings.autoLineWrap = true;
	baseSettings.cellSpacingWidth = 10;
	baseSettings.cellSpacingHeight = 10;
	baseSettings.horizontalAlignment = Settings::Alignment::CenterAlignment;
	baseSettings.verticalAlignment = Settings::Alignment::CenterAlignment;

	createTestBGroup1(manager, &baseSettings, parentContainerName);
	/*createTestBGroup2(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(2) + "." + parentContainerName + "Layer");
	createTestBGroup3(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(3) + "." + parentContainerName + "Layer");
	createTestBGroup4(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(4) + "." + parentContainerName + "Layer");
	createTestBGroup5(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(5) + "." + parentContainerName + "Layer");
	createTestBGroup6(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(6) + "." + parentContainerName + "Layer");
	createTestBGroup7(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(7) + "." + parentContainerName + "Layer");
	createTestBGroup8(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(8) + "." + parentContainerName + "Layer");
	createTestBGroup9(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(9) + "." + parentContainerName + "Layer");
	createTestBGroup10(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(10) + "." + parentContainerName + "Layer");
	createTestBGroup11(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(11) + "." + parentContainerName + "Layer");
	createTestBGroup12(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(12) + "." + parentContainerName + "Layer");
	createTestBGroup13(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(13) + "." + parentContainerName + "Layer");
	createTestBGroup14(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(14) + "." + parentContainerName + "Layer");
	createTestBGroup15(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(15) + "." + parentContainerName + "Layer");
	createTestBGroup16(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(16) + "." + parentContainerName + "Layer");
	createTestBGroup17(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(17) + "." + parentContainerName + "Layer");
	createTestBGroup18(manager, &baseSettings, parentContainerName + "." + baseAltName + Support::NumberToString(18) + "." + parentContainerName + "Layer");*/
}


void createTestBGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.horizontalGravity = Settings::Gravity::LeftGravity;
	newSettings.verticalGravity = Settings::Gravity::TopGravity;
	newSettings.horizontalFlow = Settings::Flow::LeftToRightFlow;
	newSettings.verticalFlow = Settings::Flow::TopToBottomFlow;

	createTestBSubGroup1(manager, "TestGroup1.1", &newSettings, parentContainerName);
	/*createTestBSubGroup2(manager, "TestGroup1.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup1.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup1.4", &newSettings, parentContainerName);*/
}


/*void createTestBGroup2(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup2.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup2.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup2.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup2.4", &newSettings, parentContainerName);
}


void createTestBGroup3(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup3.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup3.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup3.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup3.4", &newSettings, parentContainerName);
}


void createTestBGroup4(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup4.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup4.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup4.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup4.4", &newSettings, parentContainerName);
}


void createTestBGroup5(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup5.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup5.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup5.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup5.4", &newSettings, parentContainerName);
}


void createTestBGroup6(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup6.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup6.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup6.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup6.4", &newSettings, parentContainerName);
}


void createTestBGroup7(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup7.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup7.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup7.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup7.4", &newSettings, parentContainerName);
}


void createTestBGroup8(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup8.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup8.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup8.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup8.4", &newSettings, parentContainerName);
}


void createTestBGroup9(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup9.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup9.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup9.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup9.4", &newSettings, parentContainerName);
}


void createTestBGroup10(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup10.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup10.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup10.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup10.4", &newSettings, parentContainerName);
}


void createTestBGroup11(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup11.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup11.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup11.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup11.4", &newSettings, parentContainerName);
}


void createTestBGroup12(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup12.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup12.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup12.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup12.4", &newSettings, parentContainerName);
}


void createTestBGroup13(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup13.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup13.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup13.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup13.4", &newSettings, parentContainerName);
}


void createTestBGroup14(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::LeftOrUpperGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup14.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup14.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup14.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup14.4", &newSettings, parentContainerName);
}


void createTestBGroup15(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup15.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup15.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup15.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup15.4", &newSettings, parentContainerName);
}


void createTestBGroup16(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::RightOrLowerGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup16.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup16.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup16.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup16.4", &newSettings, parentContainerName);
}


void createTestBGroup17(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::RightOrLowerFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup17.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup17.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup17.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup17.4", &newSettings, parentContainerName);
}


void createTestBGroup18(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.verticalGravity = Settings::Gravity::CenterGravity;
	newSettings.horizontalGravity = Settings::Gravity::CenterGravity;
	newSettings.verticalFlow = Settings::Flow::LeftOrUpperFlow;

	newSettings.horizontalFlow = Settings::Flow::RightOrLowerFlow;
	createTestBSubGroup1(manager, "TestGroup18.1", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup18.2", &newSettings, parentContainerName);

	newSettings.horizontalFlow = Settings::Flow::LeftOrUpperFlow;
	createTestBSubGroup1(manager, "TestGroup18.3", &newSettings, parentContainerName);
	createTestBSubGroup2(manager, "TestGroup18.4", &newSettings, parentContainerName);
}*/


void createTestBSubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	createTestBBlock1(manager, id + ".block1", &newSettings, parentContainerName);
	/*createTestBBlock2(manager, id + ".block2", &newSettings, parentContainerName);
	createTestBBlock3(manager, id + ".block3", &newSettings, parentContainerName);
	createTestBBlock4(manager, id + ".block4", &newSettings, parentContainerName);
	createTestBBlock5(manager, id + ".block5", &newSettings, parentContainerName);
	createTestBBlock6(manager, id + ".block6", &newSettings, parentContainerName);
	createTestBBlock7(manager, id + ".block7", &newSettings, parentContainerName);
	createTestBBlock8(manager, id + ".block8", &newSettings, parentContainerName);
	createTestBBlock9(manager, id + ".block9", &newSettings, parentContainerName);
	createTestBBlock10(manager, id + ".block10", &newSettings, parentContainerName);
	createTestBBlock11(manager, id + ".block11", &newSettings, parentContainerName);
	createTestBBlock12(manager, id + ".block12", &newSettings, parentContainerName);*/
}


/*void createTestBSubGroup2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainerSettings newSettings = *baseSettings;

	newSettings.axisPriority = Settings::AxisPriority::VerticalFirst;

	createTestBBlock1(manager, id + ".block1", &newSettings, parentContainerName);
	createTestBBlock2(manager, id + ".block2", &newSettings, parentContainerName);
	createTestBBlock3(manager, id + ".block3", &newSettings, parentContainerName);
	createTestBBlock4(manager, id + ".block4", &newSettings, parentContainerName);
	createTestBBlock5(manager, id + ".block5", &newSettings, parentContainerName);
	createTestBBlock6(manager, id + ".block6", &newSettings, parentContainerName);
	createTestBBlock7(manager, id + ".block7", &newSettings, parentContainerName);
	createTestBBlock8(manager, id + ".block8", &newSettings, parentContainerName);
	createTestBBlock9(manager, id + ".block9", &newSettings, parentContainerName);
	createTestBBlock10(manager, id + ".block10", &newSettings, parentContainerName);
	createTestBBlock11(manager, id + ".block11", &newSettings, parentContainerName);
	createTestBBlock12(manager, id + ".block12", &newSettings, parentContainerName);
}*/


void createTestBBlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* testContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, testContainer);
	(*testContainer->getFlowContainerSettings()) = *baseSettings;

	testContainer->setStyle(manager.getContainerStyle("container"));
	testContainer->getFlowContainerSettings()->loadInnerSpacing(testContainer->getStyle());

	testContainer->getFlowContainerSettings()->fixedWidth = 160;
	testContainer->getFlowContainerSettings()->minHeight = 160;
	testContainer->getFlowContainerSettings()->maxHeight = 300;

	addTestBlocksB(manager, id, 4, testContainer->getPath());
}


/*void createTestBBlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 190;
	baseContainer->getFlowContainerSettings()->fixedHeight = 190;

	addTestBlocksB(manager, id, 12, baseContainer->getPath());
}


void createTestBBlock3(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->cellSpacingHeight = 4;
	baseContainer->getFlowContainerSettings()->fixedWidth = 200;
	baseContainer->getFlowContainerSettings()->fixedHeight = 200;

	addTestBlocksB(manager, id, 24, baseContainer->getPath());
}


void createTestBBlock4(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 200;
	baseContainer->getFlowContainerSettings()->minHeight = 200;
	baseContainer->getFlowContainerSettings()->maxHeight = 240;

	addTestBlocksB(manager, id, 24, baseContainer->getPath());
}


void createTestBBlock5(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 200;
	baseContainer->getFlowContainerSettings()->fixedHeight = 200;

	addTestBlocksB(manager, id, 24, baseContainer->getPath());
}


void createTestBBlock6(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 40;
	baseContainer->getFlowContainerSettings()->fixedHeight = 100;

	addTestBlocksB(manager, id, 1, baseContainer->getPath());
}


void createTestBBlock7(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 30;
	baseContainer->getFlowContainerSettings()->fixedHeight = 100;
}


void createTestBBlock8(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->autoLineWrap = false;
	baseContainer->getFlowContainerSettings()->fixedWidth = 80;
	baseContainer->getFlowContainerSettings()->fixedHeight = 80;

	addTestBlocksB(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestBBlock9(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->autoLineWrap = false;
	baseContainer->getFlowContainerSettings()->fixedWidth = 80;
	baseContainer->getFlowContainerSettings()->fixedHeight = 20;

	addTestBlocksB(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestBBlock10(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 10;
	baseContainer->getFlowContainerSettings()->fixedHeight = 100;

	addTestBlocksB(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestBBlock11(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 20;
	baseContainer->getFlowContainerSettings()->fixedHeight = 10;

	addTestBlocksB(manager, id, 3, baseContainer->getPath(), 5);
}


void createTestBBlock12(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName)
{
	FlowContainer* baseContainer = new FlowContainer(id);
	manager.addBasicBlock(parentContainerName, baseContainer);
	(*baseContainer->getFlowContainerSettings()) = *baseSettings;

	baseContainer->setStyle(manager.getContainerStyle("container"));
	baseContainer->getFlowContainerSettings()->loadInnerSpacing(baseContainer->getStyle());

	baseContainer->getFlowContainerSettings()->fixedWidth = 10;
	baseContainer->getFlowContainerSettings()->fixedHeight = 10;

	baseContainer->getFlowContainerSettings()->postNewLine = true;

	addTestBlocksB(manager, id, 3, baseContainer->getPath(), 5);
}*/


void addTestBlocksB(BlockManager& manager, const std::string id,
					const int total, const std::string parentContainerName,
					const int startingX, const int startingY)
{
	FlowContainer* container;
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
		subID = id + ".c" + Support::NumberToString(i);
		style = "";
		if(i % 4 == 0)
			style = "red";
		else if(i % 4 == 1)
			style = "green";
		else if(i % 4 == 2)
			style = "blue";
		else if(i % 4 == 3)
			style = "white";

		container = new FlowContainer(subID);
		container->setStyle(manager.getContainerStyle(style));
		container->getSettings()->minWidth = cWidths[(i + startingX) % maxValuesX];
		container->getSettings()->minHeight = cHeights[(i + startingY) % maxValuesY];
		manager.addBasicBlock(parentContainerName, container);
	}
}





