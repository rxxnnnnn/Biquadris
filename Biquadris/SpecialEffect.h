#ifndef __SPECIALEFFECT_H__
#define __SPECIALEFFECT_H__
#include "Board.h"

class SpecialEffect{
public:
    virtual void setBoard(std::shared_ptr<Board>  myboard) = 0;
    virtual void produceEffect() = 0;
    virtual ~SpecialEffect();
};

#endif
