#include "BlockI.h"
#include "Board.h"
using namespace std;

BlockI::BlockI(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'I';
    level = level1;
    coordinates.at(0).set_x(0);
    coordinates.at(0).set_y(3);
    coordinates.at(1).set_x(1);
    coordinates.at(1).set_y(3);
    coordinates.at(2).set_x(2);
    coordinates.at(2).set_y(3);
    coordinates.at(3).set_x(3);
    coordinates.at(3).set_y(3);
    numCell=4;
    isOver1 = false;
    //check if the gave is over
    for (int i = 0; i < 4; ++i) {
        if (b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y())) isOver1 = true;
    }
    //set cells to block type
    for (int i = 0; i < 4; ++i){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, nullptr);
    }
}




BlockI::~BlockI(){
    coordinates.clear();
}

void BlockI::clockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //set cells to block type
    for(int i = 0 ;i < 4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(coordinates.at(0).get_y() == coordinates.at(1).get_y()){
        
        coordinates.at(0).add_y(-3);
        coordinates.at(1).add_y(-2);
        coordinates.at(1).add_x(-1);
        coordinates.at(2).add_y(-1);
        coordinates.at(2).add_x(-2);
        coordinates.at(3).add_x(-3);
        
    }
    else if(coordinates.at(0).get_x() == coordinates.at(1).get_x()){
        if(coordinates.at(0).get_x() < 7){
            
            coordinates.at(0).add_y(3);
            coordinates.at(1).add_y(2);
            coordinates.at(1).add_x(1);
            coordinates.at(2).add_x(2);
            coordinates.at(2).add_y(1);
            coordinates.at(3).add_x(3);
        }
    }
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || coordinates.at(i).get_y() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    if(!temp){
        if(coordinates.at(0).get_y() == coordinates.at(1).get_y()){
            
            coordinates.at(0).add_y(-3);
            coordinates.at(1).add_y(-2);
            coordinates.at(1).add_x(-1);
            coordinates.at(2).add_y(-1);
            coordinates.at(2).add_x(-2);
            coordinates.at(3).add_x(-3);
            
            
        }
        else if(coordinates.at(0).get_x() == coordinates.at(1).get_x()){
            if(coordinates.at(0).get_x() < 7){
                
                coordinates.at(0).add_y(3);
                coordinates.at(1).add_y(2);
                coordinates.at(1).add_x(1);
                coordinates.at(2).add_x(2);
                coordinates.at(2).add_y(1);
                coordinates.at(3).add_x(3);
            }
        }
        //set cells to block type
    }
    for(int i=0; i < 4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}




void BlockI::counterclockwise(shared_ptr<Board>b){
    clockwise(b);
}
