#include "../include/HumanPlayer.h"
#include <string>
#include <iostream>

HumanPlayer::HumanPlayer(char type_, int point) : Player(type_, point){

}

std::vector<int> HumanPlayer::makeMove(){

    std::string choice{};
    // czy da się to jakoś mądrzej zrobić
    // napewno chcę to ciurkiem wprowadzać 1A 2B ...

    std::cout << "Your turn " << this->getType() <<"! Chose your field (row, column): ";
    std::cin >> choice;
// a co jeśli się poda się litere zamiast cyfry  :(((
    return {std::stoi(choice) - 1, static_cast<int>(choice[1]) - 65};
    //WHAT IF ITS 10 OR MORE
    // how to change to proper casting??
    // why can't I use c++20 features
    
}

