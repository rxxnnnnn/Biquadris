#include <vector>
#include <string>
#include "Cell.h"
#include "Board.h"
#include "TextDisplay.h"
#include "Block.h"
#include <cmath>
using namespace std;


//constructor of Board
Board::Board(int number, bool text_only):width{0},height{0},myTextDisplay{NULL}, number{number}, text_only{text_only},
mygraphDisplay{nullptr}{}


//destructor of Board
Board::~Board(){
    myclear();
    myBoard.clear();
}

//assigne the position at (x, y) with the block it belongs to
void Board::assignbelong(int x, int y, std::shared_ptr<Block> belonged){ 
    myBoard[y][x].assignBlock(belonged);
}

//initialize the board
void Board::init(int w, int h, shared_ptr<Board> another, shared_ptr<TextDisplay> td, shared_ptr<GraphicDisplay> gd){
    width=w;
    height=h;
    for(int i = 0; i < h; i++){
            vector<Cell> row;
            for(int k = 0; k < width; k++){
                row.emplace_back(Cell(k, i));
            }
            myBoard.emplace_back(row);
        }
        if (!text_only){
            mygraphDisplay = gd;
        }
        myTextDisplay=td;
        anotherPlayer=another;
        HeavyLevel=0;
    }



//check if the cell at postion (x,y) is occupied
bool Board::if_occupied(int x, int y){
    return myBoard[y][x].if_occupied();
}


//fill the cell at position (x,y) with content
void Board::setCell(int x, int y, char content, shared_ptr<Block> belonged){
    myBoard[y][x].fill(content);
    if(belonged!=nullptr) myBoard[y][x].assignBlock(belonged);
    myTextDisplay->updateCell(number, x, y, content);
    if (!text_only){
        mygraphDisplay->graph_updateCell(number, x, y, content);
    }
}

shared_ptr<Block> Board::getBlock(int x, int y){
    return myBoard[y][x].get_block();
}


//remove the full rows, return the number of rows removed
int Board::removeFull(int* addedScore){
    *addedScore = 0;
    int count1 = 0;
    int i = height-1;
    while(i >= 0){
        bool full=true;
        for (int k = 0; k < width; k++){
            if (!myBoard[i][k].if_occupied()){
                full=false;
                break;
            }
        }
        if (full){
            for(int n = i; n >0; n--){
                for(int m = 0; m < width; m++){
                    if(n == i){
                        int cellRemained = myBoard[n][m].get_block()->CellDeleted();
                        if (cellRemained==0){
                            *addedScore+=(pow(myBoard[n][m].get_block()->getLevel()+1, 2));                        }
                            myBoard[n][m].fill(' ');
                    }
                    myBoard[n][m].fill(myBoard[n-1][m].get_content());
                    myBoard[n][m].assignBlock(myBoard[n-1][m].get_block());
                    myTextDisplay->updateCell(number, m, n, myBoard[n-1][m].get_content());
                    if (!text_only){
                    mygraphDisplay->graph_updateCell(number, m, n, myBoard[n-1][m].get_content());
                    }
                }
            }
            for(int g = 0; g < width; g++){
                if(i == 0){
                    int cellRemained = myBoard[0][g].get_block()->CellDeleted();
                    if (cellRemained==0){
                        *addedScore+=(pow(myBoard[0][g].get_block()->getLevel()+1, 2));
                    }
                }
                myBoard[0][g].myclear();
                myTextDisplay->updateCell(number, g, 0, ' ');
                if (!text_only){
                    mygraphDisplay->graph_updateCell(number, g, 0, ' ');
                }
            }
            count1++ ;
        } else {
            i--;
        }
    }
    return count1;
}


//clear the content in the board
void Board::myclear(){
    for (int i = 0; i < height; i++){
        for (int k = 0; k < width; k++){
            myBoard[i][k].myclear();
            myTextDisplay->updateCell(number, k, i, ' ');
            if (!text_only){
                mygraphDisplay->graph_updateCell(number, k, i, ' ');
            }
        }
    }
}

//return the pointer to another board it playes with
shared_ptr<Board> Board::anotherBoard(){
    return anotherPlayer.lock();
}



//update the display with new level, score, and nextBlock
void Board::updateDisplay(int level, int score, char next){
    myTextDisplay->updateOthers(number, level, score, next);
    if (!text_only){
    mygraphDisplay->graph_updateOthers(number, level, score, next);
    }
}


//check the heavylevel of the board affected by another player
int Board::heavyLevel(){
    return HeavyLevel;
}

//set the heacylevel effected by another player
void Board::setheavy(int level){
    HeavyLevel=level;
}

//set the display of the board to be blind
void Board::setBlind(bool if_blind){
    myTextDisplay->setBlind(number, if_blind);
    if (!text_only) mygraphDisplay->setBlind(number, if_blind);
}
