
#include "Game.h"
#include "Page.h"
#include <SFML/Graphics.hpp>

QuestPage::QuestPage(Game& game) : Page(game) {
    
    this->navBar = new NavBar(400, 1080, game);
    this->content_area = new ContentArea(1520, 1080, game, "Textures/quest_menu_background.png", 400, 0);
    loggedInUser = nullptr;
    this->activate_quest1_btn = new Button({ 730, 320 }, { 224, 85 }, "Textures/start_quest_btn.png", [this]() {activateMission(1); });
    this->activate_quest2_btn = new Button({ 1034, 320 }, { 224, 85 }, "Textures/start_quest_btn.png", [this]() {activateMission(2); });
    this->activate_quest3_btn = new Button({ 1338, 320 }, { 224, 85 }, "Textures/start_quest_btn.png", [this]() {activateMission(3); });
}

QuestPage::~QuestPage() {
    delete this->navBar;
    delete this->content_area;
    delete this->activate_quest1_btn;
    delete this->activate_quest2_btn;
    delete this->activate_quest3_btn;
}

void QuestPage::setLoggedInUser(Player*player){
    loggedInUser = player;
}

void QuestPage::draw(sf::RenderWindow& window) {
    if (loggedInUser && loggedInUser->getIsQuestInProgress()) {
        game_ref.changePage(GameState::MISSION_ACTIVE);
        return; 
    }
    if (navBar != nullptr) {
        navBar->draw(window);
    }
    if (content_area != nullptr) {
        content_area->draw(window);
    }
    if (loggedInUser and loggedInUser->getQuest(0) and loggedInUser->getQuest(1) and loggedInUser->getQuest(2)) {
       // window.draw(loggedInUser->getQuest(0)->getNameText());
        window.draw(loggedInUser->getQuest(0)->getTimeText());
        window.draw(loggedInUser->getQuest(0)->getRewardText());

        //window.draw(loggedInUser->getQuest(1)->getNameText());
        window.draw(loggedInUser->getQuest(1)->getTimeText());
        window.draw(loggedInUser->getQuest(1)->getRewardText());

        //window.draw(loggedInUser->getQuest(2)->getNameText());
        window.draw(loggedInUser->getQuest(2)->getTimeText());
        window.draw(loggedInUser->getQuest(2)->getRewardText());
    }
    if (activate_quest1_btn) {
        activate_quest1_btn->draw(window);
        activate_quest2_btn->draw(window);
        activate_quest3_btn->draw(window);
    }

    if (loggedInUser and loggedInUser->getRefreshQuestsFlag()) {
        refreshQuestsForPlayer();
        loggedInUser->setRefreshQuestsflag(false);
    }
}

void QuestPage::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    if ( loggedInUser->getIsQuestInProgress()) {
        game_ref.changePage(GameState::MISSION_ACTIVE);
    }
    if (navBar != nullptr) {
        navBar->handleEvents(event, window);
    }
    if (content_area != nullptr) {
        content_area->handleEvents(event, window);
    }
    if (activate_quest1_btn) {
        activate_quest1_btn->handleEvents(mousePos, event);
        activate_quest2_btn->handleEvents(mousePos, event);
        activate_quest3_btn->handleEvents(mousePos, event);
    }

}
void QuestPage::activateMission(int quest_num) {
    try
    {
        switch (quest_num) {
        case 1:
            loggedInUser->getQuest(0)->setStartTime(std::chrono::system_clock::now());
            loggedInUser->getQuest(0)->setActive(true);
            loggedInUser->saveQuestsToFile();
            loggedInUser->setQuestInProgress(true);
            loggedInUser->loadQuestsFromFile();
             game_ref.changePage(GameState::MISSION_ACTIVE);
            break;
        case 2:
            loggedInUser->getQuest(1)->setStartTime(std::chrono::system_clock::now());
            loggedInUser->getQuest(1)->setActive(true);
            loggedInUser->saveQuestsToFile();
            loggedInUser->setQuestInProgress(true);
            loggedInUser->loadQuestsFromFile();
            game_ref.changePage(GameState::MISSION_ACTIVE);
            break;
        case 3:
            loggedInUser->getQuest(2)->setStartTime(std::chrono::system_clock::now());
            loggedInUser->getQuest(2)->setActive(true);
            loggedInUser->saveQuestsToFile();
            loggedInUser->setQuestInProgress(true);
            loggedInUser->loadQuestsFromFile();
            game_ref.changePage(GameState::MISSION_ACTIVE);
            break;
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cout<<e.what();
    }
    
}
void QuestPage::refreshQuestsForPlayer() {
    if (!loggedInUser) return;

    static std::mt19937 rng{ std::random_device{}() };
    static std::uniform_int_distribution<int> time(30, 180);
    static std::uniform_real_distribution<float> multiplier(0.3f, 0.7f);

    std::unordered_map<int, std::string> quest_names = {
        {1, "CzarnyLas"},
        {2, "ZlotaJaskinia"},
        {3, "StaryZamek"},
        {4, "TajemnySkarb"},
        {5, "MroczneBagno"},
        {6, "ZaginionaWioska"},
        {7, "CichaDolina"}
    };

    std::vector<int> available_ids = { 1, 2, 3, 4, 5, 6, 7 };

    std::vector<Quest*> quests;

    float posXBase = 440.f;
    float posY = 330.f;
    int spacing = 300;

    for (int i = 0; i < 3; ++i) {
        if (available_ids.empty()) break;

        std::uniform_int_distribution<int> index(0, (int)available_ids.size() - 1);
        int randomIndex = index(rng);
        int id = available_ids[randomIndex];
        available_ids.erase(available_ids.begin() + randomIndex);

        int duration = time(rng);
        float gold_multiplier = multiplier(rng);
        int rewardGold = static_cast<int>(duration * gold_multiplier);
        int rewardXP = static_cast<int>(duration * (1.0f - gold_multiplier));

        std::string name = quest_names[id];

        float posX = posXBase + (i+1) * spacing;

        Quest* q = new Quest(name, "Opis", duration, rewardGold, rewardXP, sf::Vector2f(posX, posY));
        quests.push_back(q);
    }

    loggedInUser->setQuests(quests);
    loggedInUser->saveQuestsToFile();
}


