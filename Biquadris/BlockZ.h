#ifndef __BLOCKZ_H__
#define __BLOCKZ_H__
#include "Block.h"
#include <memory>

class Board;

class BlockZ : public Block {
public:
	BlockZ(std::shared_ptr<Board> b, int level1);
	~BlockZ();
	
	void clockwise(std::shared_ptr<Board> b);
	void counterclockwise(std::shared_ptr<Board> b);

private:
    int ZShape;
    void ZShape1(int yy, int xx, std::shared_ptr<Board> b);
	void ZShape2(int yy, int xx, std::shared_ptr<Board> b);
    void ZShape3(int yy, int xx, std::shared_ptr<Board> b);
	void ZShape4(int yy, int xx, std::shared_ptr<Board> b);
};

#endif