#include "Game.h"
#include <iostream>

int main() {
    Game game;

    try {
        if (!game.validateFiles()) {
            std::cerr << "[BLAD] Walidacja zakonczona niepowodzeniem (bez wyjatku)"<<std::endl;
            return 1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "[WYJĄTEK] " << e.what() << std::endl;
        return 1;
    }

   
    while (game.running()) {
        game.update();
        game.render();
    }
    return 0;

    
}