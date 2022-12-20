#ifndef __CELL_H__
#define __CELL_H__
#include <memory>

class Block; //forward declaration Board


class Cell{
    bool occupied;
    char myContent;
    int myx;
    int myy;
    std::shared_ptr<Block> my_belonged;
    
public:
    Cell(){};
    Cell(int x, int y);
    void assignBlock(std::shared_ptr<Block>  belonged);
    void fill(char content);
    void myclear();
    bool if_occupied();
    char get_content() const;
    std::shared_ptr<Block>  get_block();
};


#endif
