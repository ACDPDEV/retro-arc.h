#pragma once

#include <string>
#include <vector>

#include "../PokemonAnimatedSprites/BulbasaurBack.h"
#include "../PokemonAnimatedSprites/BulbasaurFront.h"
#include "../PokemonAnimatedSprites/CharmanderBack.h"
#include "../PokemonAnimatedSprites/CharmanderFront.h"
#include "../PokemonAnimatedSprites/ChikoritaBack.h"
#include "../PokemonAnimatedSprites/ChikoritaFront.h"
#include "../PokemonAnimatedSprites/EeveeBack.h"
#include "../PokemonAnimatedSprites/EeveeFront.h"
#include "../PokemonAnimatedSprites/PikachuBack.h"
#include "../PokemonAnimatedSprites/PikachuFront.h"
#include "../PokemonAnimatedSprites/PsyduckBack.h"
#include "../PokemonAnimatedSprites/PsyduckFront.h"
#include "../PokemonAnimatedSprites/RockruffBack.h"
#include "../PokemonAnimatedSprites/RockruffFront.h"
#include "../PokemonAnimatedSprites/SquirtleBack.h"
#include "../PokemonAnimatedSprites/SquirtleFront.h"

namespace Pokemon {

    /// @brief Punteros a los frames de animacion (back/front) de un Pokemon
    /// @details Ambos punteros apuntan directamente a los arrays `{Name}Back_ALL` /
    ///          `{Name}Front_ALL` ya definidos en PokemonAnimatedSprites/. No poseen
    ///          los datos, solo los referencian (evita copiar los 10 frames por consulta).
    struct SpriteSet {
        const std::vector<std::vector<std::string>>* backFrames;
        const std::vector<std::vector<std::string>>* frontFrames;
    };

    /// @brief Tabla de lookup de sprites indexada por ID de Pokemon en la base de datos
    /// @details indice 0 = dbId 1 (Psyduck) ... indice 7 = dbId 8 (Charmander), replicando
    ///          el mapeo id -> especie de Database/PokemonDatabase.h.
    inline const SpriteSet POKEMON_SPRITE_TABLE[8] = {
        { &PsyduckBack_ALL,    &PsyduckFront_ALL    }, // 1. Psyduck
        { &PikachuBack_ALL,    &PikachuFront_ALL    }, // 2. Pikachu
        { &ChikoritaBack_ALL,  &ChikoritaFront_ALL  }, // 3. Chikorita
        { &RockruffBack_ALL,   &RockruffFront_ALL   }, // 4. Rockruff
        { &BulbasaurBack_ALL,  &BulbasaurFront_ALL  }, // 5. Bulbasaur
        { &SquirtleBack_ALL,   &SquirtleFront_ALL   }, // 6. Squirtle
        { &EeveeBack_ALL,      &EeveeFront_ALL      }, // 7. Eevee
        { &CharmanderBack_ALL, &CharmanderFront_ALL }, // 8. Charmander
    };

    /// @brief Obtiene el conjunto de sprites (back/front) de un Pokemon por su ID en la BD
    /// @param dbId ID del Pokemon en Database/PokemonDatabase.h (rango valido 1-8)
    /// @return Referencia constante al SpriteSet correspondiente. IDs fuera del rango
    ///         1-8 hacen fallback al primer Pokemon (Psyduck) para evitar comportamiento
    ///         indefinido.
    inline const SpriteSet& GetPokemonSprites(int dbId) {
        if (dbId < 1 || dbId > 8) {
            return POKEMON_SPRITE_TABLE[0];
        }
        return POKEMON_SPRITE_TABLE[dbId - 1];
    }

} // namespace Pokemon
