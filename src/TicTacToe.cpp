#include "../include/TicTacToe.h"
#include <iostream>


TicTacToe::TicTacToe(int numRows, int numColumns, int winningF):
    rows(numRows), columns(numColumns), board(numRows, std::vector<int> (numColumns, 0)), wf(winningF), playerO('O', 1), playerX('X', -1){
}

void TicTacToe::play(bool isXTurn) {
    if (checkForEndState()) {
        //displayBoard();
        return;
    }
    if (empty()){
        //system("cls");
        displayBoard();
    }

    updateBoard(isXTurn);
    //system("cls"); // ZMIANA CHWILOWA - CHYBA
    displayBoard();

    play(not isXTurn);
}

void TicTacToe::displayBoard() {
    system("cls"); // tylko windows
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
    std::vector<int> pos(2);
    do {
        pos = currentPlayer->makeMove();
    } while(not isValidBoardField(pos));

    board[pos[0]][pos[1]] = currentPlayer->getPoint();
}

bool TicTacToe::checkForEndState() { // trzeba sprawdzac przeciez ciaglości wystepowania tych wartosci
    std::vector<int> winningRow(rows); // w sumie nie trzeba tych danych zapisywac na później
    std::vector<int> winningColumn(columns);

    for (int row{0}; row < rows; ++row){ // A CO JEŚLI ROBIĆ TO OD 1 I WRACAĆ??
        for (int column{0}; column < columns; ++column){ // JEŚLI MAMY ZMIANĘ ZNAKU TO WYZERUJ
// te nazyw są troszke mylące czy zmienić?
            if (column - 1 < 0 or board[row][column] == board[row][column - 1]) {
                winningRow[row] += board[row][column]; // JESCZE JEśli wczesnieje pole to było O
            } else if (board[row][column] != board[row][column - 1]) { // ZMIANA ZNAKU NA OBECNY MOŻE JEDNA JAKAS FLAGA "JEDNEGO ZNAKU"
                winningRow[row] = board[row][column];
            }
            if (column - 1 < 0 or board[column][row] == board[column - 1][row]) {
                winningColumn[row] += board[column][row];
            } else if (board[column][row] != board[column - 1][row]){
                winningColumn[row] = board[column][row];
            }

            if (winningRow[row] == playerO.getPoint() * wf or winningRow[row] == playerX.getPoint() * wf){
                printWinner(winningRow[row]);
                return true;
            }
            if (winningColumn[row] == playerO.getPoint() * wf or winningColumn[row] == playerX.getPoint() * wf){
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

                if (winningAcrossLeft[diagonal] == playerO.getPoint() * wf or winningAcrossLeft[diagonal] == playerX.getPoint() * wf){
                    printWinner(winningAcrossLeft[diagonal]);
                    return true;
                }
            }
            ++diagonal;
        }
    }

    diagonal = 0;
    std::vector<int> winningAcrossRight(numOfDiagonals);
    //wf - 1 == 2
    for (int row{0}; row < wf - 1 ; ++row){
        for (int column{columns - 1}; column > columns - wf; --column) {
            for (int k{0}; k < rows - row  and column - k >= 0; ++k){ // zamiast rows może size??
                if ((k + row - 1 < 0) or (column - k + 1 >= rows) or board[row + k][column - k] == board[row + k - 1][column - k + 1]) {
                    winningAcrossRight[diagonal] += board[row + k][column - k];
                } else if (board[row + k][column - k] != board[row + k - 1][column - k + 1]) {
                    winningAcrossRight[diagonal] = board[row + k][column - k];
                }
                if (winningAcrossRight[diagonal] == playerO.getPoint() * wf or winningAcrossRight[diagonal] == playerX.getPoint() * wf){
                    printWinner(winningAcrossRight[diagonal]);
                    return true;
                }
            }
            ++diagonal;
        }
    }
                    
    for (int row{0}; row < rows; ++row) {
        for (int column{0}; column < columns; ++column) {
            if (board[row][column] == 0) {
                return false; // empty space left
            }
        }
    }
    printWinner(0);
    return true; // tie
}

bool TicTacToe::empty() {
    for (int row{0}; row < rows; ++row){
        for (int column{0}; column < columns; ++column) {
            if (board[row][column] != 0) {
                return false;
            }
        }
    }
    return true;
}

void TicTacToe::printWinner(int winningScore) {
    if (winningScore == playerO.getPoint() * wf)
        std::cout << "Player O won!" << std::endl;
    else if (winningScore == playerX.getPoint() * wf)
        std::cout << "Player X won!" << std::endl;
    else
        std::cout << "It's a tie!" << std::endl;
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

bool TicTacToe::isValidBoardField(std::vector<int> pos) {
    int chosenRow{pos[0]};
    int chosenColumn{pos[1]};

    if (chosenRow < 0 or chosenRow >= rows or chosenColumn < 0 or chosenColumn >= columns)
        return false;

    if (board[chosenRow][chosenColumn] != 0) // czy get board score było by nessecary - to już jak specyfikatory ja po dodawałam (czy dobrze??)
        return false;

    return true;

}


