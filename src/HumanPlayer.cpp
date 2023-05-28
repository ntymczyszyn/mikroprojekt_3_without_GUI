#include "../include/HumanPlayer.h"
#include <string>
#include <iostream>

HumanPlayer::HumanPlayer(char type_, int point) : Player(type_, point){

}

std::vector<int> HumanPlayer::makeMove(){

    std::string choice{};
    // czy da się to jakoś mądrzej zrobić
    // napewno chcę to ciurkiem wprowadzać 1A 2B ...
    do {
        std::cout << "Your turn " << this->getType() <<"! Chose your field (row, column): ";
        std::cin >> choice;
    } while(not isValid(choice));

    return {std::stoi(choice) - 1, static_cast<int>(choice[1]) - 65};
    //WHAT IF ITS 10 OR MORE
    // how to change to proper casting??
    // why can't I use c++20 features
    
}
// or mayby in Player.h
bool HumanPlayer::isValid(std::string choice) {    
    int chosenRow{std::stoi(choice) - 1};
    int chosenColumn{static_cast<int>(choice[1]) - 65};
    
    if (chosenRow < 0 or chosenRow >= rows or chosenColumn < 0 or chosenColumn >= columns)
        return false;
    
    if (board[chosenRow][chosenColumn] != 0) // czy get board score było by nessecary - to już jak specyfikatory ja po dodawałam (czy dobrze??)
        return false;
    
    return true;
}

