
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include <conio.h>
#include <stdbool.h>
//created by alexa

//flaw list/todo list
//fixed
//fixed

void delay(int a) {

	for (int i = 0; i < a * 10000000; i++) {}
}

// macros
#define ARR_LEN(array) sizeof(array)/sizeof(array[0]) //size of array
#define SET_SEED srand((unsigned)time(NULL));

//enums
enum {
    KEY_SPACE = 32,
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,
	KEY_ESC = 27
}; //ascii keys to decimal value

//VALUES
int i, j, k, x, y, spd=2;
int arrX[50];
int arrY[50];
char ch;

int size = 3, fruits = 0, fruitx = 24, fruity = 8, init=0;


//ENUMS
typedef enum Scenes {
	Intro,
	Game,
	Lose
} Scenes;

Scenes Scene = Intro;


typedef enum Directions {
	Up,
	Down,
	Left,
	Right
} Directions;

Directions playerDir;


char grid[22][60];


void reset() {

	//reset size, fruit
	size = 3; fruits = 0;

	//set all bodies to 0
	for (i = 0; i < 50; i++) {
		arrX[i] = 0;
		arrY[i] = 0;
	}

	//set to start with 3 size
	for (i = 0; i < size; i++) {
		arrX[i] = 5 - i;
		arrY[i] = 2;
	}

	x = arrX[0];
	y = arrY[0];

	playerDir = Right;
}

void gameOver() {
	Scene = Lose; init = 0; reset();
}

int main(int argc, char *argcv[]) {

	SET_SEED;
	while (true) {
		//
		//game intro init
		if (Scene == Intro && init==0) {
			//init = 1;
			system("cls");
			printf("\nSnake by alexa in C :-)\n\nWelcome to snake!\n");
			printf("Type your level; The higher, the faster the snake is--\nType a number from 1 to 4: ");
			scanf("%d", &spd);
			if (spd == 0) spd = 1; else if (spd > 4) spd = 4;
			system("cls");
			Scene = Game;
		}

		//game intro loop
		//while (Scene == Intro) {
		//}

		//game game init
		if (Scene == Game && init==0 ) {
			init = 1;
			reset();
		}

		//game game loop
		while (Scene == Game) {
			//title
			printf("\nSnake by alexa in C :-)          Move:  W - A - S - D      Quit:  Esc    Main menu:  R\n\n");

			//make grid
			for (i = 0; i < ARR_LEN(grid); i++)
			{
				printf("#");
				for (j = 0; j < ARR_LEN(grid[0]); j++)
				{
				goHere:
					if ((i == 0) | (i == ARR_LEN(grid) - 1) | (j == ARR_LEN(grid[0]) - 1)) {
						printf("#"); continue;
					}
					for (k = 0; k < size; k++)
					{
						if (j == arrX[k] && i == arrY[k]) {
							printf("#"); j++; goto goHere;
						}
					}
					if (j == fruitx && i == fruity) {
						printf("O");
					}
					else {
						printf(" ");
					}
				}
				printf("\n");
			}
			//print xy of bodies
			for (i = 0; i < 50; i++)
			{
				//printf("%d,%d  ", arrX[i], arrY[i]);
			}
			printf("SIZE: %d    SCORE: %d Fruits Colleceted\nSpeed is set to level %d of 4\n", size, fruits, spd);


			//changing the x and y of head
			switch (playerDir) {
			case Up: y--; break;
			case Down: y++; break;
			case Left: x--; break;
			case Right: x++; break;
			}

			//set the bodies one forward
			for (i = size; i > 0; i--)
			{
				if (arrX[i] != 0 | arrY[i] != 0) {
					arrX[i] = arrX[i - 1];
					arrY[i] = arrY[i - 1];

				}
			}
			arrX[0] = x;
			arrY[0] = y;

			//key press events
			if (_kbhit()) {
				ch = toupper(_getch());
				switch (ch) {
				case KEY_W: if (playerDir != Down) playerDir = Up; break;
				case KEY_A: if (playerDir != Right) playerDir = Left; break;
				case KEY_S: if (playerDir != Up) playerDir = Down; break;
				case KEY_D: if (playerDir != Left) playerDir = Right; break;
				}
				if (ch == KEY_ESC) exit(0);
				if (ch == KEY_R) Scene = Intro; init = 0;
				printf("%c", ch);

			}

			//if you touch a fruit
			if (arrX[0] == fruitx && arrY[0] == fruity) {
				fruits++;

				fruitx = rand() % 55;
				fruity = rand() % 18;

				arrX[size] = arrX[size - 1];
				arrY[size] = arrY[size - 1];
				size++;
			}

			//if it spawns in wall
			if ((fruitx == 0 | fruitx >= ARR_LEN(grid[0])) | (fruity == 0 | fruity >= ARR_LEN(grid))) {
				fruitx = rand() % 55;
				fruity = rand() % 18;
			}

			//if you touch a wall (game over)
			if (x <= 0 | y <= 0 | x >= ARR_LEN(grid[0]) - 1 | y >= ARR_LEN(grid) - 1) {
				gameOver();
			}

			//if you touch your body (game over)
			for ( i = 1; i < size; i++)
			{
				if (x == arrX[i] && y == arrY[i]) gameOver();
			}

			//
			//
			//printf("%d,%d", x, y);

			delay(12 / spd);
			system("cls");
		}

		//game lose init
		if (Scene == Lose && init==0) {
			init = 1;
			system("cls");

			printf("\nSnake by alexa in C :-)\n\n");
			printf("YOU TOUCHED...\n");
			printf("your body or a wall :-(\n\n");
			printf("Press R to restart game.\nPress Esc to quit.\n\n");
		}

		//game lose loop
		while (Scene == Lose) {
			if (_kbhit()) {
				ch = toupper(_getch());
				if (ch == KEY_R) Scene = Intro; init = 0; system("cls");
				if (ch == KEY_ESC) exit(0);
				else {
					system("cls");

					printf("\nSnake by alexa in C :-)\n\n");
					printf("YOU TOUCHED...\n");
					printf("your body or a wall :-(\n\n");
					printf("Press R to restart game.\nPress Esc to quit.\n\n");
				}

			}
		}
	}


}
