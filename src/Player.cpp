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

AIPlayer::AIPlayer(char type_, int point, int maxdepth_) : Player(type_, point), maxdepth(maxdepth_), file ("/home/antalix/CLionProjects/mikroprojekt_3_without_GUI/test5.txt") {
}

void AIPlayer::makeMove(TicTacToe* game) {
//    std::cout << "It's X turn!" << std::endl;
//    Move position = MinMax(game, {-1, -1},std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), 0, true); // raczej tak ale to się może zmienić
//    game->board[position.field[0]][position.field[1]] = this->getPoint();
//    std::cout << "AI Player chose field: " << position.field[0] + 1 << static_cast<char>(position.field[1] + 'A') << std::endl;

    Move maxEval = {{-1, -1}, std::numeric_limits<int>::min()};
    auto alpha = std::numeric_limits<int>::min();
    auto beta = std::numeric_limits<int>::max();
    auto depth = 0;
    auto round = 0;
    auto move = game->rows*game->rows - game->emptyBoardFields();
    std::string id;
    for (const auto& position : game->availableMoves()) {
        file << "Round " << round << "-------------------------- moves on board: "<< move << std::endl;
        game->board[position[0]][position[1]] = this->getPoint();
        auto eval = MinMax(round, move, game, position, alpha, beta, depth + 1, false);
        game->winner = nullptr;
        game->board[position[0]][position[1]] = 0;
        maxEval = std::max(maxEval, eval);
        file << "-------------------------------------------------------------------------------------------------------------" << std::endl;
        file << "Round " << round << " /winner " "/move " << maxEval.field[0] + 1 << static_cast<char>(maxEval.field[1] + 'A') << " /value " << maxEval.value << std::endl;
        round++;
    }
    std::cout << "It's X turn!" << std::endl;
    game->board[maxEval.field[0]][maxEval.field[1]] = this->getPoint();
    std::cout << "AI Player chose field: " << maxEval.field[0] + 1 << static_cast<char>(maxEval.field[1] + 'A') << std::endl;

}


Move AIPlayer::MinMax(int round, int move, TicTacToe* game, const std::vector<int>& pos, int alpha, int beta, int depth, bool maximizingPlayer) {

    if (game->isGameOver(false) or maxdepth == depth){
// this = maximising player won
        if (game->winner == this){
            auto score = evaluate(game);
            //return {pos, 1 * (game->emptyBoardFields() + 1)};
            if (maximizingPlayer)
                file << "Round " << round << "/moves " << move << " /max player/" << "depth " << depth << "/ "
                     << game->winner->getType() << " won/value " << score << std::endl;
            else
                file << "Round " << round << "/moves " << move << " /min player/" << "depth " << depth << "/ "
                     << game->winner->getType() << " won/value " << score << std::endl;
            return {pos, score};
        }
 // minimzing won
        else if (game->winner != nullptr) {
            auto score = evaluate(game);
            if (maximizingPlayer)
                file << "Round " << round << "/moves " << move << " /max player/" << "depth " << depth << "/ "
                     << game->winner->getType() << " won/value " << -score << std::endl;
            else
                file << "Round " << round << "/moves " << move << " /min player/" << "depth " << depth << "/ "
                     << game->winner->getType() << " won/value " << -score << std::endl;
            //return {pos, -1 * (game->emptyBoardFields() + 1)};
            return {pos, -score};
        }
        else {
            if (maximizingPlayer)
                file << "Round " << round << "/moves " << move << " /max player/" << "depth " << depth << "/ tie/value " << 0 << std::endl;
            else
                file << "Round " << round << "/moves " << move << " /min player/" << "depth " << depth << "/ tie/value " << 0 << std::endl;
            return {pos, 0};
        }
    }

    if (maximizingPlayer){
        Move maxEval = {{-1, -1}, std::numeric_limits<int>::min()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = this->getPoint();
            auto eval = MinMax(round, move, game, position, alpha, beta, depth + 1, false);
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;

            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval.value);
//            if (beta <= alpha)
//                break;
            file << "Round " << round << "/moves " << move << " /max player/" << "depth " << depth << "/move " << maxEval.field[0] + 1 << static_cast<char>(maxEval.field[1] + 'A') << " /value " << maxEval.value << std::endl;

        }
        return maxEval;
    }
    else {
        Move minEval = {{-1, -1}, std::numeric_limits<int>::max()};
        for (const auto& position : game->availableMoves()){
            game->board[position[0]][position[1]] = -this->getPoint();
            auto eval = MinMax(round, move, game, position, alpha, beta, depth + 1, true);
            game->winner = nullptr;
            game->board[position[0]][position[1]] = 0;

            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval.value);
//            if (beta <= alpha)
//                break;
            file << "Round " << round << "/moves " << move << " /min player/" << "depth " << depth << "/move " << minEval.field[0] + 1 << static_cast<char>(minEval.field[1] + 'A') << " /value " << minEval.value << std::endl;

        }
        return minEval;
    }
}

int AIPlayer::evaluate(TicTacToe* game){
    // if current boardthe we have a vinner othervies, set for wich olayer we are checkingit
    int calculationFor = game->winner->getPoint();
    int bestScore{};
    // checking for winner state
    // for winner only
    // if I won +100 + for all empty fileds
    // if only 2 in row + 10
    // if one +1 + empty
    // if my enymy 2 in row next to each other - 10
    // if opponent has some in row
    std::vector<int> winningRow(game->rows); // w sumie nie trzeba tych danych zapisywac na później
    std::vector<int> winningColumn(game->columns);

    for (int row{0}; row < game->rows; ++row){
        for (int column{0}; column < game->columns; ++column){
            if (column - 1 < 0 or game->board[row][column] == game->board[row][column - 1]) {
                winningRow[row] += game->board[row][column];
            } else if (game->board[row][column] != game->board[row][column - 1]) {
                winningRow[row] = game->board[row][column];
            }
            if (column - 1 < 0 or game->board[column][row] == game->board[column - 1][row]) {
                winningColumn[row] += game->board[column][row];
            } else if (game->board[column][row] != game->board[column - 1][row]){
                winningColumn[row] = game->board[column][row];
            }
            if (winningRow[row] == calculationFor * game->wf or winningColumn[row] == calculationFor * game->wf){
                //got max
                return 100 + game->emptyBoardFields();
            }
//            if (winningRow[row] == game->playerO->getPoint() * wf or winningRow[row] == playerX->getPoint() * wf){
//                printWinner(winningRow[row], printWin);
//                return true;
//            }
//            if (winningColumn[row] == playerO->getPoint() * wf or winningColumn[row] == playerX->getPoint() * wf){
//                printWinner(winningColumn[row],printWin);
//                return true;
            }
            if (winningRow[row] > (calculationFor * game->wf)/2.0 or winningColumn[row] > (calculationFor * game->wf)/2.0 ){
            return 10 + game->emptyBoardFields();
            }
        }


    int numOfDiagonals{(game->rows - game->wf) * 2 + 1};
    int diagonal{0};
    std::vector<int> winningAcrossLeft(numOfDiagonals);

    for (int row{0}; row < game->wf - 1 ; ++row){
        for (int column{0}; column < game->wf - 1; ++column) {
            for (int k{0}; k < game->rows - row and k < game->columns - column; ++k){
                if (k + row - 1 < 0 or k + column - 1 < 0 or game->board[k + row][k + column] == game->board[k + row - 1][k + column - 1]) {
                    winningAcrossLeft[diagonal] += game->board[k + row][k + column];
                } else if (game->board[k + row][k + column] != game->board[k + row - 1][k + column - 1]){
                    winningAcrossLeft[diagonal] = game->board[k + row][k + column];
                }
                if (winningAcrossLeft[diagonal] == calculationFor * game->wf){
                    //got max
                    return 100 + game->emptyBoardFields();
                }

//                if (winningAcrossLeft[diagonal] == playerO->getPoint() * wf or winningAcrossLeft[diagonal] == playerX->getPoint() * wf){
//                    printWinner(winningAcrossLeft[diagonal],printWin);
//                    return true;
//                }
            }
            if (winningAcrossLeft[diagonal] > (calculationFor * game->wf)/2.0){
                return 10 + game->emptyBoardFields();
            }
            ++diagonal;
        }
    }

    diagonal = 0;
    std::vector<int> winningAcrossRight(numOfDiagonals);

    for (int row{0}; row < game->wf - 1 ; ++row){
        for (int column{game->columns - 1}; column > game->columns - game->wf; --column) {
            for (int k{0}; k < game->rows - row  and column - k >= 0; ++k){
                if ((k + row - 1 < 0) or (column - k + 1 >= game->rows) or game->board[row + k][column - k] == game->board[row + k - 1][column - k + 1]) {
                    winningAcrossRight[diagonal] += game->board[row + k][column - k];
                } else if (game->board[row + k][column - k] != game->board[row + k - 1][column - k + 1]) {
                    winningAcrossRight[diagonal] = game->board[row + k][column - k];
                }
                if (winningAcrossRight[diagonal] == calculationFor * game->wf){
                    //got max
                    return 100 + game->emptyBoardFields();
                }

//                if (winningAcrossRight[diagonal] == playerO->getPoint() * wf or winningAcrossRight[diagonal] == playerX->
//                        getPoint() * wf){
//                    printWinner(winningAcrossRight[diagonal],printWin);
//                    return true;
//                }
            }
            if (winningAcrossRight[diagonal] > (calculationFor * game->wf)/2.0){
                return 10 + game->emptyBoardFields();
            }
            ++diagonal;
        }
    }

}