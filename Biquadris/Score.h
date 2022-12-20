#ifndef __SCORE_H__
#define __SCORE_H__
#include "Score.h"


class Score{
    int currentScore;
    int HiScore;
public:
    void addScore(int added);
    int getScore();
    int getHiScore();
    void reset();
};


#endif
