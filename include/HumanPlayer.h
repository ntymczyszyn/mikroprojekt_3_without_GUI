#include <vector>
#include "Player.h"
#ifndef MIKROPROJEKT_3_WITHOUT_GUI_HUMANPLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_HUMANPLAYER_H

class HumanPlayer: public Player{
public:
    std::vector<int> makeMove()  override;
    //bool validateMove();

};
#endif //MIKROPROJEKT_3_WITHOUT_GUI_HUMANPLAYER_H
