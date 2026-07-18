/// @file Music.h
/// @brief Fachada cross-platform para reproducción de audio.
/// @details Incluye Windows/Music.h (MCI) o Linux/Music.h (ffplay) según _WIN32.
///          API unificada: PlayAudio, PlayAudioLoop, StopAudio, PauseAudio, ResumeAudio.
///          Una sola instancia de audio a la vez en ambas plataformas.
#ifdef _WIN32
    #include "Windows/Music.h"
#else
    #include "Linux/Music.h"
#endif
