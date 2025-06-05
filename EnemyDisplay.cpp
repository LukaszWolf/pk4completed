#include "EnemyDisplay.h"

EnemyDisplay::EnemyDisplay(const sf::Vector2f& basePos)
    : position(basePos) {
    img.setSize({ 283.f, 283.f });
    img.setPosition(basePos);
    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
       // std::cout << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
    }
    auto createText = [&](sf::Text& text, float offsetY) {
        text.setFont(font);
        text.setCharacterSize(28);
        text.setFillColor(sf::Color::White);
        text.setPosition(basePos.x+200.f, basePos.y + offsetY);
        };


    createText(lvl_text, 292.f);
    createText(strength, 327.f);
    createText(dexterity, 360.f);
    createText(intelligence, 392.f);
    createText(durability, 424.f);
    createText(luck, 456.f);
   // createText(reward, 540);
    reward = sf::Text();
    reward.setFont(font);
    reward.setCharacterSize(42);
    reward.setFillColor(sf::Color::White);
    reward.setPosition(basePos.x + 230.f, basePos.y + 500.f);
  
  
}

void EnemyDisplay::setEnemyData(Enemy& enemy) {
    if (&enemy) {
        img.setTexture(&enemy.getCharacterTexture());
        lvl_text.setString(std::to_string(enemy.getLevel()));
        strength.setString(std::to_string(enemy.getStrength()));
        dexterity.setString(std::to_string(enemy.getDexterity()));
        intelligence.setString(std::to_string(enemy.getIntelligence()));
        durability.setString(std::to_string(enemy.getDurability()));
        luck.setString(std::to_string(enemy.getLuck()));
        reward.setString(std::to_string(enemy.getRewardGold()));
    }
}

void EnemyDisplay::draw(sf::RenderWindow& window) const {
    
    window.draw(img);
    window.draw(lvl_text);
    window.draw(strength);
    window.draw(dexterity);
    window.draw(intelligence);
    window.draw(durability);
    window.draw(luck);
    window.draw(reward);
    
}


