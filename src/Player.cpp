#include <iostream>
#include "../include/Player.h"

Player::Player(char type_, int point_): type(type_), point(point_) {
}

char Player::getType() const{
    return this->type;
}

int Player::getPoint() const {
    return this->point;
}
