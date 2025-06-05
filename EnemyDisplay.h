#ifndef ENEMY_DISPLAY_H
#define ENEMY_DISPLAY_H

#include <SFML/Graphics.hpp>
#include "Enemy.h"

class EnemyDisplay {
private:
    sf::RectangleShape img;
    sf::Text lvl_text, strength, dexterity, intelligence, durability, luck, reward;
    sf::Font font;
    sf::Vector2f position;


public:
    EnemyDisplay(const sf::Vector2f& basePos);
    void setEnemyData(Enemy& enemy);
    void draw(sf::RenderWindow& window) const;
};

#endif