#include "Position.h"


Position::Position(int xval, int yval):
    x{xval}, y{yval}{}

int Position::get_x(){ return x; }
int Position::get_y(){ return y; }
void Position::set_x(int xval){
    x = xval;
}
void Position::set_y(int yval){
    y = yval;
}
void Position::add_x(int change){
    x+=change;
}
void Position::add_y(int change){
    y+=change;
}
