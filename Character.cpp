#include "Character.h"
#include <sstream>


Character::Character(std::string nam, std::string img, int str, int dex, int intel, int con,
    int luck, int lvl): name(nam), img_file_name(img),base_luck(luck), base_strength(str),
    base_dexterity(dex), base_intelligence(intel), base_durability(con), level(lvl) {}

std::string Character::getImgName() const { 
    return img_file_name;
}
std::string Character::getName() const {
    return name; 
}
int Character::getLevel() const {
    return level; 
}


sf::Texture& Character::getCharacterTexture() {
    return character_img;
}

int Character::getBaseStrenght() const
{
    return base_strength;
}
int Character::getBaseDexterity() const
{
    return base_dexterity;
}
int Character::getBaseIntelligence() const
{
    return base_intelligence;
}
int Character::getBaseConstitution() const
{
    return base_durability;
}
int Character::getBaseLuck() const
{
    return base_luck;
}
