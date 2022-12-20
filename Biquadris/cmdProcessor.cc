#include "cmdProcessor.h"
using namespace std;

//check if the command is exit
bool cmdProcessor::exit(std:: string cmd){
    if ( cmd == "ex"|| cmd == "exi" || cmd == "exit"){
        return true;
    } else return false;
}

//check if the command is left
bool cmdProcessor::left(std:: string cmd){
    if ( cmd == "lef"|| cmd == "left"){
        return true;
    } else return false;
}

//check if the command is right
bool cmdProcessor::right(std:: string cmd){
    if (cmd == "ri" || cmd == "rig" || cmd == "righ" || cmd == "right"){
        return true;
    } else return false;
}


//check if the command is down
bool cmdProcessor::down(std:: string cmd){
    if (cmd == "do" || cmd == "dow" || cmd == "down"){
        return true;
    } else return false;
}

//check if the command is clockwise
bool cmdProcessor::clockwise(std:: string cmd){
    if (cmd == "cl" || cmd == "clo" ||cmd == "cloc"|| cmd == "clock" || cmd == "clockw"||
        cmd == "clockwi" || cmd == "clockwis" || cmd == "clockwise"){
        return true;
    } else return false;
}

//check if the command is counterclockwise
bool cmdProcessor::counterclockwise(std:: string cmd){
    if (cmd == "co" || cmd == "cou" || cmd == "coun" || cmd == "count" ||
        cmd == "counte" || cmd == "counter" || cmd == "counterc" || cmd == "countercl" ||
        cmd == "counterclo" || cmd == "countercloc" || cmd == "counterclock" || cmd == "couterclockw" ||
        cmd == "counterclockwi" || cmd == "counterclockwis" || cmd == "counterclockwise"){
        return true;
    } else return false;
}

//check if the command is drop
bool cmdProcessor::drop(std:: string cmd){
    if (cmd == "dr" || cmd == "dro" || cmd == "drop"){
        return true;
    } else return false;
}


//check if the command is levelup
bool cmdProcessor::level_up(std:: string cmd) {
    if (cmd == "levelu" || cmd == "levelup"){
        return true;
    } else return false;
}

//check if the command is leveldown
bool cmdProcessor::level_down(std:: string cmd) {
    if (cmd == "leveld" || cmd == "leveldo" || cmd == "leveldow" || cmd == "leveldown"){
        return true;
    } else return false;
}

//check if the command is random
bool cmdProcessor::random(std:: string cmd){
    if (cmd == "ra" || cmd == "ran" || cmd == "rand" || cmd == "rando" || cmd == "random"){
        return true;
    } else return false;
}

//check if the command is norandom
bool cmdProcessor::no_random(std:: string cmd){
    if (cmd == "n" || cmd == "no" || cmd == "nor" || cmd == "nora" || cmd == "noran" ||
        cmd == "norand" || cmd == "norando" || cmd == "norandom"){
        return true;
    } else return false;
}

//check if the command is sequence
bool cmdProcessor::sequence(std:: string cmd){
    if (cmd == "s" || cmd == "se" || cmd == "seq" || cmd == "sequ" || cmd == "seque" ||
        cmd == "sequen" || cmd == "sequenc" || cmd == "sequence"){
        return true;
    } else return false;
}

//check if the command is restart
bool cmdProcessor::restart(std:: string cmd) {
    if (cmd == "re" || cmd == "res" || cmd == "rest" || cmd == "resta" ||
        cmd == "restar" || cmd == "restart"){
        return true;
    } else return false;
}


//check if the command is block type
bool cmdProcessor::type(std:: string cmd){
    return (cmd=="I"||cmd=="L"||cmd=="J"||cmd=="O"||cmd=="S"||cmd=="Z"||cmd=="T");
}

//run the command
void cmdProcessor::runCommand(std:: string cmd, shared_ptr<Board> brd, shared_ptr<Block> blk){
        if (left(cmd)) {
            blk->left(brd);
        } else if (right(cmd)){
            blk->right(brd);
        } else if (down(cmd)){
            blk->down(brd);
        } else if (clockwise(cmd)){
            blk->clockwise(brd);
        } else if (counterclockwise(cmd)){
            blk->counterclockwise(brd);
        } else if (drop(cmd)){
            blk->drop(brd);
        }
}

//check if the command is multicommand
void cmdProcessor::multiCommand(int mult, std::string cmd, shared_ptr<Board> brd, shared_ptr<Block> blk){
        for (int i = 0; i < mult; i++){
            runCommand(cmd, brd, blk);
        }
}
