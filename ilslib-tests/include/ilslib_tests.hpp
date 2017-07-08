#include "ilslib.hpp"
#include "sfml_adapter/ilslibsfml_adapter.hpp"

using namespace ILSLib;


int changeTestGroup(BlockManager* blockManager, int offset);
void arrowCallbackFunc(BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue);
void ctrlADCallbackFunc(BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue);


void createAllTestsA(BlockManager& manager, const std::string parentContainerName);


void createTestAGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup2(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup3(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup4(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup5(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup6(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup7(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup8(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup9(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup10(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup11(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup12(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup13(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup14(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup15(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup16(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup17(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestAGroup18(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);


void createTestASubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestASubGroup2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);


void createTestABlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock3(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock4(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock5(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock6(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock7(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock8(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock9(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock10(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock11(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestABlock12(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);


void addTestBlocksA(BlockManager& manager, const std::string id,
					const int total, const std::string parentContainerName,
					const int startingX = 0, const int startingY = 0);




