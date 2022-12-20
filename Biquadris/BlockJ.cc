#include "BlockJ.h"
#include "Board.h"
using namespace std;

BlockJ::BlockJ(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(4, {-1, -1});
    ijloszt = 'J';
    level = level1;
    JShape = 1;
    coordinates.at(0).set_x(2);
    coordinates.at(0).set_y(4);
    coordinates.at(1).set_x(1);
    coordinates.at(1).set_y(4);
    coordinates.at(2).set_x(0);
    coordinates.at(2).set_y(4);
    coordinates.at(3).set_x(0);
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

BlockJ::~BlockJ(){
    coordinates.clear();
}

void BlockJ::clockwise(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    bool temp = true;
    //set cells to blank
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    
    if(JShape == 1){
        JShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        JShape = 2;
    }
    else if(JShape == 2){
        JShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        JShape = 3;
    }
    else if(JShape == 3){
        JShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        JShape = 4;
    }
    else if(JShape == 4){
        JShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
        JShape = 1;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(JShape == 1){
            JShape4(coordinates.at(2).get_y()-1, coordinates.at(2).get_x()+2, b);
            JShape = 4;
        }
        else if(JShape == 4){
            JShape3(coordinates.at(2).get_y()-2, coordinates.at(2).get_x()-1, b);
            JShape = 3;
        }
        else if(JShape == 3){
            JShape2(coordinates.at(2).get_y()+1, coordinates.at(2).get_x()-2, b);
            JShape = 2;
        }
        else if(JShape == 2){
            JShape1(coordinates.at(2).get_y()+2, coordinates.at(2).get_x()+1, b);  /*DONE*/
            JShape = 1;
        }
    }
    
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
}

void BlockJ::counterclockwise(shared_ptr<Board>b){
    shared_ptr<Block> belong = b->getBlock(coordinates.at(0).get_x(), coordinates.at(0).get_y());
    bool temp = true;
    //set cells blank
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ' ', nullptr);
    }
    
    if(JShape == 1){
        JShape4(coordinates.at(2).get_y()-1, coordinates.at(2).get_x()+2, b);
        JShape = 4;
    }
    else if(JShape == 2){
        JShape1(coordinates.at(2).get_y()+2, coordinates.at(2).get_x()+1, b);
        JShape = 1;
    }
    else if(JShape == 3){
        JShape2(coordinates.at(2).get_y()+1, coordinates.at(2).get_x()-2, b);
        JShape = 2;
    }
    else if(JShape == 4){
        JShape3(coordinates.at(2).get_y()-2, coordinates.at(2).get_x()-1, b);
        JShape = 3;
    }
    
    for (int i = 0; i < 4; i++) {
        if (coordinates.at(i).get_y() > 17 || coordinates.at(i).get_x() > 9 || coordinates.at(i).get_x() < 0 || b->if_occupied(coordinates.at(i).get_x(), coordinates.at(i).get_y()))
            temp = false;
    }
    
    
    if(!temp){
        if(JShape == 4){
            JShape1(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            JShape = 1;
        }
        else if(JShape == 1){
            JShape2(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            JShape = 2;
        }
        else if(JShape == 2){
            JShape3(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            JShape = 3;
        }
        else if(JShape == 3){
            JShape4(coordinates.at(2).get_y(), coordinates.at(2).get_x(), b);
            JShape = 4;
        }
    }
    //set cells to block type
    for (int i=0; i<4; i++){
        b->setCell(coordinates.at(i).get_x(), coordinates.at(i).get_y(), ijloszt, belong);
    }
    
}

// different shapes of J for rotation
void BlockJ::JShape1(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy);
    coordinates.at(0).set_x(xx+1);
    coordinates.at(1).set_y(yy);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy);
    coordinates.at(2).set_x(xx-1);
    coordinates.at(3).set_y(yy-1);
    coordinates.at(3).set_x(xx-1);
}

void BlockJ::JShape2(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy-1);
    coordinates.at(1).set_x(xx);
    coordinates.at(2).set_y(yy-2);
    coordinates.at(2).set_x(xx);
    coordinates.at(3).set_y(yy-2);
    coordinates.at(3).set_x(xx+1);
}

void BlockJ::JShape3(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy+1);
    coordinates.at(0).set_x(xx);
    coordinates.at(1).set_y(yy+1);
    coordinates.at(1).set_x(xx+1);
    coordinates.at(2).set_y(yy+1);
    coordinates.at(2).set_x(xx+2);
    coordinates.at(3).set_y(yy+2);
    coordinates.at(3).set_x(xx+2);
}

void BlockJ::JShape4(int yy, int xx, shared_ptr<Board>b){
    coordinates.at(0).set_y(yy-1);
    coordinates.at(0).set_x(xx-1);
    coordinates.at(1).set_y(yy);
    coordinates.at(1).set_x(xx-1);
    coordinates.at(2).set_y(yy+1);
    coordinates.at(2).set_x(xx-1);
    coordinates.at(3).set_y(yy+1);
    coordinates.at(3).set_x(xx-2);
}
