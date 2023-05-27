#include "../include/TicTacToe.h"
#include <iostream>


TicTacToe::TicTacToe(int numRows, int numColumns, int winningF):
    rows(numRows), columns(numColumns), board(numRows, std::vector<int> (numColumns, 0)), wf(winningF), playerO('O', 1), playerX('X', -1){
}

void TicTacToe::play(bool isXTurn) {
    if (checkForEndState()) {
        std::cout << "end state" << std::endl;
        displayBoard();
        return;
    }
    if (empty()){
        displayBoard();
    }

    updateBoard(isXTurn);
    displayBoard();

    play(not isXTurn);
}

void TicTacToe::displayBoard() {
    system("cls");
    constexpr int AinASCII{65};
    for (char columnLetter{AinASCII}; columnLetter < columns + AinASCII; ++columnLetter){
        std::cout << "     " << columnLetter;
    }
    std::cout << std::endl;

    for (int i{0}; i < rows; ++i){
        if (i == 0)
            std::cout << "---";
        std::cout << "------";
    }
    std::cout << std::endl;

    for (int row{0}; row < rows; ++row){
        std::cout << row + 1 << " |";
        for (int column{0}; column < columns; ++column) {
            std::cout << "  " << whichSign(board[row][column]) << "  |";

        }
        std::cout << std::endl;
        for (int i{0}; i < rows; ++i){
            if (i == 0)
                std::cout << "---";
            std::cout << "------";
        }
        std::cout << std::endl;
    }
}

void TicTacToe::updateBoard(bool XTurn) {
    Player* currentPlayer{};
    if (not XTurn){
        currentPlayer = &playerO;
    }
    else {
       currentPlayer = &playerX;
    }
    std::vector<int> pos = currentPlayer->makeMove();
    board[pos[0]][pos[1]] = currentPlayer->getPoint();
}

bool TicTacToe::checkForEndState() {
    std::vector<int> winningRow(rows);
    std::vector<int> winningColumn(columns);

    for (int row{0}; row < rows; ++row){
        for (int column{0}; column < columns; ++column){
            winningRow[row] += board[row][column];
            winningColumn[row] += board[column][row];
        }
    }
    for (const auto& winRow : winningRow){
        if (winRow == 1 * wf or winRow == -1 * wf){
            return true;
        }
    }
    for (const auto& winCol : winningColumn){
        if (winCol == 1 * wf or winCol == -1 * wf){
            return true;
        }
    }

//    std::vector<int> winningAcrossLeft((rows - wf) * 2 + 1);
//    std::vector<int> winningAcrossRight((rows - wf) * 2 + 1);
//
//    for (unsigned int row{0}; row < rows; ++row){
//            winningAcrossLeft += board[row][row];
//            winningAcrossRight += board[rows - row - 1][rows - row - 1]; // assuming it will be square
//    }
//        if (winningAcrossLeft == 1 * wf or winningAcrossLeft == -1 * wf)   {
//            return true;
//        }
//        else if (winningAcrossRight == 1 * wf or winningAcrossRight== -1 * wf) {
//            return true;
//        }
//
//    for (const auto& winLeft : winningAcrossLeft){
//        if (winLeft == 1 * wf or winLeft == -1 * wf){
//            return true;
//        }
//    }
//    for (const auto& winRight : winningAcrossRight){
//        if (winRight == 1 * wf or winRight == -1 * wf){
//            return true;
//        }
//    }

    for (int row{0}; row < rows; ++row) {
        for (int column{0}; column < columns; ++column) {
            if (board[row][column] == 0) {
                return false; // empty space left
            }
        }
    }

    return true; // tie
}

bool TicTacToe::empty() {
    for (int row{0}; row < rows; ++row){ // TODO: refactor this part
        for (int column{0}; column < columns; ++column) {
            if (board[row][column] != 0) {
                return false;
            }
        }
    }
    return true;
}

std::string TicTacToe::whichSign(const int& score) {
    if (score == playerO.getPoint()) {
        return "O";
    }
    else if (score == playerX.getPoint()){
        return "X";
    }
    else {
        return " ";
    }
}


