#include "../include/TicTacToe.h"
#include <iostream>
#include <algorithm>
//#include <fmt/core.h>

// coś jest chyba nie tak z użytkowaniem vectorów - > trzeba była

TicTacToe::TicTacToe(int numRows, int numColumns, int winningF):
    rows(numRows), columns(numColumns), board(numRows, std::vector<int> (numColumns, 0)), wf(winningF), playerO('O'), playerX('X'){
    //std::fill(board.begin(), board.end(), std::vector<int>(columns, 0)); // why it wasn't working ??
    board[0][0] = 1;
    board[1][1] = 1;
    board[2][2] = 2;
}

void TicTacToe::play(bool XTurn) { // should I change the name
    std::cout << "play" << std::endl;
    if (checkForEndState() and not empty()){
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
    for (int i{0}; i < 3; ++i)
        std::cout << "-------";
    std::cout << std::endl;

    for (int row{0}; row < rows; ++row){
        std::cout << row + 1 << " |";
        for (int column{0}; column < columns; ++column) {
            std::cout << "  " << whichSign(board[row][column]) << "  |";

        }
        std::cout << std::endl;
        for (int i{0}; i < 3; ++i)
            std::cout << "-------";
        std::cout << std::endl;
    }
}

void TicTacToe::updateBoard(Player* currentPlayer) {
    std::string pos = currentPlayer->makeMove();
    int currentRow{static_cast<int>(pos[0]) - 1}; // should it be different cast??
    int currentColumn{static_cast<int>(pos[1]) - 41}; // so that A = 0, B = 1

    if (currentPlayer->getType() == 'O'){
        board[currentRow][currentColumn] = 1;
    }
    else {
        board[currentRow][currentColumn] = 2;
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
        if (winningRow == 1 * wf or winningRow == 2 * wf)   {
            return true;
        }
        else {
            winningRow = 0;
        }
    }
    int winningColumn{};
    for (unsigned int column{0}; column < columns; ++column){ // TODO: refactor this part
        for (unsigned int row{0}; row < rows; ++row){
            winningColumn += board[row][column];
        }
        if (winningColumn == 1 * wf or winningColumn == 2 * wf)   {
            return true;
        }
        else {
            winningColumn = 0;
        }
    }
    int winningAcrossLeft{};
    int winningAcrossRight{};
    for (unsigned int row{0}; row < rows; ++row){ // TODO: refactor this part
            winningAcrossLeft += board[row][row];
            winningAcrossRight+= board[rows - row][rows - row]; // assuming it will be square
    }
        if (winningAcrossLeft == 1 * wf or winningAcrossLeft == 2 * wf)   {
            return true;
        }
        else if (winningAcrossRight == 1 * wf or winningAcrossRight== 2 * wf) {
            return true;
        }

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

Player::Player(char type_): type(type_) {
}

std::string Player::makeMove() {
    std::string chosenRow{};
    std::string chosenColumn{};
    // while loop
    std::cout << "Your turn" << this->type <<" ! Chose your field: " << std::endl;
    std::cin >> chosenRow;
    std::cin >> chosenColumn;
    return chosenRow + chosenColumn; // how to change to proper casting??
    // why can't I use c++20 features
    // check if the field is not already taken
    // check if it is within the boundaries
    // for now let's assume that it is always correct
    // for now there are strings
}

char Player::getType() const{
    return this->type;
}
