#ifndef HEADER_FILE
#define HEADER_FILE

int update(int **old_board, int **new_board, int x, int y, int *step);
int count_neighbors(int **board, int rows, int columns, int x, int y);

#endif