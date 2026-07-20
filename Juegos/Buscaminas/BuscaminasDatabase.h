#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <ctime>
#include <cstdlib>

namespace Buscaminas
{
    // ======================================================================
    // DATABASE
    // ======================================================================

    /**
     * Crea e inicializa el tablero de fondo con un caracter por defecto.
     * @param rows Número de filas.
     * @param cols Número de columnas.
     * @return Un tablero (Board) inicializado.
     */
    std::vector<std::vector<int>> CreateBackgroundBoard(int rows, int cols) 
    {
        
        std::vector<std::vector<int>> board(rows, std::vector<int>(cols, 0));
        
        return board;
    }

    /**
     * Ubica una cantidad específica de minas (representadas por el número 9)
     * de manera aleatoria en el tablero de fondo.
     * @param board Referencia al tablero de enteros.
     * @param minesQuantity Cantidad de minas a colocar.
     */
    void PlaceMines(std::vector<std::vector<int>>& board, int minesQuantity) 
    {
        int rows = board.size();
        int cols = board[0].size();
        int placedMines = 0;

        while (placedMines < minesQuantity) {
            int randomRow = rand() % rows;
            int randomCol = rand() % cols;

            if (board[randomRow][randomCol] != 9) {
                board[randomRow][randomCol] = 9;
                placedMines++;
            }
        }
    }

    /**
     * Recorre el tablero y calcula para cada celda vacía la cantidad de minas (9)
     * que tiene a su alrededor en las 8 direcciones posibles.
     * @param board Referencia al tablero de fondo.
     */
    void CountAdjacentMines(std::vector<std::vector<int>>& board) 
    {
        int rows = board.size();
        int cols = board[0].size();

        // Recorremos cada celda del tablero
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                
                // Si la celda actual es una mina, no necesitamos calcular nada para ella
                if (board[r][c] == 9) {
                    continue;
                }

                int mineCount = 0;

                // Escaneamos las 8 celdas de alrededor usando desplazamientos (-1, 0, 1)
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        
                        int neighborRow = r + i;
                        int neighborCol = c + j;

                        // Verificar que el vecino esté dentro de los límites del tablero
                        if (neighborRow >= 0 && neighborRow < rows && neighborCol >= 0 && neighborCol < cols) {

                            if (board[neighborRow][neighborCol] == 9) {
                                mineCount++;
                            }
                        }
                        
                    }
                }

                // Guardamos el total de minas encontradas en la celda central
                board[r][c] = mineCount;
            }
        }
    }

}
