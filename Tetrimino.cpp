#include "stdafx.h"

// class constructor
Tetrimino::Tetrimino()
{
	// insert your code here
}


// class constructor
Tetrimino::Tetrimino(short _boxSize, short _type, short _color, char _shape[], COORD *arCoord)
{
    //cout << "생성자호출!" << endl;
    

	posX = posY = 0;
	boxSize = _boxSize;
	type = _type;
	color = _color;
	shape = _shape;
	blocks = new Tile[BLOCK_SIZE];
    //coord = new COORD[4];
    //xy = new COORD{0,0};
    
	for (int i = 0; i<BLOCK_SIZE; i++)
	{
		(blocks + i)->innerX = (arCoord + i)->X;
		(blocks + i)->innerY = (arCoord + i)->Y;
		strcpy_s((blocks + i)->shape,shape);
	}


}

// class destructor
Tetrimino::~Tetrimino()
{
	// insert your code here
    //free(coord);
    //delete[] coord;
	delete[] blocks;
}

// 블럭지움
void Tetrimino::clearBlock()
{
	SetCursor(false);
    for(int i=0; i<BLOCK_SIZE; i++)
    {
		//gotoxy(posX + ((coord + i)->X), posY + ((coord + i)->Y));
		gotoxy(posX + ((blocks + i)->innerX), posY + ((blocks + i)->innerY));
        printf("%s","  ");
    }
}

// 블럭출력
void Tetrimino::printBlock()
{
	SetCursor(false);
    setcolor((int)color,BLACK);
    for(int i=0; i<BLOCK_SIZE; i++)
    {
		//gotoxy(posX + ((coord + i)->X), posY + ((coord + i)->Y));
		gotoxy(posX + ((blocks + i)->innerX), posY + ((blocks + i)->innerY));
        printf("%s",shape);
    }
}


