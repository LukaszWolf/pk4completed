#ifndef PAGE_H
#define PAGE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>
#include "Button.h"
#include "TextBox.h"
#include "ContentArea.h"
#include "Player.h"
#include "GameState.h"
#include "Character.h"
#include "NavBar.h"
#include <iomanip>
#include "DescriptionBox.h"
#include"Quest.h"
#include "LoadingBar.h";
#include "Enemy.h"
#include "EnemyDisplay.h"
#include<random>
class Game;

class Page {
protected:
    Game& game_ref;

public:
    Page(Game& game) : game_ref(game) {}
    virtual ~Page() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvents(sf::Event event, sf::RenderWindow& window) = 0;
};


class LoginPage : public Page {
private:
    ContentArea* content_area;
    Button* login_button;
    TextBox* username_text_box;
    TextBox* password_text_box;
    

    std::vector<Button*> account_btns;
    std::list<Player*> insertion_order;
    std::unordered_map<Player*, std::unique_ptr<Button>> userToButtonMap;
    const size_t MAX_PLAYERS = 6;

    bool isValidLogin(std::string login);
    bool isValidPassword(std::string password);
    bool isPasswordMatched(std::string password, std::string line);

public:
    LoginPage(Game& game);
    ~LoginPage();

    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::Event event, sf::RenderWindow& window) override;

    std::string userExistLine(std::string name, std::string file_name);
    void addAccountToAvailable(std::string stats, std::string pass);
    void updateEquipment(std::string filename, Player* player);
    void LogIn(Player* player);
};

class PlayerMenu : public Page {
private:
    Player* loggedInUser;
    int test_counter;
    NavBar* navBar;
    ContentArea* player_managment_area;
    DescriptionBox* descriptionBox;
    XPLoadingBar* xp_bar;

    sf::Image* player_image = nullptr;
    ItemSlot* helmet_slot;
    ItemSlot* armor_slot;
    ItemSlot* gloves_slot;
    ItemSlot* shoes_slot;
    ItemSlot* weapon_slot;
    ItemSlot* necklace_slot;
    ItemSlot* belt_slot;
    ItemSlot* ring_slot;
    ItemSlot* lucky_item_slot;
    ItemSlot* bag_slot1;
    ItemSlot* bag_slot2;
    ItemSlot* bag_slot3;
    ItemSlot* bag_slot4;
    ItemSlot* bag_slot5;
    ItemSlot* bag_slot6;
    ItemSlot* bag_slot7;
    ItemSlot* bag_slot8;

    ItemSlot* shop_slot1;
    ItemSlot* shop_slot2;
    ItemSlot* shop_slot3;
    ItemSlot* shop_slot4;
    ItemSlot* shop_slot5;
    ItemSlot* shop_slot6;
    Button* refresh_shop_btn;
   
    std::vector<ItemSlot*> allSlots;
    ItemSlot* dragSource = nullptr;
    bool itemSwapped;

    Button* upgrade_strenght_btn;
    Button* upgrade_dexterity_btn;
    Button* upgrade_intelligence_btn;
    Button* upgrade_durability_btn;
    Button* upgrade_luck_btn;

    sf::Font textfont;
    sf::Text* strength_text;
    sf::Text* dexterity_text;
    sf::Text* intelligence_text;
    sf::Text* durability_text;
    sf::Text* luck_text;
    sf::Text* armor_text;

    sf::Text* strenght_related_text;
    sf::Text* dexterity_related_text;
    sf::Text* intelligence_related_text;
    sf::Text* durability_related_text;
    sf::Text* luck_related_text;
    sf::Text* armor_related_text;

    sf::Text* gold_text;
    sf::Text* level_text;

    sf::RectangleShape* img_shape;

public:
    PlayerMenu(Game& game);
    ~PlayerMenu();

    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::Event event, sf::RenderWindow& window) override;
    void updateSlots();
    void updateTextStats();
    void setLoggedInUser(Player* player);
    void assignRandomStats(int& strength, int& dexterity, int& intelligence, int& durability, int& luck, int& armor);
    void refreshShop();
};

class QuestPage: public Page{
private:
    Player* loggedInUser;
    NavBar* navBar;
    ContentArea* content_area;

    Button* activate_quest1_btn;
    Button* activate_quest2_btn;
    Button* activate_quest3_btn;
    
  //  std::vector<Quest*>quests;
public:
    QuestPage(Game& game);
    ~QuestPage();
    void setLoggedInUser(Player* player);
    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::Event event, sf::RenderWindow& window) override;
    void activateMission(int quest_num);
    void refreshQuestsForPlayer();
    //Quest* getQuest(int num);

};

class QuestInProgressPage: public Page{
private:
    Player* loggedInUser;
    NavBar* navBar;
    ContentArea* content_area;
    Quest* active_quest;
    sf::Text time_left_text;
    sf::Font font;
    TimeLoadingBar* time_bar;
    Button* cancel_quest_btn;
    Button* skip_quest_btn;
public:
    QuestInProgressPage(Game& game);
    ~QuestInProgressPage();
    void setActiveQuest(Quest* quest);
    void setLoggedInUser(Player* player);
    void cancelQuest();
    void skipQuest();
    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::Event event, sf::RenderWindow& window) override;

};


class ArenaPage : public Page {
private:
    Player* loggedInUser;                    // currently logged‐in player
    NavBar* navBar;                          // left‐side navigation bar
    ContentArea* content_area;               // main content background
    Button* fight_button1;                   // button to fight enemies[0]
    Button* fight_button2;                   // button to fight enemies[1]
    Button* fight_button3;                   // button to fight enemies[2]

    sf::Font font;                           // font (if needed for extra text)
    std::vector<Enemy*> enemies;             // raw Enemy* loaded from Player
    std::vector<EnemyDisplay*> enemyDisplays; // GUI objects for each Enemy*

    // Helper to delete all existing EnemyDisplay* and clear the vector
    

public:
    ArenaPage(Game& game);
    ~ArenaPage();

    // Called by Game::setLoggedInPlayer(...) so that, when a new Player logs in,
    // ArenaPage knows which enemies to pull and display.
    void setLoggedInUser(Player* player);

    // Renders navBar, content_area, then every EnemyDisplay, then fight buttons.
    void draw(sf::RenderWindow& window) override;

    // Handles input: NavBar clicks, content_area clicks, plus fight_button clicks.
    void handleEvents(sf::Event event, sf::RenderWindow& window) override;

    
    // Called when a “fight” button is clicked; implement your fight logic here.
    void startFight(Enemy* enemy);

    // Return the i‐th Enemy* (or nullptr if out of range)
    Enemy* getEnemy(int num);

    void refreshEnemies(bool generate_new_enemies);
    void clearEnemyDisplays();
    // If you want to remove all old EnemyDisplay objects manually, call this.
    // (clearEnemyDisplays() is private; this is the public interface.)
    // You can use it anywhere—e.g., before calling createEnemyDisplays().
    //void clearEnemyDisplays(); // Already declared as private
};
class FightPage : public Page {
private:
    Player* loggedInUser;
    Enemy* enemy;
    ContentArea* content_area;
    sf::RectangleShape player_img;
    sf::RectangleShape enemy_img;
    HPBar* player_hp_bar;
    HPBar* enemy_hp_bar;
    sf::Texture player_img_texture;
    sf::Texture enemy_img_texture;
    sf::Font font;
    float enemy_current_hp;
    float player_current_hp;
    float enemy_max_hp;
    float player_max_hp;
    sf::Text player_hp_text;
    sf::Text enemy_hp_text;
    // nowe pola logiki walki
    bool fight_initialized = false;
    bool playerTurn = true;
    bool enemyTurnScheduled = false;
    std::chrono::steady_clock::time_point enemyTurnTime;

public:
    FightPage(Game& game);
    ~FightPage();

    void draw(sf::RenderWindow& window) override;
    void handleEvents(sf::Event event, sf::RenderWindow& window) override;

    void setEnemy(Enemy* enemy);
    Enemy* getEnemy();
    void setLoggedInUser(Player* player);
    void setPlayerAndEnemyImg();
    void initFight();
    void Fight(sf::RenderWindow& window);
    Player* getLoggedInUser();
};


#endif
