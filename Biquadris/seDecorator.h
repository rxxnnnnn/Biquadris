#ifndef __SEDECORATOR_H__
#define __SEDECORATOR_H__
#include "SpecialEffect.h"
#include <memory>


//the decorator of class SpecialEffect
class seDecorator: public SpecialEffect{
protected:
    std::shared_ptr<SpecialEffect>  se;
public:
    seDecorator(std::shared_ptr<SpecialEffect>  se);
    virtual ~seDecorator();
};

#endif
