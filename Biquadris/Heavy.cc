#include "Heavy.h"
#include "Board.h"
#include "SpecialEffect.h"
using namespace std;

//constructor
Heavy::Heavy(shared_ptr<SpecialEffect> se):seDecorator(se){}

//set the board producing this effect
void Heavy::setBoard(shared_ptr<Board>theboard){ 
    se->setBoard(theboard);
    myboard = theboard;
}

//produce effect on another player
void Heavy::produceEffect(){
    se->produceEffect();
    myboard->anotherBoard()->setheavy(myboard->anotherBoard()->heavyLevel()+2);
}
