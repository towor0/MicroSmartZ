#include "SetOutputPin.h"

SetOutputPin::SetOutputPin(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "set output pin"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "";
    codeName = "SetOutputPin";
}
