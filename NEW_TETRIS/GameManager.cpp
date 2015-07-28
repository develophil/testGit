#include "stdafx.h"

static const char background[22][51] = {
      {"▩▩▩▩▩▩▩▩▩▩▩▩  ▩▩▩▩▩▩▩▩▩▩▩▩"},
      {"▩                    ▩  ▩      ▩            ▩"},
      {"▩                    ▩  ▩  다  ▩            ▩"},      
      {"▩                    ▩  ▩  음  ▩            ▩"},      
      {"▩                    ▩  ▩  블  ▩            ▩"},      
      {"▩                    ▩  ▩  럭  ▩            ▩"},                        
      {"▩                    ▩  ▩      ▩            ▩"},      
      {"▩                    ▩  ▩▩▩▩▩▩▩▩▩▩▩▩"},      
      {"▩                    ▩                          "},
      {"▩                    ▩  ▩▩▩▩▩▩▩▩▩▩▩▩"},
      {"▩                    ▩  ▩시  간              ▩"},
      {"▩                    ▩  ▩                    ▩"},
      {"▩                    ▩  ▩                    ▩"},            
      {"▩                    ▩  ▩▩▩▩▩▩▩▩▩▩▩▩"},
      {"▩                    ▩  ▩레  벨              ▩"},
      {"▩                    ▩  ▩                    ▩"},
      {"▩                    ▩  ▩                    ▩"},                  
      {"▩                    ▩  ▩▩▩▩▩▩▩▩▩▩▩▩"},
      {"▩                    ▩  ▩점  수              ▩"},
      {"▩                    ▩  ▩                    ▩"},
      {"▩                    ▩  ▩                    ▩"},                  
      {"▩▩▩▩▩▩▩▩▩▩▩▩  ▩▩▩▩▩▩▩▩▩▩▩▩"},            
};

const short colors[] = {SKY_BLUE, BLUE, PLUM, YELLOW, GREEN, PURPLE, RED, GRAY, BLACK};
const char *pShapes[] = {"  ","■","□","▩"};


void gotoxy(short x,short y)
{	
	COORD pos={x*2,y};
	SetConsoleCursorPosition(COL, pos); 
 }

void setcolor(int color, int bgcolor) 
{
    color &= 0xf;
    bgcolor &= 0xf;
    SetConsoleTextAttribute(COL, (bgcolor << 4) | color);
}


// class constructor
GameManager::GameManager()
{
}

// class destructor
GameManager::~GameManager()
{
    //cout << "게임메니저 소멸자!" <<endl; 
	delete moving_block;
    delete waiting_block;
}


void GameManager::setBackGround()
{
	 setcolor(ORIGINAL, BLACK);
     
	 // 배경 블럭 출력
	 for(int i=0; i<sizeof(background)/sizeof(background[0]); i++)
     {
          cout << background[i] << endl;
     }

	 // 시간 타이머 출력
	 setTimeBoard();
	 // 레벨 보드 출력
	 setLevelBoard();
	 // 스코어 보드 출력
	 setScoreBoard();

    //OutModule write;
   
    //COORD coord[BLOCK_SIZE] = 
    //{
    //    { 0, 0 },
    //    { 0, 1 },
    //    { 0, 2 },
    //    { 1, 1 },
    //};
    //           
    //    for(int i = 0 ; i < BLOCK_SIZE ; i++ )
    //    {
    //        coord[i].X ++;
    //        coord[i].Y +=2;
    //        write.Render( coord[i], 0 );
    //    }
    //    write.flush();
    //



//     cout << sizeof(background) << endl;
//     cout << sizeof(background[0]) << endl;
//     cout << sizeof(background[0][0]) << endl;          

}

Tetrimino* GameManager::getRandomTetrimino()
{
    randomize();

    short type = random(7);
    short boxSize = 0;
    short color = 0;

	COORD arCoord[BLOCK_SIZE];
    switch(type)
    {

    case I:
        {
        boxSize = 4;
        color = SKY_BLUE;
		arCoord[0] = { 1, 0 };
		arCoord[1] = { 1, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 1, 3 };
        break;
        }
    case J:
        {
        boxSize = 3;
        color = BLUE;
		arCoord[0] = { 1, 0 };
		arCoord[1] = { 1, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 0, 2 };
        break;
        }
    case L:
        {
        boxSize = 3;
        color = GOLD;
		arCoord[0] = { 1, 0 };
		arCoord[1] = { 1, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 2, 2 };
        break;
        }
    case O:
        {
        boxSize = 4;
        color = YELLOW;
		arCoord[0] = { 1, 1 };
		arCoord[1] = { 2, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 2, 2 };
        break;
        }
    case S:
        {
        boxSize = 3;
        color = GREEN;
		arCoord[0] = { 0, 2 };
		arCoord[1] = { 1, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 2, 1 };
        break;
        }
    case T:
        {
        boxSize = 3;
        color = PLUM;
		arCoord[0] = { 0, 1 };
		arCoord[1] = { 1, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 2, 1 };
        break;
        }
    case Z:
        {
        boxSize = 3;
        color = RED;
		arCoord[0] = { 0, 1 };
		arCoord[1] = { 1, 1 };
		arCoord[2] = { 1, 2 };
		arCoord[3] = { 2, 2 };
        break;
        }
    }
    
	Tetrimino *temp = new Tetrimino(boxSize, type, color, (char *)BLOCK_SHAPE[2], arCoord);

    return temp;
}


void GameManager::createWatingBlock()
{
    waiting_block = getRandomTetrimino();
    
    moveXY(waiting_block, {19,2});

    waiting_block->printBlock();
}

// 블럭소속변경 : s, m, w
void GameManager::activeMovingBlock()
{
	if (waiting_block == nullptr) {
		createWatingBlock();
	}
	waiting_block->clearBlock();
	moving_block = waiting_block;

	absMoveXY(moving_block, {5,1});

	moving_block->printBlock();

	createWatingBlock();
}

// 좌표 이동
void GameManager::moveXY(Tetrimino* block, COORD _xy)
{
	block->posX += _xy.X;
	block->posY += _xy.Y;
}

// 좌표 이동
void GameManager::absMoveXY(Tetrimino* block, COORD _xy)
{
	block->posX = _xy.X;
	block->posY = _xy.Y;
}


// 블럭 이동 : a,s,d
void GameManager::moveBlock(char arrow)
{

    if(moving_block != nullptr && canMove(arrow))
    {
        moving_block->clearBlock(); 

        switch(arrow)
        {
		case KEY_LEFT:
        case 'a':
            moveXY(moving_block, {-1,0});
            break;
		case KEY_RIGHT:
        case 'd':
            moveXY(moving_block, {1,0});
            break;
		case KEY_DOWN:
        case 's':
            moveXY(moving_block, {0,1});
            break;
		case ' ':
			short diff = stackBlocks.getDiffTop(moving_block);
			moveXY(moving_block, { 0, diff });
			break;
        }
        moving_block->printBlock();
	}
	else{
		if (moving_block->posX == 5 && moving_block->posY == 1) {
			// 게임 종료 처리
			endGame(GAME_OVER);
			return;
		}
	}
    
        processEndline();   // 블럭 하단 도달 체크    
	    processEndScore();  // 종료 점수 체크
		
}

// 블럭 회전 : l, r
void GameManager::rotateBlock(char direction)
{
    moving_block->clearBlock();

	short adjustMoving = 0;
	short _x = moving_block->posX;
    short temp;
    for(int i=0; i<BLOCK_SIZE; i++)
    {
        temp = ((moving_block->blocks)+i)->innerX;
		((moving_block->blocks) + i)->innerX = moving_block->boxSize - 1 - ((moving_block->blocks) + i)->innerY;
		((moving_block->blocks) + i)->innerY = temp;


		// 벽 뚫는것 보정 로직
		switch (_x + ((moving_block->blocks) + i)->innerX)
		{
		case -1:
			adjustMoving = 2;
			break;
		case 0:
			if(adjustMoving == 0) adjustMoving = 1;
			break;
		case 11:
			if(adjustMoving == 0) adjustMoving = -1;
			break;
        case 12:
			adjustMoving = -2;
			break;
		}


    }

	if (adjustMoving != 0) {
		moveXY(moving_block, { adjustMoving, 0 });
	}

    moving_block->printBlock();
}

// 블럭 하단 도달 처리
void GameManager::processEndline()
{
    short x = 0;
    short y = 0;
    short _x = 0;
    short _y = 0;
    Tetrimino *temp = nullptr;
    for(int i=0; i<BLOCK_SIZE; i++)
    {
		x = ((moving_block->posX) + ((moving_block->blocks + i)->innerX));
		y = ((moving_block->posY) + ((moving_block->blocks + i)->innerY));

		if (y == 20 || stackBlocks.canMove(x, y + 1))
        {
			 stackBlocks.stack(moving_block);	// 블럭 쌓기
			 gameScore += 10;

			 gameScore += stackBlocks.deleteFullLine();		// 가득찬 라인 삭제
             waiting_block->clearBlock();		
             activeMovingBlock();
        }
    }
	setScoreBoard();
}

void GameManager::processEndScore()
{
    if(gameScore >= CLEAR_SCORE) {
        endGame(NEXT_STAGE);
    }
}


// 움직임가능여부체크
bool GameManager::canMove(char direction)
{
    bool result = true;

    short x = 0;
    short y = 0;
    short _x = 0;
    short _y = 0;

    Tetrimino *temp = nullptr;
        
    for(int i=0; i<BLOCK_SIZE; i++)
    {
		x = (moving_block->posX) + ((moving_block->blocks + i)->innerX);
		y = (moving_block->posY) + ((moving_block->blocks + i)->innerY);

        
        switch(direction)
        {
		case KEY_LEFT:
        case 'a':
			if (stackBlocks.canMove(x - 1, y)) result = false;
            break;
		case KEY_DOWN:
        case 's':
			if (stackBlocks.canMove(x, y + 1)) result = false;
            break;
		case KEY_RIGHT:
        case 'd':
			if (stackBlocks.canMove(x + 1, y)) result = false;
            break;
        }

        if(!result)
            break;
    }
 
    return result;
}


void GameManager::startGame()
{
    
    // [콘솔창 크기 변경]
    //system("mode con cols=80 lines=26");

    // [콘솔창 제목 변경]
    system("Have fun with My Tetris!");

    // [콘솔창 화면 지우기]
    system("cls");

    // [콘솔 커서 숨김]
    SetCursor(false);

	if(gameStatus == GAME_OVER) {
        gameLevel = 1;
    }else if(gameStatus == NEXT_STAGE) {
        gameLevel += 1;
    }

	gameStatus = PLAYING;
	gameScore = 0;
    gameTime = 0;
	
	stackBlocks.initStackBlocks();		// 작업공간 준비

    setBackGround();
	Sleep(1000);
    activeMovingBlock();

    int timeBuffer = 0;
	while (gameStatus == PLAYING)
    {

    	setTimeBoard();

		timeBuffer += GAME_FRAME;
		if (timeBuffer >= (DEFAULT_SPEED - (gameLevel - 1) * SPEED_INTERVAL))
        {
            timeBuffer = 0;
            moveBlock('s'); // 블럭 한칸 이동
        }else{

            char key;
            if(_kbhit())
            {
                key = _getch();
                switch( key )
                {
                case 0xE0:
                    _getch();
                    break;
				case ' ':
				case KEY_DOWN:
				case KEY_LEFT:
				case KEY_RIGHT:
                case 'a':
                case 's':
                case 'd':
                    moveBlock(key);
                    break;
				case KEY_UP:
                case 'w':
                    rotateBlock(key);
                    break;
                default:
                    break;
                }
            }
        }

		Sleep(GAME_FRAME);

    }
}



void GameManager::setTimeBoard()	// 시간 타이머 출력
{
	setcolor(ORIGINAL, BLACK);
	gotoxy(17, 11);

    gameTime += GAME_FRAME;


    if(gameTime % 1000 == 0) {
        short seconds = ( gameTime / 1000 ) % 60;
        short minutes = ( gameTime / 1000 ) / 60;
	    printf("%02d : %02d", minutes, seconds);
    }
	SetCursor(false);

}

void GameManager::setLevelBoard()	// 레벨 보드 출력
{
	SetCursor(false);
	setcolor(ORIGINAL, BLACK);
	gotoxy(21, 15);
	printf("%d", gameLevel);
}
void GameManager::setScoreBoard()	// 스코어 보드 출력
{
	SetCursor(false);
	setcolor(ORIGINAL, BLACK);
	gotoxy(19, 19);
	printf("%d", gameScore);
}


void GameManager::endGame(int aGameStatus)
{
    // 게임 종료 처리
	gameStatus = aGameStatus;			// 진행상태 변경

	stackBlocks.clearStackBlocks();		// 쌓인 블럭 클리어

    char msg[] = "아쉽지만 게임이 종료되었습니다.";

    
    char input;
    bool isClear = false;
    
	while(!isClear)
    {
        gotoxy(3,10);

        if(gameStatus == NEXT_STAGE) {
            cout << "축하합니다!! 레벨 " << gameLevel << "을 통과하셧습니다!! > next spacebar!" ;
        }else if(gameStatus == GAME_OVER) {
            cout << "아쉽지만 게임이 종료되었습니다." ;
        }
        gotoxy(0,0);
                
        input = _getch();
        switch(input)
        {
        case ' ':
            isClear = true;
			break;
        }
    }
    
	delete moving_block;
}


void GameManager::introGame()
{
    char input;
    
	while(1)
    {
        
        //system("cls");
        gotoxy(3,10);
        
        cout << "spacebar를 누르면 게임을 시작합니다." << endl;
        gotoxy(0,0);
                
        input = _getch();
        switch(input)
        {
        case ' ':
            startGame();
			break;
        }
    }
}





