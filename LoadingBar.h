#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include <SFML/Graphics.hpp>
#include<thread>
#include<chrono>

// Klasa abstrakcyjna LoadingBar
class LoadingBar {
protected:
    sf::RectangleShape progressBar;    // Pasek postêpu
    sf::Color barColor;                // Kolor paska postêpu
    float width, height;               // Szerokoœæ i wysokoœæ paska
    float progress;                    // Postêp (od 0 do 1)
    sf::Vector2f position;             // Pozycja paska

public:
    // Konstruktor
    LoadingBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Green);

    // Wirtualna funkcja do aktualizacji postêpu
    virtual void updateProgress(float value1, float value2) = 0;  // Implementacja w klasach pochodnych

    // Rysowanie paska na ekranie
    void draw(sf::RenderWindow& window);

    // Getter dla postêpu
    float getProgress() const;
};

// Klasa TimeLoadingBar dziedzicz¹ca po LoadingBar
class TimeLoadingBar : public LoadingBar {
public:
    // Konstruktor
    TimeLoadingBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Green);

    // Implementacja updateProgress dla czasu
    void updateProgress(float elapsedTime, float duration) override;
};



//te dwa ponizej da sie w jedno skleic


// Klasa XPLoadingBar dziedzicz¹ca po LoadingBar
class XPLoadingBar : public LoadingBar {
public:
    // Konstruktor
    XPLoadingBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Blue);

    // Implementacja updateProgress dla XP
    void updateProgress(float currentXP, float requiredXP) override;
};

//class HPBar : public LoadingBar {
//    float last_hp;
//    sf::Text hp_text;
//    sf::Text max_hp_text;
//public:
//    // Konstruktor
//    
//    HPBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Red);
//
//    // Implementacja updateProgress dla XP
//    void updateProgress(float currentHP, float maxHP) override;
//};

class HPBar : public LoadingBar {
public:
    HPBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Red);
    void updateProgress(float currentHP, float maxHP) override;
    void animate(float deltaTime);

    float getDisplayedHP() const;

private:
    float last_hp = 0.f;
    float target_hp = 0.f;
    float max_hp = 1.f;
    float animationSpeed = 5000.f; // domyœlnie
};

#endif // LOADINGBAR_H


