//
// Created by qpalz on 6/21/2023.
//

#include "Toolbar.h"

Toolbar::Toolbar(AssetsManager *assets) {
    this->assets = assets;
    background.setFillColor(sf::Color(209, 177, 0));
    background.setPosition(0, 24);
    background.setSize(sf::Vector2f(1200.f, 32.f));
    backgroundDivider.setFillColor(sf::Color(sf::Color::Black));
    backgroundDivider.setPosition(0, 24);
    backgroundDivider.setSize(sf::Vector2f(1200.f, 2.f));
    toolSelected = "move";
    moveTool.setTexture(assets->getTexture("MOVE_TOOL"));
    cloneTool.setTexture(assets->getTexture("CLONE_TOOL"));
    deleteTool.setTexture(assets->getTexture("DELETE_TOOL"));
    swapLineTool.setTexture(assets->getTexture("SWAP_LINE_TOOL"));
    moveTool.setPosition(sf::Vector2f(2.f, 28.f));
    cloneTool.setPosition(sf::Vector2f(34.f, 28.f));
    deleteTool.setPosition(sf::Vector2f(66.f, 28.f));
    swapLineTool.setPosition(sf::Vector2f(98.f, 28.f));
    selectedShape.setFillColor(sf::Color(175, 135, 0));
    selectedShape.setSize(sf::Vector2f(26.f, 26.f));
    selectedShape.setPosition(moveTool.getPosition());
}

Toolbar::~Toolbar() {

}

bool Toolbar::update(sf::Vector2f mousePos, bool mousePressed) {
    if (mousePressed) {
        if (moveTool.getGlobalBounds().contains(mousePos)) {
            toolSelected = "move";
            selectedShape.setPosition(moveTool.getPosition());
        } else if (cloneTool.getGlobalBounds().contains(mousePos)) {
            toolSelected = "clone";
            selectedShape.setPosition(cloneTool.getPosition());
        } else if (deleteTool.getGlobalBounds().contains(mousePos)) {
            toolSelected = "delete";
            selectedShape.setPosition(deleteTool.getPosition());
        } else if (swapLineTool.getGlobalBounds().contains(mousePos)) {
            toolSelected = "swap line";
            selectedShape.setPosition(swapLineTool.getPosition());
        } else {
            return false;
        }
        return true;
    }
    return false;
}

void Toolbar::draw(sf::RenderTarget &target) {
    target.draw(background);
    target.draw(selectedShape);
    target.draw(moveTool);
    target.draw(cloneTool);
    target.draw(deleteTool);
    target.draw(swapLineTool);
    target.draw(backgroundDivider);
}

std::string Toolbar::getSelectedTool() {
    return toolSelected;
}
