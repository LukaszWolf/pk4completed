#include "TextBox.h"
#include <iostream>

TextBox::TextBox(float x, float y, float width, float height, std::string default_text)
    : isSelectedFlag(false), isPasswordMode(false),maxLength(0) {
    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
        std::cout << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
    }

    this->text.setFont(font);
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::White);
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color(150, 150, 150));
    
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + (height - 20) / 2);

    placeholder.setFont(font);
    placeholder.setCharacterSize(20);
    placeholder.setFillColor(sf::Color(150, 150, 150));
    placeholder.setPosition(x + 5, y + (height - 20) / 2);
    placeholder.setString(default_text);
}

void TextBox::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        isSelectedFlag = shape.getGlobalBounds().contains(
            static_cast<float>(event.mouseButton.x),
            static_cast<float>(event.mouseButton.y)
        );
        shape.setOutlineColor(isSelectedFlag ? sf::Color::Blue : sf::Color(150, 150, 150));
    }

    if (event.type == sf::Event::TextEntered && isSelectedFlag) {
        if (event.text.unicode == '\b') { //backspace
            if (!inputText.empty()) {
                inputText.pop_back();
                updateTextDisplay();
            }
        }
        else if (event.text.unicode < 128 and (maxLength == 0 || inputText.size() < maxLength)) {
            inputText += static_cast<char>(event.text.unicode);
            updateTextDisplay();
        }
    }
}

void TextBox::draw(sf::RenderWindow& window) const {
    window.draw(shape);
    if (inputText.empty() && !isSelectedFlag) {
        window.draw(placeholder);
    }
    else {
        window.draw(text);
    }
}

void TextBox::setPosition(float x, float y) {
    shape.setPosition(x, y);
    sf::Vector2f size = shape.getSize();
    text.setPosition(x + 5, y + (size.y - text.getCharacterSize()) / 2);
    placeholder.setPosition(x + 5, y + (size.y - placeholder.getCharacterSize()) / 2);
}

void TextBox::setSize(float width, float height) {
    shape.setSize(sf::Vector2f(width, height));
    sf::Vector2f pos = shape.getPosition();
    text.setPosition(pos.x + 5, pos.y + (height - text.getCharacterSize()) / 2);
    placeholder.setPosition(pos.x + 5, pos.y + (height - placeholder.getCharacterSize()) / 2);
}

void TextBox::setFont(const sf::Font& font) {
    text.setFont(font);
    placeholder.setFont(font);
}
void TextBox::setCharacterSize(unsigned int size) {
    text.setCharacterSize(size);
    placeholder.setCharacterSize(size);
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f boxSize = shape.getSize();  
    float textHeight = static_cast<float>(size);
    text.setPosition(pos.x + 5, pos.y + (boxSize.y - textHeight) / 2);
    placeholder.setPosition(pos.x + 5, pos.y + (boxSize.y - textHeight) / 2);
}

void TextBox::setTextColor(const sf::Color& color) {
    text.setFillColor(color);
}

void TextBox::setBackgroundColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void TextBox::setOutlineColor(const sf::Color& color) {
    shape.setOutlineColor(color);
}

void TextBox::setOutlineThickness(float thickness) {
    shape.setOutlineThickness(thickness);
}
void TextBox::clearText()
{
    this->inputText.clear();
    this->updateTextDisplay();
}
std::string TextBox::getText() const
{
    return this->text.getString().toAnsiString();
}
void TextBox::updateTextDisplay() {
    if (isPasswordMode && !inputText.empty()) {
        displayText = std::string(inputText.size(), '*');
        text.setString(displayText);
    }
    else {
        text.setString(inputText);
    }
}
