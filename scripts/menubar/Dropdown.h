#include "Button.h"

#ifndef MICROSMARTZ_DROPDOWN_H
#define MICROSMARTZ_DROPDOWN_H

/*
 * Dropdown
 * Dropdown menu for the menu bar item selection
 */

class Dropdown {
private:
    AssetsManager *assets;
    std::vector<std::string> names;
    std::vector<Button> buttons;
    sf::Sprite sprite;
    sf::RenderTexture texture;
    bool active;
    sf::Vector2f pos;
public:
    Dropdown(AssetsManager *assets, std::vector<std::string> names, sf::Vector2f pos);
    ~Dropdown();
    std::string update(sf::Vector2f mousePos, bool mousePressed);
    void draw(sf::RenderTarget &target);
    void setActive(bool active);
    bool isActive();
};


#endif //MICROSMARTZ_DROPDOWN_H
