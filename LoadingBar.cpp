#include "LoadingBar.h"

LoadingBar::LoadingBar(float posX, float posY, float width, float height, sf::Color barColor)
    : width(width), height(height), progress(0.f), position(posX, posY), barColor(barColor) {
    progressBar.setSize(sf::Vector2f(0.f, height));  
    progressBar.setFillColor(barColor);
    progressBar.setPosition(position);
}


void LoadingBar::draw(sf::RenderWindow& window) {
    window.draw(progressBar);    
}

float LoadingBar::getProgress() const {
    return progress;
}

TimeLoadingBar::TimeLoadingBar(float posX, float posY, float width, float height, sf::Color barColor)
    : LoadingBar(posX, posY, width, height, barColor) {}

void TimeLoadingBar::updateProgress(float elapsedTime, float duration) {
    float progressValue = elapsedTime / duration;
    if (progressValue > 1.f) progressValue = 1.f;  
    progress = progressValue;

    progressBar.setSize(sf::Vector2f(progress * width, height));
}

XPLoadingBar::XPLoadingBar(float posX, float posY, float width, float height, sf::Color barColor)
    : LoadingBar(posX, posY, width, height, barColor) {}

void XPLoadingBar::updateProgress(float currentXP, float requiredXP) {
    float progressValue = currentXP / requiredXP;
    if (progressValue > 1.f) progressValue = 1.f;  
    progress = progressValue;
    progressBar.setSize(sf::Vector2f(progress * width, height));
}




HPBar::HPBar(float posX, float posY, float width_, float height_, sf::Color barColor)
    : LoadingBar(posX, posY, width_, height_, barColor),
    last_hp(0.f), target_hp(0.f), max_hp(1.f), animationSpeed(200.f) {}

void HPBar::updateProgress(float currentHP, float maxHP_) {
    if (currentHP < 0.f) currentHP = 0.f;
    if (currentHP > maxHP_) currentHP = maxHP_;

    if (last_hp == 0.f) last_hp = currentHP;
    target_hp = currentHP;
    max_hp = maxHP_;
    animationSpeed = std::abs(last_hp - target_hp); 
}

void HPBar::animate(float deltaTime) {
    if (last_hp > target_hp) {
        float delta = animationSpeed * deltaTime;
        last_hp = (last_hp - delta < target_hp) ? target_hp : last_hp - delta;
    }
    else if (last_hp < target_hp) {
        float delta = animationSpeed * deltaTime;
        last_hp = (last_hp + delta > target_hp) ? target_hp : last_hp + delta;
    }

    float ratio = last_hp / max_hp;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    progress = ratio;
    progressBar.setSize({ width * progress, height });
}

float HPBar::getDisplayedHP() const {
    return last_hp;
}

