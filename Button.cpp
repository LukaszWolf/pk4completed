#include "Button.h"
#include"Player.h"
#include <iostream>

Button::Button() {};
Button::Button(sf::Vector2f position, sf::Vector2f size, std::string texture_file_name_default, std::function<void()>action)
    :onClickFunction(action)
{
    if (!tex.loadFromFile(texture_file_name_default) and texture_file_name_default != "") {
        std::cerr << "Nie mozna zaladowac tekstury: " << texture_file_name_default << std::endl;
    }
    else if (texture_file_name_default == "") {
        shape.setTexture(nullptr);
    }
    else {
        shape.setTexture(&tex);
    }

    if (size.x == 0.f and size.y == 0.f) {
        sf::Vector2f ts = static_cast<sf::Vector2f>(tex.getSize());
        size = ts;
    }
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White); 

    hover.setSize(size);
    hover.setPosition(position);
    hover.setFillColor(sf::Color(255, 255, 255, 0)); 
}

Button::Button(const std::string& label, sf::Vector2f position, sf::Vector2f size, std::string texture_file_name_default)
{
 
    if (!tex.loadFromFile(texture_file_name_default) and texture_file_name_default != "") {
        std::cerr << "Nie mozna zaladowac tekstury: " << texture_file_name_default << std::endl;
    }
    else if (texture_file_name_default == "") {
        shape.setTexture(nullptr);
    }
    else {
        shape.setTexture(&tex);
    }
    if (size.x == 0.f and size.y == 0.f) {
        sf::Vector2f ts = static_cast<sf::Vector2f>(tex.getSize());
        size = ts;
    }
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White); 

    hover.setSize(size);
    hover.setPosition(position);
    hover.setFillColor(sf::Color(255, 255, 255, 0)); 
}

void Button::setText(const std::string& label) {
    text.setString(label);
}

void Button::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
    text.setPosition(position.x + 10, position.y + 10);
}

void Button::setSize(sf::Vector2f size) {
    shape.setSize(size);
}

void Button::setColor(sf::Color color) {
    defaultColor = color;
    shape.setFillColor(defaultColor);
}

void Button::setHover(sf::Color hover) {
    hoverColor = hover;
}

void Button::setFont(){
    if (!font.loadFromFile("Fonts / RodrigoTypo - Tobi Pro ExtraBold.otf")) {
        std::cout << "Nie mo�na zaladowac czcionki!" << std::endl;
    }
    this->font = font;
}

void Button::setTex(std::string texture_file_name){

    if (!this->tex.loadFromFile(texture_file_name)) {
        std::cout << "Nie mo�na za�adowa� tekstury: " << texture_file_name << std::endl;
    }

}

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(hover);
    window.draw(text);
}

void Button::handleEvents(sf::Vector2i mouse_pos, sf::Event event)
{
    if (this->isClicked(mouse_pos, event)) {
        if (onClickFunction) {
            onClickFunction();
        }
    }
    if (this->isHovered(mouse_pos)) {
        hover.setFillColor(sf::Color(255, 255, 255, 40));
        hover.setPosition(this->shape.getPosition());
    }
    else {
        hover.setFillColor(sf::Color(255, 255, 255, 0));
    }

}

bool Button::isHovered(sf::Vector2i mousePos) {
    sf::FloatRect bounds = shape.getGlobalBounds();
    bool isHovered = bounds.contains(static_cast<sf::Vector2f>(mousePos));

    return isHovered;
}

bool Button::isClicked(sf::Vector2i mousePos, sf::Event event) {
    return isHovered(mousePos) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
}

sf::Texture Button::getTex() const{
    return this->tex;
}

sf::Vector2f Button::getPosition() const{
    return this->shape.getPosition();
}


//////////////////ITEMSLOT



ItemSlot::ItemSlot(std::string slot_name, sf::Vector2f position, sf::Vector2f size, ItemType item_type, 
    std::string texture_file_name_default, std::function<void()>action, Item* curr_item) :
    Button(), allowed_item_type(item_type)
{
    name_id = slot_name;
    isItemDragged = false;
    isDragSource = false;
    this->setItem(curr_item);
    this->onClickFunction = action;
    setItem(current_item);
    setPosition(position);
    setSize(size);
    if (!tex.loadFromFile(texture_file_name_default) and texture_file_name_default != "") {
        std::cerr << "Nie mozna zaladowac tekstury: " << texture_file_name_default << std::endl;
    }
    else if (texture_file_name_default == "") {
        shape.setTexture(nullptr);
    }
    else {
        shape.setTexture(&tex);
    }
    hover.setSize(size);
    hover.setPosition(position);
    hover.setFillColor(sf::Color(255, 255, 255, 0));

}

void ItemSlot::setItem(Item* item){
    this->current_item = item;
    if (this->current_item) {
        this->current_item->setPosition(this->getPosition());
        this->current_item->getSprite().setTexture(current_item->getTexture());
        this->current_item->getSprite().setScale(1.f, 1.f);

    }
}

ItemType ItemSlot::getAllowedItemType() const{
    return allowed_item_type;
}

Item* ItemSlot::getCurrentItem() const{
    return current_item;
}

bool ItemSlot::getIsItemDragged() const{
    return isItemDragged;
}

std::string ItemSlot::getNameID() const{
    return name_id;
}
void ItemSlot::setIsItemDragged(bool dragging){
    isItemDragged = dragging;
}

void ItemSlot::moveItem(sf::Vector2f& diff){
 
    if (current_item) {
        current_item->getSprite().move(diff);
    }
}

sf::FloatRect ItemSlot::getGlobalBounds() const{
    return shape.getGlobalBounds();
}

void ItemSlot::draw(sf::RenderWindow& window){
    
    window.draw(this->hover);

    if (this->current_item != nullptr) {
        window.draw(this->current_item->getSprite());
    }
}

void ItemSlot::tryStartDrag(const sf::Vector2i& mousePos, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed and
        event.mouseButton.button == sf::Mouse::Left)
    {
        Item* item = getCurrentItem();
        if (!isDragSource and item and
            item->getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
        {
            isDragSource = true;
            isItemDragged = true;
            last_mouse_pos = mousePos;
        }
    }
}
void ItemSlot::swapItems(ItemSlot* source, ItemSlot* target, Player* loggedInUser) {
    Item* temp = source->getCurrentItem();

    // Jeśli kupujemy (source=shop), nie zamieniamy, tylko przenosimy
    if (source->getNameID().rfind("shop", 0) == 0) {
        target->setItem(temp);
        source->setItem(nullptr);
        if (loggedInUser and temp) {
            int cena = temp->getPrice();
            loggedInUser->setGold(loggedInUser->getGold() - cena);
        }
        if (loggedInUser) {
            loggedInUser->setItem(target->getNameID(), target->getCurrentItem());
            loggedInUser->setItem(source->getNameID(), nullptr);
        }
        return;
    }

    source->setItem(target->getCurrentItem());
    target->setItem(temp);

    if (loggedInUser) {
        loggedInUser->setItem(source->getNameID(), source->getCurrentItem());
        loggedInUser->setItem(target->getNameID(), target->getCurrentItem());
    }
}


void ItemSlot::cancelDrag() {
    isItemDragged = false;
    isDragSource = false;
}
bool ItemSlot::endDrag(const sf::Vector2i& mousePos,
    const sf::Event& event,
    ItemSlot* source,
    Player* loggedInUser)
{
    // 1) Tylko na zwolnienie lewego przycisku
    if (event.type != sf::Event::MouseButtonReleased ||
        event.mouseButton.button != sf::Mouse::Left)
    {
        return false;
    }

    // 2) Musi być faktycznie drag z innego slotu
    if (!source->getIsItemDragged() || source == this)
        return false;

    // 3) Kursor musi być nad tym slotem
    if (!this->isHovered(mousePos))
        return false;

    // 4) Nie obsługujemy swapów ze slotu sklepu ani na slot sklepu
    bool srcIsShop = (source->getNameID().rfind("shop", 0) == 0);
    bool dstIsShop = (this->getNameID().rfind("shop", 0) == 0);
    if (srcIsShop || dstIsShop)
        return false;

    // 5) Musi istnieć przedmiot źródłowy
    Item* srcItem = source->getCurrentItem();
    if (!srcItem)
        return false;

    // 6) Kompatybilność: srcItem → this slot
    if (allowed_item_type != ItemType::ANY and
        srcItem->getType() != allowed_item_type)
    {
        return false;
    }

    // 7) Kompatybilność: dstItem → source slot
    Item* dstItem = this->getCurrentItem();
    ItemType srcAllowed = source->getAllowedItemType();
    if (dstItem and srcAllowed != ItemType::ANY and
        dstItem->getType() != srcAllowed)
    {
        return false;
    }

    // 8) Wszystko gra — zamień przedmioty
    swapItems(source, this, loggedInUser);
    return true;
}


void ItemSlot::handleEvents(sf::Vector2i mouse_pos, sf::Event event){
    if (this->isHovered(mouse_pos)) {
        hover.setFillColor(sf::Color(255, 255, 255, 40));
        hover.setPosition(this->shape.getPosition());
    }
    else {
        hover.setFillColor(sf::Color(255, 255, 255, 0));
    }

    if (getIsItemDragged()) {
    sf::Vector2i delta = mouse_pos - last_mouse_pos;
    sf::Vector2f diff(static_cast<float>(delta.x), static_cast<float>(delta.y));
    moveItem(diff);
    }
    last_mouse_pos = mouse_pos;
}