#ifndef __BLOCKO_H__
#define __BLOCKO_H__
#include "Block.h"
#include <memory>

class Board;

class BlockO : public Block {

public:
	BlockO(std::shared_ptr<Board> b, int level1);
	~BlockO();
	
	void clockwise(std::shared_ptr<Board> b);
	void counterclockwise(std::shared_ptr<Board> b);
};

#endif