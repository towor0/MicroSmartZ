#include "Minus.h"

Minus::Minus(AssetsManager *assets) {
    components.emplace_back(new BlockEnd(assets, ""));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockString(assets, "-"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "value";
    codeName = "Minus";
}
