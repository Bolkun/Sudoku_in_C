#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

void color_zahlen(){
	//Farbe
	HANDLE hConsole;
	int k = 14;		//Gelb
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// pick the colorattribute k you want
	SetConsoleTextAttribute(hConsole, k);
}

void color_console(){
	//Farbe
	HANDLE hConsole;
	int z = 7;		//Grau
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// you can loop k higher to see more color choices
	//for (z = 0; z < 20; z++){
	// pick the colorattribute k you want
	SetConsoleTextAttribute(hConsole, z);
		//printf("Farbe");
	//}
}

int datei_laden(int* v, int* v2, int maxanz, char *n, int schalter){
	int i, anz = -1;
	FILE *fp;
	if ((fp = fopen(n, "rt")) == 0){
		printf("\nFehler bei oeffnen der Datei: %s\n", n);
		printf("Geben Sie ein korrektes Name der Datei!\n ");
		Sleep(5000);
		return 0;
	}
	fscanf(fp, "%d", &anz);

	if ((anz < 0) || (anz>maxanz)){
		printf("\nFehlerhafte Anzahl von int-Werten (%d) \n", anz);
		fclose(fp);
		return 0;
	}
	for (i = 0; i < anz; i++){
		if (fscanf(fp, "%d", &v[i]) != 1) {
			printf("Fehlerhafte Anzahl von int-Werten, nur %d Elemente...", n);
			break;
		}
		v2[i] = v[i];
	}
	
	fclose(fp);
	return i;
}

int anzeigen_v1(int* v[9][9], int* v2[9][9], int a){
	int i, j, schalter = 1;	// c = 12;
	char l = ' ';
	color_console();
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201, 205, 205, 205, 205, 205, 205, 205, 205, 203, 205, 205, 205, 205, 205, 205, 205, 205, 203, 205, 205, 205, 205, 205, 205, 205, 205, 187);
	// Schleife fьr Zeilen, Y-Achse
	for (i = 0; i < 9; i++) {
		//Schleife fьr Spalten, X-Achse
		for (j = 0; j < 9; j++) {
			printf("%c", 186);
			if ((schalter != 0) && (v2[i][j] != 0)){
				color_zahlen();
			}
			printf("%d ", v[i][j]);
			color_console();
			if (j == 8) printf("%c",186);
		} 
		
		if (i == 2 || i == 5) printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 204, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 206, 205, 205, 205, 205, 205, 205, 205, 205, 185);
		  if (i==8) printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 202, 205, 205, 205, 205, 205, 205, 205, 205, 188);
		  printf("\n");
		}schalter=0;
}

void gotoXY(int x, int y) {
		HANDLE hConsoleOutput;
		COORD koords;
		koords.X = x;
		koords.Y = y;
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsoleOutput, koords);
}

int editieren(int* v[9][9], int* v2[9][9], int a) {
	// x = 1 Zeichen von links entfernt
	// y = 1 Zeichen von oben entfernt
	int x = 1, y = 1, c, z = 1;	
	printf("\nDruecken Sie [ESC] um Editierung ihres Sudoku zu beenden.");
	gotoXY(x, y); // aufruf das der Cursor an der richtigen Stelle steht
	while (z){
		c = getch();
		switch (c) {
		case 75: // linke Pfeiltaste
			x = (--x + 26) % 26;
			if (x == 3 || x == 6 || x == 9 || x == 12 || x == 15 || x == 18 || x == 21 || x == 24)
				x -= 2;
			if (x == 0)
				x += 25;
			break;
		case 72:  // oben Pfeiltaste
			y = (--y + 12) % 12;
			if (y == 0)
				y += 11;
			if (y == 4 || y == 8)
				y--;
			break;
		case 77: // rechte Pfeiltaste
			x = (++x + 26) % 26;
			if (x == 2 || x == 5 || x == 8 || x == 11 || x == 14 || x == 17 || x == 20 || x == 23)
				x += 2;
			if (x == 0)
				x++;
			break;
		case 80: // unten Pfeiltaste
			y = (++y + 12) % 12;
			if (y == 4 || y == 8)
				y++;
			if (y == 0)
				y++;
			break;
		case 27: // ESC zum Abbrechen
			z = 0;
			break;
		}
		gotoXY(x, y);

		//Die Nullen ersetzen mit Ziffern von 1 bis 9
		if (c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9'){

			if (((y == 1) && ((v2[y % 12 - 1][x / 3]) == 0)) || ((y == 2) && ((v2[y % 12 - 1][x / 3]) == 0)) || ((y == 3) && ((v2[y % 12 - 1][x / 3]) == 0))) {	//v(y,x)
				v[y % 12 - 1][x / 3] = c-48;// c - 48;	//v(x,y)
				gotoXY(0, 0);
				anzeigen_v1(v, v2, a);
			}
			if ((y == 5 && v2[y % 12 - 2][x / 3] == 0) || (y == 6 && v2[y % 12 - 2][x / 3] == 0) || (y == 7 && v2[y % 12 - 2][x / 3] == 0)) {	//v(y,x)
				v[y % 12 - 2][x / 3] = c - 48;	//v(x,y)
				gotoXY(0, 0);
				anzeigen_v1(v, v2, a);
			}
			if ((y == 9 && v2[y % 12 - 3][x / 3] == 0) || (y == 10 && v2[y % 12 - 3][x / 3] == 0) || (y == 11 && v2[y % 12 - 3][x / 3] == 0)) {	//v(y,x)
				v[y % 12 - 3][x / 3] = c - 48;	//v(x,y)
				gotoXY(0, 0);
				anzeigen_v1(v, v2, a);
			}
		}
	}
	return 0;
}

int speichern_datei(int* v, char *n){
	int i; FILE *fp;
	if ((fp = fopen(n, "w+t")) == 0) {
		printf("\nFehler: konnte Datei %s nicht oefnen", n); 
		return 0;
	}
	fprintf(fp, "%d\n", 81);
	for (i = 0; i < 81; i++){
		if (i==9 || i==18 || i==27 || i==36 || i==45 || i==54 || i==63 || i==72 || i==81)
			fprintf(fp, "\n");
		fprintf(fp, "%d ", v[i]);
	}
	fclose(fp);
	return 1;
}

int loesung(int* v[9][9]) {
	int z = 0;	//true
	int s = 0;	//true
	int a, b;
	for (a = 0; a < 9; a++) {	//Y
		for (b = 0; b < 9; b++) {	//x
			if (v[a][b] != 0) {
				if ((v[a][b] != v[(a + 1) % 9][b]) &&
					(v[a][b] != v[(a + 2) % 9][b]) &&
					(v[a][b] != v[(a + 3) % 9][b]) &&
					(v[a][b] != v[(a + 4) % 9][b]) &&
					(v[a][b] != v[(a + 5) % 9][b]) &&
					(v[a][b] != v[(a + 6) % 9][b]) &&
					(v[a][b] != v[(a + 7) % 9][b]) &&
					(v[a][b] != v[(a + 8) % 9][b])) {
					z = z + 1;
				}
				else {
					printf("In Spalte ist ein Fehler aufgetretten! %d v[%d][%d]\n", v[a][b], a, b);
				}

				if ((v[a][b] != v[a][(b + 1) % 9]) &&
					(v[a][b] != v[a][(b + 2) % 9]) &&
					(v[a][b] != v[a][(b + 3) % 9]) &&
					(v[a][b] != v[a][(b + 4) % 9]) &&
					(v[a][b] != v[a][(b + 5) % 9]) &&
					(v[a][b] != v[a][(b + 6) % 9]) &&
					(v[a][b] != v[a][(b + 7) % 9]) &&
					(v[a][b] != v[a][(b + 8) % 9])) {
					s = s + 1;
				}
				else {
					printf("In Zeile ist ein Fehler aufgetretten! %d v[%d][%d] \n", v[a][b], a, b);
				}
			}
			else {
				printf("Nicht alle Werte sind eingegeben! \n");
			}
		}
	}
	printf("\n");
	/*int i, j;
	for (i = 0; i < 9; i++) {
		//Schleife fьr Spalten, X-Achse
		for (j = 0; j < 9; j++) {
			printf("%d ", v[i][j]);
		}
		printf("\n");
	}*/
	if ((z == 81) && (s == 81)) {
		printf(".. ..._ _ _ . . . . ..._ _ _.......\n");
		printf(".... (. . .). . . .. .(. . .)......\n");
		printf("..... \\. ./ . . . . . .\\. ./ . ....\n");
		printf(".._____)_(. . . . . .. .) _(____.....\n");
		printf(".(_______0)\\ ... ... . / (0_______)..\n");
		printf("(________0)-[!GEWONNEN!]-(0________).\n");
		printf("(________0)_ / \\.../ \\_  (0________).\n");
		printf(". (______0). . .\\./ . . .(0______)...\n");
		printf(". . . . . . . . . . . . . . . . . . .\n");
	}
	return 0;
}

int main() {
	int i = 1;
	int schalter = 1;
	int menu;
	int anz, maxanz = 81;
	char j, fname[100];
	int v[9][9] = { { 0, 0, 0, 0, 0, 0, 0, 8, 0 },		//vek[Y][X]
					{ 0, 0, 7, 2, 0, 9, 5, 0, 0 },
					{ 0, 3, 0, 0, 0, 0, 0, 9, 2 },
					{ 0, 6, 0, 0, 4, 0, 0, 0, 9 },
					{ 0, 0, 0, 9, 1, 0, 0, 0, 0 },
					{ 0, 9, 0, 0, 0, 2, 8, 0, 3 },
					{ 0, 2, 0, 0, 0, 4, 3, 1, 0 },
					{ 9, 0, 1, 0, 0, 0, 6, 0, 0 },
					{ 0, 0, 4, 8, 0, 1, 0, 0, 0 } 
	};
	int v2[9][9] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },		//vek[Y][X]
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
	//anzeigen_v1(v, v2, maxanz);
	printf("*******************************************\n\n");
	printf("\t\tS_U_D_O_K_U\n\n");
	printf("\t\t\t   by Serhiy Bolkun\n");
	printf("*******************************************\n");
	while (i) {
		printf("\n 1 - Laden\n 2 - Editieren\n 3 - Speichern\n 4 - Pruefen\n 5 - Spiel Verlassen\n>");
		scanf("%d", &menu);
		switch (menu) {
		case 1:	schalter--;
				printf("Waehle eine von drei Sudokus: \n 1)bsp1.txt\n 2)bsp2.txt\n 3)bsp3.txt\n");
				printf("Dateiname eingeben: ");
				scanf("%s", fname);
				datei_laden(v, v2, maxanz, fname, schalter);
				system("cls");
				anzeigen_v1(v, v2, maxanz);
				break;
		case 2: if (schalter == 1){
					schalter--;
					printf("Waehle eine von drei Sudokus: \n 1)bsp1.txt\n 2)bsp2.txt\n 3)bsp3.txt\n");
					printf("Dateiname eingeben: ");
					scanf("%s", fname);
					datei_laden(v, v2, maxanz, fname, schalter);
					system("cls");
					anzeigen_v1(v, v2, maxanz);
					break;
				}
				//system("cls");
				editieren(v, v2, maxanz);
				system("cls");
				anzeigen_v1(v, v2, maxanz);
				break;
		case 3: printf("Dateiname eingeben: ");
				scanf("%99s", fname);
				speichern_datei(v, fname);
				system("cls");
				anzeigen_v1(v, v2, maxanz);
				break;
		case 4: loesung(v); 
				break;
		case 5: printf("Moechten Sie das Spiel verlassen (j/n)? ");
				fflush(stdin);
				scanf("%c", &j);
				if (j == 'j') i--;
				break;
		}
	}
	return 0;
}