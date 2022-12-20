#ifndef __BLOCKJ_H__
#define __BLOCKJ_H__
#include "Block.h"
#include <memory>

class Board;

class BlockJ : public Block {
public:
	BlockJ(std::shared_ptr<Board> b, int level1);
	~BlockJ();
	
	void clockwise(std::shared_ptr<Board> b);
	void counterclockwise(std::shared_ptr<Board> b);

private:
    int JShape;
    void JShape1(int yy, int xx, std::shared_ptr<Board> b);
	void JShape2(int yy, int xx, std::shared_ptr<Board> b);
	void JShape3(int yy, int xx, std::shared_ptr<Board> b);
	void JShape4(int yy, int xx, std::shared_ptr<Board> b);
};

#endif
