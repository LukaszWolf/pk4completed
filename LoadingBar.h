#ifndef LOADINGBAR_H
#define LOADINGBAR_H

#include <SFML/Graphics.hpp>
#include<thread>
#include<chrono>

class LoadingBar {
protected:
    sf::RectangleShape progressBar;   
    sf::Color barColor;                
    float width, height;               
    float progress;                    
    sf::Vector2f position;             

public:

    LoadingBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Green);

    virtual void updateProgress(float value1, float value2) = 0;  

    void draw(sf::RenderWindow& window);

    float getProgress() const;
};

class TimeLoadingBar : public LoadingBar {
public:

    TimeLoadingBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Green);
    void updateProgress(float elapsedTime, float duration) override;
};

class XPLoadingBar : public LoadingBar {
public:

    XPLoadingBar(float posX, float posY, float width, float height, sf::Color barColor = sf::Color::Blue);

    void updateProgress(float currentXP, float requiredXP) override;
};

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
    float animationSpeed = 5000.f; 
};

#endif

