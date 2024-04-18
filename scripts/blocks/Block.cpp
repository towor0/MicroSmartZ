#include "Block.h"

Block::Block() {

}

Block::~Block() {
    for (auto component : components) {
        delete component;
    }
    for (auto block : valueBlocks) {
        delete block;
    }
}

std::string Block::getCode() {
    std::stringstream code;
    code << "*";
    code << codeName;
    std::stringstream arguments;
    int count = 0;
    for (auto component :components) {
        if (component->getName() == "name") {
            arguments << ",";
            arguments << component->getText();
        } else if (component->getName() == "value") {
            arguments << ",";
            if (valueBlocks[count]) {
                arguments << valueBlocks[count]->getCode();
            } else {
                arguments << component->getText();
            }
            count ++;
        }
    }
    if (!arguments.str().empty()) code << "(" << arguments.str() << ")";
    return code.str();
}

void Block::draw(sf::RenderTarget &target) {
    target.draw(sprite);
}

void Block::setPosition(sf::Vector2f pos) {
    this->pos = pos;
    sprite.setPosition(pos);
}

sf::Vector2f Block::getPosition() {
    return pos;
}

std::vector<bool> Block::update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered) {
    bool pressed = false;
    bool inputPressed = false;
    if (sprite.getGlobalBounds().contains(mousePos) && mousePressed) pressed = true;
    size = sf::Vector2f(0.f, 20.f);
    int count = 0;
    for (auto comp : components) {
        if (comp->getName() == "value" && valueBlocks[count]) {
            std::vector<bool> blockOutput = valueBlocks[count]->update(mousePos - pos, mousePressed, unicodeEntered);
            valueBlocks[count]->setPosition(sf::Vector2f(size.x, 0.f));
            if (blockOutput[1]) {
                inputPressed = true;
            }
            size.x += valueBlocks[count]->getSize().x;
        } else {
            comp->setPos(sf::Vector2f(size.x, 0.f));
            if (comp->update(mousePos - pos, mousePressed, unicodeEntered) &&
                (comp->getName() == "name" || comp->getName() == "value")) {
                inputPressed = true;
            }
            size.x += comp->getSize().x;
        }
        if (comp->getName() == "value") count ++;
    }
    texture.create(static_cast<unsigned int>(size.x), static_cast<unsigned int>(size.y));
    texture.clear(sf::Color::White);
    count = 0;
    for (auto comp : components) {
        if (comp->getName() == "value"){
            if (valueBlocks[count]) {
                valueBlocks[count]->draw(texture);
                sf::RectangleShape divider;
                divider.setFillColor(sf::Color::Black);
                divider.setSize(sf::Vector2f(2.f, 20.f));
                divider.setPosition(valueBlocks[count]->getPosition());
                texture.draw(divider);
                divider.setPosition(sf::Vector2f(valueBlocks[count]->getPosition().x + valueBlocks[count]->getSize().x - 2.f, 0.f));
                texture.draw(divider);
            }
            else comp->draw(texture);
            count ++;
        } else comp->draw(texture);
    }
    texture.display();
    sprite = sf::Sprite(texture.getTexture());
    sprite.setPosition(pos);
    return {pressed, inputPressed};
}

void Block::setDisplay(bool display) {
    this->display = display;
}

bool Block::isDisplay() {
    return display;
}

Block::Block(const Block &other) {
    for (auto comp : other.components) {
        if (comp->getName() == "name") components.emplace_back(new BlockNameInput(comp->getAssets(), comp->getText()));
        else if (comp->getName() == "value") components.emplace_back(new BlockValueInput(comp->getAssets(), comp->getText()));
        else if (comp->getName() == "string") components.emplace_back(new BlockString(comp->getAssets(), comp->getText()));
        else components.emplace_back(new BlockEnd(comp->getAssets(), comp->getText()));
    }
    for (auto valueBlock : other.valueBlocks) {
        if (valueBlock) valueBlocks.emplace_back(new Block(*valueBlock));
        else valueBlocks.emplace_back(nullptr);
    }
    display = false;
    pos = {other.pos.x, other.pos.y};
    returnType = other.returnType;
    codeName = other.codeName;
}

std::string Block::getReturnType() {
    return returnType;
}

bool Block::shove(Block *other, sf::Vector2f mousePos) {
    if (other->getReturnType() != "value") return false;
    int count = 0;
    float rXPos = 0;
    for (auto & component : components) {
        if (component->getName() == "value") {
            if (valueBlocks[count]) {
                if (rXPos <= (mousePos - pos).x && (mousePos - pos).x <= rXPos + valueBlocks[count]->getSize().x) {
                    return valueBlocks[count]->shove(other, mousePos - pos);
                }
            }
            if (rXPos <= (mousePos - pos).x && (mousePos - pos).x <= rXPos + component->getSize().x){
                delete valueBlocks[count];
                valueBlocks[count] = new Block(*other);
                component->setSelected(false);
                return true;
            }
            if (valueBlocks[count]) {
                rXPos += valueBlocks[count]->getSize().x;
            } else {
                rXPos += component->getSize().x;
            }
            count ++;
        } else {
            rXPos += component->getSize().x;
        }
    }
    return false;
}

void Block::vBlocksSetup() {
    for (auto comp : components){
        if (comp->getName() == "value") {
            valueBlocks.emplace_back(nullptr);
        }
    }
}

sf::Vector2f Block::getSize() {
    return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
}

Block *Block::getSelected(sf::Vector2f mousePos, bool d) {
    int count = 0;
    float rXPos = 0;
    for (auto & component : components) {
        if (component->getName() == "value" && valueBlocks[count]) {
            if (rXPos <= (mousePos - pos).x && (mousePos - pos).x <= rXPos + valueBlocks[count]->getSize().x) {
                Block *result = valueBlocks[count]->getSelected(mousePos - pos, d);
                if (d && result == valueBlocks[count]) {
                    valueBlocks[count] = nullptr;
                }
                return result;
            }
            rXPos += valueBlocks[count]->getSize().x;
            count ++;
        } else {
            if (rXPos <= (mousePos - pos).x && (mousePos - pos).x <= rXPos + component->getSize().x) {
                return this;
            }
            if (component->getName() == "value") count ++;
            rXPos += component->getSize().x;
        }
    }
    return nullptr;
}

std::string Block::getCodeName() {
    return codeName;
}

void Block::setArgs(const std::vector<std::string>& strArgs, std::vector<Block*> blockArgs) {
    int count = 0;
    int valueCount = 0;
    for (auto comp : components) {
        if (comp->getName() == "value" || comp->getName() == "name") {
            if (blockArgs[count]) {
                valueBlocks[valueCount] = blockArgs[count];
            } else {
                comp->setText(strArgs[count]);
            }
            if (comp->getName() == "value") valueCount ++;
            count ++;
        }
    }
}

int Block::getNumArgs() {
    int num = 0;
    for (auto comp : components) if (comp->getName() == "value" || comp->getName() == "name") num ++;
    return num;
}




