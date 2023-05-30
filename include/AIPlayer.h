//
// Created by Natalia on 30.05.2023.
//

#ifndef MIKROPROJEKT_3_WITHOUT_GUI_AIPLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_AIPLAYER_H
#include "Player.h"

class AIPlayer: public Player{
public:
    AIPlayer();
    std::vector<int> makeMove() override;
    //idk czy tu ten mini max czy w tictactoe
};
#endif //MIKROPROJEKT_3_WITHOUT_GUI_AIPLAYER_H
