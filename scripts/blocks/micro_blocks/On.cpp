#include "On.h"

On::On(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "on"));
    returnType = "value";
    codeName = "On";
}
