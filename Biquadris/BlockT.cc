#include "BlockT.h"
#include "Board.h"

using namespace std;

BlockT::BlockT(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'T';
    level = level1;
    TShape = 1;
    
    coordinates.at(0).set_x(0);
    coordinates.at(0).set_y(3);
    coordinates.at(2).set_x(1);
    coordinates.at(2).set_y(3);
    coordinates.at(1).set_x(2);
    coordinates.at(1).set_y(3);
    coordinates.at(3).set_x(1);
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

BlockT::~BlockT(){
    coordinates.clear();
}

void BlockT::clockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(TShape == 1){
        TShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        TShape = 2;
    }
    else if(TShape == 2){
        TShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        TShape = 3;
    }
    else if(TShape == 3){
        TShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        TShape = 4;
    }
    else if(TShape == 4){
        TShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        TShape = 1;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(TShape == 1){
            TShape4(coordinates.at(2).get_y()+1, coordinates.at(2).get_x(), b);//
            TShape = 4;
        }
        else if(TShape == 4){
            TShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x()+1, b); //
            TShape = 3;
        }
        else if(TShape == 3){
            TShape2(coordinates.at(2).get_y()-1, coordinates.at(2).get_x(), b); //
            TShape = 2;
        }
        else if(TShape == 2){
            TShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x()-1, b);//
            TShape = 1;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void BlockT::counterclockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(TShape == 1){
        TShape4(coordinates.at(2).get_y()+1, coordinates.at(2).get_x(), b);//
        TShape = 4;
    }
    else if(TShape == 2){
        TShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x()-1, b);//
        TShape = 1;
    }
    else if(TShape == 3){
        TShape2(coordinates.at(2).get_y()-1, coordinates.at(2).get_x(), b); //
        TShape = 2;
    }
    else if(TShape == 4){
        TShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x()+1, b); //
        TShape = 3;
    }
    //set cells to the block type
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(TShape == 4){
            TShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            TShape = 1;
        }
        else if(TShape == 1){
            TShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            TShape = 2;
        }
        else if(TShape == 2){
            TShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            TShape = 3;
        }
        else if(TShape == 3){
            TShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            TShape = 4;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

// different shapes of T for rotation

void BlockT::TShape1(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy);
    coordinates.at(1).set_x(xx+2);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx+1);
    coordinates.at(3).set_y(yy+1);
    coordinates.at(3).set_x(xx+1);
}

void BlockT::TShape2(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-1);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy+1);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx-1);
}

void BlockT::TShape3(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy+1);
    coordinates.at(0).set_x(xx+1);
    coordinates.at(1).set_y(yy+1);
    coordinates.at(1).set_x(xx-1);
    coordinates.at(2).set_y(yy+1);
    coordinates.at(2).set_x(xx);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx);
}

void BlockT::TShape4(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy);
    coordinates.at(0).set_x(xx-1);
    coordinates.at(1).set_y(yy-2);
    coordinates.at(1).set_x(xx-1);
    coordinates.at(2).set_y(yy-1);
    coordinates.at(2).set_x(xx-1);
    coordinates.at(3).set_y(yy-1);
    coordinates.at(3).set_x(xx);
}
