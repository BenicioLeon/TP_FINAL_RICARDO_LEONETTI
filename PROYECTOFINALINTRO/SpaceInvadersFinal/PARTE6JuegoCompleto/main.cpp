#include <iostream>
#include <windows.h>
#include "conio2.h"
#include <cstdlib>
#include <ctime>


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
	gotoxy(12,17); cout << "SPACEBAR -> Disparar";
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
	
	int puntaje = 0; 
	int vidas = 3; 
	int jugadorX = 40;
	int jugadorY = 22;
	bool balaEnemigaActiva = false;
	int balaEnemigaX, balaEnemigaY;
	
	char tecla;
	bool balaActiva = false;
	int balaX, balaY;
	const int FILAS = 3;
	const int COLUMNAS = 12;
	const int CANT_ENEMIGOS = FILAS * COLUMNAS;
	bool enemigoVivo[CANT_ENEMIGOS]; 
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
			
			enemigoVivo[indice] = true; 
			
			indice++;
		}
	}
	
	int direccion = 1;     
	int contador = 0;
	
	dibujarMarco();
	
	srand(time(NULL));
	
	textcolor(WHITE);
	gotoxy(3, 2);
	cout << "Puntaje: " << puntaje; 
	
	gotoxy(60, 2);
	cout << "Vidas: " << vidas;
	
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
			for (int i = 0; i < CANT_ENEMIGOS; i++) {
				if (enemigoVivo[i] &&
					balaX == ex[i] &&
					balaY == ey[i]) {
					
					enemigoVivo[i] = false;
					balaActiva = false;
					puntaje += 10;
					
					gotoxy(ex[i], ey[i]);
					cout << " ";
					
					textcolor(WHITE);
					gotoxy(12, 2);
					cout << puntaje;
				}
			}
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
		if (!balaEnemigaActiva && rand() % 80 == 0) {
			int i = rand() % CANT_ENEMIGOS;
			if (enemigoVivo[i]) {
				balaEnemigaActiva = true;
				balaEnemigaX = ex[i];
				balaEnemigaY = ey[i] + 1;
			}
		}
		if (balaEnemigaActiva) {
			gotoxy(balaEnemigaX, balaEnemigaY);
			cout << " ";
			
			balaEnemigaY++;
			
			if (balaEnemigaY < 23) {
				textcolor(LIGHTRED);
				gotoxy(balaEnemigaX, balaEnemigaY);
				cout << "!";
			} else {
				balaEnemigaActiva = false;
			}
		}
		if (balaEnemigaActiva &&
			balaEnemigaX == jugadorX &&
			balaEnemigaY == jugadorY) {
			
			balaEnemigaActiva = false;
			vidas--;
			
			textcolor(WHITE);
			gotoxy(67, 2);
			cout << vidas << " ";
			
			if (vidas <= 0) {
				borrarPantallaConEspacios();
				
				textcolor(LIGHTRED);
				gotoxy(30, 10);
				cout << "GAME OVER";
				
				textcolor(WHITE);
				gotoxy(27, 12);
				cout << "Puntaje final: " << puntaje;
				
				gotoxy(22, 15);
				cout << "Presiona una tecla para salir...";
				getch();
				return;
			}
		}
		
		bool victoria = true;
		
		for (int i = 0; i < CANT_ENEMIGOS; i++) {
			if (enemigoVivo[i]) {
				victoria = false;
				break;
			}
		}
		
		if (victoria) {
			borrarPantallaConEspacios();
			
			textcolor(LIGHTGREEN);
			gotoxy(25, 10);
			cout << "FELICIDADES";
			
			gotoxy(18, 12);
			cout << "Derrotaste a todos los enemigos";
			
			textcolor(WHITE);
			gotoxy(22, 15);
			cout << "Puntaje Final: " << puntaje;
			
			gotoxy(18, 18);
			cout << "Presiona una tecla para salir...";
			getch();
			
			return; 
		}
		for (int i = 0; i < CANT_ENEMIGOS; i++) {
			if (enemigoVivo[i] && ey[i] >= jugadorY) {
				
				vidas--;
				textcolor(WHITE);
				gotoxy(67, 2);
				cout << vidas << " ";
				
				if (vidas <= 0) {
					borrarPantallaConEspacios();
					
					textcolor(LIGHTRED);
					gotoxy(30, 10);
					cout << "GAME OVER";
					
					textcolor(WHITE);
					gotoxy(27, 12);
					cout << "Puntaje final: " << puntaje;
					
					gotoxy(22, 15);
					cout << "Presiona una tecla para salir...";
					getch();
					return; 
					
				}
				
				int idx = 0;
				for (int fila = 0; fila < FILAS; fila++) {
					for (int col = 0; col < COLUMNAS; col++) {
						ex[idx] = 10 + col * 4;
						ey[idx] = 4 + fila * 2;
						enemigoVivo[idx] = true;
						idx++;
					}
				}
				
				break; 
			}
		}
		
		for (int i = 0; i < CANT_ENEMIGOS; i++) {
			if (enemigoVivo[i]) {
				gotoxy(ex[i], ey[i]);
				dibujarEnemigo(ex[i], ey[i], tipo[i]);  
			}
		}
		
		Sleep(15);
	}
}


int main() {
	pantallaBienvenida();
	juego();
	return 0;
}

