#include <memory>
#include "include/TicTacToe.h"
#include <iostream>

void playTicTacToe(std::unique_ptr<TicTacToe> game){
    game->play(false);
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

    do {
        playTicTacToe (std::make_unique<TicTacToe>(size,size, winning));
        std::cout << "Want to play again? [y/n] ";
        std::cin >> choice;
    } while (choice == 'y' or choice == 'Y');

    return 0;
}
