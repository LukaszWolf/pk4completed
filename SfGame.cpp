#include "Game.h"
#include <iostream>

int main() {
    Game game;

    try {
        if (!game.validateFiles()) {
            return 1;
        }
    }
    catch (const std::exception& e) {
        return 1;
    }

   
    while (game.running()) {
        game.update();
        game.render();
    }
    return 0;

    
}