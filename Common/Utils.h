#pragma once

#include <array>
#include <string>
#include <vector>

using namespace std;

int Length(const std::string& str) {
    int count = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = str[i];

        // Secuencia de escape ANSI: no cuenta como carácter visible
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

vector<string> CutString(const string& str, size_t width) {
    vector<string> result;
    if (width == 0) return result;

    size_t offset = 0;
    while (offset < Length(str)) {
        result.push_back(str.substr(offset, width));
        offset += width;
    }
    return result;
}

string InvertString(string str) {
    string result;
    for (int i = str.size() - 1; i >= 0; i--) {
        result = str[i] + result;
    }
    return result;
}

string MaxString(vector<string> strings) {
    string maxLength;
    for (int i = 0; i < strings.size(); i++) {
        if (Length(strings[i]) > Length(maxLength)) {
            maxLength = strings[i];
        }
    }
    return maxLength;
}

string RepeatString(string str, int count) {
    string result;
    for (int i = 0; i < count; i++) {
        result += str;
    }
    return result;
}

vector<string> ArrayToVector(array<string, 9> arr) {
    vector<string> result;
    for (int i = 0; i < arr.size(); i++) {
        result.push_back(arr[i]);
    }
    return result;
}
