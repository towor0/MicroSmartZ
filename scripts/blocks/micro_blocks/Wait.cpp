#include "Wait.h"

Wait::Wait(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "wait"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "";
    codeName = "Wait";
}
