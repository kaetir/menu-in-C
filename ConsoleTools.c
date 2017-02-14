#include "ConsoleTools.h"



int OpenConsole() {

	// Seed the random-number generator with the current time so that
	// the numbers will be different every time we run.
	srand((unsigned)time(NULL));


	// Get handles to STDIN and STDOUT. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE ||
		hStdout == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"),
			MB_OK);
		return 1;
	}
	// Save the current text colors. 

	if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
	{
		MessageBox(NULL, TEXT("GetConsoleScreenBufferInfo"),
			TEXT("Console Error"), MB_OK);
		return 1;
	}

	wOldColorAttrs = csbiInfo.wAttributes;
	return(0);
}

int CloseConsole() {
	// Restore the original text colors. 

	SetConsoleTextAttribute(hStdout, wOldColorAttrs);
	return(0);
}

COORD GetConsoleSize() {
	COORD Size;

	Size.X = csbiInfo.dwSize.X;
	Size.Y = csbiInfo.dwSize.Y;
	return(Size);
}

void GotoXY(unsigned short int X, unsigned short int Y) {

	COORD pos;
	pos.X = X;
	pos.Y = Y;
	SetConsoleCursorPosition(hStdout, pos);
	
	return;
}
int PlotChar(char SomeChar) {
	chBuffer[0] = SomeChar;
	chBuffer[1] = 0;
	cRead = 1;
	if (WriteFile(hStdout, chBuffer, cRead, &cWritten, NULL)) {
		return(0);
	}
	else {
		return(GetLastError());
	}
}

int RangedRand(int range_min, int range_max)
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	
		int u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min) + range_min;	
	return(u);
}

