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

#define COL                   GetStdHandle(STD_OUTPUT_HANDLE)        // �ܼ�â�� �ڵ����� �ޱ�

#define randomize() srand((unsigned)time(NULL))
#define random(n) ((short)rand() % (n))

#define BLACK 0               // ������
#define DARK_BLUE 1           // �Ķ���
#define GREEN 2               // ���
#define BLUE_GREEN 3          // û���
#define BLOOD 4               // �˺�����
#define PURPLE 5              // �����
#define GOLD 6                // �ݻ�
#define ORIGINAL 7            // ���� ȸ�� (ORIGINAL CONSOLE COLOR)
#define GRAY 8                // ȸ��
#define BLUE 9                // �Ķ���
#define HIGH_GREEN 10         // ���λ�
#define SKY_BLUE 11           // �ϴû�
#define RED 12                // ������
#define PLUM 13               // ���ֻ�
#define YELLOW 14             // �����
#define WHITE 15              // ���


const static enum ARROW{
	KEY_UP		= 72, 
	KEY_DOWN	= 80, 
	KEY_LEFT	= 75, 
	KEY_RIGHT	= 77
} ARROW;


void gotoxy(short x, short y);
void setcolor(int color, int bgcolor);