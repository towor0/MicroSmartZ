#include "../Block.h"

#ifndef MICROSMARTZ_WRITEPIN_H
#define MICROSMARTZ_WRITEPIN_H

/*
 * WritePin
 * Write to the given pin HIGH or LOW
 */

class WritePin : public Block{
public:
    WritePin(AssetsManager *assets);
};


#endif //MICROSMARTZ_WRITEPIN_H
