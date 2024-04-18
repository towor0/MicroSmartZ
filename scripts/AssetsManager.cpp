#include "AssetsManager.h"

AssetsManager::AssetsManager() {
    // Font Loading
    if (!font.loadFromFile("../assets/JetBrainsMono-Regular.ttf")) {
        std::cout << "ERROR ASSETSMANAGER::ASSETSMANAGER() failed to load font.\n";
    }

    // Sprite Loading
    // Tool
    sprites["MOVE_TOOL"].loadFromFile("../assets/tools/move_tool.png");
    sprites["CLONE_TOOL"].loadFromFile("../assets/tools/clone_tool.png");
    sprites["DELETE_TOOL"].loadFromFile("../assets/tools/delete_tool.png");
    sprites["SWAP_LINE_TOOL"].loadFromFile("../assets/tools/swap_line_tool.png");
    // Box
    sprites["BOXTAB_PRESSED"].loadFromFile("../assets/coding-area/boxtab_pressed.png");
    sprites["BOXTAB"].loadFromFile("../assets/coding-area/boxtab_idle.png");
    sprites["BASIC_SYMBOL"].loadFromFile("../assets/coding-area/basic_tab.png");
    sprites["ADVANCED_SYMBOL"].loadFromFile("../assets/coding-area/advanced_tab.png");
    sprites["MICRO_SYMBOL"].loadFromFile("../assets/coding-area/micro_tab.png");
    sprites["COMP_SYMBOL"].loadFromFile("../assets/coding-area/comp_tab.png");
    // Code
    sprites["ADD_LINE"].loadFromFile("../assets/coding-area/add_line.png");
    sprites["DELETE_LINE"].loadFromFile("../assets/coding-area/delete_line.png");

    // Icon Image
    icon.loadFromFile("../assets/icon.png");
}

AssetsManager::~AssetsManager() {

}

sf::Font &AssetsManager::getFont() {
    return font;
}

sf::Texture &AssetsManager::getTexture(std::string key) {
    return sprites[key];
}

sf::Image &AssetsManager::getIcon() {
    return icon;
}

sf::Color &AssetsManager::getColor(std::string key) {
    return colors[key];
}
