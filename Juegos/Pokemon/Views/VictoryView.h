#pragma once

#include <array>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include "../../../Common/Aligned.h"
#include "../../../Common/Color.h"
#include "../../../Common/Components/BottomBar.h"
#include "../../../Common/Consts.h"
#include "../../../Common/Font.h"
#include "../../../Common/Graphics.h"
#include "../../../Common/Sprite.h"
#include "../../../Common/Terminal.h"
#include "../../../Common/Theme.h"
#include "../../../Common/Utils.h"
#include "../PokemonStaticSprites/BulbasaurFront.h"
#include "../PokemonStaticSprites/CharmanderFront.h"
#include "../PokemonStaticSprites/ChikoritaFront.h"
#include "../PokemonStaticSprites/EeveeFront.h"
#include "../PokemonStaticSprites/PikachuFront.h"
#include "../PokemonStaticSprites/PsyduckFront.h"
#include "../PokemonStaticSprites/RockruffFront.h"
#include "../PokemonStaticSprites/SquirtleFront.h"

namespace Pokemon {

    /// @brief Pantalla de victoria con titulo "VICTORIA", sprite del ganador y confeti animado
    /// @details Muestra el titulo con ConcatFont, el sprite del Pokemon ganador, confeti con particulas
    ///          aleatorias, el mensaje de victoria y el contador de rondas. La animacion continua
    ///          hasta que se presione una tecla.
    /// @param winnerName Nombre del jugador ganador
    /// @param pokemonIndex Indice del Pokemon ganador (0-7)
    /// @param round Numero de rondas jugadas
    inline void VictoryView(const std::string& winnerName, int pokemonIndex, int round) {
        Common::DrawBackground();

        // Titulo "VICTORIA" con ConcatFont (FONT9_V-FONT9_A) - 9-line font
        const std::array<std::string, 9> title = Common::ConcatFont({
            Common::FONT9_V, Common::FONT9_I, Common::FONT9_C, Common::FONT9_T,
            Common::FONT9_O, Common::FONT9_R, Common::FONT9_I, Common::FONT9_A
        }, 2);

        // Gradiente: amarillo -> rojo -> amarillo para las 9 lineas del titulo
        std::vector<std::array<int, 3>> titleGradient(9);
        for (int i = 0; i < 9; i++) {
            if (i < 3) {
                // Amarillo a rojo
                titleGradient[i] = {
                    Common::YELLOW[0] + (Common::RED[0] - Common::YELLOW[0]) * i / 3,
                    Common::YELLOW[1] + (Common::RED[1] - Common::YELLOW[1]) * i / 3,
                    Common::YELLOW[2] + (Common::RED[2] - Common::YELLOW[2]) * i / 3
                };
            } else if (i < 6) {
                // Rojo a amarillo
                int j = i - 3;
                titleGradient[i] = {
                    Common::RED[0] + (Common::YELLOW[0] - Common::RED[0]) * j / 3,
                    Common::RED[1] + (Common::YELLOW[1] - Common::RED[1]) * j / 3,
                    Common::RED[2] + (Common::YELLOW[2] - Common::RED[2]) * j / 3
                };
            } else {
                // Amarillo a rojo
                int j = i - 6;
                titleGradient[i] = {
                    Common::YELLOW[0] + (Common::RED[0] - Common::YELLOW[0]) * j / 3,
                    Common::YELLOW[1] + (Common::RED[1] - Common::YELLOW[1]) * j / 3,
                    Common::YELLOW[2] + (Common::RED[2] - Common::YELLOW[2]) * j / 3
                };
            }
        }

        // Centrar titulo horizontalmente
        const int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[0]), "center");

        // Renderizar titulo linea por linea con gradiente
        for (int i = 0; i < 9; i++) {
            Common::DrawText(
                titleX, 3 + i, -1, -1,
                {title[i]}, titleGradient[i], Common::BACKGROUND
            );
        }

        // Array de sprites de Pokemon (ordenado por spriteIndex)
        const std::vector<std::string>* pokemonSprites[] = {
            &BulbasaurFront, &CharmanderFront, &SquirtleFront, &PikachuFront,
            &PsyduckFront, &EeveeFront, &RockruffFront, &ChikoritaFront
        };

        // Sprite del Pokemon ganador (centrado, y=16)
        if (pokemonIndex >= 0 && pokemonIndex < POKEMON_COUNT) {
            const std::vector<std::string>& sprite = *pokemonSprites[pokemonIndex];
            const int spriteWidth = Common::Length(sprite[0]);
            const int spriteX = Common::AlignedX(0, Common::WIDTH_SCREEN, spriteWidth, "center");
            Common::DrawSprite(spriteX, 16, sprite);
        }

        // Mensaje de victoria (centrado, y=38)
        std::string message = "¡El " + winnerName + " ha ganado la batalla!";
        const int messageX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(message), "center");
        Common::DrawText(messageX, 38, -1, -1, {message}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

        // Contador de rondas (centrado, y=42)
        std::string roundText = "Rondas jugadas: " + std::to_string(round);
        const int roundX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(roundText), "center");
        Common::DrawText(roundX, 42, -1, -1, {roundText}, Common::ACCENT, Common::BACKGROUND);

        // Barra inferior
        Common::DrawBottomBar();

        Common::GoToEnd();

        // Inicializar generador de numeros aleatorios
        std::srand(std::time(nullptr));

        // Estructura de particula de confeti
        struct Particle {
            int x;
            int y;
            std::string character;
            int r, g, b;
            int speed;
        };

        // Mantener array de 30 particulas
        const int PARTICLE_COUNT = 30;
        Particle particles[PARTICLE_COUNT];

        // Inicializar particolas con posiciones y colores aleatorios
        for (int i = 0; i < PARTICLE_COUNT; i++) {
            particles[i].x = std::rand() % Common::WIDTH_SCREEN;
            particles[i].y = std::rand() % Common::HEIGHT_SCREEN;
            particles[i].character = (std::rand() % 2 == 0) ? "█" : "▀";
            particles[i].r = std::rand() % 256;
            particles[i].g = std::rand() % 256;
            particles[i].b = std::rand() % 256;
            particles[i].speed = 1 + (std::rand() % 3);
        }

        // Animacion de confeti (bucle infinito hasta que se presione una tecla)
        while (true) {
            // Titulo "VICTORIA" con ConcatFont (FONT9_V-FONT9_A) - 9-line font
            const std::array<std::string, 9> title = Common::ConcatFont({
                Common::FONT9_V, Common::FONT9_I, Common::FONT9_C, Common::FONT9_T,
                Common::FONT9_O, Common::FONT9_R, Common::FONT9_I, Common::FONT9_A
            }, 2);

            // Gradiente: amarillo -> rojo -> amarillo para las 9 lineas del titulo
            std::vector<std::array<int, 3>> titleGradient(9);
            for (int i = 0; i < 9; i++) {
                if (i < 3) {
                    // Amarillo a rojo
                    titleGradient[i] = {
                        Common::YELLOW[0] + (Common::RED[0] - Common::YELLOW[0]) * i / 3,
                        Common::YELLOW[1] + (Common::RED[1] - Common::YELLOW[1]) * i / 3,
                        Common::YELLOW[2] + (Common::RED[2] - Common::YELLOW[2]) * i / 3
                    };
                } else if (i < 6) {
                    // Rojo a amarillo
                    int j = i - 3;
                    titleGradient[i] = {
                        Common::RED[0] + (Common::YELLOW[0] - Common::RED[0]) * j / 3,
                        Common::RED[1] + (Common::YELLOW[1] - Common::RED[1]) * j / 3,
                        Common::RED[2] + (Common::YELLOW[2] - Common::RED[2]) * j / 3
                    };
                } else {
                    // Amarillo a rojo
                    int j = i - 6;
                    titleGradient[i] = {
                        Common::YELLOW[0] + (Common::RED[0] - Common::YELLOW[0]) * j / 3,
                        Common::YELLOW[1] + (Common::RED[1] - Common::YELLOW[1]) * j / 3,
                        Common::YELLOW[2] + (Common::RED[2] - Common::YELLOW[2]) * j / 3
                    };
                }
            }

            // Centrar titulo horizontalmente
            const int titleX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(title[0]), "center");

            // Renderizar titulo linea por linea con gradiente
            for (int i = 0; i < 9; i++) {
                Common::DrawText(
                    titleX, 3 + i, -1, -1,
                    {title[i]}, titleGradient[i], Common::BACKGROUND
                );
            }

            // Array de sprites de Pokemon (ordenado por spriteIndex)
            const std::vector<std::string>* pokemonSprites[] = {
                &BulbasaurFront, &CharmanderFront, &SquirtleFront, &PikachuFront,
                &PsyduckFront, &EeveeFront, &RockruffFront, &ChikoritaFront
            };

            // Sprite del Pokemon ganador (centrado, y=16)
            if (pokemonIndex >= 0 && pokemonIndex < POKEMON_COUNT) {
                const std::vector<std::string>& sprite = *pokemonSprites[pokemonIndex];
                const int spriteWidth = Common::Length(sprite[0]);
                const int spriteX = Common::AlignedX(0, Common::WIDTH_SCREEN, spriteWidth, "center");
                Common::DrawSprite(spriteX, 16, sprite);
            }

            // Mensaje de victoria (centrado, y=38)
            std::string message = "¡El " + winnerName + " ha ganado la batalla!";
            const int messageX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(message), "center");
            Common::DrawText(messageX, 38, -1, -1, {message}, Common::FOREGROUND_LIGHT, Common::BACKGROUND);

            // Contador de rondas (centrado, y=42)
            std::string roundText = "Rondas jugadas: " + std::to_string(round);
            const int roundX = Common::AlignedX(0, Common::WIDTH_SCREEN, Common::Length(roundText), "center");
            Common::DrawText(roundX, 42, -1, -1, {roundText}, Common::ACCENT, Common::BACKGROUND);

            // Barra inferior
            Common::DrawBottomBar();

            // Verificar si hay tecla presionada
            if (Common::Kbhit()) {
                break;
            }

            // Actualizar y dibujar cada particula
            for (int i = 0; i < PARTICLE_COUNT; i++) {
                // Limpiar posicion anterior
                Common::DrawText(particles[i].x, particles[i].y, 1, 1,
                    {" "}, Common::COLOR_DEFAULT, Common::BACKGROUND);

                // Mover particula hacia abajo
                particles[i].y += particles[i].speed;

                // Opcionalmente mover horizontalmente
                if (std::rand() % 3 == 0) {
                    particles[i].x += (std::rand() % 2 == 0) ? 1 : -1;
                }

                // Limites horizontales
                if (particles[i].x < 0) particles[i].x = 0;
                if (particles[i].x >= Common::WIDTH_SCREEN) particles[i].x = Common::WIDTH_SCREEN - 1;

                // Si la particula esta debajo de la pantalla, reiniciar en la parte superior
                if (particles[i].y >= Common::HEIGHT_SCREEN - 3) { // -3 para evitar BottomBar
                    particles[i].y = 0;
                    particles[i].x = std::rand() % Common::WIDTH_SCREEN;
                    particles[i].r = std::rand() % 256;
                    particles[i].g = std::rand() % 256;
                    particles[i].b = std::rand() % 256;
                }

                // Dibujar particula en nueva posicion con su color
                Common::DrawText(particles[i].x, particles[i].y, 1, 1,
                    {particles[i].character}, {particles[i].r, particles[i].g, particles[i].b}, Common::COLOR_DEFAULT);
            }

            Common::Sleep(50);
        }
    }

} // namespace Pokemon
