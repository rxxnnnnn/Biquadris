#include "BlockL.h"
#include "Board.h"

using namespace std;

BlockL::BlockL(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'L';
    level = level1;
    LShape = 1;
    coordinates.at(0).set_x(0);
    coordinates.at(0).set_y(4);
    coordinates.at(1).set_x(1);
    coordinates.at(1).set_y(4);
    coordinates.at(2).set_x(2);
    coordinates.at(2).set_y(4);
    coordinates.at(3).set_x(2);
    coordinates.at(3).set_y(3);
    
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

BlockL::~BlockL(){
    coordinates.clear();
}

void BlockL::clockwise(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    bool temp = true;
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    
    if(LShape == 1){
        LShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        LShape = 2;
    }
    else if(LShape == 2){
        LShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        LShape = 3;
    }
    else if(LShape == 3){
        LShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        LShape = 4;
    }
    else if(LShape == 4){
        LShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        LShape = 1;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(LShape == 1){
            LShape4(coordinates.at(2).get_y()-1, coordinates.at(2).get_x()-2, b);
            LShape = 4;
        }
        else if(LShape == 4){
            LShape3(coordinates.at(2).get_y()+2, coordinates.at(2).get_x()-1, b);
            LShape = 3;
        }
        else if(LShape == 3){
            LShape2(coordinates.at(2).get_y()+1, coordinates.at(2).get_x()+2, b);
            LShape = 2;
        }
        else if(LShape == 2){
            LShape1(coordinates.at(2).get_y()-2, coordinates.at(2).get_x()+1, b);
            LShape = 1;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void BlockL::counterclockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(LShape == 1){
        LShape4(coordinates.at(2).get_y()-1, coordinates.at(2).get_x()-2, b);
        LShape = 4;
    }
    else if(LShape == 2){
        LShape1(coordinates.at(2).get_y()-2, coordinates.at(2).get_x()+1, b);
        LShape = 1;
    }
    else if(LShape == 3){
        LShape2(coordinates.at(2).get_y()+1, coordinates.at(2).get_x()+2, b);
        LShape = 2;
    }
    else if(LShape == 4){
        LShape3(coordinates.at(2).get_y()+2, coordinates.at(2).get_x()-1, b);
        LShape = 3;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(LShape == 4){
            LShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            LShape = 1;
        }
        else if(LShape == 1){
            LShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            LShape = 2;
        }
        else if(LShape == 2){
            LShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            LShape = 3;
        }
        else if(LShape == 3){
            LShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            LShape = 4;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}


// different shapes of L for rotation
void BlockL::LShape1(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy+2);
    coordinates.at(0).set_x(xx-1);
    coordinates.at(1).set_y(yy+2);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy+2);
    coordinates.at(2).set_x(xx+1);
    coordinates.at(3).set_y(yy+1);
    coordinates.at(3).set_x(xx+1);
}

void BlockL::LShape2(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-2);
    coordinates.at(0).set_x(xx-2);
    coordinates.at(1).set_y(yy-1);
    coordinates.at(1).set_x(xx-2);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx-2);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx-1);
}

void BlockL::LShape3(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-1);
    coordinates.at(0).set_x(xx+2);
    coordinates.at(1).set_y(yy-1);
    coordinates.at(1).set_x(xx+1);
    coordinates.at(2).set_y(yy-1);
    coordinates.at(2).set_x(xx);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx);
}

void BlockL::LShape4(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy+1);
    coordinates.at(0).set_x(xx+1);
    coordinates.at(1).set_y(yy);
    coordinates.at(1).set_x(xx+1);
    coordinates.at(2).set_y(yy-1);
    coordinates.at(2).set_x(xx+1);
    coordinates.at(3).set_y(yy-1);
    coordinates.at(3).set_x(xx);
}
