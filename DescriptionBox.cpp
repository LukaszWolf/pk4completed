#include "DescriptionBox.h"
#include <sstream>

DescriptionBox::DescriptionBox(const sf::Font& font, unsigned int charSize)
    : font(font), characterSize(charSize), background(), lines()
{
    visible = false;
    padding = 8.f;
    lineSpacing = 4.f;
    item = nullptr;
    background.setFillColor(sf::Color(0, 0, 0, 150));
    background.setOutlineColor(sf::Color::Yellow);
    background.setOutlineThickness(1.f);
}

void DescriptionBox::setItem(Item* item) {
    
    this->item = item;
    visible = (item != nullptr);
    lines.clear();
    if (visible) {
        lines.clear();
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(characterSize);
        text.setFillColor(sf::Color::White);
        
            text.setString(item->getName());
            lines.push_back(text);

            text.setString("Typ: "+typeToString(item->getType()));
            lines.push_back(text);

            for (auto s : item->getDescriptionStrings()) {
                text.setString(s);
                lines.push_back(text);
            }
            text.setString("Cena: " + std::to_string(item->getPrice()));
            lines.push_back(text);
 
        updateLayout();
    }
}

void DescriptionBox::setPosition(const sf::Vector2f& pos) {
    background.setPosition(pos);
    updateLayout();
}

void DescriptionBox::draw(sf::RenderWindow& window) {
    if (!visible) {
        return;
    }
    window.draw(background);
    for (auto& line : lines) {
        window.draw(line);
    }
}

void DescriptionBox::updateLayout() {
    float width = 0.f;
    float height = padding * 2.f;

    for (std::size_t i = 0; i < lines.size(); ++i) {
        lines[i].setPosition(
            background.getPosition().x + padding,
            background.getPosition().y + padding + i * (characterSize + lineSpacing)
        );
        width = std::max(width, lines[i].getGlobalBounds().width);
        height += characterSize + lineSpacing;
    }

    background.setSize({ width + padding * 2.f, height });
}

std::string DescriptionBox::typeToString(ItemType t) const {
    switch (t) {
    case ItemType::HELMET:
        return "Helmet";
    case ItemType::ARMOR:
        return "Armor";
    case ItemType::GLOVES:
        return "Gloves";
    case ItemType::SHOES:
        return "Shoes";
    case ItemType::WEAPON:
        return "Weapon";
    case ItemType::NECKLACE:
        return "Necklace";
    case ItemType::BELT:
        return "Belt";
    case ItemType::RING:
        return "Ring";
    case ItemType::LUCKY_ITEM:
        return"Lucky item";
    default:
        return "None";
    }
}
