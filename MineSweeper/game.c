#include "game.h"


void InitBoard(char board[ARRAY_ROW][ARRAY_COLUMN], int rows, int columns,char set){
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ARRAY_ROW][ARRAY_COLUMN], int row, int column) {
	int i = 0;
	int j = 0;
	for (j = 0; j <= column; j++) {
		printf_s("%d ", j);
	}
	printf_s("\n");
	for (i = 1; i <= row; i++) {
		printf_s("%d ", i);
		for (j = 1; j <= column; j++) {
			printf_s("%c ", board[i][j]);
		}
		printf_s("\n");
	}

}

void SetMine(char board[ARRAY_ROW][ARRAY_COLUMN], int row, int column) {
	int count = EASY_COUNT;
	while (count) {
		int x = rand() % row + 1;
		int y = rand() % column + 1;
		if (board[x][y] == '0') {
			board[x][y] = '1';
			count--;
		}
	}
}
void ClacMine(char mine[ARRAY_ROW][ARRAY_COLUMN], char mineClac[ARRAY_ROW][ARRAY_COLUMN], int row, int column) {
	
	return;
}


int get_mine_count(char mine[ARRAY_ROW][ARRAY_COLUMN], char mineClac[ARRAY_ROW][ARRAY_COLUMN], int x,int y) {
	// '1' - '0' = 1
	// '3' - '0' = 3
	int valueCount = 0;

	//for (int i = x - 1; i <= x + 1; i++) {
	//	for (int j = y - 1; j <= y + 1; j++) {
	//		if (i == x && j == y) {
	//			//do nothing
	//		}
	//		else {
	//			valueCount += mine[i][j];
	//		}
	//	}
	//}
	//valueCount -= 8 * '0';

	valueCount =
		mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1];
	valueCount -= 8 * '0';

	mineClac[x][y] = valueCount +'0';
	return (valueCount);
}

void mining(char mine[ARRAY_ROW][ARRAY_COLUMN], char show[ARRAY_ROW][ARRAY_COLUMN], char mineClac[ARRAY_ROW][ARRAY_COLUMN], int row, int column,int x,int y,int* win, int param, int* currentMiningDepth,int depth) {
	int moveROW = rand() % 3;
	int moveColumn = rand() % 3;

	switch (param) {
	case FROM_CENTER:
		show[x][y] = get_mine_count(mine, mineClac, x, y) + '0';
		*win += 1;
		if (mineClac[x][y] != '0') {
			break;
		}

	case (FROM_CENTER|FROM_MINING):
#ifdef MINING_DEPTH
		if (*currentMiningDepth >= depth) {
			break;
		}
#endif
		
			for (int i = x - 1; i <= x + 1; i++) {
				for (int j = y - 1; j <= y + 1; j++) {
					
					for (int mi = 0; mi <= moveROW; mi++) {i++; if (i > x + 1) { i = x - 1; }}
					for (int mj = 0; mj <= moveColumn; mj++) { j++; if (j > y + 1) { j = y - 1; } }


					if ( (i < 1) | (j < 1) | (i > ROW) | (j > COLUMN)) {
						//do nothing
						continue;
					}
					else if (mineClac[i][j] == '*') {
						
						show[i][j] = get_mine_count(mine, mineClac, i, j) + '0';
						*win += 1;
#ifdef MINING_DEPTH
						*currentMiningDepth += 1;
#endif

						if (mineClac[i][j] == '0') {
#ifdef MINING_DEPTH
						*currentMiningDepth -= 1;
#endif

							mining(mine, show, mineClac, row, column, i, j, win,FROM_MINING,currentMiningDepth,depth);
						}
					}
				}
			}

			break;
	}
	




	
	
	return;
}

void FindMine(char mine[ARRAY_ROW][ARRAY_COLUMN], char show[ARRAY_ROW][ARRAY_COLUMN], char mineClac[ARRAY_ROW][ARRAY_COLUMN], int row, int column) {
	int x = 0;
	int y = 0;
	int win = 0;
#ifdef MINING_DEPTH
	int currentMiningDepth = 0;
#endif // MINING_DEPTH

	while (win < row*column - EASY_COUNT) {
		printf_s("Input Coordinates:");
		scanf_s("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= column) {
			//on mine
			if (mine[x][y] == '1') {
				printf_s("ops! You are on the mine...\n");
				DisplayBoard(mine, row, column);
				break;
			}
			else {//not on mine
#ifdef MINING_DEPTH
				int currentMiningDepth = 0;
				mining(mine, show, mineClac, row, column, x, y, &win, FROM_CENTER, &currentMiningDepth,MINING_DEPTH);
#else
				mining(mine, show, mineClac, row, column, x, y, &win, FROM_CENTER, NULL, NULL);
#endif
				system("cls");
				DisplayBoard(show, row, column);
				printf_s("Opened: %d\n",win);
			}
			//not on mine
		}
		else if(x == -1 && y == -1){
			win = row * column - EASY_COUNT;
		}
		else {
			printf_s("Please check your input>>>\n");

		}
	}
	if (win == row * column - EASY_COUNT) {
		printf_s("Congratulations, all mines are disclosed!\n");
		DisplayBoard(mine, row, column);
	}
}