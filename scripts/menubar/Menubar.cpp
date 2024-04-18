#include "Menubar.h"

Menubar::Menubar(AssetsManager *assets) {
    action = "";
    background.setFillColor(sf::Color(209, 177, 0));
    background.setPosition(0.f, 0.f);
    background.setSize(sf::Vector2f(1200, 24));
    buttons.emplace_back(Button(assets, 0.f, 0.f, 128.f, 24.f, sf::Color(209, 177, 0), sf::Color(175, 135, 0), "File", true));
    //buttons.emplace_back(Button(assets, 128.f, 0.f, 128.f, 24.f, sf::Color(209, 177, 0), sf::Color(175, 135, 0), "Edit", true));
    //buttons.emplace_back(Button(assets, 256.f, 0.f, 128.f, 24.f, sf::Color(209, 177, 0), sf::Color(175, 135, 0), "Settings", true));
    std::vector<std::string> fileActions = {"New", "Open", "Save", "Save As", "Export", "Upload", "Clear"};
    dropdowns.emplace_back(new Dropdown(assets, fileActions, sf::Vector2f(0.f, 24.f)));
    //std::vector<std::string> editActions = {"Test"};
    //dropdowns.emplace_back(new Dropdown(assets, editActions, sf::Vector2f(128.f, 24.f)));
    //std::vector<std::string> settingsActions = {"Test"};
    //dropdowns.emplace_back(new Dropdown(assets, settingsActions, sf::Vector2f(256.f, 24.f)));
}

Menubar::~Menubar() {
    for (auto & dropdown : dropdowns) {
        delete dropdown;
    }
}

bool Menubar::update(sf::Vector2f mousePos, bool mousePressed) {
    bool select = false;
    for (auto dropdown : dropdowns) {
        std::string tempAction = dropdown->update(mousePos, mousePressed);
        if (!tempAction.empty()) {
            action = tempAction;
            select = true;
        }
    }
    for (int i = 0; i < buttons.size(); i ++) {
        if (buttons[i].update(mousePos, mousePressed)) {
            select = true;
            dropdowns[i]->setActive(true);
        }
    }
    return select;
}

void Menubar::draw(sf::RenderTarget &target) {
    target.draw(background);
    for (int i = 0; i < buttons.size(); i ++) {
        buttons[i].draw(target);
        dropdowns[i]->draw(target);
    }
}

std::string Menubar::getAction() {
    std::string temp = action;
    action = "";
    return temp;
}
