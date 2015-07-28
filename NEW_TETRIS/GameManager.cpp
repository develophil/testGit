#include "stdafx.h"

static const char background[22][51] = {
      {"�̢̢̢̢̢̢̢̢̢̢̢�  �̢̢̢̢̢̢̢̢̢̢̢�"},
      {"��                    ��  ��      ��            ��"},
      {"��                    ��  ��  ��  ��            ��"},      
      {"��                    ��  ��  ��  ��            ��"},      
      {"��                    ��  ��  ��  ��            ��"},      
      {"��                    ��  ��  ��  ��            ��"},                        
      {"��                    ��  ��      ��            ��"},      
      {"��                    ��  �̢̢̢̢̢̢̢̢̢̢̢�"},      
      {"��                    ��                          "},
      {"��                    ��  �̢̢̢̢̢̢̢̢̢̢̢�"},
      {"��                    ��  �̽�  ��              ��"},
      {"��                    ��  ��                    ��"},
      {"��                    ��  ��                    ��"},            
      {"��                    ��  �̢̢̢̢̢̢̢̢̢̢̢�"},
      {"��                    ��  �̷�  ��              ��"},
      {"��                    ��  ��                    ��"},
      {"��                    ��  ��                    ��"},                  
      {"��                    ��  �̢̢̢̢̢̢̢̢̢̢̢�"},
      {"��                    ��  ����  ��              ��"},
      {"��                    ��  ��                    ��"},
      {"��                    ��  ��                    ��"},                  
      {"�̢̢̢̢̢̢̢̢̢̢̢�  �̢̢̢̢̢̢̢̢̢̢̢�"},            
};

const short colors[] = {SKY_BLUE, BLUE, PLUM, YELLOW, GREEN, PURPLE, RED, GRAY, BLACK};
const char *pShapes[] = {"  ","��","��","��"};


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
    //cout << "���Ӹ޴��� �Ҹ���!" <<endl; 
	delete moving_block;
    delete waiting_block;
}


void GameManager::setBackGround()
{
	 setcolor(ORIGINAL, BLACK);
     
	 // ��� �� ���
	 for(int i=0; i<sizeof(background)/sizeof(background[0]); i++)
     {
          cout << background[i] << endl;
     }

	 // �ð� Ÿ�̸� ���
	 setTimeBoard();
	 // ���� ���� ���
	 setLevelBoard();
	 // ���ھ� ���� ���
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

// ���ҼӺ��� : s, m, w
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

// ��ǥ �̵�
void GameManager::moveXY(Tetrimino* block, COORD _xy)
{
	block->posX += _xy.X;
	block->posY += _xy.Y;
}

// ��ǥ �̵�
void GameManager::absMoveXY(Tetrimino* block, COORD _xy)
{
	block->posX = _xy.X;
	block->posY = _xy.Y;
}


// �� �̵� : a,s,d
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
			// ���� ���� ó��
			endGame(GAME_OVER);
			return;
		}
	}
    
        processEndline();   // �� �ϴ� ���� üũ    
	    processEndScore();  // ���� ���� üũ
		
}

// �� ȸ�� : l, r
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


		// �� �մ°� ���� ����
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

// �� �ϴ� ���� ó��
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
			 stackBlocks.stack(moving_block);	// �� �ױ�
			 gameScore += 10;

			 gameScore += stackBlocks.deleteFullLine();		// ������ ���� ����
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


// �����Ӱ��ɿ���üũ
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
    
    // [�ܼ�â ũ�� ����]
    //system("mode con cols=80 lines=26");

    // [�ܼ�â ���� ����]
    system("Have fun with My Tetris!");

    // [�ܼ�â ȭ�� �����]
    system("cls");

    // [�ܼ� Ŀ�� ����]
    SetCursor(false);

	if(gameStatus == GAME_OVER) {
        gameLevel = 1;
    }else if(gameStatus == NEXT_STAGE) {
        gameLevel += 1;
    }

	gameStatus = PLAYING;
	gameScore = 0;
    gameTime = 0;
	
	stackBlocks.initStackBlocks();		// �۾����� �غ�

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
            moveBlock('s'); // �� ��ĭ �̵�
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



void GameManager::setTimeBoard()	// �ð� Ÿ�̸� ���
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

void GameManager::setLevelBoard()	// ���� ���� ���
{
	SetCursor(false);
	setcolor(ORIGINAL, BLACK);
	gotoxy(21, 15);
	printf("%d", gameLevel);
}
void GameManager::setScoreBoard()	// ���ھ� ���� ���
{
	SetCursor(false);
	setcolor(ORIGINAL, BLACK);
	gotoxy(19, 19);
	printf("%d", gameScore);
}


void GameManager::endGame(int aGameStatus)
{
    // ���� ���� ó��
	gameStatus = aGameStatus;			// ������� ����

	stackBlocks.clearStackBlocks();		// ���� �� Ŭ����

    char msg[] = "�ƽ����� ������ ����Ǿ����ϴ�.";

    
    char input;
    bool isClear = false;
    
	while(!isClear)
    {
        gotoxy(3,10);

        if(gameStatus == NEXT_STAGE) {
            cout << "�����մϴ�!! ���� " << gameLevel << "�� ����ϼ˽��ϴ�!! > next spacebar!" ;
        }else if(gameStatus == GAME_OVER) {
            cout << "�ƽ����� ������ ����Ǿ����ϴ�." ;
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
        
        cout << "spacebar�� ������ ������ �����մϴ�." << endl;
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





