#include "../blocks/Block.h"


#ifndef MICROSMARTZ_LINE_H
#define MICROSMARTZ_LINE_H

/*
 * Line
 * Object for storing all command blocks to be compiled
 */


class Line {
private:
    Block *block;
    sf::RenderTexture blockTexture;
    sf::Sprite sprite;
    sf::Text numText;
    int lineNum;
    AssetsManager *assets;
    void updateTextPosition();
    sf::Vector2f blockPos;
    int tabs;
    sf::RectangleShape tab;
public:
    Line(AssetsManager *assets, int num);
    ~Line();
    std::vector<bool> update(sf::Vector2f mousePos, bool mousePressed, const std::vector<int>& unicodeEntered, int tabs);
    void draw(sf::RenderTarget &target);
    bool shove(Block *other, sf::Vector2f mousePos);
    Block *getSelected(sf::Vector2f mousePos, bool d);
    void deleteBlock();
    Block *getBlock();
    float getWidth();
    std::string getCode();
    void setNum(int num);
};


#endif //MICROSMARTZ_LINE_H
