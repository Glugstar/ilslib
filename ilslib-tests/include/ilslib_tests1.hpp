#include "../../ilslib-dev/include/ilslib.hpp"
#include "../../ilslib-sfml/include/ilslibsfml_adapter.hpp"

using namespace ILSLib;



void createAllTestsA(BlockManager& manager, const std::string rootName);


void createTestAGroup1(BlockManager& manager, FlowContainerSettings* baseSettings,
					const std::string rootName);


void createTestASubGroup1(BlockManager& manager, const std::string blockName,
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




