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

	for (i = 1; i < argc; i++){
		if (strcmp(argv[i], "-h") == 0){
			printf("Dostepne opcje:\n\
			-r: losowa plansza, po tej fladze nalezy podac w odpowiedniej\n\
			kolejnosci: liczbe wierszy, liczbe kolumn i wypelnienie w procentach.\n\
			Przyklad: -r 5 5 25\n\
			\n\
			-f: wczytanie planszy z pliku o zadanej nazwie. Przykladowy format pliku:\n\
			3 3\n\
			1 1 0\n\
			0 1 0\n\
			1 0 0\n\
			Przykladowe wywolanie: -f board.txt\n\
			\n\
			-p: tryb symulacji, w ktorym stan planszy zmienia sie co 0.5 sekundy.\n\
			\n\
			-s: tryb symulacji, w ktorym zostanie zasymulowana liczba krokow podana jako\n\
			nastepny argument. Przykladowe wywolanie: -s 10\n\
			\n\
			Domyslnie zostanie uruchomiona symulacja krok po kroku, gdzie nowy krok jest\n\
			wykonywany przy	nacisnieciu dowolnego przycisku innego niz E.\n\
			Aby program dzialal poprawnie nalezy podac dane wejsciowe za pomoca flagi -f badz -r.\n");
			return 1;
		}
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
			printf("Użyj flagi -h.\n");
			return -1;
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