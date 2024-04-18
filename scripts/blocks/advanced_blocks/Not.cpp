#include "Not.h"

Not::Not(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "not"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "value";
    codeName = "Not";
}
