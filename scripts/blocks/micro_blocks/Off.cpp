#include "Off.h"

Off::Off(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "off"));
    returnType = "value";
    codeName = "Off";
}
