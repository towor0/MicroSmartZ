#include "WritePin.h"

WritePin::WritePin(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "write"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockString(assets, "to pin"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "";
    codeName = "WritePin";
}
