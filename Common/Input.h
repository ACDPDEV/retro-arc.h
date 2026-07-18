/// @file Input.h
/// @brief Utilidades de entrada y parsing cross-platform.
/// @details Usa Terminal.h (Kbhit/Getch) para abstracción Windows/Linux.
///          Prove: Validate, ParseInt, ParseIntStrict, ParseFloat, ParseChar, ParseBool,
///          Input (cin >>), TryInput (no bloqueante con backspace/echo).
///          Funciones marcadas `inline` para uso header-only.
#pragma once

#include <string>
<<<<<<< HEAD
#include
#include "Terminal.h"

using namespace std;
=======
#include <vector>
#include <tuple>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include "Terminal.h"
#include "Consts.h"

namespace Common {
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

/// @brief Valida si una entrada coincide con un tipo esperado
/// @param input String a validar
/// @param type Tipo esperado: "int", "float", "string", "char", "bool"
/// @return true si la entrada es válida para el tipo, false en caso contrario
<<<<<<< HEAD
inline bool Validate(string input, string type) {
    if (type == "int") {
        return isdigit(input[0]);
    } else if (type == "float") {
        return isdigit(input[0]) || input[0] == '.';
    } else if (type == "string") {
        return true;
    } else if (type == "char") {
        return isalpha(input[0]);
=======
inline bool Validate(std::string input, std::string type) {
    if (type == "int") {
        return std::isdigit(input[0]);
    } else if (type == "float") {
        return std::isdigit(input[0]) || input[0] == '.';
    } else if (type == "string") {
        return true;
    } else if (type == "char") {
        return std::isalpha(input[0]);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    } else if (type == "bool") {
        return input == "true" || input == "false";
    }
    return false;
}

/// @brief Convierte string a int
/// @param str String a convertir
/// @return Valor entero (lanza excepción si no es válido)
<<<<<<< HEAD
inline int ParseInt(string str) {
    return stoi(str);
=======
inline int ParseInt(std::string str) {
    return std::stoi(str);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}

/// @brief Convierte string a int con validación estricta (sin decimales, notación científica, ni comas)
/// @param str String a convertir (solo dígitos, opcionalmente signo + o - al inicio)
/// @return Valor entero
/// @throws invalid_argument si contiene '.', ',', 'e', 'E' o no es un entero válido
/// @details A diferencia de ParseInt(), rechaza "1.5", "1,000", "1e3", "1E3", "10."
<<<<<<< HEAD
inline int ParseIntStrict(string str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.' || str[i] == ',' || str[i] == 'e' || str[i] == 'E') throw invalid_argument("No es un entero válido");
    }
    return stoi(str);
=======
inline int ParseIntStrict(std::string str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.' || str[i] == ',' || str[i] == 'e' || str[i] == 'E') throw std::invalid_argument("No es un entero válido");
    }
    return std::stoi(str);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}

/// @brief Convierte string a float
/// @param str String a convertir
/// @return Valor flotante (lanza excepción si no es válido)
<<<<<<< HEAD
inline float ParseFloat(string str) {
    return stof(str);
=======
inline float ParseFloat(std::string str) {
    return std::stof(str);
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}

/// @brief Convierte string a char (primer carácter)
/// @param str String a convertir
/// @return Primer carácter
<<<<<<< HEAD
inline char ParseChar(string str) {
=======
inline char ParseChar(std::string str) {
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    return str[0];
}

/// @brief Convierte string a bool
/// @param str String a convertir: "true"/"false" o "1"/"0"
/// @return true si "true" o "1", false si "false" o "0"
/// @throws invalid_argument si el string no es un bool válido
<<<<<<< HEAD
inline bool ParseBool(string str) {
    if (str == "true" || str == "1") return true;
    if (str == "false" || str == "0") return false;
    throw invalid_argument("Invalid bool string");
=======
inline bool ParseBool(std::string str) {
    if (str == "true" || str == "1") return true;
    if (str == "false" || str == "0") return false;
    throw std::invalid_argument("Invalid bool string");
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
}

/// @brief Lee una palabra desde stdin (hasta espacio o salto de línea)
/// @return Palabra leída
<<<<<<< HEAD
inline string Input() {
    string line;
    cin >> line;
=======
inline std::string Input() {
    std::string line;
    std::cin >> line;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    return line;
}

/// @brief Intenta leer una línea completa de forma no bloqueante
/// @param[out] line Línea completa leída al presionar Enter
/// @return true si se completó la línea (se presionó Enter), false si no hay entrada lista
/// @details Maneja backspace y eco en pantalla. Usar en bucle para input interactivo.
<<<<<<< HEAD
inline bool TryInput(string& line) {
    static string buffer;
=======
inline bool TryInput(std::string& line) {
    static std::string buffer;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08

    while (Kbhit()) {
        char c = Getch();

        switch (c) {
            case '\r': // Enter
                line = buffer;
                buffer.clear();
                return true;

            case '\b': // Backspace
                if (!buffer.empty()) {
                    buffer.pop_back();
<<<<<<< HEAD
                    cout << "\b \b";
=======
                    std::cout << "\b \b";
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
                }
                break;

            default:
                if (c >= 32 && c <= 126) { // Caracteres imprimibles
                    buffer += c;
<<<<<<< HEAD
                    cout << c; // Eco en pantalla
                }
                break;
        }
=======
                    std::cout << c; // Eco en pantalla
                }
                break;
        }
        return false;
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
    }

    return false;
}
<<<<<<< HEAD
=======


/**
 * @brief Valida que un caracter de 1 Byte esté entre al menos uno de los rangos permitidos
 * @param validCharRanges Rangos de caracteres válidos tuple<minimo, maximo>
 * @param character El número del caracter que se quiere evaluar
 * @returns true si el caracter está entre al menos uno de los rangos permitidos (inclusivo)
 */
inline bool IsValidChar(std::vector<std::tuple<int, int>>& validCharRanges, int character)
{
    for (const auto& range : validCharRanges)
    {
        int min, max;
        std::tie(min, max) = range;
        if(min <= character && character <= max)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica si un carácter específico se encuentra dentro de una lista de caracteres válidos.
 * * @param validChars Referencia a una vector que contiene los caracteres permitidos.
 * @param character Referencia al vector de enteros que representa el carácter en bytes que se desea validar.
 * @return true Si el carácter coincide con alguno de la lista de caracteres válidos.
 * @return false Si el carácter no es válido.
 */
inline bool IsValidChar(std::vector<std::vector<int>>& validChars, std::vector<int>& character)
{
    for (auto& validChar : validChars)
    {
        if(validChar == character)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Lee una tecla presionada por el usuario y devuelve el código de caracter que representa
 * @param validCharRanges Rango de caracteres permitidos para lectura
 * @returns El código del último byte del caracter o -1 si es un caracter no permitido
 */
inline int ReadConsoleChar(std::vector<std::tuple<int, int>>& validCharRanges)
{
    int key;

    key = Getch();

    // Compara con AND lógico bit a bit para validar si es un caracter de 2 bytes
    if((key & 0b11100000) == 0b11000000)
    {
        key = Getch();
    }

    if (IsValidChar(validCharRanges, key))
    {
        return key;
    }
    else
    {
        return -1;
    }
}

/**
 * @brief Lee una tecla presionada por el usuario y devuelve el código de caracter que representa
 * @returns La secuencia de bytes del caracter
 */
inline std::vector<int> ReadConsoleChar()
{
    std::vector<int> bytes;

    int key = Getch();
    bytes.push_back(key);

    #ifdef _WIN32
        // Teclas especiales de conio.h
        if (key == 0 || key == 224)
        {
            bytes.push_back(Getch());
            return bytes;
        }
    #else
        // Secuencias ANSI (ESC ...)
        if (key == 27)
        {
            // Leer todos los bytes disponibles de la secuencia
            while (Kbhit())
                bytes.push_back(Getch());

            return bytes;
        }
    #endif

    // Compara con AND lógico bit a bit para validar si es un caracter con cada cantidad de bytes
    if ((key & 0b11100000) == 0b11000000)         // 2 bytes
    {
        bytes.push_back(Getch());
    }
    else if ((key & 0b11110000) == 0b11100000)    // 3 bytes
    {
        bytes.push_back(Getch());
        bytes.push_back(Getch());
    }
    else if ((key & 0b11111000) == 0b11110000)    // 4 bytes
    {
        bytes.push_back(Getch());
        bytes.push_back(Getch());
        bytes.push_back(Getch());
    }

    return bytes;
}

/**
 * @brief Convierte un byteChar en un Caracter imprimible
 * @param byteChar bytes de la tecla presionada
 */
inline std::string CastKeyToString(const std::vector<int>& byteChar)
{
    std::string character;
    for (int byte : byteChar)
    {
        character += static_cast<char>(byte);
    }
    return character;
}

/**
 * @brief Verifica si un carácter de bytes es alfanumérico.
 * * @param byteChar Vector de enteros que representa el carácter en bytes a evaluar.
 * @return true Si el carácter se encuentra en la lista de alfanuméricos.
 * @return false Si el carácter no es alfanumérico.
 */
inline bool IsAlphaNumChar(std::vector<int>& byteChar)
{
    for (auto& ch : Common::ALPHA_NUM_CHARS)
    {
        if(ch == byteChar)
        {
            return true;
        }
    }
    return false;
}


} // namespace Common
>>>>>>> 09e6a97404d22f9d819996b99ce5299164c16c08
