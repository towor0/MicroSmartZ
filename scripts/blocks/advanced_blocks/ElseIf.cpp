#include "ElseIf.h"

ElseIf::ElseIf(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "else if"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    codeName = "ElseIf";
}
