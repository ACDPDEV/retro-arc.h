/// @file Linux/Music.h
/// @brief Implementación Linux de reproducción de audio via ffplay (ffmpeg).
/// @details Usa fork+execlp para lanzar ffplay en background. Controla proceso hijo por PID global.
///          Requiere ffmpeg instalado (ffplay). Una sola instancia a la vez.
///          Señales: SIGTERM (stop), SIGSTOP (pause), SIGCONT (resume).
///          Funciones marcadas `inline` para uso header-only.
///          API idéntica a Windows/Music.h.
#pragma once
#include <string>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

namespace Common
{
    /// @brief PID del proceso de reproducción actual (0 = ninguno activo)
    /// @details Reemplaza al alias "audio" de MCI en Windows: aquí controlamos
    ///          el proceso hijo directamente por su PID.
    inline pid_t g_audioPid = 0;

    /// @brief Ruta del archivo de audio en reproduccion actual (vacio = ninguno)
    inline std::string g_currentBackground = "";

    /// @brief Indica si el audio actual esta en bucle
    inline bool g_isLooping = false;

    /// @brief Indica si hay audio de fondo reproduciendose actualmente
    /// @details Equivalente Linux de `g_isPlaying` en Windows/Music.h — envuelve `g_audioPid`
    ///          para que codigo cross-platform (p.ej. Round.h) consulte estado sin tocar el PID.
    inline bool IsAudioPlaying() { return g_audioPid > 0; }

    /// @brief Detiene el proceso de audio hijo actual, si existe
    /// @details Función auxiliar interna, usada por PlayAudio/PlayAudioLoop/StopAudio
    inline void KillAudioProcess() {
        if (g_audioPid > 0) {
            kill(g_audioPid, SIGTERM);
            waitpid(g_audioPid, nullptr, 0);
            g_audioPid = 0;
        }
    }
    
    /// @brief Reproduce un archivo de audio MP3/WAV (detiene cualquier reproducción anterior)
    /// @param file Ruta al archivo de audio (soporta rutas con espacios)
    /// @details Usa ffplay (de ffmpeg) como backend, lanzado como proceso hijo en background.
    ///          Requiere tener ffmpeg instalado (`sudo pacman -S ffmpeg` en Arch).
    ///          No bloquea: la reproducción continúa en background.
    inline void PlayAudio(const std::string& file) {
        KillAudioProcess();
        g_currentBackground = file;
        g_isLooping = false;
        pid_t pid = fork();
        if (pid == 0) {
            // Proceso hijo: silencia stdout/stderr de ffplay y lo reemplaza por el reproductor
            freopen("/dev/null", "w", stdout);
            freopen("/dev/null", "w", stderr);
            execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", file.c_str(), (char*)nullptr);
            _exit(127); // solo se llega aquí si execlp falla (ffplay no instalado)
        }
        g_audioPid = pid;
    }
    
    /// @brief Reproduce un archivo de audio en bucle infinito
    /// @param file Ruta al archivo de audio
    /// @details Igual que PlayAudio pero con "-loop 0" (infinito). Para detener: StopAudio().
    /// @warning Un solo proceso de audio a la vez: no se pueden superponer sonidos.
    inline void PlayAudioLoop(const std::string& file) {
        KillAudioProcess();
        g_currentBackground = file;
        g_isLooping = true;
        pid_t pid = fork();
        if (pid == 0) {
            freopen("/dev/null", "w", stdout);
            freopen("/dev/null", "w", stderr);
            execlp("ffplay", "ffplay", "-nodisp", "-loop", "0", "-loglevel", "quiet", file.c_str(), (char*)nullptr);
            _exit(127);
        }
        g_audioPid = pid;
    }
    
    /// @brief Detiene y cierra la reproducción de audio actual
    /// @details Termina el proceso hijo. Seguro llamar aunque no haya nada reproduciéndose.
    inline void StopAudio() {
        KillAudioProcess();
        g_currentBackground = "";
        g_isLooping = false;
    }
    
    /// @brief Reproduce un efecto de audio corto sobre el audio de fondo (pausa-reanuda)
    /// @param file Ruta al archivo de audio del efecto
    /// @details No bloqueante: usa un "doble fork" para que la espera del efecto (waitpid)
    ///          ocurra en un proceso supervisor separado, no en el proceso principal del juego.
    ///          El supervisor pausa el fondo con SIGSTOP, reproduce el efecto con ffplay
    ///          (bloqueante SOLO dentro del supervisor), reanuda el fondo con SIGCONT, y termina.
    ///          Si no hay audio de fondo, solo reproduce el efecto. Supervisores de llamadas
    ///          anteriores ya terminados se recolectan (reap) de forma no bloqueante al inicio.
    inline void PlayAudioOverlay(const std::string& file) {
        // Reap non-blocking de supervisores de overlays anteriores ya terminados
        while (waitpid(-1, nullptr, WNOHANG) > 0) {}

        pid_t savedPid = g_audioPid;
        pid_t supervisorPid = fork();
        if (supervisorPid == 0) {
            // Proceso supervisor (hijo): pausa el fondo, reproduce el efecto (bloqueante AQUI,
            // no en el proceso principal), reanuda el fondo, termina
            if (savedPid > 0) {
                kill(savedPid, SIGSTOP);
            }
            pid_t effectPid = fork();
            if (effectPid == 0) {
                freopen("/dev/null", "w", stdout);
                freopen("/dev/null", "w", stderr);
                execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", file.c_str(), (char*)nullptr);
                _exit(127);
            }
            waitpid(effectPid, nullptr, 0);
            if (savedPid > 0) {
                kill(savedPid, SIGCONT);
            }
            _exit(0);
        }
        // Proceso principal: retorna inmediatamente, no bloquea
    }

    /// @brief Pausa la reproducción de audio actual (mantiene posición)
    /// @details Envía SIGSTOP al proceso hijo, congelándolo. Reanudar con ResumeAudio().
    ///          Si no hay audio reproduciéndose, no hace nada.
    inline void PauseAudio() {
        if (g_audioPid > 0) {
            kill(g_audioPid, SIGSTOP);
        }
    }
    
    /// @brief Reanuda la reproducción desde la posición pausada
    /// @details Envía SIGCONT al proceso hijo. Solo funciona si se llamó PauseAudio() antes.
    inline void ResumeAudio() {
        if (g_audioPid > 0) {
            kill(g_audioPid, SIGCONT);
        }
    }
}
