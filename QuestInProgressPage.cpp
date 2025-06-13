#include "Game.h"
#include "Page.h"
#include <SFML/Graphics.hpp>

QuestInProgressPage::QuestInProgressPage(Game& game) : Page(game) {
    this->navBar = new NavBar(400.f, 1080.f, game);
    this->content_area = new ContentArea(1520.f, 1080.f, game, "Textures/quest_in_progress_background.png", 400, 0);
    this->time_bar = new TimeLoadingBar(826.f, 152.f, 780.f, 38.f, sf::Color(224,176,117));
    this->skip_quest_btn = new Button({ 825.f, 940.f }, { 313.f, 91.f }, "Textures/skip_quest_button.png", [this]() {skipQuest(); });
    this->cancel_quest_btn = new Button({ 1290.f, 940.f }, { 313.f, 91.f }, "Textures/cancel_mission_button.png", [this]() {cancelQuest(); });
    active_quest = nullptr;
    time_left_text.setCharacterSize(30);
    time_left_text.setString("");
    time_left_text.setPosition({ 1180.f,152.f });

    skip_price_text.setCharacterSize(32);
    skip_price_text.setString(": 100");
    skip_price_text.setPosition({ 987.f,964.f });
    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
     //   std::cout << "Nie udalo sie wczytac tekstury!" << std::endl;
    }
    else {
        time_left_text.setFont(font);
        skip_price_text.setFont(font);
    }
    loggedInUser = nullptr;
}

QuestInProgressPage::~QuestInProgressPage() {
    delete this->navBar;
    delete this->content_area;
    delete this->time_bar;
    delete this->skip_quest_btn;
    delete this->cancel_quest_btn;
}
void QuestInProgressPage::setActiveQuest(Quest* quest) {
}

void QuestInProgressPage::draw(sf::RenderWindow& window) {
    if (navBar != nullptr) {
        navBar->draw(window);
    }
    if (content_area != nullptr) {
        content_area->draw(window);
    }

    Player* player = game_ref.getLoggedInPlayer();
    if (!player) {
        time_left_text.setString(" ");
     //   std::cout << "QuestInProgressPage: brak zalogowanego gracza\n";
    }
    else {
        Quest* activeQuest = nullptr;
        for (int i = 0; i < 3; ++i) {
            Quest* q = player->getQuest(i);
            if (q && q->isActive()) {
                activeQuest = q;
             
                break;
            }
        }

        if (activeQuest) {
            float elapsedTime = activeQuest->getDurationSeconds() - activeQuest->getTimeLeft().count();  
            time_bar->updateProgress(elapsedTime, activeQuest->getDurationSeconds()); 

            std::string timeLeft = activeQuest->getFormattedTimeLeft();
            time_left_text.setString(timeLeft);
        }
        else {
            time_left_text.setString(" ");
           // std::cout << "QuestInProgressPage: brak aktywnego questa\n";
        }

        if (activeQuest) {
            auto timeLeft = activeQuest->getTimeLeft().count();
            if (timeLeft <= 0) {
                loggedInUser->setGold(loggedInUser->getGold() + activeQuest->getRewardGold());
                loggedInUser->setCurrentXP(loggedInUser->getCurrentXP() + activeQuest->getRewardXP());
                activeQuest->complete();
                game_ref.saveToFileStats();
                if(player){
                player->setQuestInProgress(false);
                player->saveQuestsToFile(); 
                player->setRefreshQuestsflag(true);
                }
                game_ref.changePage(GameState::QUEST_PAGE);
        //        std::cout << "Misja zakoñczona! Powrót do QUEST_PAGE\n";
            }
        }
    }



    if (time_bar) {
        time_bar->draw(window);
    }
    window.draw(time_left_text);
    if (cancel_quest_btn) {
        cancel_quest_btn->draw(window);
    }
    if (skip_quest_btn) {
        skip_quest_btn->draw(window);
    }
    window.draw(skip_price_text);

}

void QuestInProgressPage::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (navBar != nullptr) {
        navBar->handleEvents(event, window);
    }
    if (content_area != nullptr) {
        content_area->handleEvents(event, window);
    }
    if (cancel_quest_btn) {
        cancel_quest_btn->handleEvents(mousePos,event);
    }
    if (skip_quest_btn) {
        skip_quest_btn->handleEvents(mousePos, event);
        game_ref.setStatChangedFlag(true);
    }
}
void QuestInProgressPage::setLoggedInUser(Player* player) {
    loggedInUser = player;
}

void QuestInProgressPage::cancelQuest() {
    if (!game_ref.getLoggedInPlayer()) return;

    Quest* current_quest = nullptr;

    for (int i = 0; i < 3; ++i) {
        Quest* q = game_ref.getLoggedInPlayer()->getQuest(i);
        if (q && q->isActive()) {
            current_quest = q;
            break;
        }
    }

    current_quest->complete();
    current_quest->setStartTime(std::chrono::system_clock::time_point{}); 

    game_ref.getLoggedInPlayer()->setQuestInProgress(false);
    game_ref.getLoggedInPlayer()->saveQuestsToFile();
    game_ref.changePage(GameState::QUEST_PAGE);

}
void QuestInProgressPage::skipQuest() {
    if (!game_ref.getLoggedInPlayer()) return;

    Quest* current_quest = nullptr;
    for (int i = 0; i < 3; ++i) {
        Quest* q = game_ref.getLoggedInPlayer()->getQuest(i);
        if (q && q->isActive()) {
            current_quest = q;
            break;
        }
    }
    if(current_quest){
        loggedInUser->setGold(loggedInUser->getGold() + current_quest->getRewardGold()-100);
        loggedInUser->setCurrentXP(loggedInUser->getCurrentXP() + current_quest->getRewardXP());
        game_ref.saveToFileStats();
    }
    current_quest->complete();

    game_ref.getLoggedInPlayer()->setQuestInProgress(false);
    game_ref.getLoggedInPlayer()->saveQuestsToFile();
    game_ref.getLoggedInPlayer()->setRefreshQuestsflag(true);
    game_ref.changePage(GameState::QUEST_PAGE);
}
