#pragma once

#include "Consts.h"
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Actualiza el índice de la opción seleccionada vertical u horizontalmente basándose en la tecla presionada.
 * * Permite el comportamiento de "bucle" (orbe), donde pasar el límite mínimo lleva al máximo y viceversa.
 * * @param option Referencia a la variable que almacena la opción seleccionada actualmente (se modifica internamente).
 * @param minOption Referencia al valor mínimo permitido para las opciones.
 * @param maxOption Referencia al valor máximo permitido para las opciones.
 * @param userKey Referencia al vector que contiene los bytes de la tecla presionada por el usuario.
 * @return void No retorna ningún valor (los cambios se reflejan directamente en el parámetro 'option').
 */
inline void SetOption(int& option, const int& minOption, const int& maxOption, vector<int>& userKey)
{

    if(userKey == KEY_ARROW_TOP || userKey == KEY_ARROW_LEFT)
    {
        if(option > minOption)
            --option;
        else
            option = maxOption;
    }

    if(userKey == KEY_ARROW_BOTTOM || userKey == KEY_ARROW_RIGHT)
    {
        if(option < maxOption)
            ++option;
        else
            option = minOption;
    }
}

/**
 * @brief Verifica si un carácter de bytes corresponde a una tecla de acción.
 * * @param byteChar Vector de enteros que representa el carácter en bytes a evaluar.
 * @return true Si el carácter coincide con una tecla de acción.
 * @return false En caso contrario.
 */
inline bool IsActionKey(vector<int>& byteChar)
{
    for (auto& ch : ::ACTION_KEYS)
    {
        if(ch == byteChar)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Verifica si un carácter de bytes corresponde a una tecla de navegación.
 * * @param byteChar Vector de enteros que representa el carácter en bytes a evaluar.
 * @return true Si el carácter coincide con una tecla de navegación.
 * @return false En caso contrario.
 */
inline bool IsNavigationKey(vector<int>& byteChar)
{
    for (auto& ch : ::NAVIGATION_KEYS)
    {
        if(ch == byteChar)
        {
            return true;
        }
    }
    return false;
}