#include "../Block.h"

#ifndef MICROSMARTZ_READPIN_H
#define MICROSMARTZ_READPIN_H

/*
 * ReadPin
 * Read the given pin and returns HIGH or LOW
 */

class ReadPin : public Block{
public:
    ReadPin(AssetsManager *assets);
};


#endif //MICROSMARTZ_READPIN_H
