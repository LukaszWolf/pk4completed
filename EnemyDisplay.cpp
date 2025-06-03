#include "EnemyDisplay.h"

EnemyDisplay::EnemyDisplay(const sf::Vector2f& basePos)
    : position(basePos) {
    img.setSize({ 250.f, 250.f });
    img.setPosition(basePos);
    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
        std::cout << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
    }
    auto createText = [&](sf::Text& text, float offsetY) {
        text.setFont(font);
        text.setCharacterSize(26);
        text.setFillColor(sf::Color::White);
        text.setPosition(basePos.x, basePos.y + offsetY);
        };


    createText(lvl_text, 280);
    createText(strength, 310);
    createText(dexterity, 340);
    createText(intelligence, 370);
    createText(durability, 400);
    createText(luck, 430);
    createText(reward, 460);

  
  
}

void EnemyDisplay::setEnemyData(Enemy& enemy) {
    if (&enemy) {
        img.setTexture(&enemy.getCharacterTexture());
        lvl_text.setString("LVL: " + std::to_string(enemy.getLevel()));
        strength.setString("STR: " + std::to_string(enemy.getStrength()));
        dexterity.setString("DEX: " + std::to_string(enemy.getDexterity()));
        intelligence.setString("INT: " + std::to_string(enemy.getIntelligence()));
        durability.setString("CON: " + std::to_string(enemy.getConstitution()));
        luck.setString("LCK: " + std::to_string(enemy.getLuck()));
        reward.setString("Reward: " + std::to_string(enemy.getRewardGold()));
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


