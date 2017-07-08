#include "ilslib.hpp"
#include "sfml_adapter/ilslibsfml_adapter.hpp"

using namespace ILSLib;


int changeTestGroup(BlockManager* blockManager, int offset);
void arrowCallbackFunc(BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue);
void ctrlADCallbackFunc(BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue);


void createAllTestsA(BlockManager& manager, const std::string rootName, const std::string baseAltName);


void createTestAGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup2(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup3(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup4(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup5(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup6(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup7(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup8(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup9(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup10(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup11(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup12(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup13(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup14(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup15(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup16(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup17(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);
void createTestAGroup18(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);


void createTestASubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestASubGroup2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);


void createTestABlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock3(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock4(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock5(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock6(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock7(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock8(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock9(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock10(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock11(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestABlock12(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);


void addTestBlocksA(BlockManager& manager, const std::string id,
					const int total, const std::string rootLayer,
					const int startingX = 0, const int startingY = 0);




