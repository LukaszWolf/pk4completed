#include "Enemy.h"
#include <cmath>


Enemy::Enemy(const std::string& name, const std::string& img,
    int strength, int dexterity, int intelligence,
    int durability, int luck, int level,
    int reward)
    : Character(name, img, strength, dexterity, intelligence, durability, luck, level),
    reward_gold(reward) {
    character_img.loadFromFile(img);
}

float Enemy::attack() {
    static std::mt19937 rng{ std::random_device{}() };
    static std::uniform_real_distribution<float> damage_multiplier(0.8f, 1.2f);
    float damage = static_cast<float>(calculateDamage());
    return damage*damage_multiplier(rng);
}
int Enemy::calculateHP() {
    return getDurability() * level;
}
int Enemy::calculateDamage() {
    return getStrength() * level;
}
int Enemy::calculateEvasion() {
    return getDexterity() * level;
}
int Enemy::calculateResistance() {
    return getArmor() * level * 0.1;
}
int Enemy::calculateDamageReduction() {
    return std::floor(getIntelligence() * level / 50); 
}
double Enemy::calculateCritChance() {
    return std::min(50.0, getLuck() * 0.05); 
}

int Enemy::getStrength() {
    return base_strength; 
}
int Enemy::getDexterity() {
    return base_dexterity; 
}
int Enemy::getIntelligence() {
    return base_intelligence;
}
int Enemy::getDurability() {
    return base_durability; 
}
int Enemy::getArmor()
{
    return 0;
}
int Enemy::getLuck() {
    return base_luck; 
}

int Enemy::getRewardGold() const {
    return reward_gold; 
}
