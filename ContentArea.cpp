#include "Game.h"
#include "ContentArea.h"
#include <SFML/Graphics.hpp>
#include <iostream>

ContentArea::ContentArea(float width, float height, Game& game, const sf::Color& col) : game_ref(game), color(col) {

    this->area.setSize(sf::Vector2f(width, height));
    this->area.setFillColor(sf::Color(col));  
    this->area.setPosition(400, 0);

    void initVariables();


}

ContentArea::ContentArea(float width, float height, Game& game, const sf::Color& col, int x, int y): game_ref(game),color(col){
    this->area.setSize(sf::Vector2f(width, height));
    this->area.setFillColor(sf::Color(col)); 
    this->area.setPosition(x, y);

    void initVariables();

}

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


ContentArea::ContentArea(float width, float height, Game& game, const std::string texture_file_name) : game_ref(game) {

    this->area.setSize(sf::Vector2f(width, height));
    this->tex.loadFromFile(texture_file_name);
    this->area.setTexture(&this->tex);
    this->area.setPosition(400, 0);

    void initVariables();

}



void ContentArea::draw(sf::RenderWindow& window) {
    window.draw(this->area);
}

void ContentArea::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
}