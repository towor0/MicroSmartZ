#include "ReadPin.h"

ReadPin::ReadPin(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "read pin"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "value";
    codeName = "ReadPin";
}
