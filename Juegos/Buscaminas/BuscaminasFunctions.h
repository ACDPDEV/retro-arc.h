#ifndef BUSCAMINAS_FUNCTIONS_H
#define BUSCAMINAS_FUNCTIONS_H

#pragma once
#include <vector>

// ======================================================================
// DATABASE
// ======================================================================

vector<vector<int>> CreateBackgroundBoard(int rows, int cols);

void PlaceMines(vector<vector<int>>& board, int minesQuantity) ;

void CountAdjacentMines(vector<vector<int>>& board);


// ======================================================================
// LOGICA
// ======================================================================

vector<vector<int>> CreatePageStateBoard(int rows, int cols);

void ExecuteAction(vector<vector<int>>& stateBoard, int r, int c, int action);

#endif