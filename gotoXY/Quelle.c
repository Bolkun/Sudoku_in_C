#include <windows.h>
#include <conio.h>

void gotoXY(int x, int y); 
// Prototype erstellen, 
// danach kann man die eigentliche Funktion unter die Main-Funktion schreiben


int main(void) {
	// x = 20 Zeichen von links entfernt
	// y = 5 Zeichen von oben entfernt 
	int x = 20, y = 5, c, z = 1;

	// Ausgabe in der Mitte der Konsole
	// Positionwechsel wird angewendet
	gotoXY(x, y);
	printf("Text in der Mitte:)\n Text nach Zeilenumbruch leider wieder ganz links:(");
	gotoXY(x, y+2); // y + 2 weil man schon ein Zeilenumbruch vorher gemacht wurde
					// kleiner Nachteil dieser Funktion, man muss auf Zeilenumbrüche achten
	printf("Text wieder in der Mitte nach erneuten aufruf von gotoXY:)");
	gotoXY(x, y + 3);
	printf("Cursor kann auch mit den Pfeiltasten bewegt werden");
	y += 4;
	gotoXY(x, y); // aufruf das der Cursor an der richtigen Stelle steht
	while (z){
		c = getch();
			switch (c) {
			case 75: // linke Pfeiltaste
				x = (--x + 80) % 80;
				break;
			case 72:  // oben Pfeiltaste
				y = (--y + 25) % 25;
				break;
			case 77: // rechte Pfeiltaste
				x = (++x + 80) % 80;
				break;
			case 80: // unten Pfeiltaste
				y = (++y + 25) % 25;
				break;
			case 27: // ESC zum Abbrechen
				z = 0;
				break;
			}
			gotoXY(x, y);
		// Leertaste um Bildschirm zu leeren	
			if (c == ' '){
				system("cls");
				gotoXY(x, y);
			}
	}
	return 0;
}

// eigentliche Funktion, darf nicht vergessen werden!
void gotoXY(int x, int y) {
	HANDLE hConsoleOutput;
	COORD koords;
	koords.X = x;
	koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}
