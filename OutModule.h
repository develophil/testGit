#pragma once

class OutModule
{
public:
    static const int G_WIDTH = 80;
    static const int G_HEIGHT = 50;

private:
    HANDLE m_stdout;

    CHAR_INFO m_screenBuffer[G_HEIGHT][G_WIDTH*2];

public:
    OutModule();
    ~OutModule();
    void ClearScreen();
    void Render( COORD xy, int type );
    void flush();
};