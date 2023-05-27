#include <memory>
#include "include/TicTacToe.h"

int main() {
    constexpr int size{4};
    constexpr int winning{3};
    std::unique_ptr<TicTacToe> game = std::make_unique<TicTacToe>(size,size, winning);
    game->play(false);
    return 0;
}
