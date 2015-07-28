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
           Tetrimino *moving_block;     // 조작 블럭 
           Tetrimino *waiting_block;    // 대기 블럭     
           
		// class constructor
		   GameManager();
		// class destructor
		~GameManager();
		
        // 게임화면구성
	    void setBackGround();	// 배경 블럭 출력
		void setTimeBoard();	// 시간 타이머 출력
		void setLevelBoard();	// 레벨 보드 출력
		void setScoreBoard();	// 스코어 보드 출력
		
	    Tetrimino* getRandomTetrimino();
        void createWatingBlock();
        void activeMovingBlock();             // 움직이는 블럭 활성화
        void moveBlock(char arrow);         // 블럭 이동 : a, s, d
        void rotateBlock(char direction);   // 블럭 회전 : l, r

        void moveXY(Tetrimino* block, COORD _xy);  // 좌표 상대 이동
		void absMoveXY(Tetrimino* block, COORD _xy);  // 좌표 절대 이동

        void processEndline();                // 블럭 하단 도달 체크
        void processEndScore();                // 종료 점수 체크
        
        // 움직임가능여부체크
        bool canMove(char direction);
        
        // 게임 인트로
        void introGame();

        // 게임 시작!
        void startGame();

        // 게임 종료!
        void endGame(int aGameStatus);
        
};