#include "../Block.h"

#ifndef MICROSMARTZ_SETUP_H
#define MICROSMARTZ_SETUP_H

/*
 * Setup
 * Everything below its scope will be called for setting up the microcontroller
 */

class Setup : public Block{
public:
    Setup(AssetsManager *assets);
};


#endif //MICROSMARTZ_SETUP_H
