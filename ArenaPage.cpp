#include "Page.h"
#include "Game.h"

ArenaPage::ArenaPage(Game& game) : Page(game) {
    navBar = new NavBar(400, 1080, game);
    content_area = new ContentArea(1520, 1080, game, "Textures/aren_background.png", 400, 0);
    loggedInUser = nullptr;
    this->fight_button1 = new Button({ 700.f,800.f }, { 324.f, 80.f }, "Textures/arena_button.png", [this]() {
        startFight(getEnemy(0));
        });
    this->fight_button2 = new Button({ 1100.f,800.f }, { 324.f, 80.f }, "Textures/arena_button.png",[this]() {
            startFight(getEnemy(1));
        });
    this->fight_button3 = new Button({ 1500.f,800.f }, { 324.f, 80.f }, "Textures/arena_button.png", [this]() {
        startFight(getEnemy(2));
        });

    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
        std::cout << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
    }

}

ArenaPage::~ArenaPage() {
    delete navBar;
    delete content_area;
    //for (auto enemy : enemies) delete enemy;
    for (auto disp : enemyDisplays) delete disp;
    delete fight_button1;
    delete fight_button2;
    delete fight_button3;
}

void ArenaPage::setLoggedInUser(Player* player) {
    if(player){
    loggedInUser = player;
    loggedInUser->loadArenaEnemiesFromFile();
    refreshEnemies(0);
    }
}

void ArenaPage::draw(sf::RenderWindow& window) {
    if (navBar) navBar->draw(window);
    if (content_area) content_area->draw(window);
    for (const auto& disp : enemyDisplays) disp->draw(window);
    fight_button1->draw(window);
    fight_button2->draw(window);
    fight_button3->draw(window);
    if (loggedInUser and loggedInUser->getRefreshEnemiesFlag()) {
        refreshEnemies(1);
        loggedInUser->setRefreshEnemiesflag(false);
    }
}

void ArenaPage::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (content_area) content_area->handleEvents(event, window);
    if (navBar) navBar->handleEvents(event, window);
    if (fight_button1) fight_button1->handleEvents(mousePos, event);
    if (fight_button2) fight_button2->handleEvents(mousePos, event);
    if (fight_button3) fight_button3->handleEvents(mousePos, event);

}

void ArenaPage::startFight(Enemy*enemy) {
    //refreshEnemies(1); trzeba wlaczac po zakonczonej walce zeby przeciwnika nie odswiezylo albo najpierw ustawiac przeciwnika w fight page
    loggedInUser->setActiveEnemy(enemy);
    game_ref.setFightActiveFlag(true);
    game_ref.changePage(GameState::FIGHT_PAGE);


}

Enemy* ArenaPage::getEnemy(int num)
{
    if (enemies.size() == 3) {
        return enemies[num];
    }
}



void ArenaPage::refreshEnemies(bool generate_new_enemies) {
    if (!loggedInUser) return;

    if(!enemies.empty()){
        //for (auto enemy : enemies) {
        //    if (enemy) {
        //        delete enemy;
        //    }
        //}
        enemies.clear();
    }
    if(!enemyDisplays.empty()){
        for (auto disp : enemyDisplays) 
            if (disp) { delete disp; }
        enemyDisplays.clear();
    }

   
  

    
    std::vector<sf::Vector2f> positions = {
        {600.f, 200.f}, {1050.f, 200.f}, {1500.f, 200.f}
    };
    std::vector < std::string > image_paths{
        "Textures/test.png", "Textures/test2.png"
    };
    if(generate_new_enemies){
        static std::mt19937 rng{ std::random_device{}() };
        static std::uniform_int_distribution<int> image_id(0, 1);
        static std::uniform_real_distribution<float> stat_multiplier(0.8f, 1.2f);
        static std::uniform_real_distribution<float> level_multiplier(0.9f, 1.1f);

       for (int i = 0; i < 3; ++i) {
            Enemy* enemy = new Enemy(
            "Przeciwnik" + std::to_string(i + 1),
            image_paths[image_id(rng)], loggedInUser->getStrength() * stat_multiplier(rng),
            loggedInUser->getDexterity() * stat_multiplier(rng),
            loggedInUser->getIntelligence() * stat_multiplier(rng),
            loggedInUser->getConstitution() * stat_multiplier(rng),
            loggedInUser->getLuck() * stat_multiplier(rng), loggedInUser->getLevel() * level_multiplier(rng),
            loggedInUser->getLevel() * level_multiplier(rng) / 2);
            enemy->getCharacterTexture().loadFromFile(enemy->getImgName());
            enemies.push_back(enemy);

            EnemyDisplay* disp = new EnemyDisplay(positions[i]);
            disp->setEnemyData(*enemy);
            enemyDisplays.push_back(disp);
        }
    }
    else {
        if (loggedInUser){
        for (int i = 0; i < 3; ++i) {
            EnemyDisplay* disp = new EnemyDisplay(positions[i]);
          //  enemies.clear();
            enemies.push_back(loggedInUser->getArenaEnemy(i));
            disp->setEnemyData(*enemies[i]);
            enemyDisplays.push_back(disp);
        }
        }

    }
    loggedInUser->setArenaEnemies(enemies);
    loggedInUser->saveArenaEnemiesToFile();
}
void ArenaPage::clearEnemyDisplays() {
    for (EnemyDisplay* ed : enemyDisplays) {
        delete ed;
    }
    enemyDisplays.clear();

    // Jeœli to konieczne, to tak¿e usuñ surowe wskaŸniki do Enemy*:
    //for (Enemy* e : enemies) {
    //    delete e;
    //}
    enemies.clear();
}
