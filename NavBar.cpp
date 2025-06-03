#include "Game.h"
#include "NavBar.h"
#include <SFML/Graphics.hpp>
#include <iostream>

NavBar::NavBar(float width, float height, Game&game): game_ref(game) {

    this->player_button = new Button({ 40, 330 }, { 324, 80 }, "Textures/player_button.png", [&game]() {game.changePage(GameState::PLAYER_MENU); });
    this->quests_button = new Button({ 40, 455 }, { 324, 80 }, "Textures/quests_button.png", [&game]() {game.changePage(GameState::QUEST_PAGE);});
    this->arena_button = new Button({ 40, 580 }, { 324, 80 }, "Textures/arena_button.png", [&game]() {game.changePage(GameState::ARENA_PAGE); });
    this->logout_button = new Button({ 40, 705 }, { 324, 80 }, "Textures/logout_button.png", [&game]() {
        game.changePage(GameState::LOGIN_PAGE);
        game.LogOut(); 
        });
    this->exit_button = new Button({ 40, 830 }, { 324, 80 }, "Textures/exit_button.png", [&game]() {game.getWindow().close(); });
    

    this->bar.setSize(sf::Vector2f(width, height));
    this->tex.loadFromFile("Textures/navbar_clear.png");
    this->bar.setTexture(&this->tex);
    this->bar.setPosition(0, 0);

    void initVariables();
}
NavBar::~NavBar() {

    delete this->player_button;
    delete this->quests_button;
    delete this->arena_button;
    delete this->logout_button;
    delete this->exit_button;
}


void NavBar::draw(sf::RenderWindow& window) {
    window.draw(this->bar);
    this->player_button->draw(window);
    this->quests_button->draw(window);
    this->arena_button->draw(window);
    this->logout_button->draw(window);
    this->exit_button->draw(window);
   

}

void NavBar::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    player_button->handleEvents(mousePos, event);
    quests_button->handleEvents(mousePos, event);
    arena_button->handleEvents(mousePos, event);
    logout_button->handleEvents(mousePos, event);
    exit_button->handleEvents(mousePos, event);
}