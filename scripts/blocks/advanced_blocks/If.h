#include "../Block.h"

#ifndef MICROSMARTZ_IF_H
#define MICROSMARTZ_IF_H

/*
 * If
 * Executing blocks within its scope when a condition is met
 */

class If : public Block{
public:
    If(AssetsManager *assets);
};


#endif //MICROSMARTZ_IF_H
