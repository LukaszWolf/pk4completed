#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include<random>

class Enemy : public Character {
private:
    int reward_gold;

public:
    Enemy(const std::string& name,
        const std::string& img,
        int strength, int dexterity, int intelligence,
        int durability, int luck, int level,
        int reward);

    float attack() override;
    int calculateHP() override;
    int calculateDamage() override;
    int calculateEvasion() override;
    int calculateResistance() override;
    int calculateDamageReduction() override;
    double calculateCritChance() override;

    int getStrength() override;
    int getDexterity() override;
    int getIntelligence() override;
    int getDurability() override;
    int getArmor() override;
    int getLuck() override;
    int getRewardGold() const;
};

#endif