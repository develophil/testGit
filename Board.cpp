#include "stdafx.h"

Board::Board()
{
	posX = posY = 1;
}


Board::~Board()
{

}


void Board::initStackBlocks()
{
	for (int i = 0; i<sizeof(tiles) / sizeof(tiles[0]); i++)
	{
		for (int j = 0; j<sizeof(tiles[0]) / sizeof(tiles[0][0]); j++)
		{
			tiles[i][j] = nullptr;
		}
	}
}

void Board::clearStackBlocks()
{
	for (int i = 0; i<sizeof(tiles) / sizeof(tiles[0]); i++)
	{
		for (int j = 0; j<sizeof(tiles[0]) / sizeof(tiles[0][0]); j++)
		{
			delete tiles[i][j];
		}
	}
}

bool Board::canMove(short aI, short aJ)
{
	bool result = false;
	
	if (aI == 0 || aI == 11 || aJ == 21)
		result = true;
	else
		result = tiles[aJ - posY][aI - posX] == nullptr ? false : true;
	
	return result;
}


void Board::stack(Tetrimino *pMoving_block)
{
	short _x = pMoving_block->posX;
	short _y = pMoving_block->posY;

	short x = 0;
	short y = 0;
	short bgColor = BLACK;
	short txtColor = pMoving_block->color;
	char *shape = pMoving_block->shape;

	for (int i = 0; i < BLOCK_SIZE; i++) {
		x = _x + ((pMoving_block->blocks) + i)->innerX;
		y = _y + ((pMoving_block->blocks) + i)->innerY;

		tiles[y - posY][x - posX] = new Tile(x, y, bgColor, txtColor, shape);
	}
	
}

// 해당 블럭위치에서 쌓여있는 블럭 중 가장 가까운 최상위 블럭까지의 거리 반환
short Board::getDiffTop(Tetrimino *t)
{

	short _x = t->posX;
	short _y = t->posY;

	short iX = 0;
	short iY = 0;
	
	short xx = 0;
	short yy = 0;
	short diff = 20;
	short tempDiff = 20;
	short topY = 20;

	for (int i = 0; i<BLOCK_SIZE; i++)
	{
		iX = ((t->blocks) + i)->innerX;
		iY = ((t->blocks) + i)->innerY;
				
		topY = getTopY(_x + iX);
		tempDiff = topY - _y - iY;

		if ( tempDiff < diff ) {
			diff = tempDiff;
			xx = _x + iX;
			yy = _y + iY;
		}

	}


	return diff;
}

short Board::getTopY(short x)
{
	short result = 20;

	for (int i = 0; i<sizeof(tiles) / sizeof(tiles[0]); i++)
	{
		if (tiles[i][x-1] != nullptr) {
			result = i;
			break;
		}
	}

	return result;
}

// 게임진행 가능 여부		
bool Board::isOverflow()
{
	bool result = false;


	return result;

}

// 가득찬 라인 삭제 : 점수 반환
int Board::deleteFullLine()
{
	bool isFullLine = true;
	int score = 0;
	int add = 100;
	int multiple = 1;

	for (int i = 0; i < sizeof(tiles) / sizeof(tiles[0]); i++)
	{
		isFullLine = true;
		for (int j = 0; j<sizeof(tiles[0]) / sizeof(tiles[0][0]); j++)
		{
			if (tiles[i][j] == nullptr) {
				isFullLine = false;
				break;
			}
		}

		if (isFullLine) {	// 가득찬 라인이면
			
			memmove(tiles[1], tiles[0], sizeof(tiles[0]) * i);

			for (int t = 0; t < sizeof(tiles[0]) / sizeof(tiles[0][0]); t++)
			{
				tiles[t][0] = nullptr;
			}

			SetCursor(false);
			setcolor(ORIGINAL, BLACK);
			gotoxy(1, i + 1);
			printf("□□□□□□□□□□");
			Sleep(25); 
			gotoxy(1, i + 1);
			printf("◇◇◇◇◇◇◇◇◇◇");
			Sleep(25);
			printBlocks();

			score += add * multiple;

			multiple = (multiple << 1);
		}
	}
	return score;
}

// 쌓여있는 전체 블럭 출력
void Board::printBlocks()
{
	SetCursor(false);
	for (int i = 0; i < sizeof(tiles) / sizeof(tiles[0]); i++)
	{
		for (int j = 0; j < sizeof(tiles[0]) / sizeof(tiles[0][0]); j++)
		{
			gotoxy(j+1, i+1);
			if (tiles[i][j] != nullptr) {
				setcolor(tiles[i][j]->txtColor, tiles[i][j]->bgColor);
				printf("%s", tiles[i][j]->shape);
			}
			else{
				printf("%s", "  ");
			}
			gotoxy(0, 0);
		}
		printf("\n");
	}
}
