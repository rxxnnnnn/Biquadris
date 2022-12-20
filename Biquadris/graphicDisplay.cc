#include "graphicDisplay.h"
#include <vector>
#include <string>
#include <memory>
#include <sstream>
using namespace std;

//constructor
GraphicDisplay:: GraphicDisplay(int row, int col, shared_ptr<Xwindow> d):
row{row},col{col},level1{0},score1{0},level2{0},score2{0}, hiscore1{0}, hiscore2{0}, ifBlind1{false}, ifBlind2{false}, d{d}{
  //  d1.resize(20);
  //  d2.resize(20);
    for(int i = 0; i < row; i++){
        vector<Cell> row1(11);
        for(int k = 0; k < col; k++){
            row1.emplace_back(Cell(k, i));
        }
        d1.emplace_back(row1);
    }
    for(int i = 0; i < row; i++){
        vector<Cell> row1(11);
        for(int k = 0; k < col; k++){
            row1.emplace_back(Cell(k, i));
        }
        d2.emplace_back(row1);
    }
    d->fillRectangle(30, 0, 680, 15, Xwindow::White);
    d->drawLine(28, 14, 710, 14);
    d->drawLine(28, 0, 28, 14);
    d->drawLine(710, 0, 710, 14);
    //draw border
    d->drawLine(30, 59, 360, 59);
    d->drawLine(380, 59, 710, 59);
    d->drawLine(30, 600, 360, 600);
    d->drawLine(380, 600, 710, 600);
    d->drawLine(29, 59, 29, 600);
    d->drawLine(360, 59, 360, 600);
    d->drawLine(379, 59, 379, 600);
    d->drawLine(710, 59, 710, 600);
    d->drawString(30, 25, "Player1");
    d->drawString(30, 35, "Level");
    d->drawString(30, 45, "HiScore");
    d->drawString(30, 55, "Score");
    d->drawString(385, 25, "Player2");
    d->drawString(385, 35, "Level");
    d->drawString(385, 45, "HiScore");
    d->drawString(385, 55, "Score");
    d->drawString(30, 620, "Next");
    d->drawString(385, 620, "Next");
    string s1,s2,his1,his2,lv1,lv2;
    stringstream ss1, ss2, shis1, shis2, slv1, slv2;
    ss1 << score1;
    ss2 << score2;
    shis1 << hiscore1;
    shis2 << hiscore2;
    slv1 << level1;
    slv2 << level2;
    s1 = ss1.str();
    s2 = ss2.str();
    his1 = shis1.str();
    his2 = shis2.str();
    lv1 = slv1.str();
    lv2 = slv2.str();
    d->drawString(85, 35, lv1);
    d->drawString(440, 35, lv2);
    d->drawString(85, 55, s1);
    d->drawString(85, 45, his1);
    d->drawString(440, 55, s2);
    d->drawString(440, 45, his1);
}

GraphicDisplay:: ~GraphicDisplay(){
}

void GraphicDisplay::setBlind(int number, bool if_blind){
    if(number==1) ifBlind1=if_blind;
    if(number==2) ifBlind2=if_blind;
    if(if_blind){
        for (int i=3; i<13; i++){
            for (int j1=3; j1<10; j1++){ //blind mode
                drawHelper(j1, i, '?', number);
            }
        }
    }
    if(!if_blind){
        if(number==1){
            for (int i=3; i<13; i++){
                for (int j1=3; j1<10; j1++){ //blind mode
                    drawHelper(j1, i, d1[i][j1].get_content(), number);
                }
            }
        }
        if(number==2){
            for (int i=3; i<13; i++){
                for (int j1=3; j1<10; j1++){ //blind mode
                    drawHelper(j1, i, d2[i][j1].get_content(), number);
                }
            }
        }
    }
}

void GraphicDisplay:: graph_updateCell(int number, int x, int y, char type){
    if (number == 1){
        d1[y][x].fill(type);
    }
    if (number == 2){
        d2[y][x].fill(type);
    }
    drawHelper(x, y, type, number);
}

void GraphicDisplay:: graph_updateOthers(int number, int level, int score, char next){
    for(int i = 5; i <=8; i++){
        drawHelper(i, 19,' ',number);
    }
    for(int i = 5; i <=8; i++){
        drawHelper(i, 20,' ',number);
    }
    if (number ==1){
        level1 = level;
        score1 = score;
        next1 = next;
        if(score1 > hiscore1) hiscore1 = score1;
        string s1,his1,lv1;
        stringstream ss1, shis1, slv1;
        ss1 << score1;
        shis1 << hiscore1;
        slv1 << level1;
        s1 = ss1.str();
        his1 = shis1.str();
        lv1 = slv1.str();
        d->fillRectangle(70, 25, 30, 30, Xwindow::White);
        d->drawString(85, 35, lv1);
        d->drawString(85, 55, s1);
        d->drawString(85, 45, his1);
        DrawNext(next1, number);
        if(next1=='A') d->drawString(85, 620, "No More");
    }
    else if (number == 2){
        level2 = level;
        score2 = score;
        next2 = next;
        if(score2 > hiscore2) hiscore2 = score2;
        string s2,his2,lv2;
        stringstream ss2, shis2, slv2;
        ss2 << score2;
        shis2 << hiscore2;
        slv2 << level2;
        s2 = ss2.str();
        his2 = shis2.str();
        lv2 = slv2.str();
        d->fillRectangle(430, 25, 30, 30, Xwindow::White);
        d->drawString(440, 35, lv2);
        d->drawString(440, 55, s2);
        d->drawString(440, 45, his2);
        DrawNext(next2, number);
        if(next2=='A') d->drawString(440, 620, "No More");
    }
}
    
    void GraphicDisplay::DrawNext(char next, int num){
        if(next=='I'){
            drawHelper(5, 19, next, num);
            drawHelper(6, 19, next, num);
            drawHelper(7, 19, next, num);
            drawHelper(8, 19, next, num);
        }
        if(next=='J'){
            drawHelper(5, 19, next, num);
            drawHelper(5, 20, next, num);
            drawHelper(6, 20, next, num);
            drawHelper(7, 20, next, num);
        }
        if(next=='L'){
            drawHelper(7, 19, next, num);
            drawHelper(5, 20, next, num);
            drawHelper(6, 20, next, num);
            drawHelper(7, 20, next, num);
        }
        if(next=='O'){
            drawHelper(5, 19, next, num);
            drawHelper(5, 20, next, num);
            drawHelper(6, 19, next, num);
            drawHelper(6, 20, next, num);
        }
        if(next=='S'){
            drawHelper(6, 19, next, num);
            drawHelper(7, 19, next, num);
            drawHelper(5, 20, next, num);
            drawHelper(6, 20, next, num);
        }
        if(next=='Z'){
            drawHelper(5, 19, next, num);
            drawHelper(6, 19, next, num);
            drawHelper(6, 20, next, num);
            drawHelper(7, 20, next, num);
        }
        if(next=='T'){
            drawHelper(5, 19, next, num);
            drawHelper(6, 19, next, num);
            drawHelper(7, 19, next, num);
            drawHelper(6, 20, next, num);
        }
    }

void GraphicDisplay:: drawHelper(int x, int y, char myContent, int num){
    int margin= 30;
    if (num==1&&ifBlind1&&x>=3&&x<=9&&y>=3&&y<=12){
        d->fillRectangle( margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Black);
        return;
    }
    if (num==2&&ifBlind2&&x>=3&&x<=9&&y>=3&&y<=12){
        d->fillRectangle( margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Black);
        return;
    }
    if (myContent == 'I'){
        d->fillRectangle( margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: DarkGreen);
    }
    else if (myContent == 'J'){
        d->fillRectangle( margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Yellow);
    }
    else if (myContent == 'L'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Blue);
    }
    else if (myContent == 'O'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Green);
    }
    else if (myContent == 'S'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2  + y*30, 30, 30, Xwindow:: Orange);
    }
    else if (myContent == 'Z'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Cyan);
    }
    else if (myContent == 'T'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Red);
    }
    else if (myContent == '*'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Brown);
    }
    else if (myContent == '?'){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: Black);
    }
    else if (myContent == ' '){
        d->fillRectangle(  margin + (x*30 + 350*(num-1)), margin * 2 + y*30, 30, 30, Xwindow:: White);
    }
}
    
void GraphicDisplay:: drawString(string content){
    d->fillRectangle(29, 0, 680, 14, Xwindow::White);
    int len = content.length();
    if(content!=" "){
        if (len > 20) d->drawString((750-len)/2 -180,10,content);
        if (len < 20) d->drawString((750-len)/2 -50,10,content);
    }
}

