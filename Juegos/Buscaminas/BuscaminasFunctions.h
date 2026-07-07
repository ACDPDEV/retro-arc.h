#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <ctime>
#include <cstdlib>
#include "../../Common/Navigation.h"
#include "../../Common/Consts.h"
#include "../../Common/Output.h"

namespace Minesweeper
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

    // ======================================================================
    // LOGICA
    // ======================================================================
    /*
        VALORES DE CADA ESTADO:

        Previos: (EN DESUSO, VERIFICAR SI NO EXISTE CODIGO QUE USA ESTOS VALORES)
            0: Celda oculta (Hidden).

            1: Celda descubierta (Revealed).

            2: Celda con bandera (Flagged).

        Actuales:
            -2:   Celda con bandera (Flagged)
            -1:   Celda oculta (Hidden)
            0:    Celda segura (Valor 0)
            1-8:  Celda adyacente a una mina
            9:    Celda con una mina 


    */

    /**
     * @brief Determina la cantidad de minas según la cantidad de celdas y el nivel
     * @param rows Cantidad de filas que tiene el tablero
     * @param cols Cantidad de columnas que tiene el tablero
     * @returns La cantidad de minas a ubicar en el tablero
     */
    int SetMinesQuantity(int rows, int cols, int levelOption)
    {
        std::vector<double> factors = {0.125, 0.168, 0.208};

        if(levelOption >= factors.size())
            levelOption = factors.size() - 1;

        int minesQuantity = rows * cols * factors[levelOption];
        return minesQuantity;
    }

    int SetInitialFlagCount(int minesQuantity)
    {
        if(minesQuantity > 10)
        {
            return 10;
        }
        else
        {
            minesQuantity;
        }
    }

    /**
     * @brief Determina la cantidad de filas de acuerdo al nivel
     * @param levelOption Nivel seleccionado
     * @returns La cantidad de filas del tablero para ese nivel
     */
    int SetRowsByLevel(int levelOption)
    {
        int rows;
        switch (levelOption)
        {
        case 0:
            rows = 9;
            break;
        case 1:
            rows = 16;
            break;
        case 2:
            rows = 16;
            break;
        
        default:
            rows = 16;
            break;
        }
        return rows;
    }

    /**
     * @brief Determina la cantidad de columnas de acuerdo al nivel
     * @param levelOption Nivel seleccionado
     * @returns La cantidad de columnas del tablero para ese nivel
     */
    int SetColsByLevel(int levelOption)
    {
        int cols;
        switch (levelOption)
        {
        case 0:
            cols = 9;
            break;
        case 1:
            cols = 16;
            break;
        case 2:
            cols = 30;
            break;
        
        default:
            cols = 30;
            break;
        }
        return cols;
    }

    /**
     * Crea e inicializa el tablero de estados con puros ceros (todas las celdas ocultas).
     * @param rows cantidad de filas del tablero
     * @param cols cantidad de columnas del tablero
     * @return Un tablero (Board) inicializado.
     */
    std::vector<std::vector<int>> CreatePageStateBoard(int rows, int cols) 
    {
        std::vector<std::vector<int>> stateBoard(rows, std::vector<int>(cols, -1));
        return stateBoard;
    }

    /**
     * @brief Determina la posicion inicial del jugador.
     * @param rows cantidad de filas del tablero
     * @param cols cantidad de columnas del tablero
     * @return posición inicial {fila, columna}
     */
    std::array<int, 2> GetInitialPosition(int rows, int cols)
    {
        std::array<int, 2> position;
        position[0] = rows / 2;
        position[1] = cols / 2;

        return position;
    }

    int GetStateValueSafe()
    {
        return 0;
    }

    int GetStateValueFlagged()
    {
        return -2;
    }

    int GetStateValueHidden()
    {
        return -1;
    }

    /**
     * @brief Determina si el valor es equivalente a "oculto" dentro del State Board
     * @param stateValue El valor a evaluar
     * @return true si el valor es equivalente a "oculto"
     */
    bool StateValueIsHidden(int stateValue)
    {
        return stateValue == GetStateValueHidden();
    }

    /**
     * @brief Determina si el valor es equivalente a "con bandera" dentro del State Board
     * @param stateValue El valor a evaluar
     * @return true si el valor es equivalente a "con bandera"
     */
    bool StateValueIsFlagged(int stateValue)
    {
        return stateValue == GetStateValueFlagged();
    }

    /**
     * @brief Determina si el valor es equivalente a un valor revelado (SEGURO o ADYACENTE) dentro del State Board
     * @param stateValue El valor a evaluar
     * @return true si el valor es equivalente a revelado (SEGURO o ADYACENTE)
     */
    bool StateValueIsRevealed(int stateValue)
    {
        return -1 < stateValue && stateValue < 9;
    }

    int GetBackGroundValueSafe()
    {
        return 0;
    }

    /**
     * @brief Determina si el valor es equivalente a un valor "SEGURO" dentro del State Board
     * @param value El valor a evaluar
     * @return true si el valor es equivalente a "SEGURO"
     */
    bool BackgroundValueIsSafe(int backgroundValue)
    {
        return backgroundValue == 0;
    }

    bool BackGroundValueIsAdjacent(int backgroundValue)
    {
        return 0 < backgroundValue && backgroundValue < 9;
    }

    /**
     * @brief Ejecuta la acción de revelar según el estado de la celda (oculto, con bandera o mostrado)
     * @param backgroundBoard Tablero que contiene a las minas
     * @param stateBoard Tablero que mantiene los estados de visualización del tablero
     * @param row Fila en la que se encuentra el jugador
     * @param col Columna en la que se encuenta el jugador
     */
    void RevealSafeRegionCommand(
        std::vector<std::vector<int>> backgroundBoard, 
        std::vector<std::vector<int>>& stateBoard, 
        int playerRow, 
        int playerCol, 
        std::string& feedbackMessage)
    {
        int maxRow = backgroundBoard.size() - 1;
        int maxCol = backgroundBoard[0].size() - 1;
        std::vector<std::tuple<int, int>> safeCords = {{playerRow, playerCol}};

        while(!safeCords.empty())
        {
            int row, col;
            std::tie(row, col) = safeCords.back();
            safeCords.pop_back();

            // Escaneamos el cuadrante de 3x3 alrededor de la celda vacía actual
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int scanRow = row + i;
                    int scanCol = col + j;
                    
                    // Validar límites del tablero
                    if(0 <= scanRow && scanRow <= maxRow && 0 <= scanCol && scanCol <= maxCol)
                    {
                        // Solo interactuamos con celdas que estén estrictamente ocultas
                        if(StateValueIsHidden(stateBoard[scanRow][scanCol]))
                        {
                            // Caso A: El vecino es un '0' (Safe) -> Se revela y se sigue expandiendo
                            if(backgroundBoard[scanRow][scanCol] == GetBackGroundValueSafe())
                            {
                                stateBoard[scanRow][scanCol] = GetStateValueSafe(); 
                                safeCords.push_back({scanRow, scanCol});
                            }
                            // Caso B: El vecino es un número (1-8) -> Se revela su número, pero NO se expande
                            else if(BackGroundValueIsAdjacent(backgroundBoard[scanRow][scanCol]))
                            {
                                stateBoard[scanRow][scanCol] = backgroundBoard[scanRow][scanCol];
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Ejecuta la acción de revelar según el estado de la celda (oculto, con bandera o mostrado)
     * @param backgroundBoard Tablero que contiene a las minas
     * @param stateBoard Tablero que mantiene los estados de visualización del tablero
     * @param row Fila en la que se encuentra el jugador
     * @param col Columna en la que se encuenta el jugador
     */
    void RevealCommand(
        std::vector<std::vector<int>> backgroundBoard, 
        std::vector<std::vector<int>>& stateBoard, 
        int row, 
        int col, 
        std::string& feedbackMessage)
    {
        int backgroundValue = backgroundBoard[row][col];
        int stateValue = stateBoard[row][col];

        if(stateValue < -2 || 9 < stateValue)
        {
            feedbackMessage = "Error al revelar (RevealCommand)";
            return;
        }
        
        if(StateValueIsRevealed(stateValue))
        {
            feedbackMessage = "Esa celda ya está revelada";
        }
        else if(StateValueIsFlagged(stateValue))
        {
            feedbackMessage = "Quita la bandera para revelar";
        }
        else if(BackgroundValueIsSafe(backgroundValue))
        {
            RevealSafeRegionCommand(backgroundBoard, stateBoard, row, col, feedbackMessage);
            feedbackMessage = "";
        }
        else
        {
            stateBoard[row][col] = backgroundBoard[row][col];
            feedbackMessage = "";
        }
    }

    bool MineIsRevealed(std::vector<std::vector<int>> backgroundBoard, int row, int col, std::string& feedbackMessage)
    {
        return backgroundBoard[row][col] == 9;
    }

    /**
     * @brief Verifica si la tecla presionada corresponde a una tecla de movimiento (navegación).
     * * @param key Referencia al vector que contiene los bytes de la tecla presionada.
     * @return true Si la tecla es una tecla de navegación válida.
     * @return false En caso contrario.
     */
    bool IsMoveKey(std::vector<int>& key)
    {
        if(Common::IsNavigationKey(key))
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Verifica si la tecla presionada corresponde a la acción de revelar una casilla.
     * * Detecta tanto la 'R' mayúscula como la 'r' minúscula.
     * * @param key Referencia al vector que contiene los bytes de la tecla presionada.
     * @return true Si la tecla es 'R' o 'r'.
     * @return false En caso contrario.
     */
    bool IsRevealKey(std::vector<int>& key)
    {
        if(key == Common::KEY_R || key == Common::KEY_R_LOWER)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Verifica si la tecla presionada corresponde a la acción de colocar/quitar una bandera (flag).
     * * Detecta tanto la 'B' mayúscula como la 'b' minúscula.
     * * @param key Referencia al vector que contiene los bytes de la tecla presionada.
     * @return true Si la tecla es 'B' o 'b'.
     * @return false En caso contrario.
     */
    bool IsFlagKey(std::vector<int>& key)
    {
        if(key == Common::KEY_B || key == Common::KEY_B_LOWER)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Verifica si la tecla presionada corresponde a la acción de salir de la partida actual.
     * * Detecta la tecla Escape (ESC), así como 'Q' mayúscula o 'q' minúscula (Quit).
     * * @param key Referencia al vector que contiene los bytes de la tecla presionada.
     * @return true Si la tecla es ESC, 'Q' o 'q'.
     * @return false En caso contrario.
     */
    bool IsExitMatchKey(std::vector<int>& key)
    {
        if(key == Common::KEY_ESCAPE || key == Common::KEY_Q || key == Common::KEY_Q_LOWER)
        {
            return true;
        }
        return false;
    }

    /**
     * @brief Actualiza la posición del jugador (fila y columna) en el tablero según la flecha de dirección presionada.
     * * Maneja los límites de la matriz permitiendo un efecto de "bucle" o "envoltura" (vuelve al extremo opuesto al salir de los bordes).
     * @param playerRow Referencia a la fila actual del jugador (se modifica internamente).
     * @param playerCol Referencia a la columna actual del jugador (se modifica internamente).
     * @param rows Número total de filas del tablero.
     * @param cols Número total de columnas del tablero.
     * @param key Referencia al vector que contiene los bytes de la tecla presionada.
     */
    void MoveCommand(int& playerRow, int& playerCol, int rows, int cols, std::vector<int>& key)
    {
        if(Common::IsKeyArrowTop(key))
        {
            if(playerRow > 0)
                --playerRow;
            else
                playerRow = rows;
        }
        else if(Common::IsKeyArrowLeft(key))
        {
            if(playerCol > 0)
                --playerCol;
            else
                playerCol = cols;
        }
        else if(Common::IsKeyArrowBottom(key))
        {
            if(playerRow < rows -1)
                ++playerRow;
            else
                playerRow = 0;
        }
        else if(Common::IsKeyArrowRight(key))
        {
            if(playerCol < cols-1)
                ++playerCol;
            else
                playerCol = 0;
        }
    }

    void FlagCommand(
        int& flagCount,
        std::vector<std::vector<int>>& stateBoard, 
        int row, 
        int col, 
        std::string& feedbackMessage
    )
    {
        int stateValue = stateBoard[row][col];
        if(!StateValueIsHidden(stateValue))
        {
            feedbackMessage = "No puedes poner una bandera allí";
            Common::PrintFeedBackMessage();
        }
        else if (StateValueIsFlagged(stateValue))
        {
            stateBoard[row][col] = GetStateValueHidden();
            ++flagCount;
        }
        else
        {
            if(flagCount >0)
            {
                stateBoard[row][col] = GetStateValueFlagged();
            }
            else
            {
                feedbackMessage = "¡Ya no tienes banderas!";
                Common::PrintFeedBackMessage();
            }
        }
        
    }

    /**
     * @brief Evalúa si el estado actual del tablero representa una partida ganada.
     * * La victoria se determina si el número de casillas reveladas que no son minas 
     * es exactamente igual al total de casillas seguras que tiene el tablero.
     * * @param stateBoard Referencia a la matriz (vector de vectores) que representa el estado actual del tablero de juego.
     * @param minesQuantity Cantidad total de minas ocultas en el tablero.
     * @return true Si el jugador ha revelado todas las casillas seguras (victoria).
     * @return false Si aún quedan casillas seguras por revelar.
     */
    bool IsWonGameState(std::vector<std::vector<int>>& stateBoard, int minesQuantity)
    {
        int totalCells = stateBoard.size() * stateBoard[0].size();
        int nonMineCells = totalCells - minesQuantity;
        int countNonMine = 0;
        int hiddenValue = GetStateValueHidden();
        int mineValue = 9;
        for(auto& row : stateBoard)
        {
            for(int& cell : row)
            {
                if(cell != hiddenValue && cell != mineValue)
                {
                    ++countNonMine;
                }
            }
        }

        return countNonMine == nonMineCells;
    }

    // ======================================================================
    // VISTA --- 200 x 60
    // ======================================================================
}
