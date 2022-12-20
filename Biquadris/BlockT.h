#ifndef __BLOCKT_H__
#define __BLOCKT_H__
#include "Block.h"
#include <memory>

class Board;

class BlockT : public Block {
public:
	BlockT(std::shared_ptr<Board> b, int level1);
	~BlockT();
	
	void clockwise(std::shared_ptr<Board> b);
	void counterclockwise(std::shared_ptr<Board> b);

private:
    int TShape;
    void TShape1(int yy, int xx, std::shared_ptr<Board> b);
	void TShape2(int yy, int xx, std::shared_ptr<Board> b);
	void TShape3(int yy, int xx, std::shared_ptr<Board> b);
	void TShape4(int yy, int xx, std::shared_ptr<Board> b);
};

#endif