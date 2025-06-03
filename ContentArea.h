#ifndef CONTENT_AREA_H
#define CONTENT_AREA_H



#include <SFML/Graphics.hpp>
#include "Button.h"
class Game;
class ContentArea {
private:
    sf::RectangleShape area;
    sf::Texture tex;
    const sf::Color color;
    Game& game_ref;

public:
    ContentArea(float width, float height, Game& game, const sf::Color& col);
    ContentArea(float width, float height, Game& game, const sf::Color& col, int x, int y);
    ContentArea(float width, float height, Game& game, const std::string texture_file_name);
    ContentArea(float width, float height, std::string texture_file_name, int x, int y);
    ContentArea(float width, float height, Game& game, std::string texture_file_name, int x, int y);
    ~ContentArea();

    void initVariables();
    void draw(sf::RenderWindow& window);
    void handleEvents(sf::Event event, sf::RenderWindow& window);
};

#endif 
