#include "Page.h"
#include "Game.h"
#include <chrono>
#include <iostream>

FightPage::FightPage(Game& game) : Page(game) {
    content_area = new ContentArea(1920, 1080, game, "Textures/fight_page_background.png", 0, 0);
    player_img.setSize({ 460.f, 460.f });
    player_img.setPosition(220.f, 453.f);

    enemy_img.setSize({ 460.f, 460.f });
    enemy_img.setPosition(1240.f, 454.f);

    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
      //  std::cout << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
    }
    player_hp_text.setFont(font);
    player_hp_text.setFillColor(sf::Color::White);
    player_hp_text.setCharacterSize(32);
    player_hp_text.setPosition(345.f, 960.f);
    player_hp_text.setString("0");

    enemy_hp_text.setFont(font);
    enemy_hp_text.setFillColor(sf::Color::White);
    enemy_hp_text.setCharacterSize(32);
    enemy_hp_text.setPosition(1390.f, 960.f);
    enemy_hp_text.setString("0");

    player_hp_bar = new HPBar(185.f, 954.f, 533.f, 55.f, sf::Color::Red);
    enemy_hp_bar = new HPBar(1200.f, 956.f, 533.f, 55.f, sf::Color::Red);
    player_current_hp = 0;
    enemy_current_hp = 0;
    player_max_hp = 0;
    enemy_max_hp = 0;
    loggedInUser = nullptr;
    enemy = nullptr;
   // fight_init_flag = false;
}

FightPage::~FightPage() {
    delete content_area;
    delete player_hp_bar;
    delete enemy_hp_bar;
}

void FightPage::handleEvents(sf::Event event, sf::RenderWindow& window) {
sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
if (content_area) content_area->handleEvents(event, window);

if (playerTurn && enemy_img.getGlobalBounds().contains(mousePos) && event.type == sf::Event::MouseButtonPressed &&
    event.mouseButton.button == sf::Mouse::Left) {
    enemy_current_hp -= loggedInUser->attack();
    enemy_hp_bar->updateProgress(enemy_current_hp, enemy_max_hp);
    playerTurn = false;
    enemyTurnScheduled = true;
    enemyTurnTime = std::chrono::steady_clock::now() + std::chrono::seconds(2);
}
}

void FightPage::draw(sf::RenderWindow& window) {
    static std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<float> deltaTime = now - lastFrameTime;
    lastFrameTime = now;

    if (!fight_initialized) {
        initFight();
     //   std::cout  << "inicjalizacja walki" << std::endl;
    }

    if (player_hp_bar) {
        player_hp_bar->animate(deltaTime.count());
        float hp = player_hp_bar->getDisplayedHP();
        player_hp_text.setString(std::to_string(static_cast<int>(hp)) + "/" + std::to_string(static_cast<int>(player_max_hp)));
    }

    if (enemy_hp_bar) {
        enemy_hp_bar->animate(deltaTime.count());
        float hp = enemy_hp_bar->getDisplayedHP();
        enemy_hp_text.setString(std::to_string(static_cast<int>(hp)) + "/" + std::to_string(static_cast<int>(enemy_max_hp)));
    }

    if (fight_initialized && enemy_hp_bar && enemy_hp_bar->getDisplayedHP() <= 0.f) {
        std::cout << "Wygrana" << std::endl;
        fight_initialized = false;  
        game_ref.setFightActiveFlag(false); 
        loggedInUser->setRefreshEnemiesflag(true);
      //  std::cout << loggedInUser->getActiveEnemy()->getRewardGold() <<std::endl;
        loggedInUser->setGold(loggedInUser->getGold() + loggedInUser->getActiveEnemy()->getRewardGold());
        game_ref.changePage(GameState::ARENA_PAGE);
        return;
    }

    if (fight_initialized && player_hp_bar && player_hp_bar->getDisplayedHP() <= 0.f) {
        std::cout << "Porazka" << std::endl;
        fight_initialized = false;  
        game_ref.setFightActiveFlag(false); 
        loggedInUser->setRefreshEnemiesflag(true);
        game_ref.changePage(GameState::ARENA_PAGE);
        return;
    }

    if (enemyTurnScheduled && now >= enemyTurnTime) {
        player_current_hp -= loggedInUser->getActiveEnemy()->attack();
        player_hp_bar->updateProgress(player_current_hp, player_max_hp);
        enemyTurnScheduled = false;
        playerTurn = true;
    }

    if (content_area) content_area->draw(window);
    if (loggedInUser && loggedInUser->getActiveEnemy()) {
        window.draw(player_img);
        window.draw(enemy_img);
        player_hp_bar->draw(window);
        enemy_hp_bar->draw(window);
        window.draw(player_hp_text);
        window.draw(enemy_hp_text);
    }
}



void FightPage::initFight() {
    player_current_hp = loggedInUser->calculateHP();
    enemy_current_hp = loggedInUser->getActiveEnemy()->calculateHP();
    player_max_hp = player_current_hp;
    enemy_max_hp = enemy_current_hp;
    player_hp_bar->updateProgress(player_current_hp, player_max_hp);
    enemy_hp_bar->updateProgress(enemy_current_hp, enemy_max_hp);
    setPlayerAndEnemyImg();
    playerTurn = true;
    enemyTurnScheduled = false;
    fight_initialized = true;
}

void FightPage::setLoggedInUser(Player* player) {
    loggedInUser = player;
}

void FightPage::setPlayerAndEnemyImg() {
    player_img_texture.loadFromFile(loggedInUser->getImgName());
    player_img.setTexture(&player_img_texture);

    enemy_img_texture.loadFromFile(loggedInUser->getActiveEnemy()->getImgName()); 
    enemy_img.setTexture(&enemy_img_texture);
}


void FightPage::setEnemy(Enemy* e) {
    enemy = e;
}

Enemy* FightPage::getEnemy() {
    return enemy;
}

Player* FightPage::getLoggedInUser() {
    return loggedInUser;
}
