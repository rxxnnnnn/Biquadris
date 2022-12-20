#ifndef __BOARD_H__
#define __BOARD_H__

#include <memory>

#include <vector>
#include "xWindow.h"
#include "Cell.h"
#include "TextDisplay.h"
#include "graphicDisplay.h"
#include "Block.h"

class SpecialEffect;
class Score;
class Block;

class Board{
    std::vector<std::vector<Cell>> myBoard;
    int width;
    int height;
    std::shared_ptr<TextDisplay>  myTextDisplay;
    int HeavyLevel;
    int number;
    std::weak_ptr<Board> anotherPlayer;
    bool text_only;
    std::shared_ptr<GraphicDisplay> mygraphDisplay;


public:
    Board(int number, bool text_only);
    ~Board();

    void init(int w, int h, std::shared_ptr<Board>  another, std::shared_ptr<TextDisplay> td,
    std::shared_ptr<GraphicDisplay> gd);
    void assignbelong(int x, int y, std::shared_ptr<Block>  belonged);
    bool if_occupied(int x, int y);
    void setCell(int x, int y, char content, std::shared_ptr<Block>  belonged);
    std::shared_ptr<Block>  getBlock(int x, int y);
    int removeFull(int *);
    void myclear();
    void updateDisplay(int level, int score, char next);
    std::shared_ptr<Board>  anotherBoard();
    int heavyLevel();
    void setheavy(int level);
    void setBlind(bool if_blind);
};

#endif
