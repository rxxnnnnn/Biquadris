#ifndef __BLOCKEXTRA_H__
#define __BLOCKEXTRA_H__
#include "Block.h"
#include <memory>

class BlockExtra : public Block {
public:
	BlockExtra(std::shared_ptr<Board> b, int level1);
	~BlockExtra();
	void clockwise(std::shared_ptr<Board> b){};
	void counterclockwise(std::shared_ptr<Board> b){};
};

#endif