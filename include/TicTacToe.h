#ifndef MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
#define MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
#include <vector>
#include <string>

class Player{
public:
    Player(char type_);
    std::string makeMove();
    //bool validateMove();
    char getType() const;
private:
    char type; // X or O
};

class TicTacToe {
public:
    TicTacToe(int numRows, int numColumns, int winningF);

    void play(bool XTurn); // true == playerO
    void displayBoard();
    void updateBoard(Player* currentPlayer);
    bool checkForEndState(); // to check if current board is a winning one or a tie
    void printWinner();
    bool empty();

private:
    std::string whichSign(int score);
    std::vector<std::vector<int>> board; // size will be
    //int* boardd;
    int rows;
    int columns;
    int wf; //winingfields
    Player playerO; // or maybe pointers??
    Player playerX;
    friend class Player;
};
#endif //MIKROPROJEKT_3_WITHOUT_GUI_TICTACTOE_H
