#include "Dropdown.h"

#ifndef MICROSMARTZ_TOOLBAR_H
#define MICROSMARTZ_TOOLBAR_H

/*
 * Menubar
 * Controller for the Menubar
 */

class Menubar {
private:
    // Var
    sf::RectangleShape background;
    std::vector<Button> buttons;
    std::vector<Dropdown*> dropdowns;
    std::string action;

public:
    // Const
    Menubar(AssetsManager *assets);
    ~Menubar();

    // Func
    bool update(sf::Vector2f mousePos, bool mousePressed);
    void draw(sf::RenderTarget &target);
    std::string getAction();
};


#endif
