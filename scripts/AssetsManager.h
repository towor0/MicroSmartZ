#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <sstream>

#ifndef MICROSMARTZ_ASSETSMANAGER_H
#define MICROSMARTZ_ASSETSMANAGER_H

/*
 * AssetsManager
 * Returns desired asset
 */

class AssetsManager {
private:
    std::map<std::string, sf::Texture> sprites;
    std::map<std::string, sf::Color> colors;
    sf::Font font;
    sf::Image icon;
public:
    AssetsManager();
    ~AssetsManager();
    sf::Font &getFont();
    sf::Texture &getTexture(std::string key);
    sf::Image &getIcon();
    sf::Color &getColor(std::string key);
};


#endif //MICROSMARTZ_ASSETSMANAGER_H
