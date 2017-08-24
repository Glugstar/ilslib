#include "../../ilslib-dev/include/ilslib.hpp"
#include "../../ilslib-sfml/include/ilslibsfml_adapter.hpp"

using namespace ILSLib;

std::list<ContainerStyle*> getStyles(const ILSLibSFML::ResourceManager& resourceManager);
ContainerStyle* getStyle(const ILSLibSFML::ResourceManager& resourceManager,
						const std::string& id, int nBackgrounds);


