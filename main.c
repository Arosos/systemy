#include "board.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i, rows, columns;
	float random_fill;
	int **board;
	for (i = 0; i < argc; i++){
		if (strcmp(argv[i], "-r") == 0){
			rows = atoi(argv[++i]);
			columns = atoi(argv[++i]);
			random_fill = atof(argv[++i]);
			board = random_board(rows, columns, random_fill);
		}
		else if (strcmp(argv[i], "-f") == 0){
			board = load_board_from_file(argv[++i]);
		}
	}

	return 0;
}