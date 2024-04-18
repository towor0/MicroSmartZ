#include "Workspace.h"

Workspace::Workspace(AssetsManager *assets) {
    this->assets = assets;
    selectedBlock = nullptr;
    prevMousePos = {0, 0};
    scrolling = "";
    lineSelected = -1;
    insertLineSelected = -1;
    highlightLine.setFillColor(sf::Color(220, 220, 220));
    highlightLine.setSize(sf::Vector2f(778.f, 20.f));
    insertionLine.setFillColor(sf::Color(220, 220, 220));
    insertionLine.setSize(sf::Vector2f(778.f, 2.f));


    // Box
    boxWindow = new sf::RenderTexture();
    boxWindow->create(400, 800);
    boxTabSelected = "basic";
    basicTab.setTexture(assets->getTexture("BOXTAB_PRESSED"));
    basicTab.setPosition(0.f, 68.f);
    advancedTab.setTexture(assets->getTexture("BOXTAB"));
    advancedTab.setPosition(100.f, 68.f);
    microTab.setTexture(assets->getTexture("BOXTAB"));
    microTab.setPosition(200.f, 68.f);
    compTab.setTexture(assets->getTexture("BOXTAB"));
    compTab.setPosition(300.f, 68.f);
    boxDivider.setSize(sf::Vector2f(400.f, 2.f));
    boxDivider.setPosition(sf::Vector2f(0.f, 98.f));
    boxDivider.setFillColor(sf::Color(255, 245, 201));
    symbols.emplace_back(sf::Sprite(assets->getTexture("BASIC_SYMBOL")));
    symbols.emplace_back(sf::Sprite(assets->getTexture("ADVANCED_SYMBOL")));
    symbols.emplace_back(sf::Sprite(assets->getTexture("MICRO_SYMBOL")));
    symbols.emplace_back(sf::Sprite(assets->getTexture("COMP_SYMBOL")));
    for (int i = 0; i < 4; i ++) {
        symbols[i].setPosition(static_cast<float>(100 * i), 68.f);
    }
    boxes["basic"] = std::vector<Block*>();
    boxes["basic"].emplace_back(new Set(assets));
    boxes["basic"].emplace_back(new Get(assets));
    boxes["basic"].emplace_back(new Add(assets));
    boxes["basic"].emplace_back(new Minus(assets));
    boxes["basic"].emplace_back(new Multiply(assets));
    boxes["basic"].emplace_back(new Divide(assets));
    boxes["advanced"].emplace_back(new Equal(assets));
    boxes["advanced"].emplace_back(new Greater(assets));
    boxes["advanced"].emplace_back(new Less(assets));
    boxes["advanced"].emplace_back(new And(assets));
    boxes["advanced"].emplace_back(new Or(assets));
    boxes["advanced"].emplace_back(new Not(assets));
    boxes["advanced"].emplace_back(new While(assets));
    boxes["advanced"].emplace_back(new If(assets));
    boxes["advanced"].emplace_back(new ElseIf(assets));
    boxes["advanced"].emplace_back(new Else(assets));
    boxes["advanced"].emplace_back(new End(assets));
    boxes["micro"].emplace_back(new SetOutputPin(assets));
    boxes["micro"].emplace_back(new SetInputPin(assets));
    boxes["micro"].emplace_back(new SetInputButtonPin(assets));
    boxes["micro"].emplace_back(new Setup(assets));
    boxes["micro"].emplace_back(new Loop(assets));
    boxes["micro"].emplace_back(new WritePin(assets));
    boxes["micro"].emplace_back(new ReadPin(assets));
    boxes["micro"].emplace_back(new On(assets));
    boxes["micro"].emplace_back(new Off(assets));
    boxes["micro"].emplace_back(new Wait(assets));
    boxWindowOffset = sf::Vector2f(0.f, 100.f);
    for (const auto& box : boxes) {
        int i = 0;
        for (auto block : box.second) {
            block->setDisplay(true);
            block->setPosition(sf::Vector2f(50.f, 30.f + static_cast<float>(i++) * 50.f));
        }
    }


    // Code
    codeWindow = new sf::RenderTexture();
    codeWindow->create(778, 814);
    infoBar.setFillColor(sf::Color(220, 220, 220));
    infoBar.setSize(sf::Vector2f(788.f, 20.f));
    infoBar.setPosition(sf::Vector2f(412.f, 880.f));
    lineBackground.setFillColor(sf::Color(246, 246, 246));
    lineBackground.setPosition(sf::Vector2f(0.f, 0.f));
    lineBackground.setSize(sf::Vector2f(40.f, 814.f));
    addLine.setTexture(assets->getTexture("ADD_LINE"));
    addLine.setPosition(sf::Vector2f(415.f, 882.f));
    deleteLine.setTexture(assets->getTexture("DELETE_LINE"));
    deleteLine.setPosition(sf::Vector2f(433.f, 882.f));
    codeWindowOffset = sf::Vector2f(412.f, 56.f);
    for (int i = 1; i < 11; i ++) {
        codeLines.emplace_back(new Line(assets, i));
    }
    codeViewRect = sf::FloatRect(0.f, 0.f, 778.f, 814.f);
    codeView = sf::View(codeViewRect);
    codeWindow->setView(codeView);
    codeVerticalScroll.setPosition(sf::Vector2f(1190.f, 56.f));
    codeVerticalScroll.setSize(sf::Vector2f(10.f, 814.f));
    codeVerticalScroll.setFillColor(sf::Color(175, 135, 0));
    codeHorizontalScroll.setPosition(sf::Vector2f(412.f, 870.f));
    codeHorizontalScroll.setSize(sf::Vector2f(778.f, 10.f));
    codeHorizontalScroll.setFillColor(sf::Color(175, 135, 0));
    codeViewMax = sf::Vector2f(788.f, 814.f);
}

Workspace::~Workspace() {
    delete boxWindow;
    delete codeWindow;
    for (const auto& i : boxes) {
        for (auto c : i.second) {
            delete c;
        }
    }
    for (auto i : codeLines) {
        delete i;
    }
    delete selectedBlock;
}

bool Workspace::update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased, std::vector<int> unicodeEntered, std::string toolSelected) {
    bool mouseSelected = false;
    bool inputPressed = false;
    // Scroll
    if (mousePressed) {
        if (codeVerticalScroll.getGlobalBounds().contains(mousePos)) scrolling = "codeVertical";
        else if (codeHorizontalScroll.getGlobalBounds().contains(mousePos)) scrolling = "codeHorizontal";
    }
    if (!scrolling.empty()) {
        sf::Vector2f mouseDiff = mousePos - prevMousePos;
        if (mouseReleased) scrolling = "";
        if (scrolling == "codeVertical") {
            codeVerticalScroll.move(sf::Vector2f(0.f, mouseDiff.y));
            if (codeVerticalScroll.getGlobalBounds().top + codeVerticalScroll.getGlobalBounds().height > 880.f) {
                codeVerticalScroll.setPosition(sf::Vector2f(codeVerticalScroll.getPosition().x, 880.f - codeVerticalScroll.getGlobalBounds().height));
            }
            if (codeVerticalScroll.getGlobalBounds().top < 56.f) {
                codeVerticalScroll.setPosition(sf::Vector2f(codeVerticalScroll.getPosition().x, 56.f));
            }
            codeViewRect.top = codeViewMax.y * (codeVerticalScroll.getPosition().y - 56.f) / 824.f;
        }
        if (scrolling == "codeHorizontal") {
            codeHorizontalScroll.move(sf::Vector2f(mouseDiff.x, 0.f));
            if (codeHorizontalScroll.getGlobalBounds().left + codeHorizontalScroll.getGlobalBounds().width > 1190.f) {
                codeHorizontalScroll.setPosition(sf::Vector2f(1190.f - codeHorizontalScroll.getGlobalBounds().width, codeHorizontalScroll.getPosition().y));
            }
            if (codeHorizontalScroll.getGlobalBounds().left < 412.f) {
                codeHorizontalScroll.setPosition(sf::Vector2f(412.f, codeHorizontalScroll.getPosition().y));
            }
            codeViewRect.left = codeViewMax.x * (codeHorizontalScroll.getPosition().x - 412.f) / 778.f;
        }
        codeView = sf::View(codeViewRect);
        codeWindow->setView(codeView);
        mousePressed = false;
    }

    // Box
    if (basicTab.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x),
                                                         static_cast<float>(mousePos.y)))) {
        if (mousePressed) {
            mouseSelected = true;
            basicTab.setTexture(assets->getTexture("BOXTAB_PRESSED"));
            advancedTab.setTexture(assets->getTexture("BOXTAB"));
            microTab.setTexture(assets->getTexture("BOXTAB"));
            compTab.setTexture(assets->getTexture("BOXTAB"));
            boxTabSelected = "basic";
        }
    } else if (advancedTab.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x),
                                                                   static_cast<float>(mousePos.y)))) {
        if (mousePressed) {
            mouseSelected = true;
            basicTab.setTexture(assets->getTexture("BOXTAB"));
            advancedTab.setTexture(assets->getTexture("BOXTAB_PRESSED"));
            microTab.setTexture(assets->getTexture("BOXTAB"));
            compTab.setTexture(assets->getTexture("BOXTAB"));
            boxTabSelected = "advanced";
        }
    } else if (microTab.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x),
                                                                static_cast<float>(mousePos.y)))) {
        if (mousePressed) {
            mouseSelected = true;
            basicTab.setTexture(assets->getTexture("BOXTAB"));
            advancedTab.setTexture(assets->getTexture("BOXTAB"));
            microTab.setTexture(assets->getTexture("BOXTAB_PRESSED"));
            compTab.setTexture(assets->getTexture("BOXTAB"));
            boxTabSelected = "micro";
        }
    } else if (compTab.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x),
                                                               static_cast<float>(mousePos.y)))) {
        if (mousePressed) {
            mouseSelected = true;
            basicTab.setTexture(assets->getTexture("BOXTAB"));
            advancedTab.setTexture(assets->getTexture("BOXTAB"));
            microTab.setTexture(assets->getTexture("BOXTAB"));
            compTab.setTexture(assets->getTexture("BOXTAB_PRESSED"));
            boxTabSelected = "comp";
        }
    }
    if (mousePressed) {
        if (boxSprite.getGlobalBounds().contains(mousePos)) {
            if (selectedBlock) {
                delete selectedBlock;
                selectedBlock = nullptr;
            }
        }
    }
    for (auto block : boxes[boxTabSelected]) {
        std::vector<bool> blockOutput = block->update(mousePos - boxWindowOffset, mousePressed, unicodeEntered);
        if (blockOutput[1]) inputPressed = true;
        if (blockOutput[0]) {
            if (toolSelected == "move") {
                if (selectedBlock) {
                    if (block->shove(selectedBlock, mousePos - boxWindowOffset)) {
                        delete selectedBlock;
                        selectedBlock = nullptr;
                    }
                } else {
                    if (!blockOutput[1]) {
                        selectedBlock = new Block(*block->getSelected(mousePos - boxWindowOffset, true));
                    }
                }
            } else if (toolSelected == "clone") {
                if (selectedBlock) {
                    block->shove(selectedBlock, mousePos - boxWindowOffset);
                } else {
                    if (!blockOutput[1]) {
                        selectedBlock = new Block(*block->getSelected(mousePos - boxWindowOffset, false));
                    }
                }
            } else if (toolSelected == "delete") {
                block->getSelected(mousePos - boxWindowOffset, true);
            }
        }
    }

    // Code
    codeViewMax = sf::Vector2f(788.f, 814.f);
    int tabs = 0;
    sf::Vector2f codeMousePos = mousePos - codeWindowOffset + sf::Vector2f(codeViewRect.left, codeViewRect.top);
    if (toolSelected == "swap line") {
        if (codeSprite.getGlobalBounds().contains(mousePos)) {
            if (lineSelected == -1) {
                if (mousePressed) {
                    if (static_cast<float>(codeLines.size()) * 20.f >= codeMousePos.y) {
                        lineSelected = static_cast<int>(codeMousePos.y) / 20;
                        highlightLine.setPosition(0.f, static_cast<float>(lineSelected) * 20.f);
                    }
                }
            } else {
                if (static_cast<float>(codeLines.size()-1) * 20.f + 10.f >= codeMousePos.y) {
                    insertionLine.setPosition(0.f, static_cast<float>((static_cast<int>(codeMousePos.y + 10)) / 20) * 20.f - 1.f);
                    insertLineSelected = static_cast<int>((codeMousePos.y +10)/20);
                    if (insertLineSelected == codeLines.size()) insertLineSelected --;
                }
                if (mousePressed && insertLineSelected != -1) {
                    Block *tempBlock = nullptr;
                    if (codeLines[lineSelected]->getBlock()) tempBlock = new Block(*codeLines[lineSelected]->getBlock());
                    delete codeLines[lineSelected];
                    codeLines.erase(codeLines.begin()+lineSelected);
                    codeLines.insert(codeLines.begin()+insertLineSelected, new Line(assets, insertLineSelected));
                    codeLines[insertLineSelected]->shove(tempBlock, sf::Vector2f(0.f, 0.f));
                    delete tempBlock;
                    lineSelected = -1;
                    insertLineSelected = -1;
                    for (int i = 1; i <= codeLines.size(); i ++) {
                        codeLines[i-1]->setNum(i);
                    }
                }
            }
        }
    } else {
        lineSelected = -1;
        insertLineSelected = -1;
    }
    for (auto line: codeLines) {
        std::string codeName = line->getBlock() ? line->getBlock()->getCodeName() : "";
        if (codeName == "End" && tabs > 0) tabs--;
        std::vector<bool> lineOutput = line->update(codeMousePos, mousePressed, unicodeEntered, tabs);
        codeViewMax.x = std::max(codeViewMax.x, line->getWidth() + 80.f);
        if (codeName == "If" || codeName == "Else" || codeName == "ElseIf" || codeName == "While" || codeName == "Loop" || codeName == "Setup") tabs ++;
        if (lineOutput[1]) inputPressed = true;
        if (lineOutput[0]) {
            if (toolSelected == "move") {
                if (selectedBlock) {
                    if (line->shove(selectedBlock, codeMousePos)) {
                        delete selectedBlock;
                        selectedBlock = nullptr;
                    }
                } else if (!inputPressed) {
                    Block *tempBlock = line->getSelected(codeMousePos, true);
                    if (tempBlock) {
                        selectedBlock = new Block(*tempBlock);
                        if (tempBlock == line->getBlock()) line->deleteBlock();
                    }
                }
            } else if (toolSelected == "clone") {
                if (selectedBlock) {
                    line->shove(selectedBlock, codeMousePos);
                } else if (!inputPressed) {
                    Block *tempBlock = line->getSelected(codeMousePos, false);
                    if (tempBlock) {
                        selectedBlock = new Block(*tempBlock);
                    }
                }
            } else if (toolSelected == "delete") {
                Block *tempBlock = line->getSelected(codeMousePos, true);
                if (tempBlock) {
                    if (tempBlock == line->getBlock()) line->deleteBlock();
                    else delete tempBlock;
                }
            }
        }
    }
    codeViewMax.y = std::max(codeViewMax.y, static_cast<float>(codeLines.size()) * 20.f + 400.f);
    codeVerticalScroll.setSize(sf::Vector2f(10.f, 814.f/codeViewMax.y * 824.f));
    codeHorizontalScroll.setSize(sf::Vector2f(778.f/codeViewMax.x * 824.f, 10.f));
    insertionLine.setSize(sf::Vector2f(codeViewMax.x, 2.f));
    highlightLine.setSize(sf::Vector2f(codeViewMax.x, 20.f));
    if (addLine.getGlobalBounds().contains(mousePos) && mousePressed) codeLines.emplace_back(new Line(assets, codeLines.size() + 1));
    else if (deleteLine.getGlobalBounds().contains(mousePos) && mousePressed) if (!codeLines.empty()) codeLines.pop_back();
    lineBackground.setSize(sf::Vector2f(lineBackground.getSize().x, codeViewMax.y));

    // Other
    if (selectedBlock) {
        selectedBlock->setPosition(mousePos);
        std::vector<bool> blockOutput = selectedBlock->update(mousePos, mouseSelected, unicodeEntered);
    }
    prevMousePos = mousePos;
    return mouseSelected;
}

void Workspace::draw(sf::RenderTarget &target) {
    // Box
    target.draw(basicTab);
    target.draw(advancedTab);
    target.draw(microTab);
    target.draw(compTab);
    target.draw(boxDivider);
    for (const auto& symbol : symbols) {
        target.draw(symbol);
    }
    boxWindow->clear(sf::Color(246, 246, 246));
    for (auto block : boxes[boxTabSelected]) block->draw(*boxWindow);
    boxWindow->display();
    boxSprite = sf::Sprite(boxWindow->getTexture());
    boxSprite.setPosition(boxWindowOffset);
    target.draw(boxSprite);

    // Code
    codeWindow->clear(sf::Color::White);
    codeWindow->draw(lineBackground);
    int count = 0;
    for (auto line : codeLines) {
        if (lineSelected == count) {
            codeWindow->draw(highlightLine);
            if (insertLineSelected != -1) codeWindow->draw(insertionLine);
        }
        line->draw(*codeWindow);
        count ++;
    }
    codeWindow->display();
    codeSprite = sf::Sprite(codeWindow->getTexture());
    codeSprite.setPosition(codeWindowOffset);
    target.draw(codeSprite);
    target.draw(infoBar);
    target.draw(addLine);
    target.draw(deleteLine);
    target.draw(codeVerticalScroll);
    target.draw(codeHorizontalScroll);

    // Other
    if (selectedBlock) selectedBlock->draw(target);
}

std::string Workspace::getCode() {
    std::stringstream code;
    for (auto line : codeLines) {
        code << line->getCode() << "\n";
    }
    return code.str();
}

void Workspace::loadRawFile(const std::string& content) {
    // Split string by line
    std::vector<std::string> contentSplit;
    std::vector<std::string> emptyStringVector;
    std::stringstream ss(content);
    std::string contentLine;
    while (std::getline(ss, contentLine)) {
        contentSplit.push_back(contentLine);
    }
    for (auto line : codeLines) {
        delete line;
    }
    // Processing each line to Blocks
    codeLines.clear();
    int lineNum = 0;
    for (const auto& con : contentSplit) {
        lineNum ++;
        codeLines.emplace_back(new Line(assets, lineNum));
        std::vector<std::vector<std::string>> lineContent;
        int layer = 0;
        for (char c : con) {
            if (layer + 1 > lineContent.size()) lineContent.emplace_back(emptyStringVector);
            if (c == '(') layer ++;
            else if (c == ')') layer --;
            else if (c == ',') lineContent[layer].emplace_back("");
            else {
                if (lineContent[layer].empty()) lineContent[layer].emplace_back("");
                lineContent[layer][lineContent[layer].size()-1] += c;
            }
        }
        if (!lineContent.empty()){
            std::queue<std::pair<std::string, Block *>> curr, prev;
            for (int i = lineContent.size() - 1; i >= 0; i--) {
                for (auto strContent: lineContent[i]) {
                    if (strContent.empty()) {
                        curr.push(std::make_pair("", nullptr));
                    } else if (strContent[0] == '*') {
                        std::vector<std::string> tempStrArgs;
                        std::vector<Block *> tempBlockArgs;
                        Block *tempBlock = getBlockByName(strContent.substr(1));
                        for (int i = 0; i < tempBlock->getNumArgs(); i++) {
                            std::pair<std::string, Block *> singleArg = prev.front();
                            prev.pop();
                            tempStrArgs.push_back(singleArg.first);
                            tempBlockArgs.push_back(singleArg.second);
                        }
                        tempBlock->setArgs(tempStrArgs, tempBlockArgs);
                        curr.push(std::make_pair("", tempBlock));
                    } else {
                        curr.push(std::make_pair(strContent, nullptr));
                    }
                }
                prev = curr;
                curr = std::queue<std::pair<std::string, Block *>>();
            }
            codeLines[lineNum - 1]->shove(prev.front().second, sf::Vector2f(0.f, 0.f));
            delete prev.front().second;
            prev.pop();
        }
    }
}

Block *Workspace::getBlockByName(const std::string& name) {
    // Basic Blocks
    if (name == "Set") return new Set(assets);
    else if (name == "Get") return new Get(assets);
    else if (name == "Add") return new Add(assets);
    else if (name == "Minus") return new Minus(assets);
    else if (name == "Multiply") return new Multiply(assets);
    else if (name == "Divide") return new Divide(assets);

    // Advanced Blocks
    if (name == "Equal") return new Equal(assets);
    else if (name == "Greater") return new Greater(assets);
    else if (name == "Less") return new Less(assets);
    else if (name == "And") return new And(assets);
    else if (name == "Or") return new Or(assets);
    else if (name == "Not") return new Not(assets);
    else if (name == "While") return new While(assets);
    else if (name == "If") return new If(assets);
    else if (name == "ElseIf") return new ElseIf(assets);
    else if (name == "Else") return new Else(assets);
    else if (name == "End") return new End(assets);

    // Micro Blocks
    if (name == "SetOutputPin") return new SetOutputPin(assets);
    else if (name == "SetInputPin") return new SetInputPin(assets);
    else if (name == "SetInputButtonPin") return new SetInputButtonPin(assets);
    else if (name == "Setup") return new Setup(assets);
    else if (name == "Loop") return new Loop(assets);
    else if (name == "WritePin") return new WritePin(assets);
    else if (name == "ReadPin") return new ReadPin(assets);
    else if (name == "On") return new On(assets);
    else if (name == "Off") return new Off(assets);
    else if (name == "Wait") return new Wait(assets);

    return nullptr;
}

void Workspace::deleteSelected() {
    delete selectedBlock;
    selectedBlock = nullptr;
}

void Workspace::clearCode() {
    for (int i = 0; i < codeLines.size(); i ++) {
        codeLines[i]->deleteBlock();
    }
}



