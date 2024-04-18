#include "BlockString.h"

BlockString::BlockString(AssetsManager *assets, const std::string& string = "") {
    this->string << string;
    text.setFont(assets->getFont());
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setString(this->string.str());
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, 0.f);
    text.setPosition(sf::Vector2f((text.getGlobalBounds().width + 16.f)/2.f, 0.f));
    texture.create(static_cast<int>(text.getGlobalBounds().width) + 16, 20);
    texture.clear(sf::Color(209, 177, 0));
    texture.draw(text);
    texture.display();
    sprite = sf::Sprite(texture.getTexture());
    sprite.setPosition(0.f, 0.f);
    this->assets = assets;
}

void BlockString::draw(sf::RenderTarget &target) {
    BlockComponent::draw(target);
}

sf::Vector2f BlockString::getSize() {
    return BlockComponent::getSize();
}

void BlockString::setPos(sf::Vector2f pos) {
    BlockComponent::setPos(pos);
}

std::string BlockString::getName() {
    return "string";
}
