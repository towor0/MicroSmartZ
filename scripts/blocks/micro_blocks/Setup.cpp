#include "Setup.h"

Setup::Setup(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "setup"));
    returnType = "";
    codeName = "Setup";
}
