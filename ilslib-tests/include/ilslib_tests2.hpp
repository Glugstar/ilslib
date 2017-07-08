#include "ilslib_tests.hpp"

void createAllTestsB(BlockManager& manager, const std::string rootName, const std::string baseAltName);


void createTestBGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootLayer);


void createTestBSubGroup1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);


void createTestBBlock1(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);
void createTestBBlock2(BlockManager& manager, const std::string id,
					FlowContainerSettings* baseSettings, const std::string rootLayer);


void addTestBlocksB1(BlockManager& manager, const std::string id,
					const int total, const std::string rootLayer,
					const int startingX = 0, const int startingY = 0);
void addTestBlocksB2(BlockManager& manager, const std::string id,
					const int total, const std::string rootLayer,
					const int startingX = 0, const int startingY = 0);




