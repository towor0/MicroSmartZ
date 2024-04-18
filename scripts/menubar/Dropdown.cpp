#include "Dropdown.h"

Dropdown::Dropdown(AssetsManager *assets, std::vector<std::string> names, sf::Vector2f pos) {
    active = false;
    this->pos = pos;
    this->assets = assets;
    for (int i = 0; i < names.size(); i ++) {
        this->names.emplace_back(names[i]);
        buttons.emplace_back(Button(assets, 0.f, 24.f * static_cast<float>(i), 128.f, 24.f, sf::Color(209, 177, 0), sf::Color(175, 135, 0), names[i], false));
    }
    texture.create(128, 24 * buttons.size());
}

std::string Dropdown::update(sf::Vector2f mousePos, bool mousePressed) {
    if (active) {
        texture.clear(sf::Color::White);
        for (int i = 0; i < names.size(); i ++) {
            if (buttons[i].update(mousePos - pos, mousePressed)) {
                active = false;
                return names[i];
            }
            buttons[i].draw(texture);
        }
        texture.display();
        sprite = sf::Sprite(texture.getTexture());
        sprite.setPosition(pos);
        if (!sprite.getGlobalBounds().contains(mousePos) && mousePressed) active = false;
    }
    return "";
}

void Dropdown::draw(sf::RenderTarget &target) {
    if (active) target.draw(sprite);
}

void Dropdown::setActive(bool active) {
    this->active = active;
}

bool Dropdown::isActive() {
    return active;
}

Dropdown::~Dropdown() {

}
