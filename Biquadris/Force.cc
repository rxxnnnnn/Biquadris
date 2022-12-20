#include "Force.h"
#include "Board.h"
#include "SpecialEffect.h"
using namespace std;

//constructor
Force::Force(shared_ptr<SpecialEffect> se, char nextblock, char * affected):seDecorator(se), nextblock{nextblock}, affected{affected}{} //affected is the newBlock of another player

//set the board producing this effect
void Force::setBoard(shared_ptr<Board>theboard){
    se->setBoard(theboard);
    myboard = theboard;
}


//produce effect on the newBlock of another player
void Force::produceEffect(){
    se->produceEffect();
    *affected = nextblock;
}
