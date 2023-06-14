#include <iostream>
#include <string>
#include <limits>
#include <numeric>
#include <cmath>
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

AIPlayer::AIPlayer(char type_, int point, int maxdepth_) : Player(type_, point), maxdepth(maxdepth_), file ("/home/antalix/CLionProjects/mikroprojekt_3_without_GUI/test6.txt") {
}

void AIPlayer::makeMove(TicTacToe* game) {
    std::cout << "It's X turn!" << std::endl;
    Move position = MinMax(game, {-1, -1}, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0, true);
    game->board[position.field[0]][position.field[1]] = this->getPoint();
    std::cout << "AI Player chose field: " << position.field[0] + 1 << static_cast<char>(position.field[1] + 'A') << std::endl;
}

Move AIPlayer::MinMax(TicTacToe* game, const std::vector<int>& pos, int alpha, int beta, int depth, bool maximizingPlayer) {

    if (bool gameFinished = game->isGameOver(false) or maxdepth == depth)
        return {pos, evaluate(game, gameFinished)};

    if (maximizingPlayer){
        Move maxEval = {{-1, -1}, std::numeric_limits<int>::min()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = this->getPoint();
            auto eval = MinMax(game, position, alpha, beta, depth + 1, false);
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;

            if (maxEval.value < eval.value){
                maxEval.value = eval.value;
                maxEval.field = position;
            }
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

            if (minEval.value > eval.value){
                minEval.value = eval.value;
                minEval.field = position;
            }
            beta = std::min(beta, eval.value);
            if (beta <= alpha)
                break;
        }
        return minEval;
    }
}

int AIPlayer::evaluate(TicTacToe* game, bool gameFinished) {

    if (gameFinished) {
        if (game->winner == this) {
            return 100 + game->emptyBoardFields();
        } else if (game->winner != nullptr) {
            return -100 - game->emptyBoardFields();
        } else {
            return 0;
        }
    }
    int score{0};
    std::vector<int> pointsInRow(game->rows);
    std::vector<int> pointsInColumn(game->columns);

    for (int row{0}; row < game->rows; ++row) {
        for (int column{0}; column < game->columns; ++column) {
            if (column - 1 < 0 or game->board[row][column] == game->board[row][column - 1]) {
                pointsInRow[row] += game->board[row][column];
            } else if (game->board[row][column] != game->board[row][column - 1]) {
                score += pointsInRow[row];
                if (game->board[row][column] == 0){
                    if (pointsInRow[row] >= this->getPoint() * ceil(game->wf/2.0))
                        score += 10;
                    else if (pointsInRow[row] >= - this->getPoint() * ceil(game->wf/2.0))
                        score -= 10;
                }
                pointsInRow[row] = game->board[row][column];
            }
            if (column - 1 < 0 or game->board[column][row] == game->board[column - 1][row]) {
                pointsInColumn[row] += game->board[column][row];
            } else if (game->board[column][row] != game->board[column - 1][row]) {
                score += pointsInColumn[row];
                if (game->board[column][row]== 0){
                    if (pointsInColumn[row] >= this->getPoint() * ceil(game->wf/2.0))
                        score += 10;
                    else if (pointsInColumn[row] >= - this->getPoint() * ceil(game->wf/2.0))
                        score -= 10;
                }
                pointsInColumn[row] = game->board[column][row];
            }

        }
    }
    auto index{0};
//    for (const auto & points : pointsInRow) {
//        if (points >= this->getPoint() * ceil(game->wf / 2)) {
//            auto temp = abs(points); // redundant
//            if (game->rows - temp - 1 >= 0 and game->board[index][game->rows - temp - 1] == 0) {
//                score += 10;
//            }
//        }
//        else if (points >= - this->getPoint() * ceil(game->wf / 2)) {
//            auto temp = abs(points);
//            if (game->rows - temp - 1 >= 0 and game->board[index][game->rows - temp - 1] == 0) {
//                score += -10;
//            }
//        }
//        index++;
//    }
//    index = 0;
//    for (const auto & points : pointsInColumn) {
//        if (points >= this->getPoint() * ceil(game->wf / 2)) {
//            auto temp = abs(points); // redundant
//            if (game->rows - temp - 1 >= 0 and game->board[game->rows - temp - 1][index] == 0) {
//                score += 10;
//            }
//        }
//        else if (points >= - this->getPoint() * ceil(game->wf / 2)) {
//            auto temp = abs(points);
//            if (game->rows - temp - 1 >= 0 and game->board[game->rows - temp - 1][index] == 0) {
//                score += -10;
//            }
//        }
//        index++;
//    }
//    index = 0;

        score += std::accumulate(pointsInRow.begin(), pointsInRow.end(), 0);
        score += std::accumulate(pointsInColumn.begin(), pointsInColumn.end(), 0);

        int numOfDiagonals{(game->rows - game->wf) * 2 + 1};
        int diagonal{0};
        std::vector<int> winningAcrossLeft(numOfDiagonals);

        for (int row{0}; row < game->wf - 1; ++row) {
            for (int column{0}; column < game->wf - 1; ++column) {
                for (int k{0}; k < game->rows - row and k < game->columns - column; ++k) {
                    if (k + row - 1 < 0 or k + column - 1 < 0 or
                        game->board[k + row][k + column] == game->board[k + row - 1][k + column - 1]) {
                        winningAcrossLeft[diagonal] += game->board[k + row][k + column];
                    } else if (game->board[k + row][k + column] != game->board[k + row - 1][k + column - 1]) {
                        score += winningAcrossLeft[diagonal];
                        if (game->board[k + row][k + column]== 0){
                            if (winningAcrossLeft[diagonal] >= this->getPoint() * ceil(game->wf/2.0))
                                score += 10;
                            else if (winningAcrossLeft[diagonal] >= - this->getPoint() * ceil(game->wf/2.0))
                                score -= 10;
                        }
                        winningAcrossLeft[diagonal] = game->board[k + row][k + column];
                    }
                }
                ++diagonal;
            }
        }
//    for (const auto & points : winningAcrossLeft) {
//        if (points >= this->getPoint() * ceil(game->wf / 2)) {
//            auto temp = abs(points); // redundant
//            if (game->rows - temp - 1 >= 0 and game->board[game->rows - temp - 1][index] == 0) {
//                score += 10;
//            }
//        }
//        else if (points >= - this->getPoint() * ceil(game->wf / 2)) {
//            auto temp = abs(points);
//            if (game->rows - temp - 1 >= 0 and game->board[game->rows - temp - 1][index] == 0) {
//                score += -10;
//            }
//        }
//        index++;
//    }
        diagonal = 0;
        std::vector<int> winningAcrossRight(numOfDiagonals);

        for (int row{0}; row < game->wf - 1; ++row) {
            for (int column{game->columns - 1}; column > game->columns - game->wf; --column) {
                for (int k{0}; k < game->rows - row and column - k >= 0; ++k) {
                    if ((k + row - 1 < 0) or (column - k + 1 >= game->rows) or
                        game->board[row + k][column - k] == game->board[row + k - 1][column - k + 1]) {
                        winningAcrossRight[diagonal] += game->board[row + k][column - k];
                    } else if (game->board[row + k][column - k] != game->board[row + k - 1][column - k + 1]) {
                        score += winningAcrossLeft[diagonal];
                        if (game->board[row + k][column - k]== 0){
                            if (winningAcrossRight[diagonal] >= this->getPoint() * ceil(game->wf/2.0))
                                score += 10;
                            else if (winningAcrossRight[diagonal] >= - this->getPoint() * ceil(game->wf/2.0))
                                score -= 10;
                        }
                        winningAcrossRight[diagonal] = game->board[row + k][column - k];
                    }
                }

                ++diagonal;
            }
        }

        score += std::accumulate(winningAcrossLeft.begin(), winningAcrossLeft.end(), 0);
        score += std::accumulate(winningAcrossRight.begin(), winningAcrossRight.end(), 0);

        return score;
    }
