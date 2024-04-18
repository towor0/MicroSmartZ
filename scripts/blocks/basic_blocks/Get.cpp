#include "Get.h"

Get::Get(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "get"));
    components.emplace_back(new BlockNameInput(assets, ""));
    components.emplace_back(new BlockEnd(assets, ""));
    returnType = "value";
    codeName = "Get";
}

