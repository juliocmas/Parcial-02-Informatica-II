#include <iostream>
#include <ctime>
#include <fstream>  // Para trabajar con archivos

class Othello {
public:
    Othello() : jugadorActual('*'), juegoTerminado(false) {
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

        std::cout << "Ingrese Nombre jugador (*): ";
        std::cin >> nombreJugador[0];
        std::cout << "Ingrese Nombre Jugador (-): ";
        std::cin >> nombreJugador[1];

        // Inicializar el juego
        jugadorSinMovimientos[0] = false;
        jugadorSinMovimientos[1] = false;
        contarFichas();
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

        while (!juegoTerminado) {
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

            verificarMovimientosPosibles();
        }

        // Mostrar los resultados una vez que el juego haya terminado
        mostrarResultados();
    }

private:
    char jugadorActual;
    char** tablero;
    std::string nombreJugador[2];  // Para almacenar los nombres de los jugadores
    bool jugadorSinMovimientos[2];  // Para rastrear si un jugador no tiene movimientos
    bool juegoTerminado;  // Para rastrear si el juego ha terminado

    void verificarMovimientosPosibles() {
        jugadorSinMovimientos[0] = true;
        jugadorSinMovimientos[1] = true;

        // Iterar a través del tablero para verificar movimientos posibles
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (tablero[i][j] == ' ') {
                    if (esJugadaValida(static_cast<char>('A' + i), j + 1)) {
                        jugadorSinMovimientos[0] = false;
                        jugadorSinMovimientos[1] = false;
                        return;  // Se encontró al menos un movimiento válido
                    }
                }
            }
        }

        if (jugadorSinMovimientos[0] && jugadorSinMovimientos[1]) {
            // Ambos jugadores no tienen movimientos posibles, el juego ha terminado
            juegoTerminado = true;
        }
    }

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

    void contarFichas() {
        int fichasJugador1 = 0;
        int fichasJugador2 = 0;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (tablero[i][j] == '*') {
                    fichasJugador1++;
                } else if (tablero[i][j] == '-') {
                    fichasJugador2++;
                }
            }
        }

        std::cout << "Fichas de " << nombreJugador[0] << " (*): " << fichasJugador1 << std::endl;
        std::cout << "Fichas de " << nombreJugador[1] << " (-): " << fichasJugador2 << std::endl;
    }

    void mostrarResultados() {
        std::cout << "Fecha de Partida: " << obtenerFechaActual() << std::endl;
        std::cout << "Hora de Partida: " << obtenerHoraActual() << std::endl;

        // Contar las fichas de cada jugador
        int fichasJugador1 = contarFichasJugador('*');
        int fichasJugador2 = contarFichasJugador('-');
        std::cout << "Fichas de " << nombreJugador[0] << " (*): " << fichasJugador1 << std::endl;
        std::cout << "Fichas de " << nombreJugador[1] << " (-): " << fichasJugador2 << std::endl;

        // Determina y muestra el ganador
        if (fichasJugador1 > fichasJugador2) {
            std::cout << "Ganador " << nombreJugador[0] << " (*)" << std::endl;
        } else if (fichasJugador2 > fichasJugador1) {
            std::cout << "Ganador " << nombreJugador[1] << " (-)" << std::endl;
        } else {
            std::cout << "Empate, no hay ganador" << std::endl;
        }

        // Guardar los resultados en un archivo
        guardarResultados(fichasJugador1, fichasJugador2);
    }

    std::string obtenerFechaActual() {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d", now);
        return buffer;
    }

    std::string obtenerHoraActual() {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        char buffer[80];
        strftime(buffer, 80, "%H:%M:%S", now);
        return buffer;
    }

    bool tableroLleno() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (tablero[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    int contarFichasJugador(char ficha) {
        int contador = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (tablero[i][j] == ficha) {
                    contador++;
                }
            }
        }
        return contador;
    }

    void guardarResultados(int fichasJugador1, int fichasJugador2) {
        std::ofstream resultados("resultados.txt", std::ios::app);

        if (resultados.is_open()) {
            resultados << "Fecha de Partida: " << obtenerFechaActual() << std::endl;
            resultados << "Hora de Partida: " << obtenerHoraActual() << std::endl;
            resultados << "Fichas de " << nombreJugador[0] << " (*): " << fichasJugador1 << std::endl;
            resultados << "Fichas de " << nombreJugador[1] << " (-): " << fichasJugador2 << std::endl;

            if (fichasJugador1 > fichasJugador2) {
                resultados << "Ganador " << nombreJugador[0] << " (*)" << std::endl;
            } else if (fichasJugador2 > fichasJugador1) {
                resultados << "Ganador " << nombreJugador[1] << " (-)" << std::endl;
            } else {
                resultados << "Empate, no hay ganador" << std::endl;
            }

            resultados << std::endl;  // Separador entre partidas
            resultados.close();
        } else {
            std::cerr << "No se pudo abrir el archivo para guardar los resultados." << std::endl;
        }
    }
};

int main() {
    Othello juego;
    juego.jugar();
    return 0;
}
