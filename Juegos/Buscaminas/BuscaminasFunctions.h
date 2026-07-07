#pragma once
#include <iostream>
#include <array>
#include <vector>

namespace Minesweeper
{
    // ======================================================================
    // DATABASE
    // ======================================================================

    std::vector<std::vector<int>> CreateBackgroundBoard(int rows, int cols);

    void PlaceMines(std::vector<std::vector<int>>& board, int minesQuantity);

    void CountAdjacentMines(std::vector<std::vector<int>>& board);


    // ======================================================================
    // LOGICA
    // ======================================================================

    int SetMinesQuantity(int rows, int cols, int levelOption);

    int SetInitialFlagCount(int minesQuantity);

    int SetRowsByLevel(int levelOption);

    int SetColsByLevel(int levelOption);

    std::vector<std::vector<int>> CreatePageStateBoard(int rows, int cols);

    std::array<int, 2> GetInitialPosition(int rows, int cols);

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

    void RevealSafeRegionCommand(
        std::vector<std::vector<int>> backgroundBoard,
        std::vector<std::vector<int>>& stateBoard,
        int row,
        int col,
        std::string& feedbackMessage
    );

    void RevealCommand(
        std::vector<std::vector<int>> backgroundBoard,
        std::vector<std::vector<int>>& stateBoard,
        int row,
        int col,
        std::string& feedbackMessage);

    bool MineIsRevealed(
        std::vector<std::vector<int>> backgroundBoard,
        int row,
        int col,
        std::string& feedbackMessage);

    bool IsMoveKey(std::vector<int>& key);
    bool IsRevealKey(std::vector<int>& key);
    bool IsFlagKey(std::vector<int>& key);
    bool IsExitMatchKey(std::vector<int>& key);

    void MoveCommand(
        int& playerRow,
        int& playerCol,
        int rows,
        int cols,
        std::vector<int>& key);

    void FlagCommand(
        int& flagCount,
        std::vector<std::vector<int>>& stateBoard,
        int row,
        int col,
        std::string& feedbackMessage);

    // TODO definir la función
    bool IsWonGameState(std::vector<std::vector<int>>& stateBoard, int minesQuantity);
}
