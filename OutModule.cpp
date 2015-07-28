#include "stdafx.h"


char* GetTypeText(int type)
{
    switch(type)
    {
    case 0: return "¢Æ";
    }
    return nullptr;
}

void SetConsoleSize( int width, int height )
{
    char buffer[64] = {};
    sprintf_s( buffer, "mode con cols=%d lines=%d", width, height );
    system(buffer);
}


OutModule::OutModule()
    : m_stdout(NULL)
{
    m_stdout = GetStdHandle( STD_OUTPUT_HANDLE );

    SetConsoleSize( G_WIDTH*2, G_HEIGHT );
    ClearScreen();   
}

OutModule::~OutModule()
{
}

void OutModule::ClearScreen()
{
    ZeroMemory(m_screenBuffer, sizeof(m_screenBuffer) );
}

void OutModule::Render(COORD xy, int type)
{
    char* typeText = GetTypeText( type );

    for( int i = 0 ; i < 2 ; i++ )
    {
        m_screenBuffer[xy.Y][(xy.X*2)+i].Attributes = FOREGROUND_GREEN;
        m_screenBuffer[xy.Y][(xy.X*2)+i].Char.AsciiChar = typeText[i];
    }
}

void OutModule::flush()
{
    COORD range = { G_WIDTH*2, G_HEIGHT };
    COORD screenxy = { 0, 0 };
    SMALL_RECT rc = {0, 0, G_WIDTH*2, G_HEIGHT };
  
    BOOL success = WriteConsoleOutputA( m_stdout, (CHAR_INFO*)m_screenBuffer, range, screenxy, &rc );
    int err = GetLastError();
    ClearScreen();
}