/// @file Windows/Music.h
/// @brief Implementación Windows de reproducción de audio via MCI.
/// @details Usa mciSendString con alias "audio". Una sola instancia a la vez.
///          Funciones marcadas `inline` para uso header-only.
///          API idéntica a Linux/Music.h.
#pragma once
#include <string>
#include <windows.h>

using namespace std;

/// @brief Reproduce un archivo de audio MP3/WAV (detiene cualquier reproducción anterior)
/// @param file Ruta al archivo de audio (soporta rutas con espacios)
/// @details Usa MCI (Media Control Interface). Alias interno: "audio".
///          No bloquea: la reproducción continúa en background.
inline void PlayAudio(const string& file) {
    mciSendString("stop audio", NULL, 0, NULL);
    mciSendString("close audio", NULL, 0, NULL);

    string command = "open \"" + file + "\" type mpegvideo alias audio";
    mciSendString(command.c_str(), NULL, 0, NULL);

    mciSendString("play audio", NULL, 0, NULL);
}

/// @brief Reproduce un archivo de audio en bucle infinito
/// @param file Ruta al archivo de audio
/// @details Igual que PlayAudio pero con flag "repeat". Para detener: StopAudio().
/// @warning Mismo alias "audio" que PlayAudio: no se pueden superponer sonidos.
inline void PlayAudioLoop(const string& file) {
    mciSendString("stop audio", NULL, 0, NULL);
    mciSendString("close audio", NULL, 0, NULL);

    string command = "open \"" + file + "\" type mpegvideo alias audio";
    mciSendString(command.c_str(), NULL, 0, NULL);

    mciSendString("play audio repeat", NULL, 0, NULL);
}

/// @brief Detiene y cierra la reproducción de audio actual
/// @details Libera el alias "audio". Seguro llamar aunque no haya nada reproduciéndose.
inline void StopAudio() {
    mciSendString("stop audio", NULL, 0, NULL);
    mciSendString("close audio", NULL, 0, NULL);
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
