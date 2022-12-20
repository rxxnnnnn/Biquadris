#include "Cell.h"
#include "Block.h"
#include <iostream>
using namespace std;

//constructor of class Cell
Cell::Cell(int x, int y):
occupied{false},myContent{' '},myx{x}, myy{y}{}

//assign the block it belongs to
void Cell::assignBlock(shared_ptr<Block> belonged){
    if(belonged==nullptr) {
        if (my_belonged != nullptr) my_belonged.reset();
    }
    if(belonged!=nullptr){
        if (my_belonged != nullptr) my_belonged = belonged;
        if (my_belonged == nullptr){
            my_belonged = belonged;
        }
    }
}

shared_ptr<Block> Cell::get_block(){
    return my_belonged;
}

//fill Cell with content
void Cell::fill(char content){
    myContent=content;
    occupied=true;
    if (content == ' ') {
        occupied=false;
        if(my_belonged!=nullptr) my_belonged.reset();
    }
}

//clear the content in Cell
void Cell::myclear(){
    myContent=' ';
    occupied=false;
    if(my_belonged!=nullptr) my_belonged.reset();
}

//check if the Cell is occupied
bool Cell::if_occupied(){
    if(myContent==' ') return occupied;
    return occupied;
}

//get the content in Cell
char Cell::get_content() const{
    if(occupied) return myContent;
    if(occupied==false) return ' ';
    return ' ';
}
