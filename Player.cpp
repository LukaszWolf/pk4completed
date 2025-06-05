#include "Player.h"
#include "Game.h"
#include <cmath> 

Player::Player(std::string nam, std::string img, int str, int dex, int intel, int con, int lck,  int lvl,
 int gld,int xp,  Game&game):
Character(nam, img,str,dex,intel,con,lck,lvl),
gold(gld),current_xp(xp), game_ref(game) {
    initEquipment();
	loadQuestsFromFile();
	character_img.loadFromFile(img);
	refresh_quests_flag = false;
	refresh_enemies_flag = false;
	xp_to_next_level = getXPToNextLevel();
}

Player::~Player() {
	delete this->quest1;
	delete this->quest2;
	delete this->quest3;
}

void Player::upgradeStrength()
{
	this->base_strength++;
	int cost = this->level;
	this->setGold(gold-1);
	game_ref.saveToFileStats();
}

void Player::upgradeDexterity()
{
	this->base_dexterity++;
	int cost = this->level;
	this->setGold(gold - 1);
	game_ref.saveToFileStats();
}
void Player::upgradeIntelligence()
{
	this->base_intelligence++;
	int cost = this->level;
	this->setGold(gold - 1);
	game_ref.saveToFileStats();
}
void Player::upgradeDurability()
{
	this->base_durability++;
	int cost = this->level;
	this->setGold(gold - 1);
	game_ref.saveToFileStats();
}
void Player::upgradeLuck()
{
	this->base_luck++;
	int cost = this->level;
	this->setGold(gold - 1);
	game_ref.saveToFileStats();
	
}

float Player::attack() {
	static std::mt19937 rng{ std::random_device{}() };
	static std::uniform_real_distribution<float> damage_multiplier(0.8f, 1.2f);
	float damage = static_cast<float>(calculateDamage());
	return damage * damage_multiplier(rng);
}

int Player::calculateHP() {
	return getDurability()*level;
}

int Player::calculateDamage() {
	return getStrength()*level;
}

int Player::calculateEvasion() {
	return getDexterity()*level;
}

int Player::calculateResistance() {
	return getArmor()*level*0.1;
}

int Player::calculateDamageReduction() {
	return std::floor(getIntelligence()*level/50);
}

double Player::calculateCritChance() {
	return std::min(50,(getLuck()*0,05));
}



void Player::initEquipment()
{
    this->equipment  = {
            {"helmet", nullptr},
            {"shield", nullptr},
            {"gloves", nullptr},
            {"shoes", nullptr},
            {"weapon", nullptr},
            {"necklace", nullptr},
            {"belt", nullptr},
            {"ring", nullptr},
            {"luckyitem", nullptr},
            {"slot1", nullptr},
            {"slot2", nullptr},
            {"slot3", nullptr},
            {"slot4", nullptr},
            {"slot5", nullptr},
            {"slot6", nullptr},
            {"slot7", nullptr},
            {"slot8", nullptr},
			{"shop1", nullptr},
			{"shop2", nullptr},
			{"shop3", nullptr},
			{"shop4", nullptr},
			{"shop5", nullptr},
			{"shop6", nullptr},

    };
}

Quest* Player::getQuest(int num) const {
	try {
		
		return quests[num];
	}
	catch (const std::out_of_range e) {
		std::cout << "quests vector:" << e.what();
	}
}
Enemy* Player::getArenaEnemy(int num) const
{
	try {

		return arena_enemies[num];
	}
	catch (const std::out_of_range e) {
		std::cout << "arena enemies vector:" << e.what();
	}
}
void Player::setQuests(std::vector<Quest*>& newQuests) {
	try
	{
		for (auto q : quests) {
			delete q;
		}
		quests.clear();

		for (auto q : newQuests) {
			quests.push_back(q);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Wyjatek podczas kopiowania questoww: " << e.what() << std::endl;
	}

}

void Player::setArenaEnemies(std::vector<Enemy*>& newEnemies) {
	try {
		arena_enemies.clear();
		for (auto enemy : newEnemies) {
			arena_enemies.push_back(enemy);
		}
	}
	catch (const std::exception& e) {
		std::cout << "Wyjatek podczas kopiowania przeciwnikow: " << e.what() << std::endl;
	}

}



void Player::loadQuestsFromFile() {
	is_quest_in_progress = false;
	int i = 1;
	std::ifstream file("Data/quests.txt");
	if (!file.is_open()) {
		//std::cout << "Nie można otworzyć pliku quests.txt\n";
		return;
	}

	std::string line;
	std::regex pattern(R"(login:\s*(\w+)\s+number:\s*(\d+)\s+name:\s*([^\s]+)\s+gold:\s*(\d+)\s+xp:\s*(\d+)\s+duration:\s*(\d+)\s+start:\s*(\d+))");

	std::smatch match;

	quests.clear();
	while (std::getline(file, line)) {
		if (std::regex_match(line, match, pattern) && match[1] == this->getName()) {
			std::string quest_name = match[3];
			int reward_gold = std::stoi(match[4]);
			int reward_xp = std::stoi(match[5]);
			int duration = std::stoi(match[6]);
			long long start = std::stoll(match[7]);

			float posX = 440 + i * 300;
			float posY = 330;
			Quest* q = new Quest(quest_name, "desc", duration, reward_gold,reward_xp, {posX,posY});
			i++;
			std::cout << q->getName() << std:: endl;
			if (start > 0) {
				q->setStartTime(std::chrono::system_clock::time_point(std::chrono::seconds(start)));
				q->setDuration(std::chrono::seconds(duration));
				is_quest_in_progress = true;
				q->setActive(true);
			}

			quests.push_back(q);
			
		}

	}

}

void Player::saveQuestsToFile() {
	std::ifstream file_in("Data/quests.txt");
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file_in, line)) {
		if (line.find("login: " + this->getName()) != 0) {
			lines.push_back(line);
		}
	}
	file_in.close();

	std::ofstream file_out("Data/quests.txt", std::ios::trunc);
	for (const auto& l : lines) {
		file_out << l << "\n";
	}

	for (size_t i = 0; i < quests.size(); ++i) {
		auto q = quests[i];
		auto start = std::chrono::duration_cast<std::chrono::seconds>(
			q->getStartTime().time_since_epoch()).count();
		int duration = q->getDurationSeconds();

		file_out << "login: " << this->getName()
			<< " number: " << (i + 1)
			<< " name: " << q->getName()
			<< " gold: " << q->getRewardGold()
			<< " xp: " << q->getRewardXP()
			<< " duration: " << duration
			<< " start: " << start << "\n";
	}
	file_out.close();
}


void Player::saveArenaEnemiesToFile() {
	std::ifstream file_in("Data/enemies.txt");
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(file_in, line)) {
		if (line.find("login: " + this->getName()) != 0) {
			lines.push_back(line);
		}
	}
	file_in.close();

	std::ofstream file_out("Data/enemies.txt", std::ios::trunc);
	for (const auto& l : lines) {
		file_out << l << "\n";
	}

	for (size_t i = 0; i < arena_enemies.size(); ++i) {
		Enemy* e = arena_enemies[i];
		file_out << "login: " << this->getName()
			<< " number: " << (i + 1)
			<< " name: " << e->getName()
			<< " level: " << e->getLevel()
			<< " strength: " << e->getStrength()
			<< " dexterity: " << e->getDexterity()
			<< " intelligence: " << e->getIntelligence()
			<< " durability: " << e->getDurability()
			<< " luck: " << e->getLuck()
			<< " reward: " << e->getRewardGold()
			<< " image: " << e->getImgName()
			<< "\n";
	}

	file_out.close();
}


void Player::loadArenaEnemiesFromFile() {
	std::ifstream file("Data/enemies.txt");
	if (!file.is_open()) {
		std::cerr << "Nie można otworzyć enemies.txt\n";
		return;
	}

	std::string line;
	std::regex pattern(R"(login:\s*(\w+)\s+number:\s*(\d+)\s+name:\s*([^\s]+)\s+level:\s*(\d+)\s+strength:\s*(\d+)\s+dexterity:\s*(\d+)\s+intelligence:\s*(\d+)\s+durability:\s*(\d+)\s+luck:\s*(\d+)\s+reward:\s*(\d+)\s+image:\s*([^\s]+))");
	std::smatch match;

	if (arena_enemies.size() > 0) {
		arena_enemies.clear();
	}

	int i = 0;
	while (std::getline(file, line)) {
		if (std::regex_match(line, match, pattern) && match[1] == this->getName()) {
			std::cout << "znaleziono" << std::endl;
			std::string name = match[3];
			int level = std::stoi(match[4]);
			int strength = std::stoi(match[5]);
			int dexterity = std::stoi(match[6]);
			int intelligence = std::stoi(match[7]);
			int durability = std::stoi(match[8]);
			int luck = std::stoi(match[9]);
			int reward = std::stoi(match[10]);
			std::string image = match[11];

			Enemy* enemy = new Enemy(
				name, image,
				strength, dexterity, intelligence, durability, luck, level, reward);
			enemy->getCharacterTexture().loadFromFile(image);
			arena_enemies.push_back(enemy);
			i++;
		}
		
	}

	file.close();
}


Item* Player::getItem(const std::string& slot_name) const {
    auto it = equipment.find(slot_name);
    if (it != equipment.end()) {
        return it->second;
    }
    return nullptr;
}

void Player::setItem(const std::string& slot_name, Item* item) {
    auto it = equipment.find(slot_name);
    if (it != equipment.end()) {
		it->second = item;
    }
	
	if(!game_ref.getItemChangedFlag())
	this->game_ref.setItemChangedFlag(true);
}


void Player::updateEquipment(std::string filename)
{
	std::ifstream file(filename);
	if (!file) {
	//	std::cout << "nie udalo sie otworzyc pliku";
		return;
	}
	std::string line;
	bool found = false;

	const std::regex pattern(R"(^login:\s*(\w+)\s+helmet:\s*(\d+)\s+shield:\s*(\d+)\s+gloves:\s*(\d+)\s+shoes:\s*(\d+)\s+weapon:\s*(\d+)\s+necklace:\s*(\d+)\s+belt:\s*(\d+)\s+ring:\s*(\d+)\s+luckyitem:\s*(\d+)\s+slot1:\s*(\d+)\s+slot2:\s*(\d+)\s+slot3:\s*(\d+)\s+slot4:\s*(\d+)\s+slot5:\s*(\d+)\s+slot6:\s*(\d+)\s+slot7:\s*(\d+)\s+slot8:\s*(\d+)\s+shop1:\s*(\d+)\s+shop2:\s*(\d+)\s+shop3:\s*(\d+)\s+shop4:\s*(\d+)\s+shop5:\s*(\d+)\s+shop6:\s*(\d+)\s*$)");


	while (std::getline(file, line) and !found) {
		std::smatch match;
		if (std::regex_match(line, match, pattern)) {
			if ((std::string(match[1]) == this->getName())) {
				
				Item* helmet = (std::stoi(match[2]) != 0) ? new Item(std::stoi(match[2])) : nullptr;
				Item* shield = (std::stoi(match[3]) != 0) ? new Item(std::stoi(match[3])) : nullptr;
				Item* gloves = (std::stoi(match[4]) != 0) ? new Item(std::stoi(match[4])) : nullptr;
				Item* shoes = (std::stoi(match[5]) != 0) ? new Item(std::stoi(match[5])) : nullptr;
				Item* weapon = (std::stoi(match[6]) != 0) ? new Item(std::stoi(match[6])) : nullptr;
				Item* necklace = (std::stoi(match[7]) != 0) ? new Item(std::stoi(match[7])) : nullptr;
				Item* belt = (std::stoi(match[8]) != 0) ? new Item(std::stoi(match[8])) : nullptr;
				Item* ring = (std::stoi(match[9]) != 0) ? new Item(std::stoi(match[9])) : nullptr;
				Item* luckyitem = (std::stoi(match[10]) != 0) ? new Item(std::stoi(match[10])) : nullptr;

				Item* slot1 = (std::stoi(match[11]) != 0) ? new Item(std::stoi(match[11])) : nullptr;
				Item* slot2 = (std::stoi(match[12]) != 0) ? new Item(std::stoi(match[12])) : nullptr;
				Item* slot3 = (std::stoi(match[13]) != 0) ? new Item(std::stoi(match[13])) : nullptr;
				Item* slot4 = (std::stoi(match[14]) != 0) ? new Item(std::stoi(match[14])) : nullptr;
				Item* slot5 = (std::stoi(match[15]) != 0) ? new Item(std::stoi(match[15])) : nullptr;
				Item* slot6 = (std::stoi(match[16]) != 0) ? new Item(std::stoi(match[16])) : nullptr;
				Item* slot7 = (std::stoi(match[17]) != 0) ? new Item(std::stoi(match[17])) : nullptr;
				Item* slot8 = (std::stoi(match[18]) != 0) ? new Item(std::stoi(match[18])) : nullptr;

				Item* shop1 = (std::stoi(match[19]) != 0) ? new Item(std::stoi(match[19])) : nullptr;
				Item* shop2 = (std::stoi(match[20]) != 0) ? new Item(std::stoi(match[20])) : nullptr;
				Item* shop3 = (std::stoi(match[21]) != 0) ? new Item(std::stoi(match[21])) : nullptr;
				Item* shop4 = (std::stoi(match[22]) != 0) ? new Item(std::stoi(match[22])) : nullptr;
				Item* shop5 = (std::stoi(match[23]) != 0) ? new Item(std::stoi(match[23])) : nullptr;
				Item* shop6 = (std::stoi(match[24]) != 0) ? new Item(std::stoi(match[24])) : nullptr;

				this->setItem("helmet", helmet);
				this->setItem("shield", shield);
				this->setItem("gloves", gloves);
				this->setItem("shoes", shoes);
				this->setItem("weapon", weapon);
				this->setItem("necklace", necklace);
				this->setItem("belt", belt);
				this->setItem("ring", ring);
				this->setItem("luckyitem", luckyitem);
				
				this->setItem("slot1", slot1);
				this->setItem("slot2", slot2);
				this->setItem("slot3", slot3);
				this->setItem("slot4", slot4);
				this->setItem("slot5", slot5);
				this->setItem("slot6", slot6);
				this->setItem("slot7", slot7);
				this->setItem("slot8", slot8);

				this->setItem("shop1", shop1);
				this->setItem("shop2", shop2);
				this->setItem("shop3", shop3);
				this->setItem("shop4", shop4);
				this->setItem("shop5", shop5);
				this->setItem("shop6", shop6);
				found = true;
			};
		}
		
	}
	if (!found) {
	//	std::cout << "nie udalo sie wczytac ekwipunku";
	}
}
void Player::setQuestInProgress(bool active){
	is_quest_in_progress = active;
}

bool Player::getIsQuestInProgress(){
	return is_quest_in_progress;
}

bool Player::getRefreshQuestsFlag()
{
	return refresh_quests_flag;
}

bool Player::getRefreshEnemiesFlag()
{
	return refresh_enemies_flag;
}

void Player::setRefreshEnemiesflag(bool refresh)
{
	refresh_enemies_flag = refresh;
}

void Player::setActiveEnemy(Enemy* enemy)
{
	active_enemy = enemy;
}
Enemy* Player::getActiveEnemy() {
	return active_enemy;
}

int Player::getXPToNextLevel()
{
	return 450 + (level * 50);
}

int Player::getCurrentXP()
{
	return current_xp;
}

void Player::setCurrentXP(int amount)
{
	if (amount < xp_to_next_level) {
		this->current_xp = amount;
	}
	else {
		current_xp = amount - xp_to_next_level; 
		level++;
	}

}

void Player::setRefreshQuestsflag(bool refresh)
{
	refresh_quests_flag = refresh;
}

void Player::printStats()
{
	std::cout << "str: " << getStrength() << ", dex: " << getDexterity() << ", int:" << getIntelligence() << ", con:" << getDurability() << ", lck:" << getLuck() << std::endl;
}

void Player::setGold(int amount)
{
	this->gold = amount;
	game_ref.setStatChangedFlag(true);
}

int Player::getStrength()
{
	int total = base_strength;
	std::vector<std::string> slots = { "helmet","shield","gloves","shoes","weapon","necklace","belt","ring","luckyitem" };
	for (const auto& slot : slots) {
		auto it = equipment.find(slot);
		if (it != equipment.end() and it->second)
			total += it->second->getStrenght();
	}
	return total;
}

int Player::getDexterity()
{
	int total = base_dexterity;
	std::vector<std::string> slots = { "helmet","shield","gloves","shoes","weapon","necklace","belt","ring","luckyitem" };
	for (const auto& slot : slots) {
		auto it = equipment.find(slot);
		if (it != equipment.end() and it->second)
			total += it->second->getDexterity();
	}
	return total;
}

int Player::getIntelligence()
{
	int total = base_intelligence;
	std::vector<std::string> slots = { "helmet","shield","gloves","shoes","weapon","necklace","belt","ring","luckyitem" };
	for (const auto& slot : slots) {
		auto it = equipment.find(slot);
		if (it != equipment.end() and it->second)
			total += it->second->getIntelligence();
	}
	return total;
}

int Player::getDurability()
{
	int total = base_durability;
	std::vector<std::string> slots = { "helmet","shield","gloves","shoes","weapon","necklace","belt","ring","luckyitem" };
	for (const auto& slot : slots) {
		auto it = equipment.find(slot);
		if (it != equipment.end() and it->second)
			total += it->second->getConstitution();
	}
	return total;
}

int Player::getLuck()
{
	int total = base_luck;
	std::vector<std::string> slots = { "helmet","shield","gloves","shoes","weapon","necklace","belt","ring","luckyitem" };
	for (const auto& slot : slots) {
		auto it = equipment.find(slot);
		if (it != equipment.end() and it->second)
			total += it->second->getLuck();
	}
	return total;
}

int Player::getArmor() { 
	int total = 0;
	std::vector<std::string> slots = { "helmet","shield","gloves","shoes","weapon","necklace","belt","ring","luckyitem" };
	for (const auto& slot : slots) {
		auto it = equipment.find(slot);
		if (it != equipment.end() and it->second)
			total += it->second->getArmor();
	}
	return total;
}

int Player::getGold() const{
	return gold;
}
std::string Player::getPassword() const{
	return password;
}
void Player::setPassword(std::string pass){
	password = pass;
}


