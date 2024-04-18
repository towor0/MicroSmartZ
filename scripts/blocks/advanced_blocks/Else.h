#include "../Block.h"

#ifndef MICROSMARTZ_ELSE_H
#define MICROSMARTZ_ELSE_H

/*
 * Else
 * Connectable to If and Else If, when non of the conditions are met code within this scope will be executed
 */

class Else : public Block{
public:
    Else(AssetsManager *assets);
};


#endif //MICROSMARTZ_ELSE_H
