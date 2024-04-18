#include "../Block.h"

#ifndef MICROSMARTZ_WAIT_H
#define MICROSMARTZ_WAIT_H

/*
 * Wait
 * Wait for the amount of ms inputed
 */

class Wait : public Block{
public:
    Wait(AssetsManager *assets);
};


#endif //MICROSMARTZ_WAIT_H
