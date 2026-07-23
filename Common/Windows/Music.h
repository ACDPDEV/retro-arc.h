/// @file Windows/Music.h
/// @brief Implementación Windows de reproducción de audio via MCI.
/// @details Usa mciSendString con alias "audio". Una sola instancia a la vez.
///          Funciones marcadas `inline` para uso header-only.
///          API idéntica a Linux/Music.h.
#pragma once
#include <string>
#include <windows.h>

namespace Common
{
    /// @brief Ruta del archivo de audio en reproduccion actual (vacio = ninguno)
    inline std::string g_currentBackground = "";

    /// @brief Indica si el audio actual esta en bucle
    inline bool g_isLooping = false;

    /// @brief Indica si hay audio de fondo reproduciendose actualmente (alias "audio")
    /// @details Equivalente Windows de `g_audioPid > 0` en Linux/Music.h — permite a codigo
    ///          cross-platform (p.ej. Round.h) consultar estado de reproduccion sin PIDs.
    inline bool g_isPlaying = false;

    /// @brief Reproduce un archivo de audio MP3/WAV (detiene cualquier reproducción anterior)
    /// @param file Ruta al archivo de audio (soporta rutas con espacios)
    /// @details Usa MCI (Media Control Interface). Alias interno: "audio".
    ///          No bloquea: la reproducción continúa en background.
    inline void PlayAudio(const std::string& file) {
        mciSendString("stop audio", NULL, 0, NULL);
        mciSendString("close audio", NULL, 0, NULL);

        std::string command = "open \"" + file + "\" type mpegvideo alias audio";
        mciSendString(command.c_str(), NULL, 0, NULL);

        mciSendString("play audio", NULL, 0, NULL);
        g_isPlaying = true;
    }

    /// @brief Reproduce un archivo de audio en bucle infinito
    /// @param file Ruta al archivo de audio
    /// @details Igual que PlayAudio pero con flag "repeat". Para detener: StopAudio().
    /// @warning Mismo alias "audio" que PlayAudio: no se pueden superponer sonidos.
    inline void PlayAudioLoop(const std::string& file) {
        mciSendString("stop audio", NULL, 0, NULL);
        mciSendString("close audio", NULL, 0, NULL);

        std::string command = "open \"" + file + "\" type mpegvideo alias audio";
        mciSendString(command.c_str(), NULL, 0, NULL);

        mciSendString("play audio repeat", NULL, 0, NULL);
        g_isPlaying = true;
    }

    /// @brief Detiene y cierra la reproducción de audio actual
    /// @details Libera el alias "audio". Seguro llamar aunque no haya nada reproduciéndose.
    inline void StopAudio() {
        mciSendString("stop audio", NULL, 0, NULL);
        mciSendString("close audio", NULL, 0, NULL);
        g_isPlaying = false;
    }

    /// @brief Indica si hay audio de fondo reproduciendose actualmente
    /// @details Equivalente Windows de `g_audioPid > 0` en Linux — permite a codigo
    ///          cross-platform consultar estado sin depender de un PID.
    inline bool IsAudioPlaying() { return g_isPlaying; }

    /// @brief Reproduce un efecto de audio corto en simultaneo con el audio de fondo
    /// @param file Ruta al archivo de audio del efecto
    /// @details Usa un alias MCI separado ("audio_sfx") del alias de fondo ("audio"), por lo
    ///          que MCI mezcla ambos canales nativamente — no hay pausa/reanuda del fondo como
    ///          en Linux (ffplay-por-proceso no soporta mezcla, MCI si). `play` sin la palabra
    ///          "wait" es asincrono por defecto en MCI: esta llamada no bloquea.
    inline void PlayAudioOverlay(const std::string& file) {
        mciSendString("stop audio_sfx", NULL, 0, NULL);
        mciSendString("close audio_sfx", NULL, 0, NULL);

        std::string command = "open \"" + file + "\" type mpegvideo alias audio_sfx";
        mciSendString(command.c_str(), NULL, 0, NULL);

        mciSendString("play audio_sfx", NULL, 0, NULL);
    }

    /// @brief Pausa la reproducción de audio actual (mantiene posición)
    /// @details Equivalente a "pause" en reproductor. Reanudar con ResumeAudio().
    ///          Si no hay audio reproduciéndose, no hace nada visible.
    inline void PauseAudio() {
        mciSendString("pause audio", NULL, 0, NULL);
    }
    
    /// @brief Reanuda la reproducción desde la posición pausada
    /// @details Solo funciona si se llamó PauseAudio() antes. Si no estaba pausado, no hace nada.
    inline void ResumeAudio() {
        mciSendString("resume audio", NULL, 0, NULL);
    }
}
