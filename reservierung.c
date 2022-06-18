#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define ROWS 6
#define COLS 15

typedef struct {
	int num;
	char name[30];
	char date[10];
	bool reserved;
} SEAT;

void inittheater(SEAT *, int, int);
void randomreserve(SEAT *, int, int);
void showtheater(SEAT *, int, int);
void showstage();
void showbooking(char [30], char [10], int, int);

int main () {
	srand(time(NULL));							// Initialize Rand Seed
	printf("\e[1;1H\e[2J");						// Clear screen

	bool quit = false, eingabe = true;
	char menu;
	int reihe = ROWS + 1, platz = COLS + 1;
	char namestr[30], datestr[30];

	SEAT theater[ROWS][COLS];
	inittheater(theater[0], ROWS, COLS);
	randomreserve(theater[0], ROWS, COLS);

	while (!quit) {
		printf("\e[1;1H\e[2J");						// Clear screen
		showstage();
		showtheater(theater[0], ROWS, COLS);

		if (reihe < ROWS && platz < COLS) {
			if (theater[reihe][platz].reserved) {
				showbooking(theater[reihe][platz].name, theater[reihe][platz].date, reihe, platz);
			}
		}

		printf("\n\n\n\n\n\nMenu: (1) Reservierung anzeigen (2) Reservierung löschen (3) Reservierung tätigen --- (0) Exit\n");
		if (eingabe) scanf(" %c", &menu);

		switch (menu) {
			case '1': {
						  printf("Reihe ?: ");
						  scanf("%d", &reihe);
						  reihe--;
						  printf("Platz ?: ");
						  scanf("%d", &platz);
						  platz--;
						  if (theater[reihe][platz].reserved) eingabe = true;
						  else eingabe = false;
						  break;
					  }
			case '2': {
						  printf("Reihe ?: ");
						  scanf("%d", &reihe);
						  reihe--;
						  printf("Platz ?: ");
						  scanf("%d", &platz);
						  platz--;
						  if (theater[reihe][platz].reserved) {
							  theater[reihe][platz].reserved = false;
							  eingabe = true;
						  }
						  else eingabe = false;
						  break;
					  }
			case '3': {

						  printf("Reihe ?: ");
						  scanf("%d", &reihe);
						  reihe--;
						  printf("Platz ?: ");
						  scanf("%d", &platz);
						  platz--;
						  if (theater[reihe][platz].reserved) eingabe = false;
						  else { 
                              fflush(stdin);
							  printf("Name : ");
							  fflush(stdin);
							  scanf("%s", namestr); // Überprüfung der Eingaben evtl Fix
                              fflush(stdin);
							  printf("Datum (yyyy-mm-dd) : ");
							  scanf("%s", datestr);
							  theater[reihe][platz].reserved = true;
							  strcpy(theater[reihe][platz].name, namestr);
							  strcpy(theater[reihe][platz].date, datestr);
							  eingabe = true;
						  }
						  break;
					  }
			case '0': quit = true; break;
			default: break;
		}
	}
}

void inittheater(SEAT *t, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			t[i * cols + j].num = j + 1;
			strcpy(t[i * cols + j].name,"not reserved");
			strcpy(t[i * cols + j].date,"2022-01-01");
			t[i * cols + j].reserved = false;
		}
	}
}

void randomreserve(SEAT *t, int rows, int cols) {
	int zuf = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			zuf = rand() % 10;
			if (zuf % 3 == 0) t[i * cols + j].reserved = true;
			else t[i * cols + j].reserved = false;
		}
		printf("\n");
	}
}

void showtheater(SEAT *t, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (t[i * cols + j].reserved) printf("  x ");
			else printf("  o ");
		}
		printf("\t%d \n", i + 1);
	}
	printf("\n");
	for (int i = 0; i < cols; i++) printf(" %02d ", i + 1);
	printf("Platz \\ Reihe");
}

void showstage() {
	int q = 4 * COLS / 2 - 8;
	for (int i = 0;i < q; i++) printf(" ");
	printf("##################\n");
	for (int i = 0;i < q; i++) printf(" ");
	printf("#                #\n");
	for (int i = 0;i < q; i++) printf(" ");
	printf("#   YOUR STAGE   #\n");
	for (int i = 0;i < q; i++) printf(" ");
	printf("#                #\n");
	for (int i = 0;i < q; i++) printf(" ");
	printf("##################\n\n\n");
}

void showbooking(char name[30], char date[10], int reihe, int platz) {
	printf("\n\n\n\n");
	printf("\t\tSeat number: %d in Row %d is booked by\n\n", platz + 1, reihe + 1);
	printf("\t\tName : %s\t\t Date : %s", name, date);
	printf("\n");
}


