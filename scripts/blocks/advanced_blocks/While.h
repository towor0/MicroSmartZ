#include "../Block.h"

#ifndef MICROSMARTZ_WHILE_H
#define MICROSMARTZ_WHILE_H

/*
 * While
 * Code within the scope below will be executed repeatedly until the condition becomes false
 */

class While : public Block{
public:
    While(AssetsManager *assets);
};


#endif //MICROSMARTZ_WHILE_H
