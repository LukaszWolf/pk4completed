#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include <iostream>
#include <vector>
#include "Quest.h"
#include "Enemy.h"
//enum class Mount {
//	COW,
//	HORSE,
//	TIGER,
//	DRAGON,
//	NONE
//};

class Game;

class Player : public Character
{
	std:: string password;

	int current_xp, xp_to_next_level;
	int gold;

	int armor, strength, dexterity, intelligence, durability, luck;
	bool stat_changed;	
	std::map<std::string, Item*> equipment;
	Quest* quest1;
	Quest* quest2;
	Quest* quest3;
	std::vector<Quest*> quests;
	std::vector<Enemy*> arena_enemies;
	Enemy* active_enemy;
	bool is_quest_in_progress;
	Game& game_ref;
	bool refresh_quests_flag;
	bool refresh_enemies_flag;
public:
	Player();
	Player(std::string nam, std::string img, int strength, int dexterity, int intelligence, int durability,int luck, 
		int level, int gold,int xp, Game&game); 
	~Player();

	void loadQuestsFromFile();
	void saveQuestsToFile();

	void saveArenaEnemiesToFile();

	void loadArenaEnemiesFromFile();

	void upgradeStrength();
	void upgradeDexterity();
	void upgradeIntelligence();
	void upgradeConstitution();
	void upgradeLuck();

	void initEquipment();

	float attack() override final ;
	int calculateHP() override final;
	int calculateDamage() override final;
	int calculateEvasion() override final;
	int calculateResistance() override final;
	int calculateDamageReduction() override final;
	double calculateCritChance() override final;

	virtual int getStrength() override final;
	virtual int getDexterity() override final;
	virtual int getIntelligence()override final;
	virtual int getConstitution() override final;
	virtual int getLuck() override final;
	virtual int getArmor() override final;

	void printEquipment();
	void printStats();
	Quest* getQuest(int num) const;
	Enemy* getArenaEnemy(int num) const;
	void setQuests(std::vector<Quest*>& newQuests); // opcjonalnie setter

	void setArenaEnemies(std::vector<Enemy*>& newEnemies);

	Item* getItem(const std::string& slot_name) const;
	void setItem(const std::string& slot_name, Item* item);
	int getGold() const;
	std::string getPassword() const;
	void setPassword(std::string pass);
	void setGold(int amount);

	void updateEquipment(std::string filename);
	void setQuestInProgress(bool active);
	bool getIsQuestInProgress();
	bool getRefreshQuestsFlag();
	void setRefreshQuestsflag(bool refresh);

	bool getRefreshEnemiesFlag();
	void setRefreshEnemiesflag(bool refresh);

	void setActiveEnemy(Enemy* enemy);
	Enemy* getActiveEnemy();

	int getXPToNextLevel();
	int getCurrentXP();
	void setCurrentXP(int amount);

};

#endif