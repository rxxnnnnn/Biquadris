#ifndef __BLOCKI_H__
#define __BLOCKI_H__
#include "Block.h"
#include <memory>

class Board;

class BlockI : public Block {
public:
	BlockI(std::shared_ptr<Board> b, int level1);
	~BlockI();
	
	void clockwise(std::shared_ptr<Board> b) override;
	void counterclockwise(std::shared_ptr<Board> b) override;
};

#endif