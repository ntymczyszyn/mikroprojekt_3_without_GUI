#ifndef MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#include <vector>

class Player{
public:
    Player(char type_, int point);
     virtual std::vector<int> makeMove();
    //bool validateMove();
    char getType() const;
private:
    char type; // X or O
    int point;
    // value of a score?
};

#endif //MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
