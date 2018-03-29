#include "board.h"

int update(int **old_board, int **new_board, int x, int y, int step)
{
    int i, j, count;
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            count = count_neighbors(old_board, x, y, i, j);
            if (old_board[i][j] == 1 && count <= 1)
            {
                new_board[i][j] = 0;
            }
            else if (old_board[i][j] == 1 && count >= 4)
            {
                new_board[i][j] = 0;
            }
            else if (old_board[i][j] == 1 && (count == 2 || count == 3))
            {
                new_board[i][j] = 1;
            }
            else if (old_board[i][j] == 0 && count == 3)
            {
                new_board[i][j] = 1;
            }
            else
            {
                new_board[i][j] = 0;
            }
        }
    }
    printf("Krok#%d:\n", step);
    print_matrix(new_board, x, y);
}

int count_neighbors(int **board, int rows, int columns, int x, int y)
{
    int i, j, count = 0;
    for (i = x - 1; i <= x + 1; i++)
    {
        for (j = y - 1; j <= y + 1; j++)
        {
            if ((i != x || j != y) && i >= 0 && i < rows && j >= 0 && j < columns)
            {
                count += board[i][j];
            }
        }
    }
    return count;
}