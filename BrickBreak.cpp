#include "BrickBreak.hpp"

/****************CONSOLOE**POSITION****************/
void gotoxy(size_t x, size_t y){
	PositionOfCursor.X = x;
	PositionOfCursor.Y = y;
	SetConsoleCursorPosition(Console, PositionOfCursor);
}
/**************************************************/


/****************BORDER**CLASS****************/
Border::Border(){
	design = 219; //border design
}

char Border::getDesign(){
	return design;
}
/*********************************************/


/****************BRICK**CLASS****************/
Brick::Brick(){
	design = 254; //brick design
}

char Brick::getDesign(){
	return design;
}
/*********************************************/


/**********************FUNCTIONS**********************/
/****************MENUS****************/
void mainMenu(){
	system("cls");
	size_t x = round(WIDTH * 25 / 100);
	size_t y = round(HEIGHT * 25 / 100);

	char design = 205;

	//top design
	gotoxy(x, y - 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	size_t i = round(WIDTH * 40 / 100);
	gotoxy(i, y);
	cout << "BRICK BREAK";
	
	//bottom design
	gotoxy(x, y + 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	gotoxy(x, y + 4);
	cout << "Choose:";
	gotoxy(x, y + 5);
	cout << "1) Play The Game";
	gotoxy(x, y + 6);
	cout << "2) Instructions";
	gotoxy(x, y + 7);
	cout << "3) Quit Game";
	gotoxy(x, y + 9);
	cout << "(Use your keyboard)";
}

void playMenu(){
	Border border;
	Brick brick;
	
	size_t direction = 1;

	reset();

	while (1) {
		system("cls");
		
		drawBoarder(border);
		drawBricks(brick);
		
		gotoxy(sliderPosition[0], sliderPosition[1]);
		for (int i = 0; i < 10; i++) {
			cout << brick.getDesign();
		}
		
		gotoxy(ballPosition[0], ballPosition[1]);
		cout << 'o';
		gotoxy(0, 0);
		
		//Slider movment
		if (kbhit()) {
			char in = getch();

			if (in == 'A' || in == 'a') {
				moveLeft();
			}
			else if (in == 'D' || in == 'd') {
				moveRight();
			}
			else if (in == 27) {
				break;
			}
			else if (in == 32) {
				ballStart = 1;
			}
		}

		//wall collison
		if (ballStart) {
			if (direction == 1) {
				goTopRight(direction);
			}
			else if (direction == 2) {
				goTopLeft(direction);
			}
			else if (direction == 3) {
				goBottomLeft(direction);
			}
			else if (direction == 4) {
				goBottomRight(direction);
			}

			ballSliderCollosion(direction);
		}

		ballBrickCollosion(direction);

		if (loseStatus) {
			loseScreen();
			Sleep(500);
			break;
		}
		if (winStatus) {
			winScreen();
			Sleep(500);
			break;
		}

		Sleep(35);
		gotoxy(0, 0);
	}
}

void infoMenu(){
	system("cls");
	size_t x = round(WIDTH * 10 / 100);
	size_t y = round(HEIGHT * 25 / 100);

	gotoxy(x, y - 1);
	cout << "Use \"A\" to move Left";
	gotoxy(x, y);
	cout << "Use \"D\" to move Right";
	gotoxy(x, y + 1);
	cout << "Use \"Space Bar\" to Start the game";
	gotoxy(x, y + 3);
	cout << "Press Any Key to return to Main Menu";

	char in = getch();
}

void quitMenu(){
	system("cls");
	size_t x = round(WIDTH * 25 / 100);
	size_t y = round(HEIGHT * 25 / 100);

	char design = 205;

	//top design
	gotoxy(x, y - 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	size_t i = round(WIDTH * 45 / 100);
	gotoxy(i, y);
	cout << "GOODBYE";

	//bottom design
	gotoxy(x, y + 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	i = round(WIDTH * 45 / 100);
	gotoxy(i, y + 6);
	cout << "Game by";
	i = round(WIDTH * 43 / 100);
	gotoxy(i, y + 7);
	cout << "Bruno Galic";

	cout << endl;
	cout << endl;
}
/*************************************/


/***********STATUS**SCREENS***********/
void winScreen(){
	system("cls");
	size_t x = round(WIDTH * 25 / 100);
	size_t y = round(HEIGHT * 25 / 100);

	char design = 196;

	//top design
	gotoxy(x, y - 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	size_t i = round(WIDTH * 40 / 100);
	gotoxy(i, y);
	cout << "YOU WON";

	//bottom design
	gotoxy(x, y + 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	gotoxy(x, y + 8);
	system("pause");

	winStatus = 0;
}

void loseScreen() {
	system("cls");
	size_t x = round(WIDTH * 25 / 100);
	size_t y = round(HEIGHT * 25 / 100);

	char design = 196;

	//top design
	gotoxy(x, y - 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	size_t i = round(WIDTH * 40 / 100);
	gotoxy(i, y);
	cout << "YOU LOST";

	//bottom design
	gotoxy(x, y + 1);
	for (size_t i = x; i < WIDTH - x; i++) {
		cout << design;
	}

	gotoxy(x, y + 8);
	system("pause");

	loseStatus = 0;
}
/*************************************/


/**********BALL**DIRECTIONS***********/
//direction 1
void goTopRight(size_t& direction){
	ballPosition[0] += 0.6;
	ballPosition[1] -= 1;

	if (ballPosition[0] >= MaxX) {
		direction = 2;
	}
	if (ballPosition[1] <= MinY) {
		direction = 4;
	}
}

//direction 2
void goTopLeft(size_t& direction){
	ballPosition[0] -= 0.6;
	ballPosition[1] -= 1;

	if (ballPosition[0] <= MinX) {
		direction = 1;
	}
	if (ballPosition[1] <= MinY) {
		direction = 3;
	}
}

//direction 3
void goBottomLeft(size_t& direction){
	ballPosition[0] -= 0.5;
	ballPosition[1] += 1;

	if (ballPosition[0] <= MinX) {
		direction = 4;
	}
	if (ballPosition[1] >= MaxY) {
		direction = 2;
		loseStatus = 1;
	}
}

//direction 4
void goBottomRight(size_t& direction){
	ballPosition[0] += 0.5;
	ballPosition[1] += 1;

	if (ballPosition[0] >= MaxX) {
		direction = 3;
	}
	if (ballPosition[1] >= MaxY) {
		direction = 1;
		loseStatus = 1;
	}
}
/*************************************/


/*********SLIDER**DIRECTIONS*********/
void moveLeft(){
	if (sliderPosition[0] > 4) {
		sliderPosition[0] -= 4;
	}
}

void moveRight() {
	if (sliderPosition[0] + sliderLenght < WIDTH) {
		sliderPosition[0] += 4;
	}
}
/************************************/


/****************COLLISON****************/
void ballSliderCollosion(size_t& direction){
	if ((ballPosition[0] >= sliderPosition[0]) && (ballPosition[0] < sliderPosition[0] + sliderLenght)) {
		if (ballPosition[1] == sliderPosition[1] - 1) {
			direction = round(rand() % 2 + 1);
		}
	}
}

void ballBrickCollosion(size_t& direction){
	for (int i = 0; i < 32; i++) {
		if (visibleBricks[i]) {
			if ((ballPosition[0] >= brick[i][0]) && (ballPosition[0] <= brick[i][0] + brickLenght)){ // X position
				if(ballPosition[1] == (brick[i][1])) { // Y Position

					visibleBricks[i] = 0;
					numOfBricks--;

					if (direction == 1) {
						direction = 4;
					}
					else if (direction == 2) {
						direction = 3;
					}
					else if (direction == 3) {
						direction = 2;
					}
					else if (direction == 4) {
						direction = 1;
					}
				}
			}
		}
	}
	if (!numOfBricks) {
		winStatus = 1;
	}
}
/****************************************/


/**********BORDER**AND**BRICKS**********/
void drawBoarder(Border& b){
	size_t i = 0;

	//top border
	gotoxy(0, 0);
	for (i = 0; i < WIDTH; i++) {
		cout << b.getDesign();
	}

	//side borders
	for (i = 0; i < HEIGHT; i++) {
		gotoxy(0, i);
		cout << b.getDesign();
		gotoxy(WIDTH, i);
		cout << b.getDesign();
	}

	//bottom border
	gotoxy(0, HEIGHT);
	for (i = 0; i < WIDTH + 1; i++) {
		cout << b.getDesign();
	}
}

void drawBricks(Border& b){
	for (int i = 0; i < 32; i++) {
		if (visibleBricks[i] == 1) {
			gotoxy(brick[i][0], brick[i][1]);
			for (int i = 0; i < brickLenght; i++) {
				cout << b.getDesign();
			}
		}
	}
}
/*****************************************/


/****************RESET****************/
void reset(){
	for (int i = 0; i < 32; i++) {
		visibleBricks[i] = 1;
	}
	numOfBricks = 32;

	ballPosition[0] = (round(WIDTH * 40 / 100) + 9 / 2) + 1 ;
	ballPosition[1] = round(HEIGHT * 80 / 100) - 1;

	sliderPosition[0] = round(WIDTH * 40 / 100);
	sliderPosition[1] = round(HEIGHT * 80 / 100);

	ballStart = 0;
}
/*************************************/
/**********************FUNCTIONS**********************/