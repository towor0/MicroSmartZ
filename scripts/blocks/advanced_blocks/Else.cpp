#include "Else.h"

Else::Else(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "else"));
    vBlocksSetup();
    codeName = "Else";
}
