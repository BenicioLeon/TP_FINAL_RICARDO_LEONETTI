#include <iostream>
#include <windows.h>
#include "conio2.h"

using namespace std;

void borrarPantallaConEspacios() {
	for (int y = 1; y <= 24; y++) {
		for (int x = 1; x <= 80; x++) {
			gotoxy(x, y);
			cout << " ";
		}
	}
}

void pantallaBienvenida() {
	borrarPantallaConEspacios();
	
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
	textcolor(BLUE);
	
	for (int x = 1; x <= 80; x++) {
		gotoxy(x, 1);  cout << "-";
		gotoxy(x, 24); cout << "-";
	}
	
	for (int y = 1; y <= 24; y++) {
		gotoxy(1, y);  cout << "|";
		gotoxy(80, y); cout << "|";
	}
}

void borrarEnemigo(int x, int y) {
	gotoxy(x, y);
	cout << " ";
}

void dibujarEnemigo(int x, int y, int tipo) {
	switch (tipo) {
	case 1:
		textcolor(LIGHTRED);
		cout << "M";
		break;
	case 2:
		textcolor(LIGHTBLUE);
		cout << "W";
		break;
	case 3:
		textcolor(LIGHTGREEN);
		cout << "V";
		break;
	}
}

void juego() {
	int jugadorX = 40;
	int jugadorY = 22;
	char tecla;
	
	bool balaActiva = false;
	int balaX, balaY;
	
	
	const int FILAS = 3;
	const int COLUMNAS = 10;
	const int CANT_ENEMIGOS = FILAS * COLUMNAS;
	
	int ex[CANT_ENEMIGOS];
	int ey[CANT_ENEMIGOS];
	int tipo[CANT_ENEMIGOS];
	
	int indice = 0;
	
	for (int fila = 0; fila < FILAS; fila++) {
		for (int col = 0; col < COLUMNAS; col++) {
			ex[indice] = 10 + col * 4;  
			ey[indice] = 4 + fila * 2; 
			
			if (fila == 0) tipo[indice] = 3;       
			else if (fila == 1) tipo[indice] = 2;
			else tipo[indice] = 1;                 
			
			indice++;
		}
	}
	
	int direccion = 1;     
	int contador = 0;
	
	dibujarMarco();
	
	textcolor(LIGHTGREEN);
	gotoxy(jugadorX, jugadorY);
	cout << "A";
	
	while (true) {
		
		if (kbhit()) {
			tecla = getch();
			
			gotoxy(jugadorX, jugadorY);
			cout << " ";
			
			if ((tecla == 'a' || tecla == 'A') && jugadorX > 2)
				jugadorX--;
			
			if ((tecla == 'd' || tecla == 'D') && jugadorX < 79)
				jugadorX++;
			
			if (tecla == ' ' && !balaActiva) {
				balaActiva = true;
				balaX = jugadorX;
				balaY = jugadorY - 1;
			}
			
			if (tecla == 27)
				break;
			
			textcolor(LIGHTGREEN);
			gotoxy(jugadorX, jugadorY);
			cout << "A";
		}
		
		if (balaActiva) {
			gotoxy(balaX, balaY);
			cout << " ";
		}
	
		if (balaActiva) {
			balaY--;
			
			if (balaY <= 2)
				balaActiva = false;
		}
		
		if (balaActiva) {
			textcolor(YELLOW);
			gotoxy(balaX, balaY);
			cout << "|";
		}
		
		for (int i = 0; i < CANT_ENEMIGOS; i++) {
			borrarEnemigo(ex[i], ey[i]);
		}
		
		contador++;
		
		if (contador >= 6) {
			bool bajar = false;
			
			for (int i = 0; i < CANT_ENEMIGOS; i++) {
				if (ex[i] >= 78 && direccion == 1) bajar = true;
				if (ex[i] <= 2  && direccion == -1) bajar = true;
			}
			
			if (bajar) {
				direccion *= -1;
				for (int i = 0; i < CANT_ENEMIGOS; i++) {
					ey[i]++;
				}
			} else {
				for (int i = 0; i < CANT_ENEMIGOS; i++) {
					ex[i] += direccion;
				}
			}
			
			contador = 0;
		}
		
		for (int i = 0; i < CANT_ENEMIGOS; i++) {
			gotoxy(ex[i], ey[i]);
			dibujarEnemigo(ex[i], ey[i], tipo[i]);
		}
		
		Sleep(15);
	}
}

// -------------------------------------------------
int main() {
	pantallaBienvenida();
	juego();
	return 0;
}
