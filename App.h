#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "windows.h"
#include <algorithm>

#include "scripts/AssetsManager.h"
#include "scripts/menubar/Menubar.h"
#include "scripts/Toolbar.h"
#include "scripts/workspace/Workspace.h"
#include "scripts/FileHandler.h"
#include "scripts/Compiler.h"


#ifndef MICROSMARTZ_APP_H
#define MICROSMARTZ_APP_H

/*
 * App
 * Controller for the whole Application
 */

class App {
private:
    // Var
    sf::RenderWindow *window;
    sf::Event ev;
    sf::Vector2f mousePos;
    std::string directoryPath;

    // Inst
    AssetsManager *assets;
    Menubar *menubar;
    Toolbar *toolbar;
    Workspace *workspace;
    FileHandler fileHandler;
    Compiler compiler;


public:
    // Const
    App();
    ~App();

    // Func
    void run();
    void update();
    void draw();
};


#endif