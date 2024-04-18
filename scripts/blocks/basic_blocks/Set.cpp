#include "Set.h"

Set::Set(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "set"));
    components.emplace_back(new BlockNameInput(assets, ""));
    components.emplace_back(new BlockString(assets, "="));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    codeName = "Set";
}



