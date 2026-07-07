#pragma once

#include <array>
#include <string>
#include <vector>

namespace Common
{
    int Length(std::string str) {
        int count = 0;
        for (size_t i = 0; i < str.size(); ) {
            unsigned char c = str[i];
            if ((c & 0x80) == 0x00) i += 1;
            else if ((c & 0xE0) == 0xC0) i += 2;
            else if ((c & 0xF0) == 0xE0) i += 3;
            else if ((c & 0xF8) == 0xF0) i += 4;
            else i += 1;
            count++;
        }
        return count;
    }
    
    std::vector<std::string> CutString(const std::string& str, size_t width) {
        std::vector<std::string> result;
        if (width == 0) return result;
    
        size_t offset = 0;
        while (offset < Length(str)) {
            result.push_back(str.substr(offset, width));
            offset += width;
        }
        return result;
    }
    
    std::string InvertString(std::string str) {
        std::string result;
        for (int i = str.size() - 1; i >= 0; i--) {
            result = str[i] + result;
        }
        return result;
    }
    
    int MaxStringLength(std::vector<std::string> strings) {
        int maxLength = 0;
        for (int i = 0; i < strings.size(); i++) {
            if (Length(strings[i]) > maxLength) {
                maxLength = Length(strings[i]);
            }
        }
        return maxLength;
    }
    
    std::string RepeatString(std::string str, int count) {
        std::string result;
        for (int i = 0; i < count; i++) {
            result += str;
        }
        return result;
    }
    
    std::vector<std::string> ArrayToVector(std::array<std::string, 9> arr) {
        std::vector<std::string> result;
        for (int i = 0; i < arr.size(); i++) {
            result.push_back(arr[i]);
        }
        return result;
    }
}
