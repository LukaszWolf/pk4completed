#ifndef NAVBAR_H
#define NAVBAR_H

#include <SFML/Graphics.hpp>
#include "Button.h"
class Game;
class NavBar {
private:
    sf::RectangleShape bar;
    sf::Texture tex;
    Button* player_button;
    Button* quests_button;
    Button* arena_button;
    Button* logout_button;
    Button* exit_button;

    Game& game_ref;

public:
    NavBar(float width, float height, Game& game);
    ~NavBar();

    void draw(sf::RenderWindow& window);
    void handleEvents(sf::Event event, sf::RenderWindow& window);
};

#endif 