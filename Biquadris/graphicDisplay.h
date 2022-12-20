#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_
#include "xWindow.h"
#include "Cell.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

class GraphicDisplay {
    int row, col;
    int level1, score1, level2, score2, hiscore1, hiscore2;
    bool ifBlind1;
    bool ifBlind2;
    std::vector<std::vector<Cell>> d1;
    std::vector<std::vector<Cell>> d2;
    char next1, next2;
    std::shared_ptr<Xwindow> d;
    void drawHelper(int x, int y, char content, int num);
    void DrawNext(char next, int num);
public:
  GraphicDisplay(int row, int col, std::shared_ptr<Xwindow> d);
  ~GraphicDisplay();
  void setBlind(int number, bool if_blind);
  void graph_updateCell(int number, int x, int y, char type);
  void graph_updateOthers(int number, int level, int score, char next);
  void drawString(std::string content);
};


#endif
