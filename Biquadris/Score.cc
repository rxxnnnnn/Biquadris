#include "Score.h"


//add score to the current score
void Score::addScore(int added){
    currentScore+=added;
    if(currentScore>HiScore) HiScore=currentScore;
}

//get the current score
int Score::getScore(){
    return currentScore;
}

//get the HiScore
int Score::getHiScore(){
    return HiScore;
}

//reset the currentScore to be 0
void Score::reset(){
    currentScore=0;
}
