#ifndef MIKROPROJEKT_3_WITHOUT_GUI_HUMANPLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_HUMANPLAYER_H
#include <vector>
#include "Player.h"

class HumanPlayer: public Player{
public:
    HumanPlayer(char type_, int point);
    std::vector<int> makeMove()  override;
};

#endif //MIKROPROJEKT_3_WITHOUT_GUI_HUMANPLAYER_H
