#pragma once
#include <string>
#include <vector>

using namespace std;

const string CLAVE = "1234";
const int MAX_ATTEMPTS = 3;
const vector<int> KEY_ENTER = {13};
const vector<int> KEY_BACKSPACE = {8};
const vector<int> KEY_SPACE = {32};
const vector<int> KEY_ARROW_TOP = {224, 72};
const vector<int> KEY_ARROW_BOTTOM = {224, 80};
const vector<int> KEY_ARROW_LEFT = {224, 75};
const vector<int> KEY_ARROW_RIGHT = {224, 77};
const vector<int> KEY_ESCAPE = {27};

const vector<vector<int>> PRINTABLE_CHARS = {
        // Mayúsculas.
        {65}, {66}, {67}, {68}, {69}, {70}, {71}, {72}, {73}, {74}, {75}, {76}, {77}, {78}, {79}, {80}, {81}, {82}, {83}, {84}, {85}, {86}, {87}, {88}, {89}, {90},
        {195, 145}, // Ñ
        // Vocales con tilde mayúsculas
        {195, 129}, // Á
        {195, 137}, // É
        {195, 141}, // Í
        {195, 147}, // Ó
        {195, 154},  // Ú

        // Minúsculas
        {97}, {98}, {99}, {100}, {101}, {102}, {103}, {104}, {105}, {106}, {107}, {108}, {109}, {110}, {111}, {112}, {113}, {114}, {115}, {116}, {117}, {118}, {119}, {120}, {121}, {122},
        {195, 177}, // ñ

        // Vocales con tilde minúsculas
        {195, 161}, // á
        {195, 169}, // é
        {195, 173}, // í
        {195, 179}, // ó
        {195, 186}, // ú

        // Números
        {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {57},

        KEY_ENTER,
        KEY_BACKSPACE,
        KEY_SPACE
    };

const vector<vector<int>> NAVIGATION_KEYS = {
    KEY_ARROW_TOP,
    KEY_ARROW_LEFT,
    KEY_ARROW_BOTTOM,
    KEY_ARROW_RIGHT,
    KEY_ENTER,
    KEY_SPACE,
    KEY_ESCAPE
};
