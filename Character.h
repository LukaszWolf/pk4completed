#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "Button.h"

//enum class CharacterClass {
//    WARRIOR,
//    MAGE,
//    SCOUT
//};

class Character {
protected:
    std::string name;
    std::string img_file_name;
    sf::Texture character_img;
    int hp, damage, evasion, resistance, damage_reduction;
    double crit_chance;
    int level;
    int base_strength, base_dexterity, base_intelligence, base_durability, base_luck;


public:

    Character(std::string nam, std::string img, int strength, int dexterity, int intelligence, int durability,
        int luck,  int level);
    virtual ~Character() = default; 

    virtual float attack() = 0;
    virtual int calculateHP() = 0;
    virtual int calculateDamage() = 0;
    virtual int calculateEvasion() = 0;
    virtual int calculateResistance() = 0;
    virtual int calculateDamageReduction() = 0;
    virtual double calculateCritChance() = 0;

    int getBaseStrenght() const;
    int getBaseDexterity() const;
    int getBaseIntelligence() const;
    int getBaseConstitution() const;
    int getBaseLuck() const;

    std::string getImgName() const;
    std::string getName() const;
    int getLevel() const;
    virtual int getStrength() = 0;
    virtual int getDexterity() = 0;
    virtual int getIntelligence() = 0;
    virtual int getConstitution() = 0;
    virtual int getLuck() = 0;
    virtual int getArmor() = 0;
    sf::Texture& getCharacterTexture();

};

#endif