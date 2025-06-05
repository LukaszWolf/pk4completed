#include "Game.h"
#include "ContentArea.h"
#include <SFML/Graphics.hpp>
#include <iostream>




ContentArea::ContentArea(float width, float height, Game& game, std::string texture_file_name, int x, int y) : game_ref(game) {
    this->area.setSize(sf::Vector2f(width, height));
    this->tex.loadFromFile(texture_file_name);
    this->area.setTexture(&this->tex);
    this->area.setPosition(x, y);

    void initVariables();

}

ContentArea::~ContentArea()
{
}






void ContentArea::draw(sf::RenderWindow& window) {
    window.draw(this->area);
}

void ContentArea::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
}