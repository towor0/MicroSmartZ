#include "../AssetsManager.h"
#include "Line.h"
#include "queue"
#include "utility"

#include "../blocks/basic_blocks/Set.h"
#include "../blocks/basic_blocks/Get.h"
#include "../blocks/basic_blocks/Add.h"
#include "../blocks/basic_blocks/Minus.h"
#include "../blocks/basic_blocks/Multiply.h"
#include "../blocks/basic_blocks/Divide.h"

#include "../blocks/advanced_blocks/Equal.h"
#include "../blocks/advanced_blocks/Greater.h"
#include "../blocks/advanced_blocks/Less.h"
#include "../blocks/advanced_blocks/And.h"
#include "../blocks/advanced_blocks/Or.h"
#include "../blocks/advanced_blocks/Not.h"
#include "../blocks/advanced_blocks/While.h"
#include "../blocks/advanced_blocks/If.h"
#include "../blocks/advanced_blocks/ElseIf.h"
#include "../blocks/advanced_blocks/Else.h"
#include "../blocks/advanced_blocks/End.h"

#include "../blocks/micro_blocks/SetOutputPin.h"
#include "../blocks/micro_blocks/SetInputPin.h"
#include "../blocks/micro_blocks/SetInputButtonPin.h"
#include "../blocks/micro_blocks/Setup.h"
#include "../blocks/micro_blocks/Loop.h"
#include "../blocks/micro_blocks/WritePin.h"
#include "../blocks/micro_blocks/ReadPin.h"
#include "../blocks/micro_blocks/On.h"
#include "../blocks/micro_blocks/Off.h"
#include "../blocks/micro_blocks/Wait.h"

#ifndef MICROSMARTZ_WORKSPACE_H
#define MICROSMARTZ_WORKSPACE_H

/*
 * Workspace
 * Work area for black coding
 */

class Workspace {
private:
    // Var
    // Box
    sf::RenderTexture *boxWindow;
    sf::Sprite basicTab;
    sf::Sprite advancedTab;
    sf::Sprite microTab;
    sf::Sprite compTab;
    std::vector<sf::Sprite> symbols;
    sf::RectangleShape boxDivider;
    std::string boxTabSelected;
    std::map<std::string, std::vector<Block*>> boxes;
    sf::Vector2f boxWindowOffset;
    sf::Sprite boxSprite;
    // Code
    sf::RenderTexture *codeWindow;
    sf::RectangleShape infoBar;
    sf::RectangleShape lineBackground;
    sf::Sprite addLine;
    sf::Sprite deleteLine;
    sf::Vector2f codeWindowOffset;
    std::vector<Line*> codeLines;
    sf::View codeView;
    sf::FloatRect codeViewRect;
    sf::Vector2f codeViewMax;
    sf::RectangleShape codeVerticalScroll;
    sf::RectangleShape codeHorizontalScroll;
    sf::Sprite codeSprite;
    // Other
    AssetsManager *assets;
    Block *selectedBlock;
    int lineSelected;
    int insertLineSelected;
    sf::RectangleShape highlightLine;
    sf::RectangleShape insertionLine;
    sf::Vector2f prevMousePos;
    std::string scrolling;

    //Func


public:
    // Const
    Workspace(AssetsManager *assets);
    ~Workspace();

    // Func
    bool update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased, std::vector<int> unicodeEntered, std::string toolSelected);
    void draw(sf::RenderTarget &target);
    std::string getCode();
    void loadRawFile(const std::string& content);
    Block *getBlockByName(const std::string& name);
    void deleteSelected();
    void clearCode();
};


#endif //MICROSMARTZ_WORKSPACE_H
