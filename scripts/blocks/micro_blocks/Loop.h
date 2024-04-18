#include "../Block.h"

#ifndef MICROSMARTZ_LOOP_H
#define MICROSMARTZ_LOOP_H

/*
 * Loop
 * Everything below its scope will be looped for the microcontroller
 */

class Loop : public Block{
public:
    Loop(AssetsManager *assets);
};


#endif //MICROSMARTZ_LOOP_H
