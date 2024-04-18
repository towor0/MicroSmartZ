#include "BlockComponent.h"

#ifndef MICROSMARTZ_BLOCKVALUEINPUT_H
#define MICROSMARTZ_BLOCKVALUEINPUT_H

/*
 * BlockValueInput
 * Value Input section of the coding block
 */

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27
#define PERIOD_KEY 46

class BlockValueInput : public BlockComponent {
private:
    bool selected;
    void format();
    sf::Text defaultText;
    void setup(AssetsManager *assets, const std::string& string);

public:
    BlockValueInput(AssetsManager *assets, const std::string& string);
    ~BlockValueInput() override;
    bool update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered) override;
    void draw(sf::RenderTarget &target) override;
    sf::Vector2f getSize() override;
    void setPos(sf::Vector2f pos) override;
    std::string getName() override;
    std::string getText() override;
    void setSelected(bool sel) override;
};


#endif //MICROSMARTZ_BLOCKVALUEINPUT_H
