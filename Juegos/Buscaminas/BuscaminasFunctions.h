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

int GetUserKey(string& feedbackMessage);

int SetOption(int& option, int minOption, int maxOption, int userKey);

bool CanExcecuteOption(int userKey);

bool BuscaminasIsValidOption(int option, vector<int>& validOptions);

int SetRowsByLevel(int levelOption);

int SetColsByLevel(int levelOption);

vector<vector<int>> CreatePageStateBoard(int rows, int cols);

array<int, 2> GetInitialPosition(int rows, int cols);

void ExecuteAction(vector<vector<int>>& stateBoard, int r, int c, int action,string& feedbackMessage);

// TODO definir la función
bool IsWonGameState();
