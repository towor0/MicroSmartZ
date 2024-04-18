#include "AssetsManager.h"

#ifndef MICROSMARTZ_ITEMBAR_H
#define MICROSMARTZ_ITEMBAR_H

/*
 * Toolbar
 * GUI for managing Tools
 */

class Toolbar {
private:
    sf::RectangleShape background;
    sf::RectangleShape backgroundDivider;
    std::string toolSelected;
    AssetsManager *assets;
    sf::Sprite moveTool;
    sf::Sprite cloneTool;
    sf::Sprite deleteTool;
    sf::Sprite swapLineTool;
    sf::RectangleShape selectedShape;

public:
    Toolbar(AssetsManager *assets);
    ~Toolbar();
    bool update(sf::Vector2f mousePos, bool mousePressed);
    void draw(sf::RenderTarget &target);
    std::string getSelectedTool();
};


#endif //MICROSMARTZ_TOOLBAR_H
