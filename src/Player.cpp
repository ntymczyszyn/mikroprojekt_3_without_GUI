#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <algorithm>
#include "../include/Player.h"

Player::Player(char type_, int point_): type(type_), point(point_) {
}

char Player::getType() const{
    return this->type;
}

int Player::getPoint() const {
    return this->point;
}

Player::~Player() {
}

HumanPlayer::HumanPlayer(char type_, int point) : Player(type_, point){
}

void HumanPlayer::makeMove(TicTacToe* game){
    // czy jakoś inaczej? casting?
    // jak wyłapywać błędny input (litera zamiast cyfry) lub 9+
    std::string choice{};
    int chosenRow{};
    int chosenColumn{};

    do {
        std::cout << "Your turn " << this->getType() << "! Chose your field (row, column): ";
        std::cin >> choice;
        chosenRow = std::stoi(choice) - 1;
        chosenColumn = static_cast<int>(choice[1]) - 'A';
    } while (not game->isValidBoardField({chosenRow, chosenColumn}));

    game->board[chosenRow][chosenColumn] = this->getPoint();
}

AIPlayer::AIPlayer(char type_, int point) : Player(type_, point) {
}

void AIPlayer::makeMove(TicTacToe* game) {
    std::map<std::vector<int>, int> pos = MinMax(game, 3, true); // raczej tak ale to się może zmienić
    game->board[pos[0]][pos[1]] = this->getPoint();
}
// zwraca pozycję oraz jej wartość
std::map<std::vector<int>, int> AIPlayer::MinMax(TicTacToe* game, int depth, bool maximizingPlayer) {
    if (depth == 0 or game->isGameOver()){
        return
    }
    if (maximizingPlayer){
        // max eval też musi byc tą mapą
        int maxEval = -std::numeric_limits<int>::infinity();
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = this->getPoint();
            auto eval = MinMax(game, depth - 1, false);
            maxEval = std::max(maxEval, eval[position]);
            game->board[position[0]][position[1]] = 0;
        }
        return {}
//        for each child of position
//        eval = minimax(child, depth - 1, false)
//        maxEval = max(maxEval, eval)
//        return maxEval
    }

    return std::map<std::vector<int>, int>{};
}
//function minimax(position, depth, maximizingPlayer)
//if depth == 0 or game over in position
//return static evaluation of position
//
//if maximizingPlayer
//        maxEval = -infinity
//for each child of position
//eval = minimax(child, depth - 1, false)
//maxEval = max(maxEval, eval)
//return maxEval
//
//else
//minEval = +infinity
//for each child of position
//eval = minimax(child, depth - 1, true)
//minEval = min(minEval, eval)
//return minEval
//
//
//// initial call
//minimax(currentPosition, 3, true)
