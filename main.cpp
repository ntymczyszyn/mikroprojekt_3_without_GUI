#include <memory>
#include "include/TicTacToe.h"
#include <iostream>

auto playTicTacToe(std::unique_ptr<TicTacToe> game){
    game->play(false);
    //std::cout << game->winner->getType() << std::endl;
    return game->winner;
}

int main() {
    int size{};
    int winning{};
    char choice{};
    do {
        std::cout << " Welcome to Tic Tac Toe! " << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Chose board size: ";
        std::cin >> size;
        std::cout << "Chose number of winning fields: ";
        std::cin >> winning;
    } while (size < 3 and winning < 2);

    int tie{0};

//    for (int i {0}; i < 10; ++i){
//
//        if (not playTicTacToe (std::make_unique<TicTacToe>(size,size, winning))){
//            tie++;
//        }
//
//    }
   // std::cout << "Number of ties " << tie << "/10" << std::endl;
    do {
        playTicTacToe (std::make_unique<TicTacToe>(size,size, winning));
        std::cout << "Want to play again? [y/n] ";
        std::cin >> choice;
    } while (choice == 'y' or choice == 'Y');

    return 0;
}
