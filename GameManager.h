#pragma once

#include "Tetrimino.h"
#include "Board.h"

const signed short int BLOCK_SIZE = 4;
const static enum GAME_STATUS{ GAME_OVER, PLAYING, NEXT_STAGE } GAME_STATUS;

const static int DEFAULT_SPEED = 1000;
const static int SPEED_INTERVAL = 200;
const static int CLEAR_SCORE = 1000;

const static int GAME_FRAME = 20;

/*
 * No description
 */
class GameManager
{

	public:
	int gameStatus = GAME_OVER;	// 0: game over, 1: playing 2: stage clear
	int gameLevel = 1;	// 1 ~ 
	int gameScore = 0;
    int gameTime = 0;

		Board stackBlocks;
           Tetrimino *moving_block;     // ���� �� 
           Tetrimino *waiting_block;    // ��� ��     
           
		// class constructor
		   GameManager();
		// class destructor
		~GameManager();
		
        // ����ȭ�鱸��
	    void setBackGround();	// ��� �� ���
		void setTimeBoard();	// �ð� Ÿ�̸� ���
		void setLevelBoard();	// ���� ���� ���
		void setScoreBoard();	// ���ھ� ���� ���
		
	    Tetrimino* getRandomTetrimino();
        void createWatingBlock();
        void activeMovingBlock();             // �����̴� �� Ȱ��ȭ
        void moveBlock(char arrow);         // �� �̵� : a, s, d
        void rotateBlock(char direction);   // �� ȸ�� : l, r

        void moveXY(Tetrimino* block, COORD _xy);  // ��ǥ ��� �̵�
		void absMoveXY(Tetrimino* block, COORD _xy);  // ��ǥ ���� �̵�

        void processEndline();                // �� �ϴ� ���� üũ
        void processEndScore();                // ���� ���� üũ
        
        // �����Ӱ��ɿ���üũ
        bool canMove(char direction);
        
        // ���� ��Ʈ��
        void introGame();

        // ���� ����!
        void startGame();

        // ���� ����!
        void endGame(int aGameStatus);
        
};