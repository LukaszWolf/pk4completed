
#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "Page.h"
#include "Player.h"
#include "filesystem"
class Game {
private:
    sf::RenderWindow* window;
    sf::Event event;
    sf::VideoMode video_mode;
    sf::Vector2u windowSize;
    GameState page;
    LoginPage* login_Screen;
    PlayerMenu* player_menu_screen;
    QuestPage* quest_menu_screen;
    ArenaPage* arena_screen;
    FightPage* fight_screen;
    QuestInProgressPage* quest_in_progress_screen;
    std::vector<Player*> available_accounts; 
    Player* loggedInPlayer;
    bool was_account_added;
    bool item_changed_flag;
    bool stats_changed_flag;
    bool fight_active_flag;

 

    void initVariables();
    void initWindow();
public:
    Game();
    ~Game();
    sf::Vector2u getWindowSize() const;
    bool running() const;
    void changePage(GameState new_page);
    void pollEvents();
    void update();
    void render();
    void LogOut();
    void saveToFileStats();
    void saveToFileEquipment();
    std::vector<Player*>& getAvailableAccounts();
    void setLoggedInPlayer(Player* player);
    Player* getLoggedInPlayer() const;
    bool getItemChangedFlag() const;
    void setItemChangedFlag(bool changed);
    sf::RenderWindow& getWindow();
    
    std::string formatPlayerLine(Player* p);
    std::string formatEquipmentLine(Player* p);

    bool getFightActiveFlag();
    void setFightActiveFlag(bool active);

    bool getStatChangedFlag();
    void setStatChangedFlag(bool changed);

    bool validateFiles();
};

#endif // GAME_H