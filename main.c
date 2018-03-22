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

<<<<<<< HEAD
	for (i = 1; i < argc; i++){
=======
	for (i = 0; i < argc; i++){
		if (strcmp(argv[i], "-h") == 0){
			printf("Dostępne opcje: \
			-r: losowa plansza, po tej fladze należy podać w odpowiedniej \
			kolejności: liczbę wierszy, liczbę kolumn i wypełnienie w procentach. \
			Przykład: -r 5 5 25 \
			\
			-f: wczytanie planszy z pliku o zadanej nazwie. Przykładowy format pliku: \
			3 3 \
			1 1 0 \
			0 1 0 \
			1 0 0 \
			Przykładowe wywołanie: -f board.txt \
			\
			-p: tryb symulacji, w którym stan planszy zmienia się co 0.5 sekundy. \
			\
			-s: tryb symulacji, w którym zostanie zasymulowana liczba kroków podana jako następny argument. \
			Przykładowe wywołanie: -s 10 \
			\
			Domyślnie zostanie uruchomiona symulacja krok po kroku, gdzie nowy krok jest wykonywany przy \
			naciśnięciu dowolnego przycisku innego niż E. \
			Aby program działał poprawnie należy podać dane wejściowe za pomocą flagi -f bądź -r.\n");
			return 1;
		}
>>>>>>> b0dddd4d72ee19c08264b0f202734582591f21f3
		if (strcmp(argv[i], "-r") == 0){
			rows = atoi(argv[++i]);
			columns = atoi(argv[++i]);
			random_fill = atof(argv[++i]);
			board1 = random_board(rows, columns, random_fill);
		}
		else if (strcmp(argv[i], "-f") == 0){
			board1 = load_board_from_file(argv[++i], &rows, &columns);
			if (board1 == NULL){
				return -1;
			}
		}
		else if (strcmp(argv[i], "-p") == 0){
			play = true;
		}
		else if (strcmp(argv[i], "-s") == 0){
			steps = true;
			step_count = atoi(argv[++i]);
		}
		else {
			printf("Użyj flagi -h.");
		}
	}

	board2 = allocate_board(rows, columns);
    print_matrix(board1, rows, columns);
	i = 0;
	if (play){
		while (run){
			update(board1, board2, rows, columns, &i);
			printf("Naciśnij Ctrl+C aby zakończyć.\n");
			SWAP(board1, board2);
			nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
		}
		printf("Kończę grę...\n");
	}
	else if (steps){
		for (i = 0; i < step_count; i++){
			update(board1, board2, rows, columns, &i);
			SWAP(board1, board2);
		}
	}
	else {
		while (true){
			update(board1, board2, rows, columns, &i);
			printf("Naciśnij e aby zakończyć.\n");
			c = getchar();
			if (c == 'e'){
				break;
			}
			SWAP(board1, board2);
		}
	}

	return 0;
}