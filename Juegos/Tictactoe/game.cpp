#include "game.h"
#include "Views/TictactoeUI.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace Tictactoe
{
    /// @brief Tablero global del juego
    char tablero[TAM][TAM];

const int TOTAL_PREGUNTAS = 30;

// Preguntas y opciones del quiz de fútbol
std::string preguntas[TOTAL_PREGUNTAS] = {
"¿Quien gano el Mundial 2022?",
"¿Quien gano el Mundial 2018?",
"¿Cuantos Mundiales tiene Brasil?",
"¿En que pais se jugo el Mundial 2014?",
"¿Quien fue el maximo goleador del Mundial 2022?",
"¿Que seleccion gano el Mundial 2010?",
"¿Quien marco el gol de la final del Mundial 2010?",
"¿Que pais organizo el Mundial 2018?",
"¿Que seleccion gano la Copa America 2021?",
"¿Quien gano la Eurocopa 2024?",
"¿Cuantas Champions League tiene el FC Barcelona?",
"¿Que club gano la Champions League 2024?",
"¿Que club tiene mas Champions League?",
"¿Quien anoto el gol de la victoria en la final de Champions 2024?",
"¿Que equipo elimino al Barcelona en semifinales de Champions 2010?",
"¿Quien fue el maximo goleador historico de la Champions antes de Cristiano?",
"¿Que dorsal uso Messi en el PSG?",
"¿Que dorsal usa Cristiano Ronaldo con Portugal?",
"¿Quien gano el Balon de Oro 2010?",
"¿Quien gano el Balon de Oro 2023?",
"¿Que pais gano la primera Copa del Mundo?",
"¿Cual es el apodo de la seleccion brasilena?",
"¿Quien es el maximo goleador historico del Mundial?",
"¿Que jugador levanto la Copa del Mundo para Argentina en 2022?",
"¿Que pais gano la Eurocopa 2016?",
"¿Que club ficho primero a Cristiano Ronaldo tras salir del Sporting?",
"¿Quien es conocido como O Rei?",
"¿Que seleccion elimino a Brasil en cuartos del Mundial 2022?",
"¿Que jugador marco un triplete en la final del Mundial 2022?",
"¿Que club gano la primera Champions League?"
};

std::string opcionA[TOTAL_PREGUNTAS] = {
"Francia", "Croacia", "4", "Sudafrica", "Lionel Messi",
"Holanda", "David Villa", "Qatar", "Brasil", "Inglaterra",
"4", "Borussia Dortmund", "Milan", "Vinicius Jr.", "Inter de Milan",
"Raul", "10", "7", "Andres Iniesta", "Erling Haaland",
"Argentina", "La Roja", "Ronaldo Nazario", "Di Maria", "Francia",
"Real Madrid", "Garrincha", "Croacia", "Messi", "Milan"
};

std::string opcionB[TOTAL_PREGUNTAS] = {
"Argentina", "Francia", "5", "Brasil", "Julian Alvarez",
"Alemania", "Andres Iniesta", "Rusia", "Argentina", "España",
"5", "Manchester City", "Liverpool", "Rodrygo", "Chelsea",
"Messi", "30", "9", "Xavi", "Lionel Messi",
"Uruguay", "La Canarinha", "Miroslav Klose", "Messi", "Alemania",
"Manchester United", "Ronaldo", "Argentina", "Julian Álvarez", "Barcelona"
};

std::string opcionC[TOTAL_PREGUNTAS] = {
"Brasil", "Belgica", "6", "Rusia", "Kylian Mbappe",
"Brasil", "Fernando Torres", "Alemania", "Chile", "Francia",
"6", "Real Madrid", "Barcelona", "Jude Bellingham", "Arsenal",
"Shevchenko", "19", "10", "Lionel Messi", "Kylian Mbappe",
"Brasil", "La Albiceleste", "Pele", "Otamendi", "Portugal",
"Juventus", "Pele", "Francia", "Kylian Mbappé", "Benfica"
};

std::string opcionD[TOTAL_PREGUNTAS] = {
"Alemania", "Alemania", "7", "Qatar", "Olivier Giroud",
"España", "Xavi", "Francia", "Uruguay", "Italia",
"7", "Bayern Múnich", "Real Madrid", "Dani Carvajal", "Manchester United",
"Benzema", "7", "17", "Wesley Sneijder", "Kevin De Bruyne",
"Italia", "Los Galos", "Messi", "Dibu Martinez", "España",
"Al-Nassr", "Ronaldinho", "Paises Bajos", "Griezmann", "Milan"
};

char respuestaCorrecta[TOTAL_PREGUNTAS] = {
'B','B','B','B','C','D','B','B','B','B',
'B','C','D','A','A','A','B','A','C','B',
'B','B','B','B','C','B','C','A','C','C'
};

bool usada[TOTAL_PREGUNTAS];
int preguntasUsadas = 0;

// === Inicialización del tablero ===

/// @brief Agrega el marco interno del tablero (bordes CP437 en filas/columnas 4,8)
void agregar_marco(){
    for(int i = 0; i < 13; i++){
        tablero[i][4] = 186;
        tablero[i][8] = 186;
        tablero[4][i] = 205;
        tablero[8][i] = 205;
    }
    tablero[4][4] = 206;
    tablero[4][8] = 206;
    tablero[8][4] = 206;
    tablero[8][8] = 206;
}

/// @brief Llena el tablero con espacios en blanco
void llenar_tablero_con_espacios(){
    for(int i = 0; i < 13; i++){
        for(int j = 0; j < 13; j++)
            tablero[i][j] = 32;
    }
}

/// @brief Coloca las etiquetas numéricas (1-9) en las celdas
void agregarNumeros(){
    tablero[2][2]='1'; tablero[2][6]='2'; tablero[2][10]='3';
    tablero[6][2]='4'; tablero[6][6]='5'; tablero[6][10]='6';
    tablero[10][2]='7'; tablero[10][6]='8'; tablero[10][10]='9';
}

/// @brief Inicializa el tablero del juego
void inicializarJuego(){
    llenar_tablero_con_espacios();
    agregar_marco();
    agregarNumeros();
    Common::HideCursor();
}

// === Colocación de fichas ===

/// @brief Coloca una ficha en el tablero
void agregarFicha(char pos, char ficha){
    if(pos=='1') tablero[2][2]=ficha;
    else if(pos=='2') tablero[2][6]=ficha;
    else if(pos=='3') tablero[2][10]=ficha;
    else if(pos=='4') tablero[6][2]=ficha;
    else if(pos=='5') tablero[6][6]=ficha;
    else if(pos=='6') tablero[6][10]=ficha;
    else if(pos=='7') tablero[10][2]=ficha;
    else if(pos=='8') tablero[10][6]=ficha;
    else if(pos=='9') tablero[10][10]=ficha;
}

/// @brief Verifica si una celda está vacía
bool celdaVacia(char tecla){
    if(tecla=='1') return tablero[2][2]=='1';
    if(tecla=='2') return tablero[2][6]=='2';
    if(tecla=='3') return tablero[2][10]=='3';
    if(tecla=='4') return tablero[6][2]=='4';
    if(tecla=='5') return tablero[6][6]=='5';
    if(tecla=='6') return tablero[6][10]=='6';
    if(tecla=='7') return tablero[10][2]=='7';
    if(tecla=='8') return tablero[10][6]=='8';
    if(tecla=='9') return tablero[10][10]=='9';
    return false;
}

// === Detección de victoria ===

/// @brief Verifica si la ficha dada ganó
bool ganar(char ficha){
    if((tablero[2][2]==ficha && tablero[2][6]==ficha && tablero[2][10]==ficha) ||
       (tablero[6][2]==ficha && tablero[6][6]==ficha && tablero[6][10]==ficha) ||
       (tablero[10][2]==ficha && tablero[10][6]==ficha && tablero[10][10]==ficha) ||
       (tablero[2][2]==ficha && tablero[6][2]==ficha && tablero[10][2]==ficha) ||
       (tablero[2][6]==ficha && tablero[6][6]==ficha && tablero[10][6]==ficha) ||
       (tablero[2][10]==ficha && tablero[6][10]==ficha && tablero[10][10]==ficha) ||
       (tablero[2][2]==ficha && tablero[6][6]==ficha && tablero[10][10]==ficha) ||
       (tablero[2][10]==ficha && tablero[6][6]==ficha && tablero[10][2]==ficha))
        return true;
    return false;
}

/// @brief Verifica si el tablero está lleno (empate)
bool tableroLleno(){
    if(tablero[2][2]!='1' && tablero[2][6]!='2' && tablero[2][10]!='3' &&
       tablero[6][2]!='4' && tablero[6][6]!='5' && tablero[6][10]!='6' &&
       tablero[10][2]!='7' && tablero[10][6]!='8' && tablero[10][10]!='9')
        return true;
    return false;
}

// === Turnos ===

/// @brief Movimiento del cursor por teclas de flecha (sin wrap, clamped)
inline void moverCursor(int& cursorPos, std::vector<int>& key) {
    int row = cursorPos / 3;
    int col = cursorPos % 3;
    if (Common::IsKeyArrowTop(key) && row > 0) row--;
    else if (Common::IsKeyArrowBottom(key) && row < 2) row++;
    else if (Common::IsKeyArrowLeft(key) && col > 0) col--;
    else if (Common::IsKeyArrowRight(key) && col < 2) col++;
    cursorPos = row * 3 + col;
}

/// @brief Turno del jugador X en modo original
bool turnoX(int& cursorPos){
    std::vector<int> key;

    // Dibujar una vez al inicio del turno
    DrawBoard(tablero, cursorPos);
    DrawHUD('X', cursorPos, false);
    DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
    std::cout.flush();

    do {
        key = Common::ReadConsoleChar();

        if (Common::IsNavigationKey(key)) {
            moverCursor(cursorPos, key);
            // Redibujar solo lo que cambió
            DrawBoard(tablero, cursorPos);
            DrawHUD('X', cursorPos, false);
            std::cout.flush();
        } else if (Common::IsActionKey(key)) {
            if (celdaVacia('1' + cursorPos)) {
                agregarFicha('1' + cursorPos, 'X');
                DrawBoard(tablero, cursorPos);
                std::cout.flush();
                return true;
            }
            DrawBottomBarWithText("Casilla ocupada \u2014 elige otra");
            std::cout.flush();
            Common::Sleep(1000);
            DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
            std::cout.flush();
        } else if (key == Common::KEY_Q || key == Common::KEY_Q_LOWER || key == Common::KEY_ESCAPE) {
            return false;
        }
    } while (true);
}

/// @brief Turno del jugador O en modo original
bool turnoO(int& cursorPos){
    std::vector<int> key;

    // Dibujar una vez al inicio del turno
    DrawBoard(tablero, cursorPos);
    DrawHUD('O', cursorPos, false);
    DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
    std::cout.flush();

    do {
        key = Common::ReadConsoleChar();

        if (Common::IsNavigationKey(key)) {
            moverCursor(cursorPos, key);
            // Redibujar solo lo que cambió
            DrawBoard(tablero, cursorPos);
            DrawHUD('O', cursorPos, false);
            std::cout.flush();
        } else if (Common::IsActionKey(key)) {
            if (celdaVacia('1' + cursorPos)) {
                agregarFicha('1' + cursorPos, 'O');
                DrawBoard(tablero, cursorPos);
                std::cout.flush();
                return true;
            }
            DrawBottomBarWithText("Casilla ocupada \u2014 elige otra");
            std::cout.flush();
            Common::Sleep(1000);
            DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
            std::cout.flush();
        } else if (key == Common::KEY_Q || key == Common::KEY_Q_LOWER || key == Common::KEY_ESCAPE) {
            return false;
        }
    } while (true);
}

/// @brief Turno del jugador X en modo fútbol
bool turnoFutbolX(int& cursorPos){
    // Dibujar tablero y panel quiz al inicio
    DrawBoard(tablero, cursorPos);
    DrawHUD('X', cursorPos, true);
    DrawQuizPanel();
    DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
    std::cout.flush();

    if(!preguntaFutbol()){
        return true;
    }

    DrawCorrectAnswer();
    DrawSelectCellPrompt();
    std::cout.flush();

    std::vector<int> key;

    do {
        key = Common::ReadConsoleChar();

        if (Common::IsNavigationKey(key)) {
            moverCursor(cursorPos, key);
            DrawBoard(tablero, cursorPos);
            DrawHUD('X', cursorPos, true);
            std::cout.flush();
        } else if (Common::IsActionKey(key)) {
            if (celdaVacia('1' + cursorPos)) {
                agregarFicha('1' + cursorPos, 'X');
                DrawBoard(tablero, cursorPos);
                ClearQuizPanel();
                std::cout.flush();
                return true;
            }
            DrawBottomBarWithText("Casilla ocupada \u2014 elige otra");
            std::cout.flush();
            Common::Sleep(1000);
            DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
            std::cout.flush();
        } else if (key == Common::KEY_Q || key == Common::KEY_Q_LOWER || key == Common::KEY_ESCAPE) {
            return false;
        }
    } while (true);
}

/// @brief Turno del jugador O en modo fútbol
bool turnoFutbolO(int& cursorPos){
    // Dibujar tablero y panel quiz al inicio
    DrawBoard(tablero, cursorPos);
    DrawHUD('O', cursorPos, true);
    DrawQuizPanel();
    DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
    std::cout.flush();

    if(!preguntaFutbol()){
        return true;
    }

    DrawCorrectAnswer();
    DrawSelectCellPrompt();
    std::cout.flush();

    std::vector<int> key;

    do {
        key = Common::ReadConsoleChar();

        if (Common::IsNavigationKey(key)) {
            moverCursor(cursorPos, key);
            DrawBoard(tablero, cursorPos);
            DrawHUD('O', cursorPos, true);
            std::cout.flush();
        } else if (Common::IsActionKey(key)) {
            if (celdaVacia('1' + cursorPos)) {
                agregarFicha('1' + cursorPos, 'O');
                DrawBoard(tablero, cursorPos);
                ClearQuizPanel();
                std::cout.flush();
                return true;
            }
            DrawBottomBarWithText("Casilla ocupada \u2014 elige otra");
            std::cout.flush();
            Common::Sleep(1000);
            DrawBottomBarWithText("Flechas=mover  Enter=colocar  Q=abandonar");
            std::cout.flush();
        } else if (key == Common::KEY_Q || key == Common::KEY_Q_LOWER || key == Common::KEY_ESCAPE) {
            return false;
        }
    } while (true);
}

// === Quiz de fútbol ===

/// @brief Limpia el panel de quiz y redibuja los bordes
void limpiarPanelQuiz(){
    ClearQuizPanel();
    DrawQuizPanel();
}

/// @brief Presenta una pregunta de fútbol y valida la respuesta
/// @return true si respondió correctamente
bool preguntaFutbol(){
    limpiarPanelQuiz();

    if(preguntasUsadas == TOTAL_PREGUNTAS){
        for(int j = 0; j < TOTAL_PREGUNTAS; j++){
            usada[j] = false;
        }
        preguntasUsadas = 0;
    }

    int i;
    do{
        i = rand() % TOTAL_PREGUNTAS;
    } while(usada[i]);

    usada[i] = true;
    preguntasUsadas++;

    const int quizTextX = QuizX() + 2;
    const int quizStartY = QuizY() + 3;  // Después del título
    Common::GoToXY(quizTextX, quizStartY);
    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
    if(preguntas[i].length() <= 38){
        std::cout << preguntas[i];
    } else {
        std::cout << preguntas[i].substr(0, 38);
        Common::GoToXY(quizTextX, quizStartY + 1);
        std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND);
        std::cout << preguntas[i].substr(38);
    }

    Common::GoToXY(quizTextX, quizStartY + 3);
    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << "A) " << opcionA[i];
    Common::GoToXY(quizTextX, quizStartY + 4);
    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << "B) " << opcionB[i];
    Common::GoToXY(quizTextX, quizStartY + 5);
    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << "C) " << opcionC[i];
    Common::GoToXY(quizTextX, quizStartY + 6);
    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << "D) " << opcionD[i];
    std::cout.flush();

    Common::GoToXY(quizTextX, quizStartY + 8);
    std::cout << Common::Color(Common::FOREGROUND_LIGHT, Common::SELECTION_BACKGROUND) << "Respuesta: ";

    char respuesta = Common::Getch();
    respuesta = std::toupper(respuesta);
    std::cout << respuesta;
    std::cout.flush();

    if(respuesta == respuestaCorrecta[i]){
        Common::PlayAudio("correcto.mp3");
        Common::GoToXY(quizTextX, quizStartY + 10);
        std::cout << Common::Color(Common::LIGHT_GREEN, Common::SELECTION_BACKGROUND) << "\u2714 Correcto!";
        std::cout.flush();
        Common::Getch();
        limpiarPanelQuiz();
        return true;
    }

    Common::PlayAudio("incorrecto.mp3");
    Common::GoToXY(quizTextX, quizStartY + 10);
    std::cout << Common::Color(Common::RED, Common::SELECTION_BACKGROUND) << "Incorrecto. Pierdes el turno.";
    std::cout.flush();
    Common::Getch();
    limpiarPanelQuiz();
    return false;
}

// === Orquestación del juego ===

/// @brief Muestra el resultado de la partida
void mostrarResultado(){
    DrawResult();
}

/// @brief Pantalla de victoria para modo fútbol
void victoriaFutbol(){
    DrawVictoryScreen();
}

/// @brief Bucle completo del juego original
void jugarOriginal(){
    int cursorPos = 4;
    inicializarJuego();

    while(true){
        if(!turnoX(cursorPos))
            break;
        if(ganar('X') || tableroLleno())
            break;
        if(!turnoO(cursorPos))
            break;
        if(ganar('O') || tableroLleno())
            break;
    }

    if(ganar('X') || ganar('O') || tableroLleno()){
        DrawResult();
        Common::Sleep(1500);
        DrawVictoryScreen();
    }
}

/// @brief Bucle completo del modo fútbol
void jugarFutbol(){
    int cursorPos = 4;
    inicializarJuego();
    preguntasUsadas = 0;

    for(int i = 0; i < TOTAL_PREGUNTAS; i++){
        usada[i] = false;
    }

    while(true){
        if(!turnoFutbolX(cursorPos))
            break;
        if(ganar('X') || tableroLleno())
            break;
        if(!turnoFutbolO(cursorPos))
            break;
        if(ganar('O') || tableroLleno())
            break;
    }

    if(ganar('X') || ganar('O') || tableroLleno()){
        DrawResult();
        Common::Sleep(1500);
        DrawVictoryScreen();
    }
}

/// @brief Prompt "¿Jugar de nuevo?"
bool jugarNuevamente(){
    DrawPlayAgainPrompt();
    char opcion = Common::Getch();
    opcion = std::toupper(opcion);
    return opcion == 'S';
}

} // namespace Tictactoe
