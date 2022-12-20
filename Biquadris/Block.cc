#include "Board.h"
#include "Position.h"
#include "Block.h"
#include <vector>
using namespace std;

Block::Block(){}
Block::~Block(){}

//assign the cells with the block as its belonged
void Block::assignbelong(shared_ptr<Board> b , shared_ptr<Block> myblock){
    for (int i= 0 ; i < numCell; i++){
        b->assignbelong(coordinates.at(i).get_x(), coordinates.at(i).get_y(), myblock);
    }
}

/* Check if the direction of the movement is allowed */

bool Block::canDown(shared_ptr<Board>b){
    for (int i= 0 ; i < numCell; i++){
        if(coordinates.at(i).get_y() == 17) return false;                //top index is 0; bottom index is 17
        else if(b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()+1)) return false;
    }
    return true;
}

bool Block::canLeft(shared_ptr<Board>b){
    for (int i= 0 ; i < numCell; i++){
        if(coordinates.at(i).get_x() == 0) return false;                 //left index is 0; right index is 10
        else if(b->if_occupied(coordinates.at(i).get_x()-1, coordinates.at(i).get_y())) return false;
    }
    return true;
}

bool Block::canRight(shared_ptr<Board>b){
    for (int i= 0 ; i < numCell; i++){
        if(coordinates.at(i).get_x() == 10) return false;                 //left index is 0; right index is 10
        else if(b->if_occupied(coordinates.at(i).get_x()+1, coordinates.at(i).get_y())) return false;
    }
    return true;
}

/* If the direction of the movement is allowed, move in that direction */

void Block::left(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    
    if(canLeft(b)){
        for(int i = 0; i < numCell; i++){
            coordinates.at(i).set_x(coordinates.at(i).get_x()-1);
        }
    }
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void Block::right(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(canRight(b)){
        for(int i = 0; i < numCell; i++){
            coordinates.at(i).set_x(coordinates.at(i).get_x()+1);
        }
    }
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void Block::down(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(canDown(b)){
        for(int i = 0; i < numCell; i++){
            coordinates.at(i).set_y(coordinates.at(i).get_y()+1);
        }
    }
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void Block::drop(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    while(canDown(b)) {
        for(int i = 0; i < numCell; i++){
            coordinates.at(i).set_y(coordinates.at(i).get_y()+1);
        }
    }
    for(int i = 0; i < numCell; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

int Block::getLevel(){
    return level;
}

char Block::getType(){
    return ijloszt;
}

/* return true if the game is over */
bool Block::isOver(){ return isOver1; }

/* set all the cells in a block to blank to clear */
void Block::my_clear(shared_ptr<Board>b){
    for(int i = 0; i<numCell;i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
}

/* decrement the number of cells */
int Block::CellDeleted(){
    numCell--;
    return numCell;
}




