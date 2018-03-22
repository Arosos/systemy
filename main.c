#include "board.h"
#include "processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

#define SWAP(x,y) temp = x; x = y; y = temp;

bool run = true;

void stop(int i){
	run = false;
}

int main(int argc, char **argv)
{
	int i, rows, columns, step_count;
	float random_fill;
	int **board1, **board2, **temp;
	bool play = false, steps = false;
	char c;

	signal(SIGINT, stop);

	for (i = 0; i < argc; i++){
		if (strcmp(argv[i], "-r") == 0){
			rows = atoi(argv[++i]);
			columns = atoi(argv[++i]);
			random_fill = atof(argv[++i]);
			board1 = random_board(rows, columns, random_fill);
		}
		else if (strcmp(argv[i], "-f") == 0){
			board1 = load_board_from_file(argv[++i], &rows, &columns);
		}
		else if (strcmp(argv[i], "-p") == 0){
			play = true;
		}
		else if (strcmp(argv[i], "-s") == 0){
			steps = true;
			step_count = atoi(argv[++i]);
		}
	}

	board2 = allocate_board(rows, columns);
    print_matrix(board1, rows, columns);
	if (play){
		while (run){
			update(board1, board2, rows, columns);
			printf("Press Ctrl+C to end.\n");
			SWAP(board1, board2);
			nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
		}
		printf("Ending game...\n");
	}
	else if (steps){
		for (i = 0; i < step_count; i++){
			printf("Step#%d:\n", i + 1);
			update(board1, board2, rows, columns);
			SWAP(board1, board2);
		}
	}
	else {
		while (true){
			update(board1, board2, rows, columns);
			printf("Press e to end.\n");
			c = getchar();
			if (c == 'e'){
				break;
			}
			SWAP(board1, board2);
		}
	}

	return 0;
}