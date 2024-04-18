#include "BlockComponent.h"

BlockComponent::BlockComponent(AssetsManager *assets, const std::string &string) {
    this->assets = assets;
}

BlockComponent::~BlockComponent() {

}

bool BlockComponent::update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered) {
    return false;
}

void BlockComponent::draw(sf::RenderTarget &target) {
    target.draw(sprite);
}

sf::Vector2f BlockComponent::getSize() {
    return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
}

void BlockComponent::setPos(sf::Vector2f pos) {
    this->pos = pos;
    sprite.setPosition(pos);
}

BlockComponent::BlockComponent() {

}

std::string BlockComponent::getName() {
    return "component";
}

AssetsManager *BlockComponent::getAssets() {
    return assets;
}

std::string BlockComponent::getText() {
    return string.str();
}

void BlockComponent::setSelected(bool sel) {
    ;
}

void BlockComponent::setText(std::string str) {
    string.clear();
    string << str;
}


