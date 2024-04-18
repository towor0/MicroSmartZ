#include "BlockComponent.h"

#ifndef MICROSMARTZ_BLOCKEND_H
#define MICROSMARTZ_BLOCKEND_H

/*
 * BlockEnd
 * Extra spacing towards the end of a command block
 */

class BlockEnd : public BlockComponent{
public:
    BlockEnd(AssetsManager *assets, const std::string& string);
    void draw(sf::RenderTarget &target) override;
    sf::Vector2f getSize() override;
    void setPos(sf::Vector2f pos) override;
    std::string getName() override;
};


#endif //MICROSMARTZ_BLOCKEND_H
