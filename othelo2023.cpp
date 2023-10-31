#include <iostream>

class Othello {
public:
    Othello() : jugadorActual('*') {
        // Inicializar el tablero utilizando memoria dinámica y punteros
        tablero = new char*[8];
        for (int i = 0; i < 8; i++) {
            tablero[i] = new char[8];
            for (int j = 0; j < 8; j++) {
                tablero[i][j] = ' ';
            }
        }
        tablero[3][3] = '*';
        tablero[3][4] = '-';
        tablero[4][3] = '-';
        tablero[4][4] = '*';

        // Otros miembros de la clase
    }

    ~Othello() {
        // Liberar la memoria dinámica utilizada por el tablero
        for (int i = 0; i < 8; i++) {
            delete[] tablero[i];
        }
        delete[] tablero;
    }

    void jugar() {
        std::cout << "¡Bienvenido a Othello!" << std::endl;

        while (true) {
            dibujarTablero();

            char fila;
            int columna;

            std::cout << "Turno del jugador " << jugadorActual << ". Ingresa tu jugada (por ejemplo, 'C4'): ";
            std::cin >> fila >> columna;

            if (esJugadaValida(fila, columna)) {
                hacerJugada(fila, columna);
                jugadorActual = (jugadorActual == '*') ? '-' : '*';
            } else {
                std::cout << "Jugada inválida. Inténtalo de nuevo." << std::endl;
            }
        }
    }

private:
    char jugadorActual;
    char** tablero;

    bool esJugadaValida(char fila, int columna) {
        int filaIndex = fila - 'A';
        int columnaIndex = columna - 1;

        if (fila < 'A' || fila > 'H' || columna < 1 || columna > 8 || tablero[filaIndex][columnaIndex] != ' ') {
            return false;
        }

        char rival = (jugadorActual == '*') ? '-' : '*';

        bool jugadaValida = false;

        for (int dirX = -1; dirX <= 1; dirX++) {
            for (int dirY = -1; dirY <= 1; dirY++) {
                if (dirX == 0 && dirY == 0) {
                    continue;
                }

                int x = filaIndex + dirX;
                int y = columnaIndex + dirY;
                bool encontradasFichasDelOponente = false;

                while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (tablero[x][y] == rival) {
                        encontradasFichasDelOponente = true;
                    } else if (tablero[x][y] == jugadorActual) {
                        if (encontradasFichasDelOponente) {
                            jugadaValida = true;
                            break;
                        }
                        break;
                    } else {
                        break;
                    }
                    x += dirX;
                    y += dirY;
                }
            }
        }

        return jugadaValida;
    }

    void hacerJugada(char fila, int columna) {
        int filaIndex = fila - 'A';
        int columnaIndex = columna - 1;

        char rival = (jugadorActual == '*') ? '-' : '*';

        tablero[filaIndex][columnaIndex] = jugadorActual;

        for (int dirX = -1; dirX <= 1; dirX++) {
            for (int dirY = -1; dirY <= 1; dirY++) {
                if (dirX == 0 && dirY == 0) {
                    continue;
                }

                int x = filaIndex + dirX;
                int y = columnaIndex + dirY;
                bool encontradasFichasDelOponente = false;

                while (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    if (tablero[x][y] == rival) {
                        encontradasFichasDelOponente = true;
                    } else if (tablero[x][y] == jugadorActual) {
                        if (encontradasFichasDelOponente) {
                            int xx = filaIndex + dirX;
                            int yy = columnaIndex + dirY;

                            while (xx != x || yy != y) {
                                tablero[xx][yy] = jugadorActual;
                                xx += dirX;
                                yy += dirY;
                            }
                        }
                        break;
                    } else {
                        break;
                    }
                    x += dirX;
                    y += dirY;
                }
            }
        }
    }

    void dibujarTablero() {
        std::cout << "  1 2 3 4 5 6 7 8" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << (char)('A' + i) << ' ';
            for (int j = 0; j < 8; j++) {
                std::cout << tablero[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Othello juego;
    juego.jugar();
    return 0;
}