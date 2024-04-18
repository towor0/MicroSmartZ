#include "SetInputButtonPin.h"

SetInputButtonPin::SetInputButtonPin(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "set input button pin"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "";
    codeName = "SetInputButtonPin";
}
