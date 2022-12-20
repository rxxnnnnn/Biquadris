#ifndef __BLOCKS_H__
#define __BLOCKS_H__
#include "Block.h"
#include <memory>

class Board;

class BlockS : public Block {
public:
	BlockS(std::shared_ptr<Board> b, int level1);
	~BlockS();
	
	void clockwise(std::shared_ptr<Board> b);
	void counterclockwise(std::shared_ptr<Board> b);

private:
    int SShape;
    void SShape1(int yy, int xx, std::shared_ptr<Board> b);
	void SShape2(int yy, int xx, std::shared_ptr<Board> b);
    void SShape3(int yy, int xx, std::shared_ptr<Board> b);
    void SShape4(int yy, int xx, std::shared_ptr<Board> b);
};

#endif