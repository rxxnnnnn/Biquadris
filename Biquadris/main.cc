#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cmath>
#include <memory>
#include "xWindow.h"
#include "Board.h"
#include "Block.h"
#include "Cell.h"
#include "Score.h"
#include "BlockI.h"
#include "BlockJ.h"
#include "BlockL.h"
#include "BlockO.h"
#include "BlockS.h"
#include "BlockZ.h"
#include "BlockT.h"
#include "BlockExtra.h"
#include "newBlock.h"
#include "cmdProcessor.h"
#include "TextDisplay.h"
#include "SpecialEffect.h"
#include "DoNothing.h"
#include "Blind.h"
#include "Heavy.h"
#include "Force.h"
#include "graphicDisplay.h"
using namespace std;


//A helper function to initialize a board given a type in char
shared_ptr<Block> initBlock(char type, shared_ptr<Board> b, int level){
    if (type == 'I'){
        auto tmp1 = make_shared<BlockI>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    else if (type == 'J'){
        auto tmp1 = make_shared<BlockJ>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    else if (type == 'L'){
        auto tmp1 = make_shared<BlockL>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    else if (type == 'O'){
        auto tmp1 = make_shared<BlockO>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    else if (type == 'S'){
        auto tmp1 = make_shared<BlockS>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    else if (type == 'Z'){
        auto tmp1 = make_shared<BlockZ>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    else if (type == 'T'){
        auto tmp1 = make_shared<BlockT>(b, level);
        shared_ptr<Block>tmp = static_pointer_cast<Block>(tmp1);
        tmp->assignbelong(b,tmp);
        return tmp;
    }
    return NULL;
}


int main (int argc, const char* argv[]) {
    string fileone = "sequence1.txt"; //the sequenec file of player1
    string filetwo = "sequence2.txt"; //the sequenec file of player2
    int seed= time(NULL); //for random number
    bool text_only = false; //text_only mode is default off
    bool multspecialEffect1 = false;//if can produce multiple effects simultaneously
    bool multspecialEffect2 = false;
   //the default start level is 0
    int level1 = 0;
    int level2 = 0;
    for (int i=0; i<argc; i++){
        string arg;
        arg = argv[i];
        if (arg == "-seed"){ //set random number generator
            istringstream ss{argv[i+1]};
            ss >> seed;
        }
        if (arg == "-startlevel"){ //set start level
            int n;
            istringstream ss{argv[i+1]};
            ss >> n;
            if (n >= 0 && n <= 4){
                level1 = n;
                level2 = n;
            }
        }
        if (arg == "-scriptfile1"){ //set the sequence file for player1
            fileone = argv[i+1];
            i++;
        }
        if (arg == "-scriptfile2"){ //set the sequence file for player2
            filetwo = argv[i+1];
            i++;
        }
        if (arg == "-text"){ //turn on text only mode
            text_only = true;
        }
        if (arg == "-cheat1"){
            multspecialEffect1 = true;
        }
        if (arg == "-cheat2"){
            multspecialEffect2 = true;
        }
    }
    //initialize a TextDisplay
    shared_ptr<TextDisplay> td = make_shared<TextDisplay>(18,11);
    // initialize a command processor
    shared_ptr<cmdProcessor> cmdprc = make_unique<cmdProcessor>();
    //initialized two boards
    shared_ptr<Board> b1 = make_shared<Board>(1, text_only);
    shared_ptr<Board> b2 = make_shared<Board>(2, text_only);
    // initialize tow Score class for two Boards
    shared_ptr<Score> sc1 = make_unique<Score>();
    shared_ptr<Score> sc2 = make_unique<Score>();
    //initialized SpecialEffect for two players
    auto tmp1 = make_shared<DoNothing>();
    auto tmp2 = make_shared<DoNothing>();
    shared_ptr<SpecialEffect> se1 = static_pointer_cast<SpecialEffect>(tmp1);
    shared_ptr<SpecialEffect> se2 = static_pointer_cast<SpecialEffect>(tmp2);
    shared_ptr<Xwindow> xw;
    shared_ptr<GraphicDisplay> gd;
    // taking in command-line arguments
    if (!text_only){
        //initialize GraphicDisplay and Xwindow
        xw = make_shared<Xwindow>();
        gd = make_shared <GraphicDisplay>(18, 11, xw);
        b1->init(11, 18, b2, td, gd); //set width, height, anotherplayer, textdisplay, graphic desplay for two boards
        b2->init(11, 18, b1, td, gd);
    } else {
    //set width, height, anotherplayer, textdisplay for two boards
        b1->init(11, 18, b2, td, nullptr);
        b2->init(11, 18, b1, td, nullptr);
    }
    //initialized two newBlock class
    shared_ptr<newBlock> newblk1;
    shared_ptr<newBlock> newblk2;
    try {
        ifstream in1;
        in1.exceptions(ifstream::failbit);
        in1.open(fileone);
        newblk1 = make_unique<newBlock>(level1, seed, fileone);
    } catch (...) {
        string output = "File " + fileone + " doesn't exist or not accessible";
        if(!text_only) gd->drawString(output);
        cout<<"File "<<fileone<<" doesn't exist or not accessible"<<endl;
        b1->myclear(); //clear the board
        b2->myclear();
        return 0;
    }
    try {
        ifstream in2;
        in2.exceptions(ifstream::failbit);
        in2.open(fileone);
        newblk2 = make_unique<newBlock>(level2, seed, filetwo);
    } catch (...) {
        string output = "File " + filetwo + " doesn't exist or not accessible";
        if(!text_only) gd->drawString(output);
        cout<<"File "<<filetwo<<" doesn't exist or not accessible"<<endl;
        b1->myclear(); //clear the board
        b2->myclear();
        return 0;
    }
    // get the current block for two boards
    shared_ptr<Block> curblock1 = initBlock(newblk1->getBlock(), b1, level1);
    shared_ptr<Block> curblock2 = initBlock(newblk2->getBlock(), b2, level2);
    // get the nextBlock for teo boards
    char nextb1 = newblk1->getBlock();
    char nextb2 = newblk2->getBlock();

    //start game
    cout << "Welcome to BiQuadris!" << endl;
    
    //display the initial state of board
    b1->updateDisplay(level1, sc1->getScore(), nextb1);
    b2->updateDisplay(level2, sc2->getScore(), nextb2);
    cout << *td;
    
    if (curblock1 == nullptr || curblock2 == nullptr) { // seqfile1 or seqfile2 has no input
        string output = "Input File ";
        cout << "Input File ";
        if(!curblock1){
            cout << fileone << " ";
            output += (fileone + " ");
        }
        if(!curblock2){
            cout << filetwo << " ";
            output += (filetwo + " ");
        }
        if(!text_only) gd->drawString(output);
        cout << "has no input!" << '\n' << "Game Over!"<<endl;
        b1->myclear(); //clear the board
        b2->myclear();
        return 0; //Game Over
    }

    //set the current board and its relevant classes
    bool player1turn = true; //Player1 plays first
    bool player2turn = false;
    int numPlaced1 = 0;
    int numPlaced2 = 0;
    shared_ptr<newBlock> * curnew = nullptr;
    shared_ptr<Board> * curboard = nullptr;
    shared_ptr<Block> * curblock = nullptr;
    char * curnextb = nullptr;
    shared_ptr<Score> * cursc = nullptr;
    shared_ptr<SpecialEffect> * curse = nullptr;
    int * curlevel = nullptr;
    int * curnumPlaced = nullptr;
    bool * curmultspecial = nullptr;
    string curfilename;
    string cmd;
    string fname;
    ifstream fin;
    cout<<"Player1's turn"<<endl;
    string output = "Player1's turn";
    if(!text_only) gd->drawString(output);
    bool rightcmd = false;
    while (1) { // read in command
        if(fname==""){
            cin>>cmd;
            if(cin.fail()) break;
        }
        if(fname!=""){
            fin>>cmd;
            if(fin.fail()) break;
        }
        if (player1turn){ // player1's turn
            curboard = &b1;
            curnew = &newblk1;
            curblock = &curblock1;
            curnextb = &nextb1;
            curfilename = fileone;
            cursc = &sc1;
            curse = &se1;
            curlevel = &level1;
            curnumPlaced = &numPlaced1;
            curmultspecial = &multspecialEffect1;
        }
        else if (player2turn){ //player2's turn
            curboard = &b2;
            curnew = &newblk2;
            curblock = &curblock2;
            curnextb = &nextb2;
            curfilename = filetwo;
            cursc = &sc2;
            curse = &se2;
            curlevel = &level2;
            curnumPlaced = &numPlaced2;
            curmultspecial = &multspecialEffect2;
        }
        //check command
        if (cmdprc->exit(cmd)){
            if(player1turn) cout<<"Player1 exits. ";
            if(player2turn) cout<<"Player2 exits. ";
            cout<<"Game Over"<<endl;
            b1->myclear();
            b2->myclear();
            td.reset();
            cmdprc.reset();
            b1.reset();
            b2.reset();
            sc1.reset();
            sc2.reset();
            se1.reset();
            se2.reset();
            newblk1.reset();
            newblk2.reset();
            if(!text_only) xw.reset();
            if(!text_only) gd.reset();
            return 0;
        }
        else if (cmdprc->sequence(cmd)){ //command is sequence
            if(fname!="") fin>>fname;//get file name from fin
            if(fname=="") cin>>fname;//get file name from cin
            try{ //deal with invalid input of filename
                ifstream myin;
                myin.exceptions(ifstream::failbit);
                myin.open(fname);
                fin = ifstream{fname};
                continue;
            }
            catch(...){
                cout<<"File doesn't exist or not accessible."<<endl;
                if(!text_only) gd->drawString("File doesn't exist or not accessible.");
                continue;
            }
        }
        else if (cmdprc->restart(cmd)){ //restart the game
            sc1->reset(); //reset score
            sc2->reset();
            b1->myclear(); //clear the board
            b2->myclear();
            level1 = 0;
            level2 = 0;
            newblk1 = make_shared<newBlock>(level1, seed, fileone);
            newblk2 = make_shared<newBlock>(level1, seed, filetwo);
            curblock1 = initBlock(newblk1->getBlock(), b1, 0);
            curblock2 = initBlock(newblk2->getBlock(), b2, 0);
            nextb1 = newblk1->getBlock();
            nextb2 = newblk2->getBlock();
            b1->updateDisplay(level1, sc1->getScore(), nextb1);
            b2->updateDisplay(level2, sc2->getScore(), nextb2);
            player1turn = true;
            player2turn = false;
            cout << *td;
            cout<<"Player1's turn"<<endl;
            continue;
        }
        else {
            if (cmdprc->drop(cmd)){ //when drop is called
                rightcmd = true;
                cmdprc->runCommand(cmd, *curboard, *curblock); //run the command
                (*curboard)->setBlind(false); //turn off the blind mode
                (*curnumPlaced)++;  //increase the number of number of cell places without removing at least one line
                int addedScore = 0;
                int numCleared = (*curboard)->removeFull(&addedScore); //addedScore becomes to the score added because of the removal of a block
                (*cursc)->addScore(addedScore);
                if (numCleared>0) (*cursc)->addScore(pow(numCleared + (*curlevel), 2));
                (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                if (*curnextb == 'A'){ // EOF
                    cout << *td;
                    cout << "Input stream " << curfilename << " reaches EOF!" << endl;
                    cout << "GAME OVER" << endl;
                    string output = "Input stream " + curfilename + " reaches EOF! " +"GAME OVER!";
                    b1->myclear(); //clear the board
                    b2->myclear();
                    if(!text_only) gd->drawString(output);
                    td.reset();
                    cmdprc.reset();
                    b1.reset();
                    b2.reset();
                    sc1.reset();
                    sc2.reset();
                    se1.reset();
                    se2.reset();
                    newblk1.reset();
                    newblk2.reset();
                    if(!text_only) xw.reset();
                    if(!text_only) gd.reset();
                    return 0;
                }
                *curblock = initBlock(*curnextb, *curboard, *curlevel); //point the current block to the next block
                if ((*curblock)->isOver()){//curblock can't be put into the board
                    cout << "Game Over" << endl;
                    string output = "Game Over";
                    if(player2turn){
                        cout<<"Player1 wins"<<endl;
                        output += " Player1 wins";
                    }
                    if(player1turn) {
                        cout<<"Player2 wins"<<endl;
                        output += " Player2 wins";
                    }
                    cout << "Type restart to start a new game. Type exit to exit the game." <<endl;
                    output += " Type restart to start a new game. Type exit to exit the game.";
                    if(!text_only) gd->drawString(" ");
                    if(!text_only) gd->drawString(output);
                    continue;
                }
                *curnextb = (*curnew)->getBlock(); //generate the next block
                (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                cout << *td;
                //when no lines is cleared and the number of cells places is 5(or 10, 15...) and the level is 4
                if ((numCleared==0)&&((*curlevel) == 4) && (((*curnumPlaced) % 5) == 0) && ((*curnumPlaced) >= 5)){
                    if(!(*curboard)->if_occupied(5, 3)){ // if the 1*1 Board can be placed at the centre colomn, created it
                        auto tmp = make_shared<BlockExtra>(*curboard, *curlevel);
                        shared_ptr<Block> added = static_pointer_cast<Block>(tmp);
                        added->assignbelong(*curboard,added);
                        added->drop(*curboard); // drop it
                        int addedScore = 0;
                        int numCleared = (*curboard)->removeFull(&addedScore);
                        (*cursc)->addScore(addedScore);
                        if (numCleared>0) {
                            (*cursc)->addScore(pow(numCleared + *curlevel, 2));
                            *curnumPlaced = 0;
                        }
                        (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                        cout<<*td;
                    }
                }
                //if there are lines cleared
                if (numCleared >= 1){
                    (*curnumPlaced) = 0;
                    if (numCleared == 1){
                        cout << "Remove 1 line!"<<endl; //1 line is cleared
                        string output = "Remove 1 line!";
                        if(!text_only) gd->drawString(output);
                    }
                    if (numCleared >= 2){ //special action being triggered
                        cout << "WOW! Remove "<<numCleared<<" lines!!!"<<endl;
                        if(player1turn) cout<<"Player2 ";
                        if(player2turn) cout<<"Player1 ";
                        cout << "can choose Special Action from the following: " << '\n' <<
                        "Blind, Heavy, Force (if choose Force, followed by a block type)" << endl;
                        stringstream ss;
                        ss << numCleared;
                        string sss = ss.str();
                        string output = "WOW! Remove "+sss+" lines!"+"choose Special Action from:Blind,Heavy,Force.";
                        if(*curmultspecial){ //check it multiple effects can be produced simultaneously
                            output += "Type END to end selection";
                            cout<<"Type END to end selection"<<endl;
                        }
                        if(!text_only) gd->drawString(output);
                        string spact;
                        //check which special effect
                        while(cin >> spact){
                            if (spact == "blind"||spact == "Blind"){
                                auto tmp = make_shared<Blind>(*curse);
                                *curse= static_pointer_cast<SpecialEffect>(tmp);
                                if(!*curmultspecial) break;
                            }
                            else if (spact == "heavy"||spact == "Heavy"){
                                auto tmp = make_shared<Heavy>(*curse);
                                *curse= static_pointer_cast<SpecialEffect>(tmp);
                                if(!*curmultspecial) break;
                            }
                            else if (spact == "force"||spact == "Force"){
                                char nexttype;
                                while (cin>>nexttype) {
                                    if (nexttype != 'I' && nexttype != 'J' &&nexttype != 'L' && nexttype != 'O' && nexttype != 'S' && nexttype != 'Z' &&nexttype != 'T'){
                                        cout << "wrong block type, enter again"<<endl;
                                        string output = "wrong block type, enter again";
                                        if(!text_only) gd->drawString(" ");
                                        if(!text_only) gd->drawString(output);
                                    } else break;
                                }
                                char *effected;
                                if (player1turn) effected = &nextb2;
                                if (player2turn) effected = &nextb1;
                                auto tmp = make_shared<Force>(*curse, nexttype,effected);
                                (*curse) = static_pointer_cast<SpecialEffect>(tmp);
                                if(!*curmultspecial) break;
                            }
                            else if (spact == "END") break;
                        }
                        (*curse)->setBoard(*curboard);
                        (*curse)->produceEffect();
                        auto tmp3 = make_shared<DoNothing>();
                        *curse = static_pointer_cast<SpecialEffect>(tmp3);
                        b1->updateDisplay(level1, sc1->getScore(), nextb1);
                        b2->updateDisplay(level2, sc2->getScore(), nextb2);
                        cout<<*td;
                    }
                }
                
            }
            else if (cmdprc->level_up(cmd)){ //level_up() is called
                rightcmd = true;
                if (*curlevel <= 3){ //check if current level can be added
                    (*curlevel)++;
                    (*curnew)->addLevel(); //increment level
                    *curnextb = (*curnew)->getBlock(); //get next block according to the new level
                    (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                }
                cout << *td;
            }
            else if (cmdprc->level_down(cmd)){ //level_down() is called
                rightcmd = true;
                if (*curlevel >= 1){ //check if current level can be subtracted
                    (*curlevel)--;
                    (*curnew)->subLevel(); //decrement level
                    *curnextb = (*curnew)->getBlock(); //get next block according to the new level
                    (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                }
                cout << *td;
            }
            else if (cmdprc->left(cmd) || cmdprc->right(cmd) || cmdprc->down(cmd) || //a regular movement
                        cmdprc->clockwise(cmd) || cmdprc->counterclockwise(cmd) ){
                    rightcmd = true;
                    cmdprc->runCommand(cmd, *curboard, *curblock); //run the command
                    if (*curlevel == 3 || *curlevel == 4){ //check if it's on a "Heavy" level produced according to level
                        (*curblock)->down(*curboard);
                    }
                    if(cmdprc->left(cmd) || cmdprc->right(cmd)){//produce the "Heavy" special effect
                        for(int i = 0; i < (*curboard)->heavyLevel(); i++){
                            (*curblock)->down(*curboard);
                        }
                    }
                (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                cout << *td;
            }
            else if (cmdprc->no_random(cmd)){ //no_random is called, level 3, 4 only
                rightcmd = true;
                if (*curlevel == 3 || *curlevel == 4){
                    string norandFile;
                    cin >> norandFile;
                    (*curnew).reset(new newBlock(*curlevel, seed, norandFile));
                    (*curnew)->setNoRandom();
                }
            }
            else if (cmdprc->random(cmd)){ //random is called, level 3, 4 only
                rightcmd = true;
                if (*curlevel == 3 || *curlevel == 4){
                    (*curnew).reset(new newBlock(*curlevel, seed, curfilename));
                    (*curnew)->setRandom();
                }
            }
            else if (cmdprc->type(cmd)){ //specific type of block replace the current block
                rightcmd = true;
                char t = cmd[0];
                (*curblock)->my_clear(*curboard); //clear the current block from the board
                *curblock = initBlock(t, *curboard, *curlevel);
                (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                cout << *td;
            }
            else if (isdigit(cmd[0])){ //check command multiplier prefix
                rightcmd = true;
                int mult = 0;
                int numlen = 1;
                string thecmd, themult;
                while (isdigit(cmd[numlen])){
                numlen++;
                }
                thecmd = cmd.substr(numlen);
                themult = cmd.substr(0, numlen);
                istringstream iss{themult};
                iss >> mult;
                //check the command
                if (cmdprc->left(thecmd) || cmdprc->right(thecmd) || cmdprc->down(thecmd) ||
                    cmdprc->clockwise(thecmd) || cmdprc->counterclockwise(thecmd) ) {    //regular movement
                    cmdprc->multiCommand(mult, thecmd, *curboard, *curblock); //run the command mult times
                    if (*curlevel == 3 || *curlevel == 4){ //check if it's on a "Heavy" level produced according to level
                        (*curblock)->down(*curboard);
                    }
                    if(cmdprc->left(cmd) || cmdprc->right(cmd)){//produce the "Heavy" special effect
                        for(int i = 0; i < (*curboard)->heavyLevel(); i++){
                            (*curblock)->down(*curboard);
                        }
                    }
                    (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                    cout << *td;
                }
                else if (cmdprc->level_down(thecmd)){ //command is leveldown
                    for (int i=0; i<mult; i++) {
                        if (*curlevel >= 1){ //check if current level can be subtracted
                            (*curlevel)--;
                            (*curnew)->subLevel(); //decrement level
                            *curnextb = (*curnew)->getBlock(); //get next block according to the new level
                            (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                        }
                    }
                    cout << *td;
                }
                else if (cmdprc->level_up(thecmd)){ //command is levelup
                    for (int i=0; i<mult; i++){
                        if (*curlevel <= 3){ //check if current level can be added
                            (*curlevel)++;
                            (*curnew)->addLevel(); //increment level
                            *curnextb = (*curnew)->getBlock(); //get next block according to the new level
                            (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                        }
                    }
                    cout <<*td;
                }
                else if (cmdprc->drop(thecmd)){ //command is drop
                    int numCleared = 0;
                    bool finished = false;
                    for (int i=0; i< mult; i++){ //run for loop
                        cmdprc->runCommand(thecmd, *curboard, *curblock); //run the command
                        (*curboard)->setBlind(false); //turn off the blind mode
                        (*curnumPlaced)++;  //increase the number of number of cell places without removing at least one line
                        int addedScore = 0;
                        numCleared = (*curboard)->removeFull(&addedScore); //addedScore becomes to the score added because of the removal of a block
                        (*cursc)->addScore(addedScore);
                        if (numCleared>0) (*cursc)->addScore(pow(numCleared + (*curlevel), 2));
                        (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                        if (*curnextb == 'A'){ // EOF
                            cout << *td;
                            cout << "Input stream" << curfilename << " reaches EOF!" << endl;
                            cout << "GAME OVER" << endl;
                            b1->myclear(); //clear the board
                            b2->myclear();
                            td.reset();
                            cmdprc.reset();
                            b1.reset();
                            b2.reset();
                            sc1.reset();
                            sc2.reset();
                            se1.reset();
                            se2.reset();
                            newblk1.reset();
                            newblk2.reset();
                            if(!text_only) xw.reset();
                            if(!text_only) gd.reset();
                            return 0;
                        }
                        *curblock = initBlock(*curnextb, *curboard, *curlevel); //point the current block to the next block
                        if ((*curblock)->isOver()){//curblock can't be put into the board
                            cout << "Game Over" << endl;
                            string output = "Game Over";
                            if(player2turn){
                                cout<<"Player1 wins"<<endl;
                                output += " Player1 wins";
                            }
                            if(player1turn) {
                                cout<<"Player2 wins"<<endl;
                                output += " Player2 wins";
                            }
                            cout << "Type restart to start a new game. Type exit to exit the game." <<endl;
                            output += " Type restart to start a new game. Type exit to exit the game.";
                            if(!text_only) gd->drawString(" ");
                            if(!text_only) gd->drawString(output);
                            finished = true;
                        }
                        *curnextb = (*curnew)->getBlock(); //generate the next block
                        (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                        cout << *td;
                        //when no lines is cleared and the number of cells places is 5(or 10, 15...) and the level is 4
                        if ((numCleared==0)&&((*curlevel) == 4) && (((*curnumPlaced) % 5) == 0) && ((*curnumPlaced) >= 5)){
                            if(!(*curboard)->if_occupied(5, 3)){ // if the 1*1 Board can be placed at the centre colomn, created it
                                auto tmp = make_shared<BlockExtra>(*curboard, *curlevel);
                                shared_ptr<Block> added = static_pointer_cast<Block>(tmp);
                                added->drop(*curboard); // drop it
                                int addedScore = 0;
                                int numCleared = (*curboard)->removeFull(&addedScore);
                                (*cursc)->addScore(addedScore);
                                if (numCleared>0) {
                                    (*cursc)->addScore(pow(numCleared + *curlevel, 2));
                                    *curnumPlaced = 0;
                                }
                                (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                                cout<<*td;
                            }
                        }
                        //if there are lines cleared
                        if (numCleared >= 1){
                            (*curnumPlaced) = 0;
                            if (numCleared == 1) cout << "Remove 1 line!"<<endl; //1 line is cleared
                            if (numCleared >= 2){ //special action being triggered
                                cout << "WOW! Remove "<<numCleared<<" lines!!!"<<endl;
                                if(player1turn) cout<<"Player2 ";
                                if(player2turn) cout<<"Player1 ";
                                cout << "can choose Special Action from the following: " << '\n' <<
                                "Blind, Heavy, Force (if choose Force, followed by a block type)" << endl;
                                stringstream ss;
                                ss << numCleared;
                                string sss = ss.str();
                                string output = "WOW! Remove "+sss+" lines!"+"choose Special Action from:Blind,Heavy,Force.";
                                if(*curmultspecial){ //check it multiple effects can be produced simultaneously
                                    output += "Type END to end selection";
                                    cout<<"Type END to end selection"<<endl;
                                }
                                if(!text_only) gd->drawString(output);
                                string spact;
                                //check which special effect
                                while(cin >> spact){
                                    if (spact == "blind"||spact == "Blind"){
                                        auto tmp = make_shared<Blind>(*curse);
                                        *curse= static_pointer_cast<SpecialEffect>(tmp);
                                        if(!*curmultspecial) break;
                                    }
                                    else if (spact == "heavy"||spact == "Heavy"){
                                        auto tmp = make_shared<Heavy>(*curse);
                                        *curse= static_pointer_cast<SpecialEffect>(tmp);
                                        cout<<"???";
                                        if(!*curmultspecial) break;
                                    }
                                    else if (spact == "force"||spact == "Force"){
                                        char nexttype;
                                        while (cin>>nexttype) {
                                            if (nexttype != 'I' && nexttype != 'J' &&nexttype != 'L' && nexttype != 'O' && nexttype != 'S' && nexttype != 'Z' &&nexttype != 'T'){
                                                cout << "wrong block type, enter again"<<endl;
                                                string output = "wrong block type, enter again";
                                                if(!text_only) gd->drawString(" ");
                                                if(!text_only) gd->drawString(output);
                                            } else break;
                                        }
                                        char *effected;
                                        if (player1turn) effected = &nextb2;
                                        if (player2turn) effected = &nextb1;
                                        auto tmp = make_shared<Force>(*curse, nexttype,effected);
                                        *curse= static_pointer_cast<SpecialEffect>(tmp);
                                        if(!*curmultspecial) break;
                                    }
                                    else if (spact == "END") break;
                                }
                                (*curse)->setBoard(*curboard);
                                (*curse)->produceEffect();
                                auto tmp3 = make_shared<DoNothing>();
                                *curse = static_pointer_cast<SpecialEffect>(tmp3);
                                b1->updateDisplay(level1, sc1->getScore(), nextb1);
                                b2->updateDisplay(level2, sc2->getScore(), nextb2);
                                cout << *td;
                            }
                        }
                    }
                    if (finished) continue;
                }
                else if (cmdprc->restart(thecmd)){ //mult have no effect on restart
                    sc1->reset(); //reset score
                    sc2->reset();
                    b1->myclear(); //clear the board
                    b2->myclear();
                    level1 = 0;
                    level2 = 0;
                    newblk1 = make_shared<newBlock>(level1, seed, fileone);
                    newblk2 = make_shared<newBlock>(level1, seed, filetwo);
                    curblock1 = initBlock(newblk1->getBlock(), b1, 0);
                    curblock2 = initBlock(newblk2->getBlock(), b2, 0);
                    nextb1 = newblk1->getBlock();
                    nextb2 = newblk2->getBlock();
                    b1->updateDisplay(level1, sc1->getScore(), nextb1);
                    b2->updateDisplay(level2, sc2->getScore(), nextb2);
                    player1turn = true;
                    player2turn = false;
                    cout << *td;
                    cout<<"Player1's turn"<<endl;
                    continue;
                }
                else if (cmdprc->no_random(thecmd)){  //mult have no effect on norandom
                    if (*curlevel == 3 || *curlevel == 4){
                        string norandFile;
                        cin >> norandFile;
                        (*curnew).reset(new newBlock(*curlevel, seed, norandFile));
                        (*curnew)->setNoRandom();
                    }
                }
                else if (cmdprc->random(thecmd)){ //mult have no effect on norandom
                    if (*curlevel == 3 || *curlevel == 4){
                        (*curnew).reset(new newBlock(*curlevel, seed, curfilename));
                        (*curnew)->setRandom();
                    }
                }
                else if (cmdprc->type(thecmd)){ //mult have no effect on appointing a specific curblock
                    cout<<"hi";
                    char t = cmd[0];
                    (*curblock)->my_clear(*curboard); //clear the current block from the board
                    *curblock = initBlock(t, *curboard, *curlevel);
                    (*curboard)->updateDisplay(*curlevel, (*cursc)->getScore(), *curnextb);
                    cout << *td;
                }
            }
            if(rightcmd){
                //swap turn
                player1turn = !player1turn;
                player2turn = !player2turn;
            }
            string output;
            if (player1turn){
                cout<<"Player1's turn"<<endl;
                output = "Player1's turn";
            }
            if (player2turn){
                cout<<"Player2's turn"<<endl;
                output = "Player2's turn";
            }
            if(!text_only) gd->drawString(output);
            rightcmd = false;
        }
    }
    b1->myclear(); //clear the board
    b2->myclear();
    return 0;
}
