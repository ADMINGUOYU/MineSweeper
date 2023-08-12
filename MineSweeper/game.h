#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COLUMN 9
#define EASY_COUNT 50

#define ARRAY_ROW ROW+2
#define ARRAY_COLUMN COLUMN+2

#define FROM_CENTER 0
#define FROM_UP 1
#define FROM_DOWN 2
#define FROM_LEFT 3
#define FROM_RIGHT 4
#define FROM_LUP 5
#define FROM_LDOWN 6
#define FROM_RUP 7
#define FROM_RDOWN 8
#define FROM_MINING 9

//#define MINING_DEPTH 10



void InitBoard(char board[ARRAY_ROW][ARRAY_COLUMN], int rows, int columns,char set);
void DisplayBoard(char board[ARRAY_ROW][ARRAY_COLUMN], int row, int column);
void SetMine(char board[ARRAY_ROW][ARRAY_COLUMN], int row, int column);
void FindMine(char mine[ARRAY_ROW][ARRAY_COLUMN],char show[ARRAY_ROW][ARRAY_COLUMN], char mineClac[ARRAY_ROW][ARRAY_COLUMN], int row, int column);