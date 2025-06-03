#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include<iostream>
#include <fstream>
#include <regex>
enum class ItemType {
    WEAPON,
    ARMOR,
    HELMET,
    GLOVES,
    SHOES,
    RING,
    NECKLACE,
    BELT,
    LUCKY_ITEM,
    ANY
};

class Item {
private:
    int id;
    ItemType type;
    std::string name;
    std::string description;
    sf::Sprite sprite;
    sf::Texture texture;
    int strength;
    int dexterity;
    int intelligence;
    int durability;
    int luck;
    int armor;
    int price;

public:

    // Statystyki

    Item(int item_id);
    Item(int id, const std::string& texturePath, const std::string& name, ItemType type, int strength, int dexterity, int intelligence, int durability, int luck, int armor, int price);
    std:: string ItemTypeToString(ItemType t);
    void setPosition(sf::Vector2f pos);
    sf::FloatRect getGlobalBounds() const;
    int getId() const;
    ItemType getType() const;
    sf::Sprite& getSprite() ;
    sf::Texture& getTexture() ;
    int getStrenght()const;
    int getDexterity() const;
    int getIntelligence() const;
    int getConstitution() const;
    int getLuck() const;
    int getArmor() const;
    std::string getName()const;
    std::vector <std::string> getDescriptionStrings();
    int getPrice() const;

};
#endif