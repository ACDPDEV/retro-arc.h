#include <string>
using namespace std;

bool Validate(string input, string type) {
    if (type == "int") {
        return isdigit(input[0]);
    } else if (type == "float") {
        return isdigit(input[0]) || input[0] == '.';
    } else if (type == "string") {
        return true;
    } else if (type == "char") {
        return isalpha(input[0]);
    } else if (type == "bool") {
        return input == "true" || input == "false";
    } else {
        return false;
    }
}

int parseInt(string str) {
    return stoi(str);
}

float parseFloat(string str) {
    return stof(str);
}

char parseChar(string str) {
    return str[0];
}

bool parseBool(string str) {
    return str == "true";
}
