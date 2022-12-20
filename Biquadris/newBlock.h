#ifndef _NEWBLOCK_H
#define _NEWBLOCK_H

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include "Block.h"
#include "Board.h"

class newBlock{
    int level;
    int seed;
    std:: string filename;
    std:: ifstream ifseq;
    bool isChanged;
    bool isRandom;
    char newtype;
    std::shared_ptr<Board>  b;
    char checktype(std::string type);
public:
    newBlock(int level, int seed, std::string f);
    ~newBlock();
    char getBlock();
    void setNoRandom();
    void setRandom();
    void addLevel();
    void subLevel();
};


#endif
