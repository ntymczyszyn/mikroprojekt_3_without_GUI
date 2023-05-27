#include "../include/HumanPlayer.h"
#include <string>
#include <iostream>

HumanPlayer::HumanPlayer(char type_, int point) : Player(type_, point){

}

std::vector<int> HumanPlayer::makeMove(){

    std::string choice{};
    // while loop
    std::cout << "Your turn " << this->getType() <<"! Chose your field (row, column): ";
    // validate the input string - maybe additional variables for clarity
    std::cin >> choice;

    std::cout << choice[0] << " " << choice[1] << std::endl;

    return {std::stoi(choice) - 1, static_cast<int>(choice[1]) - 65};
    // how to change to proper casting??
    // why can't I use c++20 features
    // check if the field is not already taken
    // check if it is within the boundaries
    // for now let's assume that it is always correct
    // for now there are strings
}




