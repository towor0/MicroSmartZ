#include "Loop.h"

Loop::Loop(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "loop"));
    returnType = "";
    codeName = "Loop";
}
