#include <iostream>

#include "game.hpp"


int main() {
    srand((unsigned int)time(NULL));
    Game game(2, 2);
    game.playGame();
    
    return 0;
}