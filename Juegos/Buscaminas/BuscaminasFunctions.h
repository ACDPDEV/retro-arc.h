#pragma once
#include <iostream>
#include <array>
#include <vector>
using namespace std;

// ======================================================================
// DATABASE
// ======================================================================

vector<vector<int>> CreateBackgroundBoard(int rows, int cols);

void PlaceMines(vector<vector<int>>& board, int minesQuantity) ;

void CountAdjacentMines(vector<vector<int>>& board);


// ======================================================================
// LOGICA
// ======================================================================

int SetMinesQuantity(int rows, int cols, int levelOption);

int SetRowsByLevel(int levelOption);

int SetColsByLevel(int levelOption);

vector<vector<int>> CreatePageStateBoard(int rows, int cols);

array<int, 2> GetInitialPosition(int rows, int cols);

// ----------------------------
// STATE BOARD - getters setters validators
// ----------------------------
int GetStateValueSafe();
int GetStateValueFlagged();
int GetStateValueHidden();
bool StateValueIsHidden(int stateValue);
bool StateValueIsFlagged(int stateValue);
bool StateValueIsRevealed(int stateValue);

// ----------------------------
// BACKGROUND BOARD - getters setters validators
// ----------------------------
bool BackgroundValueIsSafe(int backgroundValue);
bool BackGroundValueIsAdjacent(int backgroundValue);
int GetBackGroundValueSafe();

bool VectorContainsTuple(vector<tuple<int, int>>& vec, tuple<int, int> tup);

void RevealSafeRegionCommand(
    vector<vector<int>> backgroundBoard, 
    vector<vector<int>>& stateBoard, 
    int row, 
    int col, 
    string& feedbackMessage
);

void RevealCommand(
    vector<vector<int>> backgroundBoard, 
    vector<vector<int>>& stateBoard, 
    int row, 
    int col, 
    string& feedbackMessage);

bool MineIsRevealed(vector<vector<int>> backgroundBoard, int row, int col, string& feedbackMessage);

bool IsMoveKey(vector<int>& key);
bool IsRevealKey(vector<int>& key);
bool IsFlagKey(vector<int>& key);
bool IsExitMatchKey(vector<int>& key);

void MoveCommand(int& playerRow, int& playerCol, int rows, int cols, vector<int>& key);

void FlagCommand(
    int& flagCount,
    vector<vector<int>>& stateBoard, 
    int row, 
    int col, 
    string& feedbackMessage);

// TODO definir la función
bool IsWonGameState();
