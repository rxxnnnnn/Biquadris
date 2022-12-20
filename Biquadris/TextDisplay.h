#ifndef _TEXTDISPLAY_H
#define _TEXTDISPLAY_H
#include "Cell.h"
#include <sstream>
#include <iostream>
#include <vector>

class TextDisplay {
    int row, col;
    int level1, score1, level2, score2, hiscore1, hiscore2;
    char next1, next2;
    std::vector<std::vector<Cell>> display1;
    std::vector<std::vector<Cell>> display2;
    bool ifBlind1;
    bool ifBlind2;
    
public:
    TextDisplay(int row, int col);
    ~TextDisplay();
    void updateCell(int number, int x, int y, char content);
    void updateOthers(int number, int level, int score, char next);
    void setBlind(int number, bool if_blind);
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif

