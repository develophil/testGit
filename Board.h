#pragma once
#include "Tetrimino.h"

typedef struct Tile
{
	short innerX;
	short innerY;
	short bgColor;
	short txtColor;
	char shape[3];

	Tile() {
		innerX = innerY = 0;
		bgColor = 0;	// BLACK
		txtColor = 7;	// ORIGINAL
	};
	Tile(short aI, short aJ, short aBgColor, short aTxtColor, char aShape[]) {
		innerX = aI;
		innerY = aJ;
		bgColor = aBgColor;
		txtColor = aTxtColor;
		strcpy_s(shape, aShape);
	};
} Tile;


class Board
{
	short posX;
	short posY;
	Tile *tiles[20][10];

public:
	Board();
	~Board();

	void stack(Tetrimino *pMoving_block);
	void initStackBlocks();
	void clearStackBlocks();

	bool canMove(short aI, short aJ);
	bool isOverflow();		// 게임진행 가능 여부

	short getDiffTop(Tetrimino *t);	// 해당 블럭위치에서 쌓여있는 블럭 중 가장 가까운 최상위 블럭까지의 거리 반환
	short getTopY(short x);

	int deleteFullLine();	// 가득찬 라인 삭제 : 점수반환
	void printBlocks();		// 쌓여있는 전체 블럭 출력

	void printText(short delay, char *text);
};

