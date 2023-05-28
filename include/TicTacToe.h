#ifndef MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
#define MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
#include <vector>
#include <string>
#include "Player.h"
#include "HumanPlayer.h"


class TicTacToe {
public:
    TicTacToe(int numRows, int numColumns, int winningF);

    void play(bool XTurn); // true == playerO
    void displayBoard();
    void updateBoard(bool XTurn);
    bool checkForEndState();
    void printWinner(int winningScore);
    bool empty();

private:
    std::string whichSign(const int& score); // what static does??
    std::vector<std::vector<int>> board; // size will be
    int rows;
    int columns;
    int wf; // wining fields
    HumanPlayer playerO; // or maybe pointers??
    HumanPlayer playerX; // how to change to use Player class here
    friend class Player;
};
#endif //MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
