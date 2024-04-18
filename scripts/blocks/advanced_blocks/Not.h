#include "../Block.h"

#ifndef MICROSMARTZ_NOT_H
#define MICROSMARTZ_NOT_H

/*
 * Not
 * Returning the opposite value (1->0 and 0->1)
 */

class Not : public Block{
public:
    Not(AssetsManager *assets);
};


#endif //MICROSMARTZ_NOT_H
