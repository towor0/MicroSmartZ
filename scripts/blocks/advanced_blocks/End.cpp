#include "End.h"

End::End(AssetsManager *assets) {
    components.emplace_back(new BlockString(assets, "end"));
    vBlocksSetup();
    codeName = "End";
}
