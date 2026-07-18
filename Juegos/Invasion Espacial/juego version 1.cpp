#include <iostream>

#include "juego.h"
#include "pantallas.h"

using namespace std;

int main()
{
    configurarPantalla();

    presentacion();

    if(clave())
    {
        string usuario = solicitarUsuario();

        bienvenida(usuario);

        menu(usuario);
    }
    else
    {
        claveIncorrecta();
    }

    return 0;
}
