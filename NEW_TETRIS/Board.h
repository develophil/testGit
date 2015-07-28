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
	bool isOverflow();		// �������� ���� ����

	short getDiffTop(Tetrimino *t);	// �ش� ����ġ���� �׿��ִ� �� �� ���� ����� �ֻ��� �������� �Ÿ� ��ȯ
	short getTopY(short x);

	int deleteFullLine();	// ������ ���� ���� : ������ȯ
	void printBlocks();		// �׿��ִ� ��ü �� ���

	void printText(short delay, char *text);
};

