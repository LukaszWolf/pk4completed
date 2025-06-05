#ifndef QUEST_H
#define QUEST_H

#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
# include<iostream>

class Quest {
private:
    sf::Font text_font;
    std::string name;
    std::string description;
    int reward_gold;
    int reward_xp;
    bool isActivated;
    bool isCompletedFlag;
    int durationSeconds;
    sf::Vector2f text_pos;

    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;

    sf::Text nameText;
    sf::Text timeText;
    sf::Text rewardText;

public:
    Quest(const std::string& name, const std::string& description, int durationSeconds, int gold, int xp, sf::Vector2f text_position);
    Quest(const Quest& other);

    Quest& operator=(const Quest& other);

    void start();
    void complete();

    bool isActive() const;
    bool isCompleted() const;
    int getRewardGold() const;
    int getRewardXP() const;
    std::string getName() const;
    std::string getDescription() const;
    std::chrono::system_clock::time_point getStartTime() const;
    std::chrono::system_clock::time_point getEndTime() const;
    std::chrono::seconds getTimeLeft() const;
    std::string getFormattedTimeLeft() const;
    int getDurationSeconds() const;

    void setStartTime(std::chrono::system_clock::time_point start);
    void setDuration(std::chrono::seconds duration);
    void setActive(bool active);
    void updateText();

    sf::Text& getNameText();
    sf::Text& getTimeText();
    sf::Text& getRewardText();
};

#endif