#ifndef MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#include <vector>
#include <string>

class TicTacToe;
#include "TicTacToe.h"

class Player{
public:
    Player(char type_, int point);
    virtual void makeMove(TicTacToe* game) = 0; // do I need virtual keyword?
    virtual ~Player();
    char getType() const;
    int getPoint() const;
private:
    char type; // X or O
    int point;
    // value of a score?
};


class HumanPlayer: public Player {
public:
    HumanPlayer(char type_, int point);
    void makeMove(TicTacToe* game) override;
};

class Node {
public:
    std::vector<int> field{};
    int value{};
    bool operator>(const Node& other) const {
        return value > other.value;
    }
    bool operator<(const Node& other) const {
        return value < other.value;
    }
    bool operator>=(const Node& other) const {
        return value >= other.value;
    }
    bool operator<=(const Node& other) const {
        return value <= other.value;
    }
    bool operator==(const Node& other) const {
        return value == other.value;
    }
};

class AIPlayer: public Player {
public:
    AIPlayer(char type_, int point);
    void makeMove(TicTacToe* game) override;
    Node MinMax(TicTacToe* game, const std::vector<int>& pos, int depth, bool maximizingPlayer);
};


#endif //MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
