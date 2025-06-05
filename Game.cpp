
#include "Game.h"
#include <iostream>


void Game::initVariables() { 
    this->window = nullptr;
    this->player_menu_screen = nullptr;
    this->login_Screen = nullptr;
    this->quest_menu_screen = nullptr;
    this->quest_in_progress_screen = nullptr;
    this->arena_screen = nullptr;
    this->changePage(GameState::LOGIN_PAGE);
    
}

void Game::initWindow() {
    this->video_mode = sf::VideoMode::getDesktopMode();
    this->window = new sf::RenderWindow(this->video_mode, "Gra", sf::Style::Fullscreen);
    this->window->setFramerateLimit(60);
}

std::string Game:: formatPlayerLine(Player* p) {
    std::ostringstream oss;
    oss
        << "login: " << p->getName()
        << " pass: " << p->getPassword()
        << " image: " << p->getImgName()
        << " strenght: " << p->getBaseStrenght()
        << " dexterity: " << p->getBaseDexterity()
        << " intelligence: " << p->getBaseIntelligence()
        << " durability: " << p->getBaseDurability()
        << " luck: " << p->getBaseLuck()
        << " level: " << p->getLevel()
        << " gold: " << p->getGold()
        << " xp: " << p->getCurrentXP();
    return oss.str();
}

std::string Game::formatEquipmentLine(Player*p) {


    std::ostringstream oss;
    oss << "login: " << p->getName()
        << " helmet: " << (p->getItem("helmet") ? std::to_string(p->getItem("helmet")->getId()) : "000")
        << " shield: " << (p->getItem("shield") ? std::to_string(p->getItem("shield")->getId()) : "000")
        << " gloves: " << (p->getItem("gloves") ? std::to_string(p->getItem("gloves")->getId()) : "000")
        << " shoes: " << (p->getItem("shoes") ? std::to_string(p->getItem("shoes")->getId()) : "000")
        << " weapon: " << (p->getItem("weapon") ? std::to_string(p->getItem("weapon")->getId()) : "000")
        << " necklace: " << (p->getItem("necklace") ? std::to_string(p->getItem("necklace")->getId()) : "000")
        << " belt: " << (p->getItem("belt") ? std::to_string(p->getItem("belt")->getId()) : "000")
        << " ring: " << (p->getItem("ring") ? std::to_string(p->getItem("ring")->getId()) : "000")
        << " luckyitem: " << (p->getItem("luckyitem") ? std::to_string(p->getItem("luckyitem")->getId()) : "000")
        << " slot1: " << (p->getItem("slot1") ? std::to_string(p->getItem("slot1")->getId()) : "000")
        << " slot2: " << (p->getItem("slot2") ? std::to_string(p->getItem("slot2")->getId()) : "000")
        << " slot3: " << (p->getItem("slot3") ? std::to_string(p->getItem("slot3")->getId()) : "000")
        << " slot4: " << (p->getItem("slot4") ? std::to_string(p->getItem("slot4")->getId()) : "000")
        << " slot5: " << (p->getItem("slot5") ? std::to_string(p->getItem("slot5")->getId()) : "000")
        << " slot6: " << (p->getItem("slot6") ? std::to_string(p->getItem("slot6")->getId()) : "000")
        << " slot7: " << (p->getItem("slot7") ? std::to_string(p->getItem("slot7")->getId()) : "000")
        << " slot8: " << (p->getItem("slot8") ? std::to_string(p->getItem("slot8")->getId()) : "000")
        << " shop1: " << (p->getItem("shop1") ? std::to_string(p->getItem("shop1")->getId()) : "000")
        << " shop2: " << (p->getItem("shop2") ? std::to_string(p->getItem("shop2")->getId()) : "000")
        << " shop3: " << (p->getItem("shop3") ? std::to_string(p->getItem("shop3")->getId()) : "000")
        << " shop4: " << (p->getItem("shop4") ? std::to_string(p->getItem("shop4")->getId()) : "000")
        << " shop5: " << (p->getItem("shop5") ? std::to_string(p->getItem("shop5")->getId()) : "000")
        << " shop6: " << (p->getItem("shop6") ? std::to_string(p->getItem("shop6")->getId()) : "000");

    return oss.str();
}

void Game::saveToFileStats() {
    const std::string fileName = "Data/accounts.txt";
    std::ifstream in(fileName);
    if (!in.is_open()) {
      //  std::cout << "Nie można otworzyć pliku do odczytu: " << fileName << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    in.close();

    std::string newLine = formatPlayerLine(loggedInPlayer);

    bool replaced = false;
    std::string prefix = "login: " + loggedInPlayer->getName() + " ";
    for (auto& ln : lines) {
        if (ln.rfind(prefix, 0) == 0) {
            ln = newLine;
            replaced = true;
            break;
        }
    }
    if (!replaced) {
        lines.push_back(newLine);
    }

    std::ofstream out(fileName, std::ios::trunc);
    if (!out.is_open()) {
       // std::cout << "Nie można otworzyć pliku do zapisu: " << fileName <<std::endl;
        return;
    }
    for (const auto& ln : lines) {
        out << ln << "\n";
    }
    out.close();

}
void Game::saveToFileEquipment() {
    const std::string fileName = "Data/equipments.txt";

    
    std::ifstream in(fileName);
    if (!in.is_open()) {
       // std::cout << "Nie można otworzyć pliku do odczytu: " << fileName << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    in.close();

    std::string newLine = formatEquipmentLine(loggedInPlayer);

    bool replaced = false;
    const std::string prefix = "login: " + loggedInPlayer->getName() + " ";
    for (auto& ln : lines) {
        if (ln.rfind(prefix, 0) == 0) {
            ln = newLine;
            replaced = true;
            break;
        }
    }
    if (!replaced) {
        lines.push_back(newLine);
    }

    std::ofstream out(fileName, std::ios::trunc);
    if (!out.is_open()) {
       // std::cout << "Nie można otworzyć pliku do zapisu: " << fileName << std::endl;
        return;
    }
    for (const auto& ln : lines) {
        out << ln << "\n";
    }
    out.close();
}

Game::Game() {
    this->initVariables();
    this->initWindow();
    this->login_Screen = new LoginPage(*this);
    this->player_menu_screen = new PlayerMenu(*this);
    this->quest_menu_screen = new QuestPage(*this);
    this->quest_in_progress_screen = new QuestInProgressPage(*this);
    this->arena_screen = new ArenaPage(*this);
    this->fight_screen = new FightPage(*this);
    was_account_added = false;
    item_changed_flag = false;
}

Game::~Game() {
    if (loggedInPlayer) {
        saveToFileStats();
        saveToFileEquipment();
    }
    if (login_Screen != nullptr) {
        delete login_Screen;
    }
    if (player_menu_screen != nullptr) {
        delete player_menu_screen;
    }
    if (quest_menu_screen) {
        delete quest_menu_screen;
    }
    if (quest_in_progress_screen) {
        delete quest_in_progress_screen;
    }
    if (arena_screen) {
        delete arena_screen;
    }
    if (fight_screen) {
        delete fight_screen;
    }
    delete this->window;
}

sf::Vector2u Game::getWindowSize() const {
    return this->window->getSize();
}

bool Game::running() const {
    return this->window->isOpen();
}

void Game::changePage(GameState new_page) {
    this->page = new_page;
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->event)) {
        if (this->event.type == sf::Event::KeyPressed) {
            if (this->event.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
        }
        

        switch (this->page) { 
        case GameState::LOGIN_PAGE:
            this->login_Screen->handleEvents(this->event, *this->window);
            break;
        case GameState::PLAYER_MENU:
            this->player_menu_screen->handleEvents(this->event, *this->window); 
            break;
        case GameState::QUEST_PAGE:
            this->quest_menu_screen->handleEvents(this->event, *this->window);
            break;
        case GameState::MISSION_ACTIVE:
            this->quest_in_progress_screen->handleEvents(this->event, *this->window);
            break;
        case GameState::ARENA_PAGE:
            this->arena_screen->handleEvents(this->event, *this->window);
            break;
        case GameState::FIGHT_PAGE:
            this->fight_screen->handleEvents(this->event, *this->window);
            break;
        default:
            break;
        }
    }
}

void Game::update() {
    this->pollEvents();
}

void Game::render() {
    this->window->clear(sf::Color(25, 162, 210, 255));
    switch (this->page) {
    case GameState::LOGIN_PAGE:
        this->login_Screen->draw(*this->window);
        break;
    case GameState::PLAYER_MENU:
        this->player_menu_screen->draw(*this->window);
        break;
    case GameState::QUEST_PAGE:
        this->quest_menu_screen->draw(*this->window);
        break;
    case GameState::MISSION_ACTIVE:
        this->quest_in_progress_screen->draw(*this->window);
        break;
    case GameState::ARENA_PAGE:
        this->arena_screen->draw(*this->window);
        break;
    case GameState::FIGHT_PAGE:
        this->fight_screen->draw(*this->window);
        break;
    default:
        break;
    }

    this->window->display();
}

std::vector<Player*>& Game::getAvailableAccounts(){
    return available_accounts;
}


sf::RenderWindow& Game::getWindow(){
    return *window;
}

void Game::LogOut(){

    if (loggedInPlayer == nullptr) {
     //   std::cout << "Nie ma zalogowanego gracza!" << std::endl;
        
    }
    else {
        saveToFileStats();
        saveToFileEquipment();
        std::vector<std::string> equipmentSlots = {
            "helmet", "shield", "gloves", "shoes", "weapon", "necklace", "belt", "ring", "luckyitem",
            "slot1", "slot2", "slot3", "slot4", "slot5", "slot6", "slot7", "slot8"
        };

        for (const std::string& slot : equipmentSlots) {

            Item* item = loggedInPlayer->getItem(slot); 
            if (item != nullptr) {

                delete item;
           
            }

            loggedInPlayer->setItem(slot, nullptr);
        }
    }
    if (arena_screen) {
        arena_screen->clearEnemyDisplays(); 
    }

    setLoggedInPlayer(nullptr);
    changePage(GameState::LOGIN_PAGE);
}




void Game::setLoggedInPlayer(Player* player){
    this->loggedInPlayer = player;
    player_menu_screen->setLoggedInUser(player);
    quest_menu_screen->setLoggedInUser(player);
    quest_in_progress_screen->setLoggedInUser(player);
    arena_screen->setLoggedInUser(player);
    fight_screen->setLoggedInUser(player);
}

Player* Game::getLoggedInPlayer() const{
    return loggedInPlayer;
}

bool Game::getItemChangedFlag()const{
    return item_changed_flag;
}
bool Game::getFightActiveFlag()
{
    return fight_active_flag;
}
void Game::setFightActiveFlag(bool active)
{
    fight_active_flag = active;
}
bool Game::getStatChangedFlag()
{
    return stats_changed_flag;
}

void Game::setStatChangedFlag(bool changed) {
    stats_changed_flag = changed;
}
void Game::setItemChangedFlag(bool changed) {
    item_changed_flag = changed;
}


bool Game::validateFiles() {
    namespace fs = std::filesystem;

    std::vector<std::string> requiredFolders = { "Data", "Textures", "Fonts" };
    for (const auto& dir : requiredFolders) {
        if (!fs::exists(dir) || !fs::is_directory(dir)) {
            throw std::runtime_error("Brakuje folderu: " + dir);
        }
    }

    std::vector<std::string> requiredTxt = {
        "accounts", "equipments", "Items", "quests", "enemies"
    };

    std::vector<std::string> requiredTextures = {
        "aren_background.png", "Arena_button.png", "bialy-przyc.png", "buty.png", "customksztalt.png", "czapka.png",
        "exit_button.png", "fight_background.png","kusza.png", "login_button.png", "login_menu.jpg", "logout_button.png", 
        "naszyjnik.png","navbar_clear.png", "pas.png", "pierscien.png", "player_button.png", "player_menu_background.png",
        "player_menu_background2.png", "quest_menu_background.png", "quests_button.png", "rekawice.png", "shop_button.png",
        "shop_refresh_btn.png", "test.png", "test2.png", "upgrade_stat_button.png",
        "was.png", "wybor_postaci.png", "zbroja.png", "player_img1.png","player_img2.png","enemy_img1.png","enemy_img2.png",
        "enemy_img3.png","enemy_img4.png","enemy_img5.png","enemy_img6.png"
    };

    std::map<std::string, std::regex> regexPatterns = {
        {"accounts", std::regex(R"(login:\s*(\w+)\s+pass:\s*(\w+)\s+image:\s*(\S+)\s+strenght:\s*(\d+)\s+dexterity:\s*(\d+)\s+intelligence:\s*(\d+)\s+durability:\s*(\d+)\s+luck:\s*(\d+)\s+level:\s*(\d+)\s+gold:\s*(\d+)\s+xp:\s*(\d+))")},
        {"equipments", std::regex(R"(login:\s*(\w+)\s+helmet:\s*(\d+)\s+shield:\s*(\d+)\s+gloves:\s*(\d+)\s+shoes:\s*(\d+)\s+weapon:\s*(\d+)\s+necklace:\s*(\d+)\s+belt:\s*(\d+)\s+ring:\s*(\d+)\s+luckyitem:\s*(\d+)\s+slot1:\s*(\d+)\s+slot2:\s*(\d+)\s+slot3:\s*(\d+)\s+slot4:\s*(\d+)\s+slot5:\s*(\d+)\s+slot6:\s*(\d+)\s+slot7:\s*(\d+)\s+slot8:\s*(\d+)\s+shop1:\s*(\d+)\s+shop2:\s*(\d+)\s+shop3:\s*(\d+)\s+shop4:\s*(\d+)\s+shop5:\s*(\d+)\s+shop6:\s*(\d+))")},
        {"Items", std::regex(R"(id:\s*(\d+)\s+img:\s*([^\s]+)\s+name:\s*([^\s]+)\s+type:\s*([^\s]+)\s+strength:\s*(\d+)\s+dexterity:\s*(\d+)\s+intelligence:\s*(\d+)\s+durability:\s*(\d+)\s+luck:\s*(\d+)\s+armor:\s*(\d+))")},
        {"quests", std::regex(R"(login:\s*(\w+)\s+number:\s*(\d+)\s+name:\s*([^\s]+)\s+gold:\s*(\d+)\s+xp:\s*(\d+)\s+duration:\s*(\d+)\s+start:\s*(\d+))")},
        {"enemies", std::regex(R"(login:\s*(\w+)\s+number:\s*(\d+)\s+name:\s*([^\s]+)\s+level:\s*(\d+)\s+strength:\s*(\d+)\s+dexterity:\s*(\d+)\s+intelligence:\s*(\d+)\s+durability:\s*(\d+)\s+luck:\s*(\d+)\s+reward:\s*(\d+)\s+image:\s*([^\s]+))")}
    };

    std::map<std::string, fs::path> foundDataFiles;
    for (const auto& entry : fs::directory_iterator("Data")) {
        if (!entry.is_regular_file()) continue;
        std::string name = entry.path().stem().string(); 
        foundDataFiles[name] = entry.path();
    }

    for (const auto& required : requiredTxt) {
        if (foundDataFiles.find(required) == foundDataFiles.end()) {
            throw std::runtime_error("Brakuje pliku: Data/" + required);
        }
    }

    for (const auto& [name, path] : foundDataFiles) {
        auto it = regexPatterns.find(name);
        if (it == regexPatterns.end()) continue;

        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Nie mozna otworzyc pliku: " + path.string());
        }

        std::string line;
        int lineNumber = 0;
        while (std::getline(file, line)) {
            ++lineNumber;
            std::string trimmed = std::regex_replace(line, std::regex(R"(^\s+|\s+$)"), "");
            if (!trimmed.empty() && !std::regex_match(trimmed, it->second)) {
                throw std::runtime_error("Blad regex w pliku " + name + ", linia " + std::to_string(lineNumber) + ": " + trimmed);
            }
        }
    }

    for (const auto& tex : requiredTextures) {
        std::string texPath = "Textures/" + tex;
        if (!fs::exists(texPath)) {
            throw std::runtime_error("Brakuje tekstury: " + texPath);
        }
    }

    std::string fontPath = "Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf";
    if (!fs::exists(fontPath)) {
        throw std::runtime_error("Brakuje czcionki: " + fontPath);
    }

    return true;
}

