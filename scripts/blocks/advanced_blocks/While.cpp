#include "While.h"

While::While(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "while"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    codeName = "While";
}
