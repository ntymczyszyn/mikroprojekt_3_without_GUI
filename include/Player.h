#ifndef MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#define MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
#include <vector>
#include <string>

class Player{
public:
    Player(char type_, int point);
    virtual std::vector<int> makeMove() = 0; // do I need virtual keyword?
    bool isValid(std::string choice);
    char getType() const;
    int getPoint() const;
private:
    char type; // X or O
    int point;
    // value of a score?
};

#endif //MIKROPROJEKT_3_WITHOUT_GUI_PLAYER_H
