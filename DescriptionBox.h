#ifndef DESCRIPTION_BOX
#define DESCRIPTION_BOX

#include <SFML/Graphics.hpp>
#include <vector>
#include "Item.h"

class DescriptionBox {
public:
    DescriptionBox(const sf::Font& font, unsigned int charSize = 14 );
    void setItem(Item* item);
    void setPosition(const sf::Vector2f& pos);
    void setVisible(bool show) { visible = show; }
    void draw(sf::RenderWindow& window);

private:
    const sf::Font& font;
    unsigned int characterSize;
    sf::RectangleShape background;
    std::vector<sf::Text> lines;
    bool visible;
    float padding;
    float lineSpacing;
    Item* item;

    void updateLayout();
    std::string typeToString(ItemType t) const;
};

#endif // DESCRIPTIONBOX_H


