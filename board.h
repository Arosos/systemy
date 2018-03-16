#ifndef HEADER_FILE
#define HEADER_FILE

int **load_board_from_file(char *filename);

int **random_board(int x, int y, float random_fill);

int **allocate_board(int x, int y);

int print_matrix(int **board, int x, int y);

#endif