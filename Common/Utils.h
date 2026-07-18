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
