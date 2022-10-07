#include <windows.h> //adds all the functions that let me control and measure the console window
#include <conio.h> //library that lets me detect input
#include <iostream>
#include <iomanip> //setw and setfill
#include <stdio.h>


//defining keycodes for readability
#define KEY_SPACE 32
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;


//added a struct to hold X and Y coordinates
struct Vector2
{
	int x;
	int y;
};

//This 2D array holds the basic stickman's "model"
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


//This grabs the current coordinates of the console's cursor
Vector2 cursorCoords() {
	
	Vector2 tempCoord;
	
	CONSOLE_SCREEN_BUFFER_INFO csbi; //This contains info about the window size and cursor's position
	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	tempCoord.x = csbi.dwCursorPosition.X; //dwCursorPosition is just the cursor's location
	tempCoord.y = csbi.dwCursorPosition.Y;


	return tempCoord;
}




//This gets the dimension of the console's window
//Uses CONSOLE_SCREEN_BUFFER_INFO like in cursorCoords()
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



//Function to control the coordinates of the cursor using my Vector2 struct
void moveCursor(Vector2 pos) {

	COORD coord;
	coord.X = pos.x;
	coord.Y = pos.y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void drawPlayer() {

	//Grab the coordinates of the current cursor's position
	Vector2 setCursor;
	setCursor.x = cursorCoords().x;
	setCursor.y = cursorCoords().y;
	
	//Cycle through the 2D array and print each character
	for (int k = 0; k < 9; k++) {
		for (int l = 0; l < 7; l++) {
			cout << characterModel[k][l];

		}
		setCursor.y += 1;
		moveCursor(setCursor); //Reset the cursor's position to the beginning of the next line (instead of the next character)

	}
	
	//Once the character is drawn, reset the cursor's position to the top left corner of the character
	setCursor.y -= 9;
	
	moveCursor(setCursor);
	
}

//Clear the player's character
//Similar to drawing it
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



//Move the player by clearing it, moving the cursor by 1, and drawing it again
int movePlayer(int key) {
	
	Vector2 tempPos = cursorCoords();
	

	//Handle keyboard input
	switch (key) {
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




//Set the start coordinates of the cursor depending on the size of the window
int setStartCoords() {
	
	int xPos = consoleDimensions().x * 0.25f;			//uses the first 25% of the window size for the X pos
	int yPos = (consoleDimensions().y * 0.75f) - 9;		//uses the same 25% as the floor, and then goes up by 9 to account for the height of the character
	

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

			for (int j = 0; j < consoleDimensions().x; j++) {			//draws the floor according to the window' size's X size
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