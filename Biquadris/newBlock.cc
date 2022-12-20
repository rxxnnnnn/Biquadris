#include "newBlock.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;


//constructor
newBlock:: newBlock(int level, int seed, string f):
level{level},
seed{seed},
filename{f},
isChanged{false},
isRandom{true}
{
    srand(seed);
    ifseq=ifstream{filename};
}

//destructor
newBlock:: ~newBlock(){
    ifseq.close();
}

//helper function to check type
char newBlock::checktype(string type){
    if (type == "I"){
        return 'I';
    }
    else if (type == "J"){
        return 'J';
    }
    else if (type == "L"){
        return 'L';
    }
    else if (type == "O"){
        return 'O';
    }
    else if (type == "S"){
        return 'S';
    }
    else if (type == "Z"){
        return 'Z';
    }
    else if (type == "T"){
        return 'T';
    }
    return 'A';
}


//get new block
char newBlock::getBlock(){
    int rnum;
    string s;
    if (level == 0){ //if at level 0
        while (ifseq>>s){
            char tmp = checktype(s);
            if (tmp!='A') {
                return tmp;
            } else continue;
        }
        return 'A';
        //at level 1
    } else if (level == 1){
        rnum = rand()%12; //s and z 1/12, else 1/6
        if (rnum == 0){
            return 'S';
        }
        else if (rnum == 1){
            return 'Z';
        }
        else if (rnum == 2 || rnum == 3){
            return 'I';
        }
        else if (rnum == 4 || rnum == 5){
            return 'J';
        }
        else if (rnum == 6 || rnum == 7){
        return 'L';
        }
        else if (rnum == 8 || rnum == 9){
            return 'O';
        }
        else if (rnum == 10 || rnum == 11){
            return 'T';
        }
    }
    //level 2
    else if (level == 2){
        rnum = rand()%7; //all block's prob is 1/7
        if (rnum == 1){
            return  'I';
        }
        else if (rnum == 2){
            return  'J';
        }
        else if (rnum == 3){
            return  'L';
        }
        else if (rnum == 4){
            return  'S';
        }
        else if (rnum == 5){
            return  'Z';
        }
        else if (rnum == 6){
            return  'O';
        }
        else if (rnum == 0){
            return  'T';
        }
    }
    //level 3 or 4
    else if (level == 3 || level == 4){ //level 3, 4: s and z block get 2/9 prob, others get 1/9
        if(isRandom){ //if random
            rnum = rand()%9;
            if (rnum == 0 || rnum == 1){
            return  'S';
            }
            else if (rnum == 2 || rnum == 3){
                return  'Z';
            }
            else if (rnum == 4){
                return  'I';
            }
            else if (rnum == 5){
                return  'T';
            }
            else if (rnum == 6){
                return  'O';
            }
            else if (rnum == 7){
                return  'J';
            }
            else if (rnum == 8){
                return  'L';
            }
        } else {                        // no random called in level 3, 4
            if (ifseq >> s){
            return checktype(s);
            }
        }
    }
    return 'A';
}


void newBlock:: setNoRandom(){
    if (level==3||level == 4){
        isRandom = false;
    }
}


void newBlock:: setRandom(){
    if (level==3||level == 4){
        isRandom = true;
        }
}

void newBlock:: addLevel(){
        ++level;
}
    
void newBlock:: subLevel(){
    --level;
}
