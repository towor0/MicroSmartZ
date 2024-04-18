#include <vector>
#include "BlockValueInput.h"

BlockValueInput::BlockValueInput(AssetsManager *assets, const std::string& string) {
    setup(assets, string);
}

BlockValueInput::~BlockValueInput() {

}

bool BlockValueInput::update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered) {
    if (mousePressed) {
        if (sprite.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))) {
            selected = true;
            return true;
            format();
        } else {
            selected = false;
            format();
        }
    }
    if (selected) {
        for (int unicode : unicodeEntered) {
            if (unicode < 128) {
                if (unicode != DELETE_KEY && unicode != ENTER_KEY && unicode != ESCAPE_KEY) {\
                    if (isdigit(unicode) || unicode == PERIOD_KEY) string << static_cast<char>(unicode);
                    format();
                } else if (unicode == DELETE_KEY) {
                    if (string.str().length() > 0) {
                        std::string s = string.str();
                        std::string newS = "";
                        for (int i = 0; i < s.length() - 1; i++) {
                            newS.push_back(s[i]);
                        }
                        string.str("");
                        string << newS;
                    }
                } else if (unicode == ESCAPE_KEY) {
                    selected = false;
                } else if (unicode == ENTER_KEY) {
                    selected = false;
                }
            }
        }
        format();
    }
    return false;
}

void BlockValueInput::draw(sf::RenderTarget &target) {
    target.draw(sprite);
}

sf::Vector2f BlockValueInput::getSize() {
    return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
}

void BlockValueInput::format() {
    sf::FloatRect textRect;
    if (string.str().length() > 0 || selected) {
        if (selected) text.setString(string.str() + "_");
        else text.setString(string.str());
        textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, 0.f);
        text.setPosition(sf::Vector2f((text.getGlobalBounds().width + 16.f)/2.f, 0.f));
        texture.create(static_cast<int>(textRect.width) + 16, 20);
        texture.clear(sf::Color::White);
        texture.draw(text);
    } else {
        textRect = defaultText.getGlobalBounds();
        texture.create(static_cast<int>(textRect.width) + 16, 20);
        texture.clear(sf::Color::White);
        texture.draw(defaultText);
    }
    sf::RectangleShape divider;
    divider.setFillColor(sf::Color::Black);
    divider.setSize(sf::Vector2f(2.f, 20.f));
    divider.setPosition(sf::Vector2f(0.f, 0.f));
    texture.draw(divider);
    divider.setPosition(sf::Vector2f(textRect.width + 14.f, 0.f));
    texture.draw(divider);
    texture.display();
    sprite = sf::Sprite(texture.getTexture());
    sprite.setPosition(pos);
}

void BlockValueInput::setPos(sf::Vector2f pos) {
    this->pos = pos;
    sprite.setPosition(pos);
}

std::string BlockValueInput::getName() {
    return "value";
}

std::string BlockValueInput::getText() {
    return string.str();
}

void BlockValueInput::setup(AssetsManager *assets, const std::string &string) {
    text.setFont(assets->getFont());
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(16);
    text.setString(string);
    this->string << string;
    defaultText.setFont(assets->getFont());
    defaultText.setFillColor(sf::Color(220, 220, 220));
    defaultText.setCharacterSize(16);
    defaultText.setString("value");
    sf::FloatRect textRect = defaultText.getLocalBounds();
    defaultText.setOrigin(textRect.left + textRect.width/2.0f, 0.f);
    defaultText.setPosition(sf::Vector2f((defaultText.getGlobalBounds().width + 16.f)/2.f, 0.f));
    selected = false;
    texture.create(100, 100);
    format();
    this->assets = assets;
}

void BlockValueInput::setSelected(bool sel) {
    selected = sel;
}
