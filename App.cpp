#include "App.h"

App::App() {
    sf::VideoMode videoMode = sf::VideoMode(1200, 900);
    window = new sf::RenderWindow(videoMode, "MicroSmartZ", sf::Style::Titlebar | sf::Style::Close);
    window->setVerticalSyncEnabled(true);
    assets = new AssetsManager();
    menubar = new Menubar(assets);
    toolbar = new Toolbar(assets);
    workspace = new Workspace(assets);
    window->setIcon(assets->getIcon().getSize().x, assets->getIcon().getSize().y, assets->getIcon().getPixelsPtr());
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string filePath(buffer);
    std::size_t found = filePath.find_last_of("\\");
    directoryPath = filePath.substr(0, found);
    directoryPath = directoryPath.substr(0, directoryPath.find_last_of ("\\"));
    std::replace(directoryPath.begin(), directoryPath.end(), '\\', '/');
    fileHandler.setPath(directoryPath);
}

App::~App() {
    delete window;
    delete assets;
    delete menubar;
    delete toolbar;
    delete workspace;
}

void App::run() {
    while (window->isOpen()) {
        update();
        draw();
    }
}

void App::update() {
    // Event Polling
    mousePos =sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x),
                           static_cast<float>(sf::Mouse::getPosition(*window).y));
    std::vector<int> unicodeEntered;
    bool mousePressed = false;
    bool mouseReleased = false;
    while (window->pollEvent(ev)) {
        switch(ev.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::MouseButtonPressed:
                switch (ev.key.code) {
                    case sf::Mouse::Left:
                        mousePressed = true;
                        break;
                }
                break;
            case sf::Event::MouseButtonReleased:
                switch (ev.key.code) {
                    case sf::Mouse::Left:
                        mouseReleased = true;
                        break;
                }
                break;
            case sf::Event::TextEntered:
                unicodeEntered.emplace_back(ev.text.unicode);
                break;
        }
    }
    if (menubar->update(mousePos, mousePressed)) {
        mousePressed = false;
        std::string action = menubar->getAction();
        if (action == "New") {
            fileHandler.setCWFilePath("");
            delete workspace;
            workspace = new Workspace(assets);
        } else if (action == "Save") {
            if (!fileHandler.getCWFilePath().empty()) {
                fileHandler.saveToFile(fileHandler.getCWFilePath(), workspace->getCode());
            } else {
                std::string filePath = fileHandler.openFileDialog();
                if (!filePath.empty()) {
                    fileHandler.setCWFilePath(filePath);
                    fileHandler.saveToFile(filePath, workspace->getCode());
                }
            }
        } else if (action == "Save As") {
            std::string filePath = fileHandler.openFileDialog();
            if (!filePath.empty()) {
                fileHandler.setCWFilePath(filePath);
                fileHandler.saveToFile(filePath, workspace->getCode());
            }
        } else if (action == "Open") {
            std::string filePath = fileHandler.openFileDialog();
            if (!filePath.empty()) {
                fileHandler.setCWFilePath(filePath);
                workspace->loadRawFile(fileHandler.readFileContent(filePath));
            }
        } else if (action == "Export") {
            std::string filePath = fileHandler.openFileDialogSketch();
            if (!filePath.empty()) {
                std::string content = workspace->getCode();
                std::string sketchCode = compiler.exportSketch(content);
                fileHandler.saveToFile(filePath, sketchCode);
            }
        } else if (action == "Upload") {
            std::string code = compiler.exportSketch(workspace->getCode());
            fileHandler.saveToFile(directoryPath + "/temp/temp.ino", code);
            fileHandler.uploadCode();
        } else if (action == "Clear") {
            workspace->clearCode();
        }
    }
    if (toolbar->update(mousePos, mousePressed)) {
        mousePressed = false;
        workspace->deleteSelected();
    }
    if (workspace->update(mousePos, mousePressed, mouseReleased, unicodeEntered, toolbar->getSelectedTool())) mousePressed = false;
}

void App::draw() {
    window->clear(sf::Color(255, 245, 201));
    toolbar->draw(*window);
    workspace->draw(*window);
    menubar->draw(*window);
    window->display();
}