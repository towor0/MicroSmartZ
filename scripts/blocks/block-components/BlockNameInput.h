#include "BlockComponent.h"

#ifndef MICROSMARTZ_BLOCKNAMEINPUT_H
#define MICROSMARTZ_BLOCKNAMEINPUT_H

/*
 * BlockNameInput
 * Name Input section of the coding block
 */

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class BlockNameInput : public BlockComponent {
private:
    sf::Text defaultText;
    bool selected;
    void format();


public:
    BlockNameInput(AssetsManager *assets, const std::string& string);
    ~BlockNameInput() override;
    bool update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered) override;
    void draw(sf::RenderTarget &target) override;
    sf::Vector2f getSize() override;
    void setPos(sf::Vector2f pos) override;
    std::string getName() override;
    std::string getText() override;
};


#endif //MICROSMARTZ_BLOCKNAMEINPUT_H
