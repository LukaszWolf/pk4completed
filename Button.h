#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include<functional>
#include "Item.h"
#include <sstream>

class Player;
class Button {
private:

    sf::Text text;
    sf::Font font;
    sf::Color defaultColor;

protected:
    sf::RectangleShape shape;
    sf::RectangleShape hover;
    sf::Texture tex;
    sf::Color hoverColor;
    std::function<void()> onClickFunction;
public:
    Button();
    Button(const std::string& label, sf::Vector2f position, sf::Vector2f size, std::string texture_file_name_default);
    Button(sf::Vector2f position, sf::Vector2f size, std::string texture_file_name_default, std::function<void()>action);
    virtual void draw(sf::RenderWindow& window);
    virtual void handleEvents(sf::Vector2i mouse_pos, sf::Event event);
    void setText(const std::string& label);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void setColor(sf::Color color);
    void setHover(sf::Color hover);
    void setFont();
    void setTex(std::string texture_file_name);
    bool isHovered(sf::Vector2i mousePos);
    bool isClicked(sf::Vector2i mousePos, sf::Event event);

    sf::Texture getTex() const;
    sf::Vector2f getPosition() const;


};

class ItemSlot : public Button {
private:
    Item* current_item;
    ItemType allowed_item_type; 
    bool isItemDragged;
    bool isDragSource;
    sf::Vector2i last_mouse_pos;   
    std::string name_id;
public:
    ItemSlot(std::string slot_name , sf::Vector2f position, sf::Vector2f size, ItemType item_type, std::string texture_file_name_default, std::function<void()>action, Item* curr_item); //eq
    
    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::Vector2i mouse_pos, sf::Event event);
    void tryStartDrag(const sf::Vector2i& mousePos, const sf::Event& event);
    void cancelDrag();
    bool endDrag(const sf::Vector2i& mousePos, const sf::Event& event, ItemSlot*source, Player*loggedInUSer);
    void swapItems(ItemSlot* source, ItemSlot* target, Player*loggedInUser);

    std::string getNameID() const;
    ItemType getAllowedItemType() const;
    ItemType getSlotType() const;
    void setItem(Item* item);
    Item* getCurrentItem() const;
    bool getIsItemDragged() const;
    void setIsItemDragged(bool dragging);
    void moveItem(sf::Vector2f&diff);
    sf::FloatRect getGlobalBounds() const;
};

#endif