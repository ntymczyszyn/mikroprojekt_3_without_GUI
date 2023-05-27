#include "../include/TicTacToe.h"
#include <iostream>

// coś jest chyba nie tak z użytkowaniem vectorów - > trzeba był0 jednak inaczej inicjować

TicTacToe::TicTacToe(int numRows, int numColumns, int winningF):
    rows(numRows), columns(numColumns), board(numRows, std::vector<int> (numColumns, 0)), wf(winningF), playerO('O'), playerX('X'){
//    board[0][0] = 1;
//    board[1][1] = 1;
//    board[2][2] = 2;
}

void TicTacToe::play(bool XTurn) { // should I change the name
    std::cout << "play" << std::endl;
    if (checkForEndState()){
        std::cout << "end state" << std::endl;
        displayBoard();
        return;
    }

    if (XTurn){
        std::cout << "XTurn" << std::endl;
        updateBoard(&playerX);

    }
    else {
        std::cout << "OTurn" << std::endl;
        updateBoard(&playerO);
    }
    //if(not empty()){
    displayBoard();

    play(not XTurn);
} // definitely up for checkup

void TicTacToe::displayBoard() {
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

void TicTacToe::updateBoard(Player* currentPlayer) {
    std::vector<int> pos = currentPlayer->makeMove();
    int currentRow{pos[0]}; // should it be different cast??
    int currentColumn{pos[1]}; // so that A = 0, B = 1

    if (currentPlayer->getType() == 'O'){
        board[currentRow][currentColumn] = 1;
    }
    else {
        board[currentRow][currentColumn] = - 1; // changed form 2
    }

}

bool TicTacToe::checkForEndState() {
    // if in row the same number
    // if in column the same number
    // if on the diagonal
    int winningRow{};

    for (unsigned int row{0}; row < rows; ++row){ // TODO: refactor this part
        for (unsigned int column{0}; column < columns; ++column){
            winningRow += board[row][column];
        }
        if (winningRow == 1 * wf or winningRow == -1 * wf)   {
            return true;
        }
        else {
            winningRow = 0;
        }
    }
    std::cout << "after row" << std::endl;
    int winningColumn{};
    for (unsigned int column{0}; column < columns; ++column){ // TODO: refactor this part
        for (unsigned int row{0}; row < rows; ++row){
            winningColumn += board[row][column];
        }
        if (winningColumn == 1 * wf or winningColumn == -1 * wf)   {
            return true;
        }
        else {
            winningColumn = 0;
        }
    }
    std::cout << "after column" << std::endl;
    int winningAcrossLeft{};
    int winningAcrossRight{};
    for (unsigned int row{0}; row < rows; ++row){ // TODO: refactor this part
            winningAcrossLeft += board[row][row];
            winningAcrossRight += board[rows - row - 1][rows - row - 1]; // assuming it will be square
    }
        if (winningAcrossLeft == 1 * wf or winningAcrossLeft == -1 * wf)   {
            return true;
        }
        else if (winningAcrossRight == 1 * wf or winningAcrossRight== -1 * wf) {
            return true;
        }
    std::cout << winningRow << " " << winningColumn << " " << winningAcrossLeft << " " << winningAcrossRight << std::endl;
    for (unsigned int row{0}; row < rows; ++row){ // TODO: refactor this part
        for (unsigned int column{0}; column < columns; ++column){
           if (board[row][column] == 0){
               return false; // empty space left
           }
        }

    }
    return true; // tie
}

bool TicTacToe::empty() {
    for (unsigned int row{0}; row < rows; ++row){ // TODO: refactor this part
        for (unsigned int column{0}; column < columns; ++column) {
            if (board[row][column] != 0) {
                return false;
            }
        }
    }
    return true;
}

std::string TicTacToe::whichSign(int score) {
    if (score == 0){
        return " ";
    }
    else if (score == 1) {
        return "O";
    }
    else {
        return "X";
    }

}


