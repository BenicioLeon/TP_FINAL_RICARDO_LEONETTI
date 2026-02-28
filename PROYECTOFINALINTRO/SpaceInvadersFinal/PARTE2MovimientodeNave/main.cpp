#include <iostream>
#include <ctime>
#include <windows.h>  
#include "conio2.h"

using namespace std;

void limpiarPantalla() {
	
}
void borrarPantallaConEspacios() {
	for (int y = 1; y <= 24; y++) {
		for (int x = 1; x <= 80; x++) {
			gotoxy(x, y);
			cout << " ";
		}
	}
}

void pantallaBienvenida() {
	limpiarPantalla();
	
	textcolor(LIGHTBLUE);
	gotoxy(10,3); cout << "************************************";
	gotoxy(10,4); cout << "*       SPACE INVADERS LITE        *";
	gotoxy(10,5); cout << "************************************";
	
	textcolor(LIGHTCYAN);
	gotoxy(10,7); cout << "Alumno: Ricardo Esteban Leonetti";
	
	gotoxy(10,9); cout << "Objetivos del Juego:";
	gotoxy(12,10); cout << "- Controlar la nave en la parte inferior";
	gotoxy(12,11); cout << "- Disparar a las naves enemigas";
	gotoxy(12,12); cout << "- Evitar ser alcanzado por los enemigos";
	
	gotoxy(10,14); cout << "Controles:";
	gotoxy(12,15); cout << "A -> Mover izquierda";
	gotoxy(12,16); cout << "D -> Mover derecha";
	gotoxy(12,17); cout << "SPACE -> Disparar";
	gotoxy(10,19); cout << "Presiona cualquier tecla para comenzar...";
	getch();
	borrarPantallaConEspacios();
}
void dibujarMarco() {
	textcolor(WHITE);
	
	for (int i = 1; i <= 80; i++) {
		gotoxy(i, 1);  cout << "-";
		gotoxy(i, 24); cout << "-";
	}
	
	for (int i = 1; i <= 24; i++) {
		gotoxy(1, i);  cout << "|";
		gotoxy(80, i); cout << "|";
	}
}

// -------------------------------------------------
void juego() {
	int x = 40;       
	int y = 22;        
	char tecla;
	
	dibujarMarco();
	
	textcolor(LIGHTGREEN);
	gotoxy(x, y);
	cout << "A";          
	
	while (true) {
		if (kbhit()) {
			tecla = getch();
			
			gotoxy(x, y);
			cout << " ";
	
			if ((tecla == 'a' || tecla == 'A') && x > 2) {
				x--;
			}
			if ((tecla == 'd' || tecla == 'D') && x < 79) {
				x++;
			}
			
			if (tecla == 27) {
				break;
			}

			gotoxy(x, y);
			cout << "A";
		}
		
		Sleep(30);  
	}
}

int main() {
	pantallaBienvenida();
	juego();
	return 0;
}
