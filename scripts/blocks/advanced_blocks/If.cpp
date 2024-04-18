#include "If.h"

If::If(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "if"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    codeName = "If";
}
