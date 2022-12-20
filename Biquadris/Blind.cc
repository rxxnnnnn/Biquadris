#include "Blind.h"
#include "Board.h"
#include "SpecialEffect.h"
using namespace std;

//constructor
Blind::Blind(shared_ptr<SpecialEffect> se):seDecorator(se){}

//set the board producing this effect
void Blind::setBoard(shared_ptr<Board> theboard){
    se->setBoard(theboard);
    myboard = theboard;
}

//produce effect on another player
void Blind::produceEffect(){
    se->produceEffect();
    myboard->anotherBoard()->setBlind(true); //remember to set it to false when a new block is dropped
}
