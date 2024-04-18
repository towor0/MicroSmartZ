#include "BlockComponent.h"


#ifndef MICROSMARTZ_BLOCKSTRING_H
#define MICROSMARTZ_BLOCKSTRING_H
/*
 * BlockString
 * String section of the coding block
 */

class BlockString : public BlockComponent{
private:

public:
    BlockString(AssetsManager *assets, const std::string& string);
    void draw(sf::RenderTarget &target) override;
    sf::Vector2f getSize() override;
    void setPos(sf::Vector2f pos) override;
    std::string getName() override;
};


#endif //MICROSMARTZ_BLOCKSTRING_H
