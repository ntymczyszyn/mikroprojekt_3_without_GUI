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
    std::cout << "HumanPlayer" << std::endl;
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
    std::cout << "AIPlayer" << std::endl;
}

void AIPlayer::makeMove(TicTacToe* game) {
    std::cout << "AIPlayer (X) is making a move!" << std::endl;
    //może zmienisz żeby były 2 min max które można wywyołać
    Node position = MinMax(game,{-1,-1}, 3, true); // raczej tak ale to się może zmienić
    std::cout << position.field[0] << " " << position.field[1] << " " << position.value << std::endl;
    game->board[position.field[0]][position.field[1]] = this->getPoint();
}
// zwraca pozycję oraz jej wartość
Node AIPlayer::MinMax(TicTacToe* game, const std::vector<int>& pos, int depth, bool maximizingPlayer) {
    // trzeba wymyśleć jak sprawdzać kto wygrał i zależnie od tego przyznawać punkty
    // czy to można uniezależnić od znaku

    if (game->isGameOver(false)){ //depth == 0 or
        if (game->winner == game->playerX) // X won (WE WON)
            return {pos, 1 * (game->emptyBoardFields() + 1)}; // static evaluation
        else if (game->winner == game->playerO) // O won
            return {pos,-1 * (game->emptyBoardFields() + 1)}; // tie
        else
            return {pos, 0};
    }
    if (maximizingPlayer){
        Node maxEval = {{-1,-1}, std::numeric_limits<int>::min()};
        std::cout << "(MAX EVAL - BEFORE FOR) X player "<< maxEval.value << std::endl;
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = this->getPoint();
            std::cout << "(BEFORE MINMAX) X player "<< position[0] << " " << position[1] << std::endl;
            auto eval = MinMax(game, position, depth - 1, false);
            std::cout << "X player (AFTER MINMAX) "<< eval.field[0] << " " << eval.field[1] << " " << eval.value << std::endl;
            if (maxEval.value < eval.value) {
                maxEval.value = eval.value;
                maxEval.field = eval.field;
                std::cout << "X player (IN IF)"<< eval.field[0] << " " << eval.field[1] << " " << eval.value << std::endl;
            }
            //maxEval = std::max(maxEval, eval);
            //redo the step
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;
        }
        std::cout << "X player (MAX EVAL) "<< maxEval.value << std::endl;
        return maxEval;
    }
    else {
        Node minEval = {{-1,-1}, std::numeric_limits<int>::max()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = -this->getPoint();
            std::cout << "(BEFORE MINMAX) O player "<< position[0] << " " << position[1] << std::endl;
            auto eval = MinMax(game, position, depth - 1, true);
            std::cout << "O player (AFTER MINMAX) "<< eval.field[0] << " " << eval.field[1] << " " << eval.value << std::endl;
            if (minEval.value > eval.value) {
                minEval.value = eval.value;
                minEval.field = eval.field;
                std::cout << "O player (IN IF)"<< eval.field[0] << " " << eval.field[1] << " " << eval.value << std::endl;
            }
            //minEval = std::min(minEval, eval);
            //redo the step
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;
        }
        std::cout << "O player (MIN EVAL) " << minEval.value << std::endl;
        return minEval;
    }

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
