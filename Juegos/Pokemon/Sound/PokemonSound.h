/// @file Sound/PokemonSound.h
/// @brief Fachada centralizada de audio para el juego Pokemon.
/// @details Define constantes de ruta para los 15 archivos de audio, funciones
///          envolventes para cada evento de sonido, y el flag g_isBattleMusicPaused
///          para el toggle SONIDO. Delega en Common::Music.h para la reproduccion real.
///          Sigue el patron header-only con funciones inline.
#pragma once

#include <string>
#include <cstdlib>

#include "../../../Common/Music.h"

namespace Pokemon {

    // ============================================================
    // Path constants (relative to project root)
    // ============================================================
    const std::string POKEMON_OPENING_PATH      = "Juegos/Pokemon/Sounds/PokemonOpening.mp3";
    const std::string NAME_MUSIC_PATH           = "Juegos/Pokemon/Sounds/NameMusic.mp3";
    const std::string BATTLE_BEGINNING_PATH     = "Juegos/Pokemon/Sounds/BattleBeginning.mp3";
    const std::string BATTLE_CONTINUATION_PATH  = "Juegos/Pokemon/Sounds/BattleContinuation.mp3";
    const std::string BACKPACK_PATH             = "Juegos/Pokemon/Sounds/BackPack.mp3";
    const std::string VICTORY_SOUND_PATH        = "Juegos/Pokemon/Sounds/VictorySound.mp3";
    const std::string RUN_EFFECT_PATH           = "Juegos/Pokemon/Sounds/RunEffect.mp3";
    const std::string ESCAPE_MUSIC_PATH         = "Juegos/Pokemon/Sounds/EscapeMusic.mp3";

    /// Heal sound filename with spaces — ffplay handles quoted paths via `file.c_str()`
    const std::string HEAL_SOUND_PATH           = "Juegos/Pokemon/Sounds/In-Battle Heal HP Restore.mp3";
    const std::string LOW_HEALTH_PATH           = "Juegos/Pokemon/Sounds/LowHealth.mp3";
    const std::string PIKACHU_ATTACK_PATH       = "Juegos/Pokemon/Sounds/pikachuAttack.mp3";

    // 4 generic attack sounds
    const std::string GENERIC_ATTACK_1_PATH     = "Juegos/Pokemon/Sounds/Roost.mp3";
    const std::string GENERIC_ATTACK_2_PATH     = "Juegos/Pokemon/Sounds/Acid Armor.mp3";
    const std::string GENERIC_ATTACK_3_PATH     = "Juegos/Pokemon/Sounds/Giga Impact.mp3";
    const std::string GENERIC_ATTACK_4_PATH     = "Juegos/Pokemon/Sounds/Confuse Ray.mp3";

    /// Pikachu DB ID for attack sound assignment
    const int PIKACHU_ID = 2;

    /// @brief Indica si la musica de batalla fue pausada por el toggle SONIDO
    /// @details Flag separado de g_audioPid para evitar el bug existente.
    ///          true = pausada por el usuario, false = reproduciendo o detenida.
    inline bool g_isBattleMusicPaused = false;

    // ============================================================
    // Battle music lifecycle
    // ============================================================

    /// @brief Inicia el bucle de musica de batalla (BattleContinuation.mp3)
    inline void StartBattleMusic() {
        Common::PlayAudioLoop(BATTLE_CONTINUATION_PATH);
        g_isBattleMusicPaused = false;
    }

    /// @brief Detiene toda la reproduccion de audio (musica de batalla incluida)
    inline void StopBattleMusic() {
        Common::StopAudio();
        g_isBattleMusicPaused = false;
    }

    /// @brief Reanuda la musica de batalla si fue pausada por SONIDO
    /// @details No-op si g_isBattleMusicPaused es false (musica no pausada)
    inline void ResumeBattleMusic() {
        if (g_isBattleMusicPaused) {
            Common::ResumeAudio();
            g_isBattleMusicPaused = false;
        }
    }

    /// @brief Pausa la musica de batalla para el toggle SONIDO
    /// @details No-op si ya estaba pausada o si no hay musica activa
    inline void PauseBattleMusic() {
        if (!g_isBattleMusicPaused && Common::IsAudioPlaying()) {
            Common::PauseAudio();
            g_isBattleMusicPaused = true;
        }
    }

    // ============================================================
    // Opening screen music
    // ============================================================

    /// @brief Inicia el bucle de musica de la pantalla de titulo
    inline void PlayOpeningMusic() {
        Common::PlayAudioLoop(POKEMON_OPENING_PATH);
    }

    /// @brief Detiene la musica de la pantalla de titulo
    inline void StopOpeningMusic() {
        Common::StopAudio();
    }

    // ============================================================
    // Name input screen music
    // ============================================================

    /// @brief Inicia el bucle de musica de la pantalla de nombres
    inline void PlayNameMusic() {
        Common::PlayAudioLoop(NAME_MUSIC_PATH);
    }

    /// @brief Detiene la musica de la pantalla de nombres
    inline void StopNameMusic() {
        Common::StopAudio();
    }

    // ============================================================
    // Battle beginning effect
    // ============================================================

    /// @brief Reproduce el efecto de inicio de batalla (BattleBeginning.mp3)
    /// @details No usa overlay porque no hay musica de fondo activa en ese punto
    inline void PlayBattleBeginningSound() {
        Common::PlayAudio(BATTLE_BEGINNING_PATH);
    }

    // ============================================================
    // Sound effects (use overlay to resume background music)
    // ============================================================

    /// @brief Reproduce el sonido de boton/confirmacion (BackPack.mp3)
    /// @details Overlay: pausa la musica de fondo, reproduce el efecto, reanuda
    inline void PlayButtonPressSound() {
        Common::PlayAudioOverlay(BACKPACK_PATH);
    }

    /// @brief Reproduce el sonido de victoria (VictorySound.mp3)
    /// @details No usa overlay porque la musica de batalla ya fue detenida
    inline void PlayVictorySound() {
        Common::PlayAudio(VICTORY_SOUND_PATH);
    }

    /// @brief Reproduce el efecto de huida (RunEffect.mp3)
    /// @details Overlay para no interrumpir musica de fondo si existe
    inline void PlayRunEffectSound() {
        Common::PlayAudioOverlay(RUN_EFFECT_PATH);
    }

    /// @brief Reproduce el sonido de escape al confirmar HUIDA
    /// @details Overlay para no interrumpir musica de fondo si existe
    inline void PlayEscapeSound() {
        Common::PlayAudioOverlay(ESCAPE_MUSIC_PATH);
    }

    /// @brief Reproduce el sonido de curacion al usar pocion
    /// @details Overlay para no interrumpir musica de batalla
    inline void PlayHealSound() {
        Common::PlayAudioOverlay(HEAL_SOUND_PATH);
    }

    /// @brief Reproduce el sonido de PS bajos cuando un Pokemon se desmaya
    /// @details Overlay para no interrumpir musica de batalla
    inline void PlayLowHealthSound() {
        Common::PlayAudioOverlay(LOW_HEALTH_PATH);
    }

    // ============================================================
    // Attack sounds (Pokemon-specific assignment)
    // ============================================================

    /// @brief Reproduce un sonido de ataque generico aleatorio
    /// @details Elige uno de {Roost, Acid Armor, Giga Impact, Confuse Ray}
    ///          mediante std::rand() % 4. Overlay para reanudar musica de fondo.
    inline void PlayAttackSound() {
        const std::string genericAttacks[4] = {
            GENERIC_ATTACK_1_PATH,
            GENERIC_ATTACK_2_PATH,
            GENERIC_ATTACK_3_PATH,
            GENERIC_ATTACK_4_PATH
        };
        int index = std::rand() % 4;
        Common::PlayAudioOverlay(genericAttacks[index]);
    }

    /// @brief Reproduce el sonido de ataque segun el Pokemon
    /// @param pokemonId ID del Pokemon atacante (PIKACHU_ID = 2 para pikachuAttack.mp3)
    /// @details Pikachu usa pikachuAttack.mp3; los demas obtienen un sonido generico aleatorio
    inline void PlayAttackForPokemon(int pokemonId) {
        if (pokemonId == PIKACHU_ID) {
            Common::PlayAudioOverlay(PIKACHU_ATTACK_PATH);
        } else {
            PlayAttackSound();
        }
    }

} // namespace Pokemon
