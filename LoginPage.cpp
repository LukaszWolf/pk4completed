#include "Page.h"
#include "Game.h"
#include <regex>
#include <iostream>

LoginPage::LoginPage(Game& game) : Page(game) {

    this->content_area = new ContentArea(1920, 1080, game, "Textures/wybor_postaci.png", 0, 0);
    this->username_text_box = new TextBox(1370, 320, 354, 90, "Login");
    this->password_text_box = new TextBox(1370, 450, 354, 90, "Haslo");
    password_text_box->setPasswordMode(true);
    this->login_button = new Button("LOGIN", { 1390, 580 }, { 314, 80 }, "Textures/login_button.png");
}

LoginPage::~LoginPage() {
    delete this->content_area;
    delete this->username_text_box;
    delete this->password_text_box;
    delete this->login_button;

    for (auto btn : account_btns) {
        if (btn != nullptr) {
            delete btn;
        }
    }
    
}

void LoginPage::draw(sf::RenderWindow& window) {
    if (this->content_area != nullptr)
        this->content_area->draw(window);

    if (this->username_text_box != nullptr)
        this->username_text_box->draw(window);

    if (this->password_text_box != nullptr)
        this->password_text_box->draw(window);

    if (this->login_button != nullptr)
        this->login_button->draw(window);

    for (const auto& player : insertion_order) {
        userToButtonMap[player]->draw(window);
    }
}

void LoginPage::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (this->content_area != nullptr)
        this->content_area->handleEvents(event, window);

    for (const auto& pair : userToButtonMap) {
        pair.second->handleEvents(mousePos, event);
        if (pair.second->isClicked(mousePos, event)) {
            LogIn(pair.first);
            break;
        }
    }

    if (this->login_button->isClicked(mousePos, event)) {
        std::string login = this->username_text_box->getText();
        std::string pass = this->password_text_box->getText();
        std::string line = userExistLine(login, "Data/accounts.txt");

        if (isValidLogin(login) and isPasswordMatched(pass, line)) {
            addAccountToAvailable(line, pass);
            username_text_box->clearText();
            password_text_box->clearText();
        }

    }

    if (this->username_text_box != nullptr)
        this->username_text_box->handleEvent(event);
    if (this->password_text_box != nullptr)
        this->password_text_box->handleEvent(event);

    login_button->handleEvents(mousePos, event);

}

std::string LoginPage::userExistLine(std::string nam, std::string file_name) {
    std::ifstream file(file_name);
    if (!file) {
       // std::cout << "Nie mozna otworzyc pliku: " << file_name << std::endl;
        return "";
    }
    std::string line;
    std::string to_find = "login: " + nam;
    while (std::getline(file, line)) {
        if (line.find(to_find) != std::string::npos) {
            return line;
        }
    }
    return "";
  //  std::cout << "nie udalo sie zalogowac";
}

bool LoginPage::isValidLogin(std::string login) {
    if (login.empty()) return false;
    for (char c : login) {
        if (!isalnum(c)) return false;
    }
    return true;
}

bool LoginPage::isValidPassword(std::string password) {
    return true;
}

bool LoginPage::isPasswordMatched(std::string password, std::string line) {
    std::string to_find = "pass: " + password;
    bool matched= isValidPassword(password) && line.find(to_find) != std::string::npos;
    if (matched) {
      
        return true;
    }
      return false;

}

void LoginPage::addAccountToAvailable(std::string stats, std::string password) {
    std::regex pattern(R"(login:\s*(\w+)\s+pass:\s*(\w+)\s+image:\s*(\S+)\s+strenght:\s*(\d+)\s+dexterity:\s*(\d+)\s+intelligence:\s*(\d+)\s+durability:\s*(\d+)\s+luck:\s*(\d+)\s+level:\s*(\d+)\s+gold:\s*(\d+)\s+xp:\s*(\d+))");
    std::smatch matches;

    if (!std::regex_search(stats, matches, pattern)) {
     //   std::cout << "blad regex";
        return;
    }
    std::string login = matches[1];
    std::string image = matches[3];
    int str = std::stoi(matches[4]);
    int dex = std::stoi(matches[5]);
    int intel = std::stoi(matches[6]);
    int con = std::stoi(matches[7]);
    int luck = std::stoi(matches[8]);
    int level = std::stoi(matches[9]);
    int gold = std::stoi(matches[10]);
    int xp = std::stoi(matches[11]);


    Player* new_player = new Player(login, image, str, dex, intel, con, luck, 
        level, gold,xp,game_ref);
    new_player->setPassword(password);
    insertion_order.push_front(new_player);

    
    if (insertion_order.size() > MAX_PLAYERS) {
        auto it = insertion_order.end();
        --it;
        Player* oldest = *it;
        insertion_order.erase(it);
        userToButtonMap.erase(oldest);
        delete oldest;
    }

    float basePosX = 250;
    float spacingX = 270;
    float basePosY = 280;
    float spacingY = 250;
    int i = 0;
    for (const auto& player : insertion_order) {
        int y = i / 3;
        int x = i % 3;
        sf::Vector2f pos{ basePosX + x * spacingX, basePosY + y * spacingY };

        if (userToButtonMap.find(player) == userToButtonMap.end()) {
            userToButtonMap[player] = std::make_unique<Button>(login, pos, sf::Vector2f{ 160,160 }, image);
        }
        else {
            userToButtonMap[player]->setPosition(pos);
        }
        ++i;
    }
}

void LoginPage::updateEquipment(std::string filename, Player* player) {
    player->updateEquipment(filename);
}

void LoginPage::LogIn(Player* player) {
    if(player){
        game_ref.setLoggedInPlayer(player);

        game_ref.changePage(GameState::PLAYER_MENU);
   
        player->updateEquipment("Data/equipments.txt");
        player->loadQuestsFromFile();

    }
}
