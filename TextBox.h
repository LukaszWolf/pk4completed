#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
private:
    void updateTextDisplay();

    sf::RectangleShape shape;
    sf::Text text;
    sf::Text placeholder;
    std::string inputText;
    std::string displayText;
    bool isSelectedFlag;
    bool isPasswordMode;
    unsigned int maxLength;
    sf::Font font;
public:
    TextBox(float x, float y, float width, float height, std::string default_text);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window) const;

    void setPosition(float x, float y);
    void setSize(float width, float height);
    void setFont(const sf::Font& font);
    void setCharacterSize(unsigned int size);
    void setTextColor(const sf::Color& color);
    void setBackgroundColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(float thickness);
    void setPasswordMode(bool isPassword);
    void clearText();
    std::string getText() const;


};

#endif 