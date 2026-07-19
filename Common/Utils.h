#pragma once

#include <array>
#include <string>
#include <vector>

namespace Common {
    inline int Length(const std::string& str) {
        int count = 0;
        for (size_t i = 0; i < str.size(); ) {
            unsigned char c = str[i];

            // Secuencia de escape ANSI: no cuenta como carácter visible
            // NOTA (FIX W1): Esta lógica de skip ANSI se duplica en CutString().
            // Refactor futuro: extraer a helper común SkipAnsiEscape() para evitar duplicación.
            if (c == 0x1B) {
                i++; // saltar ESC

                if (i < str.size() && str[i] == '[') {
                    // CSI: ESC [ parametros... byte_final (0x40-0x7E)
                    i++;
                    while (i < str.size() && !(str[i] >= 0x40 && str[i] <= 0x7E)) {
                        i++;
                    }
                    if (i < str.size()) i++; // consumir byte final (ej. 'm')
                } else if (i < str.size() && str[i] == ']') {
                    // OSC: ESC ] ... terminado en BEL o ESC \
                    i++;
                    while (i < str.size() && str[i] != 0x07 &&
                        !(str[i] == 0x1B && i + 1 < str.size() && str[i + 1] == '\\')) {
                        i++;
                    }
                    if (i < str.size()) {
                        i += (str[i] == 0x07) ? 1 : 2;
                    }
                } else if (i < str.size()) {
                    i++; // secuencias de 2 bytes simples (ej. ESC c)
                }
                continue; // no incrementa count
            }

            if ((c & 0x80) == 0x00) i += 1;
            else if ((c & 0xE0) == 0xC0) i += 2;
            else if ((c & 0xF0) == 0xE0) i += 3;
            else if ((c & 0xF8) == 0xF0) i += 4;
            else i += 1;
            count++;
        }
        return count;
    }

    inline std::vector<std::string> CutString(const std::string& str, size_t width) {
        std::vector<std::string> result;
        if (width == 0 || str.empty()) return result;

        size_t bytePos = 0;
        int charCount = 0;
        size_t lineStart = 0;

        while (bytePos < str.size()) {
            unsigned char c = str[bytePos];

            // Saltar secuencias de escape ANSI (no cuentan como caracteres visibles)
            // NOTA (FIX W1): Esta lógica de skip ANSI se duplica en Length().
            // Refactor futuro: extraer a helper común SkipAnsiEscape() para evitar duplicación.
            if (c == 0x1B) {
                bytePos++; // saltar ESC

                if (bytePos < str.size() && str[bytePos] == '[') {
                    bytePos++;
                    while (bytePos < str.size() && !(str[bytePos] >= 0x40 && str[bytePos] <= 0x7E)) {
                        bytePos++;
                    }
                    if (bytePos < str.size()) bytePos++;
                } else if (bytePos < str.size() && str[bytePos] == ']') {
                    bytePos++;
                    while (bytePos < str.size() && str[bytePos] != 0x07 &&
                        !(str[bytePos] == 0x1B && bytePos + 1 < str.size() && str[bytePos + 1] == '\\')) {
                        bytePos++;
                    }
                    if (bytePos < str.size()) {
                        bytePos += (str[bytePos] == 0x07) ? 1 : 2;
                }
                } else if (bytePos < str.size()) {
                    bytePos++;
                }
                continue; // no incrementa charCount
            }

            // Determinar bytes del carácter UTF-8
            size_t charBytes = 1;
            if ((c & 0x80) == 0x00) charBytes = 1;
            else if ((c & 0xE0) == 0xC0) charBytes = 2;
            else if ((c & 0xF0) == 0xE0) charBytes = 3;
            else if ((c & 0xF8) == 0xF0) charBytes = 4;

            bytePos += charBytes;
            charCount++;

            // Cuando llegamos al ancho máximo, cortar la línea
            if (static_cast<size_t>(charCount) >= width) {
                result.push_back(str.substr(lineStart, bytePos - lineStart));
                lineStart = bytePos;
                charCount = 0;
            }
        }

        // Agregar el resto si queda algo
        if (lineStart < str.size()) {
            result.push_back(str.substr(lineStart));
        }

        return result;
    }

    inline std::string InvertString(std::string str) {
        std::string result;
        for (int i = str.size() - 1; i >= 0; i--) {
            result = str[i] + result;
        }
        return result;
    }

    inline std::string MaxString(std::vector<std::string> strings) {
        std::string maxLength;
        for (int i = 0; i < strings.size(); i++) {
            if (Length(strings[i]) > Length(maxLength)) {
                maxLength = strings[i];
            }
        }
        return maxLength;
    }

    inline std::string RepeatString(std::string str, int count) {
        std::string result;
        for (int i = 0; i < count; i++) {
            result += str;
        }
        return result;
    }

    /// @brief Trunca una cadena a un número máximo de caracteres visibles.
    /// @param str Cadena de entrada (puede contener ANSI escapes).
    /// @param maxLen Número máximo de caracteres visibles.
    /// @return Cadena truncada sin cortar secuencias ANSI.
    inline std::string TruncateVisible(const std::string& str, int maxLen) {
        std::vector<std::string> lines = CutString(str, maxLen);
        if (lines.empty()) return "";
        return lines[0];
    }

    inline std::vector<std::string> ArrayToVector(std::array<std::string, 9> arr) {
        std::vector<std::string> result;
        for (int i = 0; i < arr.size(); i++) {
            result.push_back(arr[i]);
        }
        return result;
    }

    inline std::vector<std::string> ArrayToVector(std::array<std::string, 4> arr) {
        std::vector<std::string> result;
        for (int i = 0; i < arr.size(); i++) {
            result.push_back(arr[i]);
        }
        return result;
    }

    inline std::vector<std::string> VectorSum(std::vector<std::vector<std::string>> vectors) {
        std::vector<std::string> result;
        for (size_t i = 0; i < vectors.size(); i++) {
            for (size_t j = 0; j < vectors[i].size(); j++) {
                result.push_back(vectors[i][j]);
            }
        }
        return result;
    }
} // namespace Common
