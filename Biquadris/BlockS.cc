#include "BlockS.h"
#include "Board.h"

using namespace std;

BlockS::BlockS(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'S';
    level = level1;
    SShape = 1;
    
    coordinates.at(0).set_x(2);
    coordinates.at(0).set_y(3);
    coordinates.at(1).set_x(1);
    coordinates.at(1).set_y(3);
    coordinates.at(2).set_x(1);
    coordinates.at(2).set_y(4);
    coordinates.at(3).set_x(0);
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

BlockS::~BlockS(){
    coordinates.clear();
}

void BlockS::clockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(SShape == 1){
        SShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        SShape = 2;
    }
    else if(SShape == 2){
        SShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        SShape = 3;
    }
    else if(SShape == 3){
        SShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        SShape = 4;
    }
    else if(SShape == 4){
        SShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        SShape = 1;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || coordinates.at(i).get_y() < 0
            || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    if(!temp){
        if(SShape == 1){
            SShape4(coordinates.at(2).get_y()+1, coordinates.at(2).get_x(), b);// !!!
            SShape = 4;
        }
        else if(SShape == 4){
            SShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x()-1, b); //
            SShape = 3;
        }
        else if(SShape == 3){
            SShape2(coordinates.at(2).get_y()+1, coordinates.at(2).get_x(), b);//
            SShape = 2;
        }
        else if(SShape == 2){
            SShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x()+1, b);//
            SShape = 1;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void BlockS::counterclockwise(shared_ptr<Board>b){
    bool temp = true;
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    //clear the original block
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    if(SShape == 1){
        SShape4(coordinates.at(2).get_y()+1, coordinates.at(2).get_x(), b);//
        SShape = 4;
    }
    else if(SShape == 2){
        SShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x()+1, b);//
        SShape = 1;
    }
    else if(SShape == 3){
        SShape2(coordinates.at(2).get_y()+1, coordinates.at(2).get_x(), b);//
        SShape = 2;
    }
    else if(SShape == 4){
        SShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x()-1, b);//
        SShape = 3;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || coordinates.at(i).get_y() < 0
            || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(SShape == 4){
            SShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            SShape = 1;
        }
        else if(SShape == 1){
            SShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            SShape = 2;
        }
        else if(SShape == 2){
            SShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            SShape = 3;
        }
        else if(SShape == 3){
            SShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            SShape = 4;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

// different shapes of L for rotation
void BlockS::SShape1(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy+1);
    coordinates.at(0).set_x(xx-1);
    coordinates.at(1).set_y(yy+1);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx+1);
}

void BlockS::SShape2(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy-1);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy-1);
    coordinates.at(2).set_x(xx-1);
    coordinates.at(3).set_y(yy-2);
    coordinates.at(3).set_x(xx-1);
}

void BlockS::SShape3(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy+1);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy+1);
    coordinates.at(1).set_x(xx+1);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx+1);
    coordinates.at(3).set_y(yy);
    coordinates.at(3).set_x(xx+2);
}

void BlockS::SShape4(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-1);
    coordinates.at(0).set_x(xx-1);
    coordinates.at(1).set_y(yy);
    coordinates.at(1).set_x(xx-1);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx);
    coordinates.at(3).set_y(yy+1);
    coordinates.at(3).set_x(xx);
}
