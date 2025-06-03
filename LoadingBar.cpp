#include "LoadingBar.h"

// Konstruktor LoadingBar
LoadingBar::LoadingBar(float posX, float posY, float width, float height, sf::Color barColor)
    : width(width), height(height), progress(0.f), position(posX, posY), barColor(barColor) {
    // Ustawienie paska postêpu
    progressBar.setSize(sf::Vector2f(0.f, height));  // Na pocz¹tku szerokoœæ jest 0
    progressBar.setFillColor(barColor);
    progressBar.setPosition(position);
}

// Rysowanie paska postêpu
void LoadingBar::draw(sf::RenderWindow& window) {
    window.draw(progressBar);    // Rysowanie paska postêpu
}

// Getter dla postêpu
float LoadingBar::getProgress() const {
    return progress;
}

// Konstruktor TimeLoadingBar
TimeLoadingBar::TimeLoadingBar(float posX, float posY, float width, float height, sf::Color barColor)
    : LoadingBar(posX, posY, width, height, barColor) {}

// Implementacja updateProgress dla czasu
void TimeLoadingBar::updateProgress(float elapsedTime, float duration) {
    // Obliczamy postêp na podstawie up³ywaj¹cego czasu
    float progressValue = elapsedTime / duration;
    if (progressValue > 1.f) progressValue = 1.f;  // Górna granica 100%
    progress = progressValue;

    // Ustawienie szerokoœci paska postêpu
    progressBar.setSize(sf::Vector2f(progress * width, height));
}

// Konstruktor XPLoadingBar
XPLoadingBar::XPLoadingBar(float posX, float posY, float width, float height, sf::Color barColor)
    : LoadingBar(posX, posY, width, height, barColor) {}

// Implementacja updateProgress dla XP
void XPLoadingBar::updateProgress(float currentXP, float requiredXP) {
    // Obliczamy postêp na podstawie XP
    float progressValue = currentXP / requiredXP;
    if (progressValue > 1.f) progressValue = 1.f;  // Górna granica 100%
    progress = progressValue;

    // Ustawienie szerokoœci paska postêpu
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
    animationSpeed = std::abs(last_hp - target_hp); // 1 sekunda animacji
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


//HPBar::HPBar(float posX, float posY, float width, float height, sf::Color barColor)
//    : LoadingBar(posX, posY, width, height, barColor) {
//    
//    hp_text.setCharacterSize(16);
//    max_hp_text.setCharacterSize(16);
//
//    hp_text.setFillColor(sf::Color::White);
//    max_hp_text.setFillColor(sf::Color::White);
//    
//  
//    hp_text.setString ("0");
//    max_hp_text.setString("0");
//    last_hp = 0.f;

//}
//void HPBar::updateProgress(float currentHP, float maxHP_) {
//    currentHP = std::clamp(currentHP, 0.f, maxHP_);
//    if (last_hp == 0.f) {
//        last_hp = currentHP;
//    }
//    target_hp = currentHP;
//    max_hp = maxHP_;
//}
//
//void HPBar::animate(float deltaTime) {
//    if (last_hp > target_hp) {
//        float delta = animationSpeed * deltaTime;
//        last_hp = std::max(last_hp - delta, target_hp);
//    }
//    float ratio = std::clamp(last_hp / max_hp, 0.f, 1.f);
//    progressBar.setSize({ width * ratio, height });
//}
////
////void HPBar::updateProgress(float currentHP, float maxHP) {
////    // Obliczamy postêp na podstawie XP
////    if (currentHP < 0.f) {
////        currentHP = 0.f;
////    }
////    if (last_hp == 0.f) {
////        last_hp = currentHP;
////    }
////    progressBar.setSize(sf::Vector2f((last_hp/maxHP) * width, height));
////    float delta;
////    while(currentHP<last_hp){
////        delta = (last_hp - currentHP) / 10.f;
////        last_hp -= delta;
////        if (last_hp < currentHP) {
////            last_hp = currentHP;
////        }
////        float progressValue = last_hp / maxHP;
////        //if (progressValue > 1.f) progressValue = 1.f;  // Górna granica 100%
////        progress = progressValue;
////        progressBar.setSize(sf::Vector2f(progress * width, height));
////        std::this_thread::sleep_for(std::chrono::milliseconds(500));
////    }
////    // Ustawienie szerokoœci paska postêpu
////    
//    
//}