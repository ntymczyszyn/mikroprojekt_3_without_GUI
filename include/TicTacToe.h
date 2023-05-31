#ifndef MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
#define MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
#include <vector>
#include <string>
class Player;
class HumanPlayer;
class AIPlayer;
#include "Player.h"


class TicTacToe {
public:
    TicTacToe(int numRows, int numColumns, int winningF);
    ~TicTacToe();

    void play(bool XTurn); // true == playerO
    void displayBoard();
    void updateBoard(bool XTurn);

    bool isGameOver(bool printWin);
    void printWinner(const int& winningScore, bool print);

    bool empty();
    bool isValidBoardField(const std::vector<int>& pos);
    std::vector<std::vector<int>> availableMoves();
    int emptyBoardFields();

    std::vector<std::vector<int>> board;
    Player* winner;
    Player* playerO; // or maybe pointers??
    Player* playerX; // how to change to use Player class here
private:
    std::string whichSign(const int& score); // what static does??
    int rows;
    int columns;
    int wf; // wining fields

    //friend class Player;

};
#endif //MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
