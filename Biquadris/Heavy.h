#ifndef __HEAVY_H__
#define __HEAVY_H__
#include "seDecorator.h"
#include "Board.h"
#include "SpecialEffect.h"
#include <memory>

class Heavy: public seDecorator{
    std::shared_ptr<Board>  myboard;
public:
    Heavy(std::shared_ptr<SpecialEffect>  se);
    void setBoard(std::shared_ptr<Board>  theboard);
    void produceEffect();
};


#endif
