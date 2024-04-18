//
// Created by qpalz on 6/25/2023.
//

#include "BlockEnd.h"

BlockEnd::BlockEnd(AssetsManager *assets, const std::string &string) {
    texture.create(8, 20);
    texture.clear(sf::Color(209, 177, 0));
    texture.display();
    sprite = sf::Sprite(texture.getTexture());
    sprite.setPosition(0.f, 0.f);
    this->assets = assets;
}

void BlockEnd::draw(sf::RenderTarget &target) {
    BlockComponent::draw(target);
}

sf::Vector2f BlockEnd::getSize() {
    return BlockComponent::getSize();
}

void BlockEnd::setPos(sf::Vector2f pos) {
    BlockComponent::setPos(pos);
}

std::string BlockEnd::getName() {
    return "end";
}
