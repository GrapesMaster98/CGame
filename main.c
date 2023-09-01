/* COMENTARIO VARIAS LINEAS
*
* UNIAT PROPE
* FECHA: 31-08-23
* AUTOR: YOMERO
* VERSION: 0.3
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <string.h>

// Función para imprimir mapa
void tablero(short a, short h, short personaje[2], short monstruo[2], short c1x, short c1y, short c2x, short c2y) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < a; x++) {
            if (x == 0 || x == a - 1 || y == 0 || y == h - 1)
                putchar('1');
            else if (x == personaje[0] && y == personaje[1])
                putchar('P');
            else if (x == monstruo[0] && y == monstruo[1])
                putchar('M');
            else if ((x == c1x && y == c1y) || (x == c2x && y == c2y))
                putchar('C');                 
            else
                putchar('0');
        }
        putchar('\n');
    }
}

// Detectar la colision con item
int isTouching(short playerX, short playerY, short c1x, short c1y, short c2x, short c2y) {
    if ((playerX == c1x && playerY == c1y) || (playerX == c2x && playerY == c2y)) {
        return 1;
    } else {
        return 0;
    }
}

void displayMessage(const char *message) {
    clear();
    mvprintw(LINES / 2, (COLS - strlen(message)) / 2, "%s", message);
    refresh();
}

//Función principal
void main()
{
    srand(time(NULL));     //Generación de valor semilla para números aleatorios
     
    initscr();             //Inicializar la terminal para entrada de teclado estándar
    keypad(stdscr, TRUE);     

    short ch;  //Variable para lectura de teclado o entrada
    short score = 0;
    
    //Mapa con dimensiones aleatorias
    short a = rand() % 16 + 5;
    short h = rand() % 16 + 5;

    short personaje[2]={1,1}; //Coordenada inicial del personaje 
    short monstruo[2]={a-2,h-2};  
    
    printf("%d,%d\n",monstruo[0],monstruo[1]);
    
    short c_1x = a-2;  // Coordenada x del ítem 1
    short c_1y = 1;  // Coordenada y del ítem 1
    short c_2x = 1; // Coordenada x del ítem 2
    short c_2y = h-2;  // Coordenada y del ítem 2

    while ( score < 2 && (ch = getch()) != 'q') { 
        
        system("clear");

        switch(ch) {
            case KEY_UP:
                //printw("Tecla de dirección hacia arriba\n");
                personaje[1]--;
                break;
            case KEY_DOWN:
                //printw("Tecla de dirección hacia abajo\n");
                personaje[1]++;
                break;
            case KEY_LEFT:
                //printw("Tecla de dirección hacia la izquierda\n");
                personaje[0]--;
                break;
            case KEY_RIGHT:
                //printw("Tecla de dirección hacia la derecha\n");
                personaje[0]++;
                break;
        }
        
        if (isTouching(personaje[0], personaje[1], c_1x, c_1y, c_2x, c_2y)) {
            score++;
            c_1x = rand() % (a - 2) + 1;
            c_1y = rand() % (h - 2) + 1;
        }
        
        refresh();
        
        tablero(a, h, personaje, monstruo, c_1x, c_1y, c_2x, c_2y);
    }    
    
    if (score == 2) {
        displayMessage("ganaste");
        sleep(2);
    }

    endwin();
 
}
