#include "../../ilslib-dev/include/ilslib.hpp"
#include "../../ilslib-sfml/include/ilslibsfml_adapter.hpp"

using namespace ILSLib;



int changeTestGroup(BlockManager* blockManager, int offset);
void arrowCallbackFunc(BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue);
void ctrlADCallbackFunc(BasicBlock* block, const Event* eventInfo,
					BlockManager* blockManager, EventQueue* eventQueue);


void createAllTestsB(BlockManager& manager, const std::string parentContainerName);


void createTestBGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup2(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup3(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup4(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup5(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup6(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup7(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup8(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup9(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup10(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup11(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup12(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup13(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup14(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup15(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup16(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup17(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);
void createTestBGroup18(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string parentContainerName);


void createTestBSubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBSubGroup2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);


void createTestBBlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock3(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock4(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock5(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock6(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock7(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock8(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock9(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock10(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock11(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);
void createTestBBlock12(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string parentContainerName);


void addTestBlocksB(BlockManager& manager, const std::string id,
					const int total, const std::string parentContainerName,
					const int startingX = 0, const int startingY = 0);




