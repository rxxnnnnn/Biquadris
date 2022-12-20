#include "TextDisplay.h"
#include <vector>
#include "Cell.h"
#include "Block.h"
using namespace std;


//constructor
TextDisplay:: TextDisplay(int row, int col):
row{row},
col{col},
level1{0},score1{0},level2{0},score2{0}, hiscore1{0}, hiscore2{0}{
    for(int i = 0; i < row; i++){
        vector<Cell> row1;
        for(int k = 0; k < col; k++){
            row1.emplace_back(Cell(k, i));
        }
        display1.emplace_back(row1);
    }
    for(int i = 0; i < row; i++){
        vector<Cell> row1;
        for(int k = 0; k < col; k++){
            row1.emplace_back(Cell(k, i));
        }
        display2.emplace_back(row1);
    }
};


//destructor
TextDisplay:: ~TextDisplay(){
    display1.clear();
    display2.clear();
}




//update cell in the corresponding display
void TextDisplay::updateCell(int number, int x, int y, char content){
    if (number == 1){
        display1[y][x].fill(content);
    }
    else if (number == 2){
        display2[y][x].fill(content);
    }
}

//update the level, score and nectBlock for the corresponding display
void TextDisplay:: updateOthers(int number, int level, int score, char next){
    if (number ==1){
        level1 = level;
        score1 = score;
        next1 = next;
        if(score1 > hiscore1) hiscore1 = score1;
    }
    else if (number == 2){
        level2 = level;
        score2 = score;
        next2 = next;
        if(score2 > hiscore2) hiscore2 = score2;
    }
}

//set the blind field
void TextDisplay::setBlind(int number, bool if_blind){
    if (number==1) ifBlind1=if_blind;
    if (number==2) ifBlind2=if_blind;
}

//helper function to print the textdisplay
string printFirstLine(char type){
    string firstline;
    if(type == 'A'){
        firstline = "No more    ";
    }
    else if(type == 'I'){
        firstline = "IIII       ";
    }
    else if (type == 'J'){
        firstline = "J          ";
    }
    else if (type == 'L'){
        firstline= "  L        ";
    }
    else if (type == 'O'){
        firstline= "OO         ";
    }
    else if (type == 'S'){
        firstline= " SS        ";
    }
    else if (type == 'T'){
        firstline = "TTT        ";
    }
    else if (type == 'Z'){
        firstline = "ZZ         ";
    }
    return firstline;
}

string printSecLine(char type){
    string secline;
    if(type == 'I'||type == 'A'){
        secline = "           ";
    }
    else if (type == 'J'){
        secline = "JJJ        ";
    }
    else if (type == 'L'){
        secline= "LLL        ";
    }
    else if (type == 'O'){
        secline= "OO         ";
    }
    else if (type == 'S'){
        secline="SS         ";
    }
    else if (type == 'T'){
        secline = " T         ";
    }
    else if (type == 'Z'){
        secline = " ZZ        ";
    }
    return secline;
}


//output operator for TextDiaplay
std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
    out << "Player1                Player2     "<<endl;
    out << "Level:    " << td.level1 << "            " << "Level:    " << td.level2 << endl;
    out << "HiScore:  " << td.hiscore1 << "            " << "HiScore:  " << td.hiscore2 << endl;
    out << "Score:    " << td.score1 << "            " << "Score:    " << td.score2 << endl;
    out << "-----------" << "            " << "-----------" << endl;
    
    //output board
    for(int i = 0; i < td.row; ++i) {
        //output first display
        for(int j1 = 0; j1 < td.col; ++j1) {
            if(td.ifBlind1&&((i>=3)&&(i<=12))&&((j1>=3)&&(j1<=9))){ //blind mode
                out<<"?";
            } else {
                out << td.display1[i][j1].get_content();
            }
        }
        out<< "            ";
        //output second display
        for(int j2 = 0; j2 < td.col; ++j2) {
            if(td.ifBlind2&&((i>=3)&&(i<=12))&&((j2>=3)&&(j2<=9))){ //blind mode
                out<<"?";
            } else {
                out<< td.display2[i][j2].get_content();
            }
        }
        out<<endl;
    }
    
    out << "-----------" << "            " << "-----------" << endl;
    out << "Next:" << "                  " << "Next:" << endl;
    char next1;
    char next2;
    next1 = td.next1;
    next2 = td.next2;
    out << printFirstLine(next1) << "            " << printFirstLine(next2) << endl;  //output next block
    out << printSecLine(next1) << "            " << printSecLine(next2) << endl;  //output next block
    return out;
}

