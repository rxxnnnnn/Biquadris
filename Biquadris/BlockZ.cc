#include "BlockZ.h"
#include "Board.h"
using namespace std;

BlockZ::BlockZ(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'Z';
    level = level1;
    ZShape = 1;
    
    coordinates.at(0).set_x(0);
    coordinates.at(0).set_y(3);
    coordinates.at(1).set_x(1);
    coordinates.at(1).set_y(3);
    coordinates.at(2).set_x(1);
    coordinates.at(2).set_y(4);
    coordinates.at(3).set_x(2);
    coordinates.at(3).set_y(4);
    
    numCell=4;
    
    isOver1 = false;
    for (int i = 0; i < 4; i++) {
        if (b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            isOver1 = true;
    }
    //set cells to block type
    for (int i = 0; i < 4; ++i){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, nullptr);
    }
    
}

BlockZ::~BlockZ(){
    coordinates.clear();
}

void BlockZ::clockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    
    if(ZShape == 1){
        ZShape2(coordinates.at(0).get_y()+1, coordinates.at(0).get_x(), b);
        ZShape = 2;
    }
    else if(ZShape == 2){
        ZShape1(coordinates.at(1).get_y(), coordinates.at(1).get_x(), b);
        ZShape = 1;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(ZShape == 1) {
            ZShape2(coordinates.at(0).get_y()+1, coordinates.at(0).get_x(), b); //
            ZShape = 2;
        }
        else if(ZShape == 2){
            ZShape1(coordinates.at(1).get_y(), coordinates.at(1).get_x(), b); //
            ZShape = 1;
        }
        
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void BlockZ::counterclockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(ZShape == 1){
        ZShape2(coordinates.at(0).get_y()+1, coordinates.at(0).get_x(), b);
        ZShape = 2;
    }
    else if(ZShape == 2){
        ZShape1(coordinates.at(1).get_y(), coordinates.at(1).get_x(), b);
        ZShape = 1;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(ZShape == 2){
            ZShape1(coordinates.at(1).get_y(), coordinates.at(1).get_x(), b);
            ZShape = 1;
        }
        else if(ZShape == 1){
            ZShape2(coordinates.at(0).get_y()+1, coordinates.at(0).get_x(), b);
            ZShape = 2;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}
// different shapes of Z for rotation
void BlockZ::ZShape1(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-1);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy-1);
    coordinates.at(1).set_x(xx+1);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx+1);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx+2);
}

void BlockZ::ZShape2(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-1);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy-2);
    coordinates.at(2).set_x(xx+1);
    coordinates.at(3).set_y(yy-1);
    coordinates.at(3).set_x(xx+1);
}



// void BlockZ::ZShape3(int yy, int xx, shared_ptr<Board>b){
//     coordinates.at(0).set_y(yy+1);
//     coordinates.at(0).set_x(xx+2);
//     coordinates.at(1).set_y(yy+1);
//     coordinates.at(1).set_x(xx+1);
//     coordinates.at(2).set_y(yy);
//     coordinates.at(2).set_x(xx+1);
//     coordinates.at(3).set_y(yy);
//     coordinates.at(3).set_x(xx);
// }

// void BlockZ::ZShape4(int yy, int xx, shared_ptr<Board>b){
//     coordinates.at(0).set_y(yy+1);
//     coordinates.at(0).set_x(xx-1);
//     coordinates.at(1).set_y(yy);
//     coordinates.at(1).set_x(xx-1);
//     coordinates.at(2).set_y(yy);
//     coordinates.at(2).set_x(xx);
//     coordinates.at(3).set_y(yy-1);
//     coordinates.at(3).set_x(xx);
// }
