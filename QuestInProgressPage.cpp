#include "Game.h"
#include "Page.h"
#include <SFML/Graphics.hpp>

QuestInProgressPage::QuestInProgressPage(Game& game) : Page(game) {
    this->navBar = new NavBar(400, 1080, game);
    this->content_area = new ContentArea(1520, 1080, game, "Textures/test2.png", 400, 0);
    this->time_bar = new TimeLoadingBar(100.f, 50.f, 600.f, 30.f, sf::Color::Green);
    this->skip_quest_btn = new Button({ 800, 455 }, { 324, 80 }, "Textures/quests_button.png", [this]() {skipQuest(); });
    this->cancel_quest_btn = new Button({ 1200, 455 }, { 324, 80 }, "Textures/arena_button.png", [this]() {cancelQuest(); });
    active_quest = nullptr;
    time_left_text.setCharacterSize(30);
    time_left_text.setString("");
    time_left_text.setPosition({ 700,700 });
    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
        std::cout << "Nie udalo sie wczytac tekstury!" << std::endl;
    }
    else {
        time_left_text.setFont(font);
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
    //active_quest = quest;
    //if (active_quest) {
    //    time_left_text.setString(active_quest->getFormattedTimeLeft());
    //}
    //else {
    //    time_left_text.setString("");
    //}
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
        time_left_text.setString("Brak zalogowanego gracza");
        std::cout << "QuestInProgressPage: brak zalogowanego gracza\n";
    }
    else {
        Quest* activeQuest = nullptr;
        for (int i = 0; i < 3; ++i) {
            Quest* q = player->getQuest(i);
            if (q && q->isActive()) {
                activeQuest = q;
               // std::cout << "QuestInProgressPage: aktywny quest: " << q->getName() << "\n";
                break;
            }
        }
        //if (activeQuest) {
        //    std::string timeLeft = activeQuest->getFormattedTimeLeft();
        //    time_left_text.setString(timeLeft);
        //    std::cout << "QuestInProgressPage: czas pozostaly: " << timeLeft << "\n";
        //}
        //else {
        //    time_left_text.setString("Brak aktywnego questa");
        //    std::cout << "QuestInProgressPage: brak aktywnego questa\n";
        //}


        if (activeQuest) {
            // Obliczamy czas, kt�ry up�yn��
            float elapsedTime = activeQuest->getDurationSeconds() - activeQuest->getTimeLeft().count();  // Czas, kt�ry up�yn��
            time_bar->updateProgress(elapsedTime, activeQuest->getDurationSeconds());  // Aktualizujemy pasek czasu

            // Wy�wietlanie pozosta�ego czasu
            std::string timeLeft = activeQuest->getFormattedTimeLeft();
            time_left_text.setString(timeLeft);
            //std::cout << "QuestInProgressPage: czas pozostaly: " << timeLeft << "\n";
        }
        else {
            time_left_text.setString("Brak aktywnego questa");
            std::cout << "QuestInProgressPage: brak aktywnego questa\n";
        }

        if (activeQuest) {
            auto timeLeft = activeQuest->getTimeLeft().count();
            if (timeLeft <= 0) {
                // Misja zako�czona, zmiana stanu gry
                loggedInUser->setGold(loggedInUser->getGold() + activeQuest->getRewardGold());
                loggedInUser->setCurrentXP(loggedInUser->getCurrentXP() + activeQuest->getRewardXP());
                activeQuest->complete();
                game_ref.saveToFileStats();
                if(player){
                player->setQuestInProgress(false);
                player->saveQuestsToFile(); // Zapisz zmian�
                player->setRefreshQuestsflag(true);
                }
                game_ref.changePage(GameState::QUEST_PAGE);
                std::cout << "Misja zako�czona! Powr�t do QUEST_PAGE\n";
            }
        }
    }

    // Tymczasowy test - zobacz czy tekst wy�wietla si�
    // time_left_text.setString("Test wy�wietlania");

    window.draw(time_left_text);
    if (time_bar) {
        time_bar->draw(window);
    }
    if (cancel_quest_btn) {
        cancel_quest_btn->draw(window);
    }
    if (skip_quest_btn) {
        skip_quest_btn->draw(window);
    }

}

void QuestInProgressPage::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    /*if (active_quest and game_ref.getLoggedInPlayer()) {
        time_left_text.setString(active_quest->getFormattedTimeLeft());
    }*/
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
    
   // sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
}
void QuestInProgressPage::setLoggedInUser(Player* player) {
    loggedInUser = player;
}

void QuestInProgressPage::cancelQuest() {
    if (!game_ref.getLoggedInPlayer()) return;

    Quest* current_quest = nullptr;
    // Znajd� aktywny quest gracza
    for (int i = 0; i < 3; ++i) {
        Quest* q = game_ref.getLoggedInPlayer()->getQuest(i);
        if (q && q->isActive()) {
            current_quest = q;
            break;
        }
    }

    //if (!activeQuest) {
    //    std::cout << "Brak aktywnego questa do pomini�cia.\n";
    //    return;
    //}

    // Zako�cz questa natychmiast
    current_quest->complete();
    current_quest->setStartTime(std::chrono::system_clock::time_point{}); // zerowa warto�� czasu (epoch)

    // Zresetuj flag� quest in progress
    game_ref.getLoggedInPlayer()->setQuestInProgress(false);

    // Zapisz zmiany
    game_ref.getLoggedInPlayer()->saveQuestsToFile();

    // Ustaw flag� od�wie�enia quest�w, je�li masz tak� w grze
    //game_ref.getLoggedInPlayer()->setRefreshQuestsflag(true);

    // Prze��cz stron� na QUEST_PAGE
    game_ref.changePage(GameState::QUEST_PAGE);

    std::cout << "Quest zosta� pomini�ty i zako�czony natychmiast.\n";
}
void QuestInProgressPage::skipQuest() {
    if (!game_ref.getLoggedInPlayer()) return;

    Quest* current_quest = nullptr;
    // Znajd� aktywny quest gracza
    for (int i = 0; i < 3; ++i) {
        Quest* q = game_ref.getLoggedInPlayer()->getQuest(i);
        if (q && q->isActive()) {
            current_quest = q;

            //kasiorka
           // loggedInUser->setGold(loggedInUser->getGold() + active_quest->getRewardGold());
            break;
        }
    }
    //kasiorka
    if(current_quest){
        loggedInUser->setGold(loggedInUser->getGold() + current_quest->getRewardGold());
        loggedInUser->setCurrentXP(loggedInUser->getCurrentXP() + current_quest->getRewardXP());
        game_ref.saveToFileStats();
    }
    // Zako�cz questa natychmiast
    current_quest->complete();

    // Zresetuj flag� quest in progress
    game_ref.getLoggedInPlayer()->setQuestInProgress(false);

    // Zapisz zmiany
    game_ref.getLoggedInPlayer()->saveQuestsToFile();

    // Ustaw flag� od�wie�enia quest�w, je�li masz tak� w grze
    game_ref.getLoggedInPlayer()->setRefreshQuestsflag(true);

    // Prze��cz stron� na QUEST_PAGE
    game_ref.changePage(GameState::QUEST_PAGE);

    std::cout << "Quest zosta� pomini�ty i zako�czony natychmiast.\n";
}
