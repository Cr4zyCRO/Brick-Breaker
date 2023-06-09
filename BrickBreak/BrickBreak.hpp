#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <Windows.h>
#include <handleapi.h>
#include <conio.h> // getch() 
#include <dos.h> // sleep()

using namespace std;

/****************MAIN**SCREEN****************/
constexpr auto WIDTH = 63;
constexpr auto HEIGHT = 20;
/********************************************/


/****************PLAY**AREA****************/
const size_t MaxX = WIDTH - 2;
const size_t MinX = 2;
const size_t MaxY = HEIGHT - 1;
const size_t MinY = 1;
/********************************************/


/****************GAME**STATUS****************/
size_t winStatus = 0;
size_t loseStatus = 0;
/********************************************/


/****************BRICK**WINDOW****************/
size_t numOfBricks = 32;
//            _______|
//            |
double brick[32][2] = {
	{7,2},{12,2},{17,2},{22,2},{27,2},{32,2},{37,2},{42,2},
		{12,4},{17,4},{22,4},{27,4},{32,4},{37,4},{42,4},{47,4},
	{7,6},{12,6},{17,6},{22,6},{27,6},{32,6},{37,6},{42,6},
		{12,8},{17,8},{22,8},{27,8},{32,8},{37,8},{42,8},{47,8},
};

size_t visibleBricks[32] = { 
	1,1,1,1, 1,1,1,1, 
	1,1,1,1, 1,1,1,1, 
	1,1,1,1, 1,1,1,1,
	1,1,1,1, 1,1,1,1 
};
/*********************************************/


/****************SLIDER**AND**BALL****************/
size_t sliderPosition[2] = { round(WIDTH * 40 / 100), round(HEIGHT * 80 / 100) };

size_t posX = (round(WIDTH * 40 / 100) + 9 / 2) + 1;

double ballPosition[2] = { posX, round(HEIGHT * 80 / 100) - 1 };

size_t ballStart = 0;

const size_t sliderLenght = 10;
const size_t brickLenght = 4;
/*************************************************/


/****************CONSOLOE**POSITION****************/
HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PositionOfCursor;

void gotoxy(size_t x, size_t y); //set a cursor at position in console
/**************************************************/


/****************BORDER**CLASS****************/
class Border {
	char design;
public:
	Border();
	char virtual getDesign();
};
/*********************************************/


/****************BRICK**CLASS****************/
class Brick : public Border {
	char design;
public:
	Brick();
	char getDesign() override;
};
/********************************************/


/****************FUNCTIONS****************/
/**MENUS*/
void mainMenu();
void playMenu();
void infoMenu();
void quitMenu();

/**STATUS**SCREENS*/
void winScreen();
void loseScreen();

/**BALL**DIRECTIONS**/
void goTopRight(size_t& direction);
void goTopLeft(size_t& direction);
void goBottomLeft(size_t& direction);
void goBottomRight(size_t& direction);

/**SLIDER**DIRECTIONS**/
void moveLeft();
void moveRight();

/**COLLISON**/
void ballSliderCollosion(size_t& direction);
void ballBrickCollosion(size_t& direction);

/**BORDER**AND**BRICKS**/
void drawBoarder(Border& b);
void drawBricks(Border& b);

/**RESET**/
void reset();
/*****************************************/

