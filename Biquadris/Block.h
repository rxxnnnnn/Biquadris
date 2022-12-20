#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Position.h"
#include <vector>
#include <memory>

class Board;

class Block{
    protected:
    /*numCell records the number of coordinates in a block(usually four, except for the secial block in level 4)*/
    std::vector <Position> coordinates;  
    char ijloszt;  //type of block
    int level;
    
    bool canDown(std::shared_ptr<Board> b);
    bool canLeft(std::shared_ptr<Board> b);
    bool canRight(std::shared_ptr<Board> b);
    bool isOver1; 
    int numCell;  
    std::shared_ptr<Block> mybelong;


    public:
    Block();  
    virtual ~Block();
    void left(std::shared_ptr<Board> b);
    void right(std::shared_ptr<Board> b);
    void down(std::shared_ptr<Board> b);
    void drop(std::shared_ptr<Board> b);
    int getLevel();
    char getType(); /* get the type of the block, either i, j, l, o, s,z or t*/
    bool isOver(); /* return true if the game is over */
    void my_clear(std::shared_ptr<Board> b); /* set all the cells in a block to blank to clear */
    int CellDeleted(); /* decrement the number of cells */
    void assignbelong(std::shared_ptr<Board> b,std::shared_ptr<Block> myblock);
    virtual void clockwise(std::shared_ptr<Board> b) = 0;
    virtual void counterclockwise(std::shared_ptr<Board> b) = 0;
};

#endif


