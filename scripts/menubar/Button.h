#include "../AssetsManager.h"

#ifndef MICROSMARTZ_BUTTON_H
#define MICROSMARTZ_BUTTON_H

/*
 * Button
 * Clickable Object
 */

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    bool selectable;
    bool selected;
    sf::Color color;
    sf::Color secColor;

public:
    Button(AssetsManager *assets, float x, float y, float width, float height, sf::Color color, sf::Color secColor, const std::string& word, bool selectable=false);
    ~Button();
    bool update(sf::Vector2f mosuePos, bool mousePressed);
    void draw(sf::RenderTarget &target);
};


#endif //MICROSMARTZ_BUTTON_H
