#include "SetInputPin.h"

SetInputPin::SetInputPin(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "set input pin"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "";
    codeName = "SetInputPin";
}
