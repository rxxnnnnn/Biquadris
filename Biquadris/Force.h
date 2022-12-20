#ifndef __FORCE_H__
#define __FORCE_H__
#include "seDecorator.h"
#include "Board.h"
#include "SpecialEffect.h"
#include "newBlock.h"
#include <memory>

class Force: public seDecorator{
    char nextblock;
    char * affected;
    std::shared_ptr<Board>  myboard;
public:
    Force(std::shared_ptr<SpecialEffect>  se, char nextblock, char * affected);
    void setBoard(std::shared_ptr<Board>  theboard);
    void produceEffect();
};


#endif

