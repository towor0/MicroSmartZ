#include "../../AssetsManager.h"

#ifndef MICROSMARTZ_BLOCKCOMPONENT_H
#define MICROSMARTZ_BLOCKCOMPONENT_H

/*
 * BlockComponent
 * Base class for all Block Components
 */

class BlockComponent {
protected:
    sf::RectangleShape shape;
    sf::Text text;
    std::stringstream string;
    sf::RenderTexture texture;
    sf::Sprite sprite;
    sf::Vector2f pos;
    AssetsManager *assets;

public:
    BlockComponent();
    BlockComponent(AssetsManager *assets, const std::string& string);
    virtual ~BlockComponent();
    virtual bool update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered);
    virtual void draw(sf::RenderTarget &target);
    virtual sf::Vector2f getSize();
    virtual void setPos(sf::Vector2f pos);
    virtual std::string getName();
    AssetsManager *getAssets();
    virtual std::string getText();
    virtual void setText(std::string str);
    virtual void setSelected(bool sel);

};


#endif //MICROSMARTZ_BLOCKCOMPONENT_H
