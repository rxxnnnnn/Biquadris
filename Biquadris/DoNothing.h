#ifndef __DONOTHING_H__
#define __DONOTHING_H__
#include "SpecialEffect.h"
#include "Board.h"
#include <memory>

//a subcalss of class SpecialEffect which does nothing
class DoNothing: public SpecialEffect{
    std::shared_ptr<Board>  myboard;
public:
    void setBoard(std::shared_ptr<Board>  theboard){ myboard = theboard; };
    void produceEffect(){};
};

#endif
