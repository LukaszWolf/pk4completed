#include "Quest.h"
#include <iomanip>
#include <sstream>

Quest::Quest(const std::string& name, const std::string& description, int durationSeconds, int gold,int xp, sf::Vector2f text_position)
    : name(name), description(description), reward_gold(gold),reward_xp(xp), isActivated(false), isCompletedFlag(false), text_pos(text_position)
{

    this->durationSeconds = durationSeconds;
    endTime = std::chrono::system_clock::now() + std::chrono::seconds(durationSeconds);
    sf::Font font;
    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
        std::cout << "Nie udalo sie wczytac tekstury!" << std::endl;
    }
    else{
    text_font = font;
    nameText.setFont(text_font);
    }
    nameText.setCharacterSize(40);
    nameText.setFillColor(sf::Color::Black);
    nameText.setString(name);
    nameText.setPosition({ text_pos.x,text_pos.y });

    timeText.setFont(text_font);
    timeText.setCharacterSize(40);
    timeText.setFillColor(sf::Color::Black);
   // posY += 130.f;
    timeText.setPosition({ text_pos.x,text_pos.y+130.f});

    rewardText.setFont(text_font);
    rewardText.setCharacterSize(40);
    rewardText.setFillColor(sf::Color(69,45,6));
    //posY += 150.f;
    rewardText.setPosition({ text_pos.x,text_pos.y + 280.f });

    updateText();
}


// Konstruktor kopiuj¹cy
Quest::Quest(const Quest& other)
    : name(other.name), description(other.description), reward_gold(other.reward_gold),
    reward_xp(other.reward_xp), isActivated(other.isActivated), isCompletedFlag(other.isCompletedFlag),
    durationSeconds(other.durationSeconds), startTime(other.startTime), endTime(other.endTime),
    text_font(other.text_font), text_pos(other.text_pos) // mo¿e wymagaæ specjalnego podejœcia
{
    // Inicjalizuj sf::Text ponownie, bo kopiowanie fontów i tekstów SFML mo¿e byæ z³o¿one
    nameText = other.nameText;
    timeText = other.timeText;
    rewardText = other.rewardText;


   

    nameText.setCharacterSize(40);
    nameText.setFillColor(sf::Color::Black);
    nameText.setString(name);
    nameText.setPosition({ text_pos.x,text_pos.y });

    timeText.setFont(text_font);
    timeText.setCharacterSize(40);
    timeText.setFillColor(sf::Color::Black);
    //posY += 130.f;
    timeText.setPosition({ text_pos.x,text_pos.y+130.f });

    rewardText.setFont(text_font);
    rewardText.setCharacterSize(40);
    rewardText.setFillColor(sf::Color(69, 45, 6));
    //posY += 150.f;
    rewardText.setPosition({ text_pos.x,text_pos.y+280.f });

    updateText();
}

// Operator przypisania (opcjonalnie)
Quest& Quest::operator=(const Quest& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        reward_gold = other.reward_gold;
        reward_xp = other.reward_xp;
        isActivated = other.isActivated;
        isCompletedFlag = other.isCompletedFlag;
        durationSeconds = other.durationSeconds;
        startTime = other.startTime;
        endTime = other.endTime;
        text_font = other.text_font;
        nameText = other.nameText;
        timeText = other.timeText;
        rewardText = other.rewardText;
    }
    return *this;
}



void Quest::start() {
    startTime = std::chrono::system_clock::now();
    endTime = startTime + (endTime - std::chrono::system_clock::now());
    isActivated = true;
}

void Quest::complete() {
    isActivated = false;
    isCompletedFlag = true;
}

bool Quest::isActive() const {
    return isActivated;
}

bool Quest::isCompleted() const {
    return isCompletedFlag;
}

int Quest::getRewardGold() const
{
    return reward_gold;
}

int Quest::getRewardXP() const {
    return reward_xp;
}

std::string Quest::getName() const {
    return name;
}

std::string Quest::getDescription() const {
    return description;
}

std::chrono::system_clock::time_point Quest::getStartTime() const {
    return startTime;
}

std::chrono::system_clock::time_point Quest::getEndTime() const {
    return endTime;
}

std::chrono::seconds Quest::getTimeLeft() const {
    auto now = std::chrono::system_clock::now();
    if (now >= endTime) return std::chrono::seconds(0);
    return std::chrono::duration_cast<std::chrono::seconds>(endTime - now);
}

std::string Quest::getFormattedTimeLeft() const {
    auto secondsLeft = getTimeLeft().count();
    int minutes = secondsLeft / 60;
    int seconds = secondsLeft % 60;
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setfill('0') << std::setw(2) << seconds;
    return oss.str();
}

int Quest::getDurationSeconds() const
{
    return durationSeconds;
}

void Quest::updateText() {
    timeText.setString("Czas misji\n" + getFormattedTimeLeft());
    rewardText.setString("Nagroda\n" + std::to_string(reward_gold) + "\n" + std::to_string(reward_xp));
}

sf::Text& Quest::getNameText() {
    return nameText;
}

sf::Text& Quest::getTimeText() {
    return timeText;
}

sf::Text& Quest::getRewardText() {
    return rewardText;
}

void Quest::setStartTime(std::chrono::system_clock::time_point start) {
    this->startTime = start;
}

void Quest::setDuration(std::chrono::seconds duration) {
    this->endTime = this->startTime + duration;
}
void Quest::setActive(bool active) {
    this->isActivated = true;
}
