#include <stdio.h>
#include <stdlib.h>
#include "game.h"

void menu() {
	printf_s("                MineSweeper                 \n");
	printf_s("********************************************\n");
	printf_s("**********         0.Exit        ***********\n");
	printf_s("**********         1.Play        ***********\n");
	printf_s("********************************************\n");

}

void game() {
	srand((unsigned int)time(NULL));
	system("cls");

	//set mine
	char mine[ARRAY_ROW][ARRAY_COLUMN] = { 0 };
	//declare array that stores calculation when user click
	char show[ARRAY_ROW][ARRAY_COLUMN] = { 0 };
	char mineClac[ARRAY_ROW][ARRAY_COLUMN] = { 0 };
	//initialize Array
	InitBoard(mine, ARRAY_ROW, ARRAY_COLUMN, '0');	//passing &char[] in default
	InitBoard(show, ARRAY_ROW, ARRAY_COLUMN, '*');
	InitBoard(mineClac, ARRAY_ROW, ARRAY_COLUMN, '*');

	//Print
	DisplayBoard(show,ROW,COLUMN);
	//set mine in mine ARRAY
	SetMine(mine, ROW,COLUMN);
	//DisplayBoard(mine, ROW, COLUMN);
	//find mine
	FindMine(mine,show, mineClac,ROW,COLUMN);

	Sleep(5000);
}


void test() {
	int input = 0;
	do {
		menu();
		printf_s("Please choose to continue:");
		scanf_s("%d", &input);
		system("cls");

		switch (input)
		{
		case 1:
			game();
			system("cls");
			break;
		case 0:
			printf_s("QUIT\n");
			break;
		default:
			
			printf_s(":( Unrecognizable Character\n");
			break;
		}


	} while (input);

}


int main() {

	test();

	return 0;
}