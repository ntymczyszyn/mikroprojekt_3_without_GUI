#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <unistd.h>
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
    std::cout << "It's X turn!" << std::endl;
    Move position = MinMax(game, {-1, -1},std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 3, true); // raczej tak ale to się może zmienić
    game->board[position.field[0]][position.field[1]] = this->getPoint();
    sleep(1);
}

Move AIPlayer::MinMax(TicTacToe* game, const std::vector<int>& pos, int alpha, int beta, int depth, bool maximizingPlayer) {
    // czy to można uniezależnić od znaku
    if (game->isGameOver(false)){ //depth == 0 or
        if (game->winner == game->playerX) // X won (WE WON)
            return {pos, 1 * (game->emptyBoardFields() + 1)};
        else if (game->winner == game->playerO) // O won
            return {pos,-1 * (game->emptyBoardFields() + 1)}; // tie
        else
            return {pos, 0};
    }
    if (maximizingPlayer){
        Move maxEval = {{-1, -1}, std::numeric_limits<int>::min()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = this->getPoint();
            auto eval = MinMax(game, position, alpha, beta, depth - 1, false);
            //redo the step
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval.value);
            if (beta <= alpha)
                break;

        }
        return maxEval;
    }
    else {
        Move minEval = {{-1, -1}, std::numeric_limits<int>::max()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = -this->getPoint();
            auto eval = MinMax(game, position, alpha, beta, depth - 1, true);
            //redo the step
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval.value);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

