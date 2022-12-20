#ifndef _POSITION_H_
#define _POSITION_H_

class Position{
    int x;
    int y;

    public:
        Position(int xval = -1, int yval = -1);
        int get_x();
        int get_y();
        void set_x(int xval);
        void set_y(int yval);
        void add_x(int change);
        void add_y(int change);
};


#endif