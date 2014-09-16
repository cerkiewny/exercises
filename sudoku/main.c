#include "stdio.h"
#include "stdlib.h"
#include "fcntl.h"

#define BUF_SIZE 1024

struct {
	int x;
	int y;
	int poss;
	int onlyPoss;
} typedef point;

struct solverTree{
	struct solverTree *Parent;
	struct solverTree *FirstChild;
	struct solverTree *Next;
} typedef solverTree;

struct{
	int possibilities[9][9][9];
	int board[9][9];
} typedef Board;

int numToSquare(int x, int y){
	return (x / 3) + (3 * (y / 3));
}

int calculatePoss(int board[9][9], int poss[9][9][9]){
	int RowPoss[9][9] = {0}, ColPoss[9][9] = {0}, SquarePoss[9][9] = {0}, i, j, k;
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(board[i][j]!=0){
				if(SquarePoss[numToSquare(i, j)][board[i][j] - 1] == 1 || RowPoss[j][board[i][j] - 1] == 1 || ColPoss[i][board[i][j] - 1] == 1){
					return 0;
				}
				SquarePoss[numToSquare(i, j)][board[i][j] - 1] = 1;
				RowPoss[j][board[i][j] - 1] = 1;
				ColPoss[i][board[i][j] - 1] = 1;
			}
		}
	}
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			for(k = 0; k < 9; k++){
				poss[i][j][k] = SquarePoss[numToSquare(i, j)][k] + RowPoss[j][k] + SquarePoss[j][k];
			}
		}
	}
	
	return 1;
}

int charToInt(char in){
	switch(in){
	case (int)'0':
		return 0;
	case (int)'1':
		return 1;
	case (int)'2':
		return 2;
	case (int)'3':
		return 3;
	case (int)'4':
		return 4;
	case (int)'5':
		return 5;
	case (int)'6':
		return 6;
	case (int)'7':
		return 7;
	case (int)'8':
		return 8;
	case (int)'9':
		return 9;
	}
	return -1;
}

point * findPoss(int board[9][9], int poss[9][9][9]){
	int i, j, k, max = 0, count, lastPos;
	point *ret = malloc(sizeof(point));
	ret->x = -1;
	ret->y = -1;
	for(i = 0; i<9; i++){
		for(j = 0; j<9; j++){
			count = 0;
			if(board[i][j] > 0){
				for(k = 0; k<9; k++){
					if( poss[i][j][k] > 0){
						count++;
					}
					else{
						lastPos = k;
					}
					
				}
				if(max < count){
					max = count;
					ret->onlyPoss = lastPos;
					ret->poss = count;
					ret->x = i;
					ret->y = j;
				}
			}
		}
	}
	return ret;
}

void printPoss(int poss[9][9][9]){
	int i, j, k, count;
	printf("+-------+-------+-------+\n");
	for(i = 0; i<9; i++){
		if(i==3 || i == 6){
			printf("+-------+-------+-------+\n");
		}
		printf("| ");
		for(j = 0; j<9; j++){
			if(j==3 || j == 6){
				printf("| ");
			}
			count = 0;
			for(k = 0; k<9; k++){
				if( poss[i][j][k] > 0){
					count++;
				}
			}
			printf("%i ", 9 - count);
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
}

void printBoard(int sudoku[9][9]){
	int i, j;
	printf("+-------+-------+-------+\n");
	for(i = 0; i<9; i++){
		if(i==3 || i == 6){
			printf("+-------+-------+-------+\n");
		}
		printf("| ");
		for(j = 0; j<9; j++){
			if(j==3 || j == 6){
				printf("| ");
			}
			printf("%i ", sudoku[i][j]);
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
}


int main(int argc, char **argv){
	int fin = open("in", O_RDONLY), fout = open("out", O_RDWR | O_CREAT | O_SYNC);
        char buffer[BUF_SIZE] = {0};
	int b, readCount, c, curel = 0;
	Board Board = {0};
	point *p = NULL;
	readCount = read(fin, &buffer, 1024);
	buffer[readCount] = 0x00;
	for(b = 0; b<9; b++){
		for(c = 0; c<9; c++){
			Board.board[b][c] = charToInt(buffer[curel]);
			curel++;
			curel++;
		}
	}
	printBoard(Board.board);
	do{
		if(!calculatePoss(Board.board, Board.possibilities)){
			printf("not possible board\n");	
			return;
		}
		p = findPoss(Board.board, Board.possibilities);	
		if(p->poss == 1){
			Board.board[p->x][p->y] == p->onlyPoss;
		}
		if(p->x == -1){
			printf("no possibilities left");
			return;
		}
	}while(p->poss == 1);
	printf("first max in: %i %i\n", p->x, p->y);
	printPoss(Board.possibilities);
	free(p);
        close(fin), close(fout);
        return 0;

	
}
