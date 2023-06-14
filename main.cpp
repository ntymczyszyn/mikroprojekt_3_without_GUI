#include <memory>
#include <iostream>
#include "include/TicTacToe.h"

auto playTicTacToe(std::unique_ptr<TicTacToe> game){
    game->play(false);
    return game->winner;
}

int main() {
    int size{1};
    int winning{};
    int maxDepth{0};
    char choice{};
    do {
        std::cout << " Welcome to Tic Tac Toe! " << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Chose board size: ";
        std::cin >> size;
        std::cout << "Chose number of winning fields: ";
        std::cin >> winning;
        std::cout << "Chose max depth: ";
        std::cin >> maxDepth;
    } while (size < 3 and winning < 2) ;

//    int tie{0};
//    for (int i {0}; i < 10; ++i){
//        if (not playTicTacToe (std::make_unique<TicTacToe>(size,size, winning))){
//            tie++;
//        }
//    }
//    std::cout << "Number of ties " << tie << "/10" << std::endl;
    do {
        playTicTacToe (std::make_unique<TicTacToe>(size,size, winning, maxDepth));
        std::cout << "Want to play again? [y/n] ";
        std::cin >> choice;
    } while (choice == 'y' or choice == 'Y');

    return 0;
}
