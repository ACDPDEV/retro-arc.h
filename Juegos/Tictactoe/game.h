#pragma once

// 1. Librerías estándar
#include <string>

// 2. Librerías propias (jerarquía + orden alfabético)
#include "../../Common/Color.h"
#include "../../Common/Music.h"
#include "../../Common/Terminal.h"
#include "../../Common/UnicodeGlyphs.h"

namespace Tictactoe
{
    /// @brief Dimensión del tablero (arreglo 13x13)
    const int TAM = 13;
    /// @brief Tablero global del juego
    extern char tablero[TAM][TAM];

    // === Funciones de lógica ===

    /// @brief Inicializa el tablero con bordes y números
    void inicializarJuego();
    /// @brief Llena el tablero con espacios en blanco
    void llenar_tablero_con_espacios();
    /// @brief Agrega el marco interno del tablero (bordes en filas/columnas 3,7)
    void agregar_marco();
    /// @brief Coloca las etiquetas numéricas (1-9) en las celdas de la grilla 3x3
    void agregarNumeros();
    /// @brief Coloca una ficha en el tablero
    /// @param pos Tecla de posición ('1'-'9')
    /// @param ficha Carácter de la ficha ('X' o 'O')
    void agregarFicha(char pos, char ficha);
    /// @brief Verifica si una celda del tablero está vacía
    /// @param tecla Tecla de posición ('1'-'9')
    /// @return true si la celda aún contiene su etiqueta numérica
    bool celdaVacia(char tecla);

    /// @brief Verifica si la ficha dada ganó
    /// @param ficha Carácter de la ficha a verificar ('X' o 'O')
    /// @return true si esa ficha tiene tres en línea
    bool ganar(char ficha);
    /// @brief Verifica si el tablero está lleno (empate)
    /// @return true si las 9 celdas están ocupadas
    bool tableroLleno();

    // === Funciones de turno ===

    /// @brief Turno del jugador X en modo original
    /// @return true si colocó ficha, false si abandonó
    bool turnoX(int& cursorPos);
    /// @brief Turno del jugador O en modo original
    /// @return true si colocó ficha, false si abandonó
    bool turnoO(int& cursorPos);
    /// @brief Turno del jugador X en modo fútbol (incluye quiz)
    /// @return true si colocó ficha, false si abandonó
    bool turnoFutbolX(int& cursorPos);
    /// @brief Turno del jugador O en modo fútbol (incluye quiz)
    /// @return true si colocó ficha, false si abandonó
    bool turnoFutbolO(int& cursorPos);
    /// @brief Flujo de pregunta del quiz para modo fútbol
    /// @return true si respondió correctamente, false en caso contrario
    bool preguntaFutbol();

    // === Orquestación del juego ===

    /// @brief Bucle completo del juego original
    void jugarOriginal();
    /// @brief Bucle completo del modo fútbol
    void jugarFutbol();
    /// @brief Prompt "¿Jugar de nuevo?" y lectura de input
    /// @return true si el jugador quiere jugar de nuevo
    bool jugarNuevamente();
}
