#ifndef MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#include <vector>
#include <string>
#include <fstream>

class TicTacToe;
#include "TicTacToe.h"

class Player{
public:
    Player(char type_, int point);
    virtual void makeMove(TicTacToe* game) = 0;
    virtual ~Player();
    char getType() const;
    int getPoint() const;
private:
    char type; // X or O
    int point;
};


class HumanPlayer: public Player {
public:
    HumanPlayer(char type_, int point);
    void makeMove(TicTacToe* game) override;
};

class Move {
public:
    std::vector<int> field{};
    int value{};
    bool operator>(const Move& other) const {
        return value > other.value;
    }
    bool operator<(const Move& other) const {
        return value < other.value;
    }
    bool operator>=(const Move& other) const {
        return value >= other.value;
    }
    bool operator<=(const Move& other) const {
        return value <= other.value;
    }
    bool operator==(const Move& other) const {
        return value == other.value;
    }
};

class AIPlayer: public Player {
public:
    AIPlayer(char type_, int point, int maxdepth_);
    void makeMove(TicTacToe* game) override;
    Move MinMax(TicTacToe* game, const std::vector<int>& pos, int alpha, int beta,  int depth, bool maximizingPlayer);
    int evaluate( TicTacToe* game, bool finished);
    std::ofstream file;
private:
    int maxdepth;
};


#endif //MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
