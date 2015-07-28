#pragma once

enum BLOCK_TYPE {I,J,L,O,S,T,Z};
const char BLOCK_SHAPE[4][3] = {"  ","��","��","��"};

class Tetrimino
{
      public:
              short boxSize;
              short type;
              short color;
              char *shape;
			  Tile *blocks;
			  short posX;
			  short posY;
	

		// class constructor
		Tetrimino();
		Tetrimino(short boxSize, short type, short color, char *shape, COORD *arCoord);		
		// class destructor
		~Tetrimino();
		
		// ����� 

        // ������
        void clearBlock();
        // �����
        void printBlock();

        
};
