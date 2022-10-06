#include <windows.h>
#include <conio.h> //library that lets me detect input
#include <iostream>
#include <iomanip> //setw and setfill
#include <stdio.h>


#define KEY_SPACE 32
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;

struct Vector2
{
	int x;
	int y;
};




char characterModel[9][7] = {
	{' ', ' ', ' ', 'X', ' ', ' ', ' '},
	{' ', 'X', ' ', ' ', ' ', 'X', ' '},
	{' ', ' ', ' ', 'X', ' ', ' ', ' '},
	{' ', ' ', 'X', 'X', 'X', ' ', ' '},
	{' ', 'X', ' ', 'X', ' ', 'X', ' '},
	{' ', ' ', ' ', 'X', ' ', ' ', ' '},
	{' ', ' ', ' ', 'X', ' ', ' ', ' '},
	{' ', ' ', 'X', ' ', 'X', ' ', ' '},
	{' ', 'X', ' ', ' ', ' ', 'X', ' '}
};



Vector2 cursorCoords() {
	
	Vector2 tempCoord;
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	tempCoord.x = csbi.dwCursorPosition.X;
	tempCoord.y = csbi.dwCursorPosition.Y;


	return tempCoord;
}





Vector2 consoleDimensions() {

	Vector2 result;
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int rows, columns;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	result.x = columns;
	result.y = rows;
	
	return result;
}




void moveCursor(Vector2 pos) {

	COORD coord;
	coord.X = pos.x;
	coord.Y = pos.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}





void drawPlayer() {

	Vector2 setCursor;
	setCursor.x = cursorCoords().x;
	setCursor.y = cursorCoords().y;
	
	for (int k = 0; k < 9; k++) {
		for (int l = 0; l < 7; l++) {
			cout << characterModel[k][l];

		}
		setCursor.y += 1;
		moveCursor(setCursor);

	}
	
	setCursor.y -= 9;
	
	moveCursor(setCursor);
	
}





void clearPlayer() {
	
	Vector2 setCursor;
	setCursor.x = cursorCoords().x;
	setCursor.y = cursorCoords().y;
	
	for (int k = 9; k > 0; k--) {
		for (int l = 7; l > 0; l--) {
			cout << "\b \b";
		}
		setCursor.y -= 1;
		moveCursor(setCursor);
	}
	
	setCursor.x -= 7;
	moveCursor(setCursor);
}





int movePlayer(int key) {
	
	Vector2 tempPos = cursorCoords();
	
	switch (key) { //tells me the keycode of what i press
	case KEY_RIGHT:
		clearPlayer();
		tempPos.x += 1;
		moveCursor(tempPos);
		drawPlayer();

		break;
	case KEY_LEFT:
		clearPlayer();
		tempPos.x -= 1;
		moveCursor(tempPos);
		drawPlayer();

		break;
	}
	
	return 0;
}





int setStartCoords() {
	
	int xPos = consoleDimensions().x * 0.25f;
	int yPos = (consoleDimensions().y * 0.75f) - 9;
	

	Vector2 coords;
	coords.x = xPos;
	coords.y = yPos;
	

	moveCursor(coords);
	return 0;
}





int drawFloor() {

	
    int floorLevel = consoleDimensions().y * 0.75f;						//the floor is 75% down of the window

	int whereToDraw = floorLevel - cursorCoords().y;					
    
	for (int i = 0; i <= whereToDraw; i++) {
		
		if (i == whereToDraw) {

			for (int j = 0; j < consoleDimensions().x; j++) {			//draws the floor according to the window size
				cout << '_';
			}
			
		}
		else {
			cout << endl;
		}
		
	}
	
    return 0;
}




int main() {
	int key_code;

	bool startUpCompleted = false;

	while (true) {
		if (_kbhit()) {					                       //_kbhit() activates when a key is pressed

			if (startUpCompleted == false) {				   //runs once, startup code
				system("cls");
				drawFloor();
				setStartCoords();
				drawPlayer();
				startUpCompleted = true;
			}
			else {
				movePlayer(key_code = _getch());			// redirects input to the moveplayer funcion
				
			}

		}
		else
			continue;
	}

}