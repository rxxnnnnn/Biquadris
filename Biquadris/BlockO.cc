#include "BlockO.h"
#include "Board.h"

using namespace std;

BlockO::BlockO(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'O';
    level = level1;
    
    coordinates.at(0).set_x(0);
    coordinates.at(0).set_y(3);
    coordinates.at(1).set_x(0);
    coordinates.at(1).set_y(4);
    coordinates.at(2).set_x(1);
    coordinates.at(2).set_y(3);
    coordinates.at(3).set_x(1);
    coordinates.at(3).set_y(4);
    
    numCell=4;
    
    isOver1 = false;
    for (int i = 0; i < 4; ++i) {
        if (b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            isOver1 = true;
    }
    //set cells to block type
    for (int i = 0; i < 4; ++i){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, nullptr);
    }
}

BlockO::~BlockO(){
    coordinates.clear();
}

void BlockO::clockwise(shared_ptr<Board>b){}

void BlockO::counterclockwise(shared_ptr<Board>b){}
