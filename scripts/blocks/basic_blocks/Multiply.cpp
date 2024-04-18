//
// Created by qpalz on 6/26/2023.
//

#include "Multiply.h"

Multiply::Multiply(AssetsManager *assets) {
    components.emplace_back(new BlockEnd(assets, ""));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockString(assets, "*"));
    components.emplace_back(new BlockValueInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    vBlocksSetup();
    returnType = "value";
    codeName = "Multiply";
}
