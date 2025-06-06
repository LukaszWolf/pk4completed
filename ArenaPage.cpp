#include "Page.h"
#include "Game.h"

ArenaPage::ArenaPage(Game& game) : Page(game) {
    navBar = new NavBar(400, 1080, game);
    content_area = new ContentArea(1520, 1080, game, "Textures/aren_background.png", 400, 0);
    loggedInUser = nullptr;
    this->fight_button1 = new Button({ 513.f,350.f }, { 400.f, 620.f }, "", [this]() {
        startFight(getEnemy(0));
        });
    this->fight_button2 = new Button({ 960.f,350.f }, { 400.f, 620.f }, "",[this]() {
            startFight(getEnemy(1));
        });
    this->fight_button3 = new Button({ 1407.f,350.f }, { 400.f, 620.f }, "", [this]() {
        startFight(getEnemy(2));
        });

    if (!font.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf")) {
   //     std::cout << "Nie mo¿na za³adowaæ czcionki!" << std::endl;
    }

}

ArenaPage::~ArenaPage() {
    delete navBar;
    delete content_area;
    for (auto disp : enemyDisplays){
        delete disp;
    }
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
    loggedInUser->setActiveEnemy(enemy);
    game_ref.setFightActiveFlag(true);
    game_ref.changePage(GameState::FIGHT_PAGE);
}

Enemy* ArenaPage::getEnemy(int num){
    if (enemies.size() == 3) {
        return enemies[num];
    }
}



void ArenaPage::refreshEnemies(bool generate_new_enemies) {
    if (!loggedInUser) return;

    if(!enemies.empty()){
        enemies.clear();
    }
    if(!enemyDisplays.empty()){
        for (auto disp : enemyDisplays) 
            if (disp) { delete disp; }
        enemyDisplays.clear();
    }

   
    std::vector<sf::Vector2f> positions = {
        {572.f, 399.f}, {1018.f, 399.f}, {1465.f, 399.f}
    };
    std::vector < std::string > image_paths{
        "Textures/enemy_img1.png","Textures/enemy_img2.png","Textures/enemy_img3.png","Textures/enemy_img4.png",
        "Textures/enemy_img5.png","Textures/enemy_img6.png",
    };
    if(generate_new_enemies){
        static std::mt19937 rng{ std::random_device{}() };
        static std::uniform_int_distribution<int> image_id(0, 3);
        static std::uniform_real_distribution<float> stat_multiplier(0.8f, 1.2f);
        static std::uniform_real_distribution<float> level_multiplier(0.9f, 1.1f);

       for (int i = 0; i < 3; ++i) {
           int img = image_id(rng);
            Enemy* enemy = new Enemy(
            "Przeciwnik" + std::to_string(i + 1),
            image_paths[img], loggedInUser->getStrength() * stat_multiplier(rng),
            loggedInUser->getDexterity() * stat_multiplier(rng),
            loggedInUser->getIntelligence() * stat_multiplier(rng),
            loggedInUser->getDurability() * stat_multiplier(rng),
            loggedInUser->getLuck() * stat_multiplier(rng), loggedInUser->getLevel() * level_multiplier(rng),
            loggedInUser->getLevel() * level_multiplier(rng) / 2);
            enemy->getCharacterTexture().loadFromFile(enemy->getImgName());
            enemies.push_back(enemy);
            image_paths.erase(image_paths.begin() + img);
            EnemyDisplay* disp = new EnemyDisplay(positions[i]);
            disp->setEnemyData(*enemy);
            enemyDisplays.push_back(disp);
        }
    }
    else {
        if (loggedInUser){
        for (int i = 0; i < 3; ++i) {
            EnemyDisplay* disp = new EnemyDisplay(positions[i]);
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
    enemies.clear();
}
