#include "Line.h"

Line::Line(AssetsManager *assets, int num) {
    this->assets = assets;
    numText.setFillColor(sf::Color::Black);
    numText.setFont(assets->getFont());
    numText.setString(std::to_string(num));
    numText.setCharacterSize(16);
    updateTextPosition();
    block = nullptr;
    blockPos = sf::Vector2f(40.f, static_cast<float>(num-1) * 20.f);
    tabs = 0;
    tab.setPosition(sf::Vector2f(40.f, static_cast<float>(num-1) * 20.f));
    tab.setFillColor(sf::Color::Yellow);
    setNum(num);
}

Line::~Line() {
    delete block;
}

std::vector<bool> Line::update(sf::Vector2f mousePos, bool mousePressed, const std::vector<int>& unicodeEntered, int tabs) {
    this->tabs = tabs;
    tab.setSize(sf::Vector2f(20.f * static_cast<float>(tabs), 20.f));
    blockPos.x = tab.getGlobalBounds().left + tab.getLocalBounds().width;
    blockPos.y = tab.getGlobalBounds().top;
    std::vector<bool> lineOutput = {false, false};
    if (mousePressed && mousePos.x >= 40 && mousePos.y >= blockPos.y && mousePos.y < blockPos.y + 20) lineOutput[0] = true;
    if (mousePos.x >= 0.f && mousePos.y >= blockPos.y && mousePos.y < blockPos.y + 20) {
        if (numText.getStyle() == sf::Text::Regular) {
            numText.setStyle(sf::Text::Bold);
            updateTextPosition();
        }
    } else if (numText.getStyle() == sf::Text::Bold) {
        numText.setStyle(sf::Text::Regular);
        updateTextPosition();
    }
    if (block) {
        std::vector<bool> output = block->update(mousePos - blockPos, mousePressed, unicodeEntered);
        blockTexture.create(static_cast<int>(block->getSize().x), static_cast<int>(block->getSize().y));
        blockTexture.clear(sf::Color::White);
        block->draw(blockTexture);
        blockTexture.display();
        sprite = sf::Sprite(blockTexture.getTexture());
        sprite.setPosition(blockPos);
        return output;
    }
    return lineOutput;
}

void Line::draw(sf::RenderTarget &target) {
    target.draw(numText);
    if (block) target.draw(sprite);
    if (tabs) target.draw(tab);
}

void Line::updateTextPosition() {
    sf::FloatRect textRect = numText.getLocalBounds();
    numText.setPosition(sf::Vector2f((int)(38-textRect.width), 20 * (lineNum - 1)));
}

bool Line::shove(Block *other, sf::Vector2f mousePos) {
    if (other) {
        if (block) {
            return block->shove(other, mousePos - blockPos);
        } else {
            block = new Block(*other);
            block->setPosition(sf::Vector2f(0.f, 0.f));
            return true;
        }
    }
}

Block *Line::getSelected(sf::Vector2f mousePos, bool d) {
    if (block) {
        return block->getSelected(mousePos - blockPos, d);
    }
    return nullptr;
}

void Line::deleteBlock() {
    delete block;
    block = nullptr;
}

Block *Line::getBlock() {
    return block;
}

float Line::getWidth() {
    if (block) {
        return blockPos.x + block->getSize().x;
    }
    return 40.f + static_cast<float>(tabs) * 20.f;
}

std::string Line::getCode() {
    if (block) return block->getCode();
    return "";
}

void Line::setNum(int num) {
    lineNum = num;
    numText.setString(std::to_string(num));
    blockPos = sf::Vector2f(40.f, static_cast<float>(num-1) * 20.f);
    tabs = 0;
    tab.setPosition(sf::Vector2f(40.f, static_cast<float>(num-1) * 20.f));
    tab.setFillColor(sf::Color::Yellow);
    updateTextPosition();
}
