#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **allocate_board(int x, int y){
    int i;
    int **board = malloc(x * sizeof(int*));
    for (i = 0; i < x; i++){
        board[i] = malloc(y * sizeof(int));
    }
    return board;
}

int **load_board_from_file(char *filename, int *rows, int *columns){
    FILE *f;
    int **board;
    int x, y, i, j, value;
    f = fopen(filename, "r");
    if (f == NULL){
        printf("Nie mogę otworzyć pliku!");
        return NULL;
    }
    fscanf(f, "%d", &x);
    fscanf(f, "%d", &y);
    *rows = x;
    *columns = y;
    board = allocate_board(x, y);
    for (i = 0; i < x; i++){
        for (j = 0; j < y; j++){
            fscanf(f, "%d", &value);
            board[i][j] = value;
        }
    }
    fclose(f);
    return board;
}

int **random_board(int x, int y, float random_fill){
    int **board = allocate_board(x, y);
    int i, j;
    float r;
    random_fill /= 100;
    srand(time(NULL));
    for (i = 0; i < x; i++){
        for (j = 0; j < y; j++){
            r = (float)rand() / RAND_MAX;
            if (r < random_fill){
                board[i][j] = 1;
            }
            else {
                board[i][j] = 0;
            }
        }
    }
    return board;
}

int print_matrix(int **board, int x, int y){
    int i, j;
    for (i = 0; i < x; i++){
        for (j = 0; j < y; j++){
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}