#pragma once
#include <windows.h>

class Console{
private:
	HANDLE _hdl;		//a handle to the output console
	COORD _coord;		//coordinate of the output console
	int dColor;
	int wWidth;
	int wHeight;
public:
	Console():_hdl(GetStdHandle(STD_OUTPUT_HANDLE)){
		_coord.X = 0;
		_coord.Y = 0;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(_hdl,&csbi);
		dColor = csbi.wAttributes;
		wWidth = csbi.dwMaximumWindowSize.X;
		wHeight = csbi.dwMaximumWindowSize.Y;	
	}

	void setPos(int x, int y){
		_coord.X = x;
		_coord.Y = y;
		SetConsoleCursorPosition(_hdl,_coord);
	}
	
	void setColor(int cc){
		SetConsoleTextAttribute(_hdl,cc);
	}

	void setDefaultColor(){
		SetConsoleTextAttribute(_hdl,dColor);
	}

	int getConsoleWidth(){
		return wWidth;
	}

	int getConsoleHeight(){
		return wHeight;
	}
	
	int getCursorX(){
		return _coord.X;
	}

	int getCursorY(){
		return _coord.Y;
	}

	int getCursorXNow(){
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(_hdl,&csbi);
		return csbi.dwCursorPosition.X;
	}

	int getCursorYNow(){
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(_hdl,&csbi);
		return csbi.dwCursorPosition.Y;
	}


}console;