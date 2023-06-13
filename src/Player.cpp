#include <iostream>
#include <string>
#include <limits>
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

AIPlayer::AIPlayer(char type_, int point, int maxdepth_) : Player(type_, point), maxdepth(maxdepth_) {
}

void AIPlayer::makeMove(TicTacToe* game) {
    std::cout << "It's X turn!" << std::endl;
    Move position = MinMax(game, {-1, -1},std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0, true); // raczej tak ale to się może zmienić
    game->board[position.field[0]][position.field[1]] = this->getPoint();
    std::cout << "AI Player chose field: " << position.field[0] + 1 << static_cast<char>(position.field[1] + 'A') << std::endl;

}


Move AIPlayer::MinMax(TicTacToe* game, const std::vector<int>& pos, int alpha, int beta, int depth, bool maximizingPlayer) {

    if (game->isGameOver(false)){
// this = maximising player
        if (game->winner == this)
            return {pos, 1 * (game->emptyBoardFields() + 1 - depth)};
 // if minimzing won
        else if (game->winner != nullptr)
            return {pos,      depth - 1 * (game->emptyBoardFields() + 1)};
        else
            return {pos, 0};
    }

    if (maximizingPlayer){
        Move maxEval = {{-1, -1}, std::numeric_limits<int>::min()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = this->getPoint();
            auto eval = MinMax(game, position, alpha, beta, depth + 1, false);
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
            auto eval = MinMax(game, position, alpha, beta, depth + 1, true);
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

