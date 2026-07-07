#pragma once
#include <string>
#include <vector>

using namespace std;

const string CLAVE = "1234";
const int MAX_ATTEMPTS = 3;
const int WIDTH_SCREEN = 200;
const int HEIGHT_SCREEN = 50;
const int MAX_FEEDBACK_MESSAGE_LENGTH = 80;

// ACTION KEYS
const vector<int> KEY_ENTER = {13};
const vector<int> KEY_SPACE = {32};
const vector<int> KEY_BACKSPACE = {8};
const vector<int> KEY_ESCAPE = {27};

// NAVIGATION KEYS
const vector<int> KEY_ARROW_TOP = {224, 72};
const vector<int> KEY_ARROW_LEFT = {224, 75};
const vector<int> KEY_ARROW_BOTTOM = {224, 80};
const vector<int> KEY_ARROW_RIGHT = {224, 77};

const vector<int> KEY_ARROW_TOP_2 = {0, 72};
const vector<int> KEY_ARROW_LEFT_2 = {0, 75};
const vector<int> KEY_ARROW_BOTTOM_2 = {0, 80};
const vector<int> KEY_ARROW_RIGHT_2 = {0, 77};

const vector<vector<int>> NAVIGATION_KEYS = {
    KEY_ARROW_TOP,
    KEY_ARROW_LEFT,
    KEY_ARROW_BOTTOM,
    KEY_ARROW_RIGHT,
    KEY_ARROW_TOP_2,
    KEY_ARROW_LEFT_2,
    KEY_ARROW_BOTTOM_2,
    KEY_ARROW_RIGHT_2,
};

const vector<vector<int>> ACTION_KEYS = {
    KEY_ENTER,
    KEY_SPACE
};

// LETRAS EN MAYÚSCULA
const vector<int> KEY_A = {65};
const vector<int> KEY_B = {66};
const vector<int> KEY_C = {67};
const vector<int> KEY_D = {68};
const vector<int> KEY_E = {69};
const vector<int> KEY_F = {70};
const vector<int> KEY_G = {71};
const vector<int> KEY_H = {72};
const vector<int> KEY_I = {73};
const vector<int> KEY_J = {74};
const vector<int> KEY_K = {75};
const vector<int> KEY_L = {76};
const vector<int> KEY_M = {77};
const vector<int> KEY_N = {78};
const vector<int> KEY_O = {79};
const vector<int> KEY_P = {80};
const vector<int> KEY_Q = {81};
const vector<int> KEY_R = {82};
const vector<int> KEY_S = {83};
const vector<int> KEY_T = {84};
const vector<int> KEY_U = {85};
const vector<int> KEY_V = {86};
const vector<int> KEY_W = {87};
const vector<int> KEY_X = {88};
const vector<int> KEY_Y = {89};
const vector<int> KEY_Z = {90};
const vector<int> KEY_ENYE_CAPS = {195, 145}; // Ñ

// VOCALES EN MAYÚSCULA
const vector<int> KEY_A_ACCENT_CAPS = {195, 129}; // Á
const vector<int> KEY_E_ACCENT_CAPS = {195, 137}; // É
const vector<int> KEY_I_ACCENT_CAPS = {195, 141}; // Í
const vector<int> KEY_O_ACCENT_CAPS = {195, 147}; // Ó
const vector<int> KEY_U_ACCENT_CAPS = {195, 154}; // Ú

// LETRAS EN MINÚSCULA
const vector<int> KEY_A_LOWER = {97};
const vector<int> KEY_B_LOWER = {98};
const vector<int> KEY_C_LOWER = {99};
const vector<int> KEY_D_LOWER = {100};
const vector<int> KEY_E_LOWER = {101};
const vector<int> KEY_F_LOWER = {102};
const vector<int> KEY_G_LOWER = {103};
const vector<int> KEY_H_LOWER = {104};
const vector<int> KEY_I_LOWER = {105};
const vector<int> KEY_J_LOWER = {106};
const vector<int> KEY_K_LOWER = {107};
const vector<int> KEY_L_LOWER = {108};
const vector<int> KEY_M_LOWER = {109};
const vector<int> KEY_N_LOWER = {110};
const vector<int> KEY_O_LOWER = {111};
const vector<int> KEY_P_LOWER = {112};
const vector<int> KEY_Q_LOWER = {113};
const vector<int> KEY_R_LOWER = {114};
const vector<int> KEY_S_LOWER = {115};
const vector<int> KEY_T_LOWER = {116};
const vector<int> KEY_U_LOWER = {117};
const vector<int> KEY_V_LOWER = {118};
const vector<int> KEY_W_LOWER = {119};
const vector<int> KEY_X_LOWER = {120};
const vector<int> KEY_Y_LOWER = {121};
const vector<int> KEY_Z_LOWER = {122};
const vector<int> KEY_ENYE_LOWER = {195, 177}; // ñ

// VOCALES CON ACENTO EN MINÚNCULA
const vector<int> KEY_A_ACCENT_LOWER = {195, 161}; // á
const vector<int> KEY_E_ACCENT_LOWER = {195, 169}; // é
const vector<int> KEY_I_ACCENT_LOWER = {195, 173}; // í
const vector<int> KEY_O_ACCENT_LOWER = {195, 179}; // ó
const vector<int> KEY_U_ACCENT_LOWER = {195, 186}; // ú

// NÚMEROS
const vector<int> KEY_0 = {48};
const vector<int> KEY_1 = {49};
const vector<int> KEY_2 = {50};
const vector<int> KEY_3 = {51};
const vector<int> KEY_4 = {52};
const vector<int> KEY_5 = {53};
const vector<int> KEY_6 = {54};
const vector<int> KEY_7 = {55};
const vector<int> KEY_8 = {56};
const vector<int> KEY_9 = {57};

const vector<vector<int>> ALPHA_NUM_CHARS = {
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
        {48}, {49}, {50}, {51}, {52}, {53}, {54}, {55}, {56}, {57}
};
