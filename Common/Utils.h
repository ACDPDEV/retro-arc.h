#pragma once

#include <string>
#include <vector>

using namespace std;

vector<string> CutString(string str, int width) {
    string buffer;
    vector<string> result;
    while (buffer.size() < width) {
        result.push_back(buffer.substr(0, width));
        buffer = str.substr(buffer.size(), width);
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

int MaxStringLength(vector<string> strings) {
    int maxLength = 0;
    for (int i = 0; i < strings.size(); i++) {
        if (strings[i].size() > maxLength) {
            maxLength = strings[i].size();
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
