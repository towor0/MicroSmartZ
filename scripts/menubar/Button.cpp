#include "Button.h"

Button::Button(AssetsManager *assets, float x, float y, float width, float height, sf::Color color, sf::Color secColor, const std::string& word, bool selectable) {
    shape = sf::RectangleShape(sf::Vector2f(width, height));
    shape.setPosition(sf::Vector2f(x, y));
    shape.setFillColor(color);
    text.setFont(assets->getFont());
    text.setString(word);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,
                   textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x + width/2.f, y + height/2.f));
    this->selectable = selectable;
    selected = false;
    this->color = color;
    this->secColor = secColor;
}

Button::~Button() {

}

bool Button::update(sf::Vector2f mousePos, bool mousePressed) {
    if (shape.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        shape.setFillColor(secColor);
        if (mousePressed){
            if (selectable) selected = !selected;
            return true;
        }
    } else {
        if (!selected) shape.setFillColor(color);
        else if (selected && mousePressed) {
            selected = false;
        }
    }
    return false;
}

void Button::draw(sf::RenderTarget &target) {
    target.draw(shape);
    target.draw(text);
}
