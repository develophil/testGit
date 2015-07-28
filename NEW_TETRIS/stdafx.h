// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "Board.h"
#include "Tetrimino.h"
#include "GameManager.h"
#include "OutModule.h"

using namespace std;

#define COL                   GetStdHandle(STD_OUTPUT_HANDLE)        // 콘솔창의 핸들정보 받기

#define randomize() srand((unsigned)time(NULL))
#define random(n) ((short)rand() % (n))

#define BLACK 0               // 검정색
#define DARK_BLUE 1           // 파란색
#define GREEN 2               // 녹색
#define BLUE_GREEN 3          // 청녹색
#define BLOOD 4               // 검붉은색
#define PURPLE 5              // 보라색
#define GOLD 6                // 금색
#define ORIGINAL 7            // 밝은 회색 (ORIGINAL CONSOLE COLOR)
#define GRAY 8                // 회색
#define BLUE 9                // 파란색
#define HIGH_GREEN 10         // 연두색
#define SKY_BLUE 11           // 하늘색
#define RED 12                // 빨간색
#define PLUM 13               // 자주색
#define YELLOW 14             // 노란색
#define WHITE 15              // 흰색


const static enum ARROW{
	KEY_UP		= 72, 
	KEY_DOWN	= 80, 
	KEY_LEFT	= 75, 
	KEY_RIGHT	= 77
} ARROW;


void gotoxy(short x, short y);
void setcolor(int color, int bgcolor);