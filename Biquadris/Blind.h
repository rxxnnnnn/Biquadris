#ifndef __BLIND_H__
#define __BLIND_H__
#include "seDecorator.h"
#include "Board.h"
#include "SpecialEffect.h"
#include <memory>

class Blind: public seDecorator{
    std::shared_ptr<Board>  myboard;
public:
    Blind(std::shared_ptr<SpecialEffect>  se);
    void setBoard(std::shared_ptr<Board>  theboard);
    void produceEffect();
};







#endif
