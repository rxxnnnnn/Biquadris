#ifndef __BLOCKL_H__
#define __BLOCKL_H__
#include "Block.h"
#include <memory>

class Board;

class BlockL : public Block {
public:
	BlockL(std::shared_ptr<Board> b, int level1);
	~BlockL();
	
	void clockwise(std::shared_ptr<Board> b);
	void counterclockwise(std::shared_ptr<Board> b);

private:
	int LShape;
    void LShape1(int yy, int xx, std::shared_ptr<Board> b);
	void LShape2(int yy, int xx, std::shared_ptr<Board> b);
	void LShape3(int yy, int xx, std::shared_ptr<Board> b);
	void LShape4(int yy, int xx, std::shared_ptr<Board> b);
};

#endif