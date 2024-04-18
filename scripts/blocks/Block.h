#include "../AssetsManager.h"
#include "block-components/BlockString.h"
#include "block-components/BlockNameInput.h"
#include "block-components/BlockValueInput.h"
#include "block-components/BlockEnd.h"

#ifndef MICROSMARTZ_BLOCK_H
#define MICROSMARTZ_BLOCK_H


/*
 * Block
 * Base class for all the block commands
 */

class Block {
protected:
     sf::RenderTexture texture;
     sf::Sprite sprite;
     sf::Vector2f size;
     sf::Vector2f pos;
     std::vector<BlockComponent*> components;
     std::vector<Block*> valueBlocks;
     bool display;
     std::string returnType;
     std::string codeName;

public:
    Block();
    virtual ~Block();
    virtual std::string getCode();
    virtual std::vector<bool> update(sf::Vector2f mousePos, bool mousePressed, std::vector<int> unicodeEntered);
    virtual void draw(sf::RenderTarget &target);
    virtual void setPosition(sf::Vector2f pos);
    virtual sf::Vector2f getPosition();
    virtual void setDisplay(bool display);
    virtual bool isDisplay();
    Block(const Block &other);
    virtual std::string getReturnType();
    virtual bool shove(Block* other, sf::Vector2f mousePos);
    virtual void vBlocksSetup();
    virtual sf::Vector2f getSize();
    virtual Block *getSelected(sf::Vector2f mousePos, bool d);
    std::string getCodeName();
    void setArgs(const std::vector<std::string>& strArgs, std::vector<Block*> blockArgs);
    int getNumArgs();
};


#endif //MICROSMARTZ_BLOCK_H
