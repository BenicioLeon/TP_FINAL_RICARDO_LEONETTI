#include<iostream>
#include<ctime>
#include "conio2.h"

using namespace std;

void limpiarPantalla() {
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
	gotoxy(12,15); cout << "a -> Mover izquierda";
	gotoxy(12,16); cout << "d -> Mover derecha";
	gotoxy(12,17); cout << "SPACE -> Disparar";
	gotoxy(10,19); cout << "Presiona cualquier tecla para comenzar...";
	getch();
	limpiarPantalla();
}

int main() {
	pantallaBienvenida();

	return 0;
}




