#ifndef _CMDPROCESSOR_H
#define _CMDPROCESSOR_H
#include <string> 
#include "Board.h"
#include "Block.h"
#include <memory>

class cmdProcessor {
  public:
    bool exit(std:: string cmd);
    bool left(std:: string cmd);
    bool right(std:: string cmd);
    bool down(std:: string cmd);
    bool clockwise(std:: string cmd);
    bool counterclockwise(std:: string cmd);
    bool drop(std:: string cmd);
    bool level_up(std:: string cmd);
    bool level_down(std:: string cmd);
    bool random(std:: string cmd);
    bool no_random(std:: string cmd);
    bool sequence(std:: string cmd);
    bool restart(std:: string cmd);
    bool type(std:: string cmd);
    void runCommand(std:: string cmd, std::shared_ptr<Board>  brd, std::shared_ptr<Block>  blk);
    void multiCommand(int mult, std:: string cmd, std::shared_ptr<Board>  brd, std::shared_ptr<Block>  blk);
};


#endif
