#pragma once

#include <windows.h> 
#include <time.h>

HANDLE hStdout, hStdin;
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
WORD wOldColorAttrs;
CHAR chBuffer[256];
DWORD cRead, cWritten, fdwMode, fdwOldMode;

int OpenConsole();
int CloseConsole();
COORD GetConsoleSize();
void GotoXY(unsigned short int X, unsigned short int Y);
int PlotChar(char SomeChar);

int RangedRand(int range_min, int range_max);

