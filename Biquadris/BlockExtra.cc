#include "BlockExtra.h"
#include "Board.h"
using namespace std;

BlockExtra::BlockExtra(shared_ptr<Board>b, int level1) {
    coordinates = vector<Position>(1, {5, 3});  
    ijloszt = '*';
    level = level1;
	numCell=1;
	isOver1 = false;
	if (b->if_occupied(5, 3)) isOver1 = true;
    b->setCell(5, 3, ijloszt,nullptr);
}

BlockExtra::~BlockExtra(){
	coordinates.clear();
}
