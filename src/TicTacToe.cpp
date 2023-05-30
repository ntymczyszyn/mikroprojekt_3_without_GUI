#include "../include/TicTacToe.h"
#include <iostream>
#include <algorithm>

TicTacToe::TicTacToe(int numRows, int numColumns, int winningF):
    rows(numRows), columns(numColumns), board(numRows, std::vector<int> (numColumns, 0)), wf(winningF){
    playerO = new HumanPlayer('O', 1);
    playerX = new HumanPlayer('X', -1);
}

TicTacToe::~TicTacToe() {
    delete playerO;
    delete playerX;
}

void TicTacToe::play(bool isXTurn) {
    if (isGameOver()) {
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
    system("clear"); // tylko windows <-'cls'; linux 'claer'
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
    std::cout << emptyBoardFields() << std::endl;
}

void TicTacToe::updateBoard(bool XTurn) {
    Player* currentPlayer{};
    if (not XTurn)
        currentPlayer = playerO;
    else
       currentPlayer = playerX;

    currentPlayer->makeMove(this);
}

bool TicTacToe::isGameOver() {
    std::vector<int> winningRow(rows); // w sumie nie trzeba tych danych zapisywac na później
    std::vector<int> winningColumn(columns);

    for (int row{0}; row < rows; ++row){
        for (int column{0}; column < columns; ++column){
// te nazyw są troszke mylące czy zmienić?
            if (column - 1 < 0 or board[row][column] == board[row][column - 1]) {
                winningRow[row] += board[row][column];
            } else if (board[row][column] != board[row][column - 1]) {
                winningRow[row] = board[row][column];
            }
            if (column - 1 < 0 or board[column][row] == board[column - 1][row]) {
                winningColumn[row] += board[column][row];
            } else if (board[column][row] != board[column - 1][row]){
                winningColumn[row] = board[column][row];
            }

            if (winningRow[row] == playerO->getPoint() * wf or winningRow[row] == playerX->getPoint() * wf){
                printWinner(winningRow[row]);
                return true;
            }
            if (winningColumn[row] == playerO->getPoint() * wf or winningColumn[row] == playerX->getPoint() * wf){
                printWinner(winningColumn[row]);
                return true;
            }
        }

        
    }

    int numOfDiagonals{(rows - wf) * 2 + 1};
    int diagonal{0};
    std::vector<int> winningAcrossLeft(numOfDiagonals);

    for (int row{0}; row < wf - 1 ; ++row){
        for (int column{0}; column < wf - 1; ++column) {
            for (int k{0}; k < rows - row and k < columns - column; ++k){
                if (k + row - 1 < 0 or k + column - 1 < 0 or board[k + row][k + column] == board[k + row - 1][k + column - 1]) {
                    winningAcrossLeft[diagonal] += board[k + row][k + column];
                } else if (board[k + row][k + column] != board[k + row - 1][k + column - 1]){
                    winningAcrossLeft[diagonal] = board[k + row][k + column];
                }

                if (winningAcrossLeft[diagonal] == playerO->getPoint() * wf or winningAcrossLeft[diagonal] == playerX->getPoint() * wf){
                    printWinner(winningAcrossLeft[diagonal]);
                    return true;
                }
            }
            ++diagonal;
        }
    }

    diagonal = 0;
    std::vector<int> winningAcrossRight(numOfDiagonals);

    for (int row{0}; row < wf - 1 ; ++row){
        for (int column{columns - 1}; column > columns - wf; --column) {
            for (int k{0}; k < rows - row  and column - k >= 0; ++k){ // zamiast rows może size??
                if ((k + row - 1 < 0) or (column - k + 1 >= rows) or board[row + k][column - k] == board[row + k - 1][column - k + 1]) {
                    winningAcrossRight[diagonal] += board[row + k][column - k];
                } else if (board[row + k][column - k] != board[row + k - 1][column - k + 1]) {
                    winningAcrossRight[diagonal] = board[row + k][column - k];
                }
                if (winningAcrossRight[diagonal] == playerO->getPoint() * wf or winningAcrossRight[diagonal] == playerX->
                getPoint() * wf){
                    printWinner(winningAcrossRight[diagonal]);
                    return true;
                }
            }
            ++diagonal;
        }
    }

    if (emptyBoardFields() != 0)
        return false;

    printWinner(0);
    return true; // tie
}

bool TicTacToe::empty() {
    return emptyBoardFields() == rows * columns;
}

void TicTacToe::printWinner(const int& winningScore) {
    if (winningScore == playerO->getPoint() * wf)
        std::cout << "Player O won!" << std::endl;
    else if (winningScore == playerX->getPoint() * wf)
        std::cout << "Player X won!" << std::endl;
    else
        std::cout << "It's a tie!" << std::endl;
}

std::string TicTacToe::whichSign(const int& score) {
    if (score == playerO->getPoint())
        return "O";
    else if (score == playerX->getPoint())
        return "X";
    else
        return " ";
}

bool TicTacToe::isValidBoardField(const std::vector<int>& pos) {
    std::vector<std::vector<int>> available = availableMoves();
    return std::find(available.begin(), available.end(), pos) != available.end();
}

std::vector<std::vector<int>> TicTacToe::availableMoves() {
    std::vector<std::vector<int>> emptyBoardFields;

    for (int i {0}; i < rows; ++i){
        for (int j{0}; j < columns; ++j){
            if (board[i][j] == 0)
                emptyBoardFields.push_back({i, j});
        }
    }
    return  emptyBoardFields;
}

int TicTacToe::emptyBoardFields() {
    return availableMoves().size();
}




