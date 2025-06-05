#include "Item.h"

Item::Item(int item_id) : id(0), strength(0), dexterity(0), intelligence(0), durability(0), luck(0), armor(0),price(100)
, type(ItemType::ANY) {

    std::ifstream file("Data/Items.txt");
    if (!file.is_open()) {
     //   std::cout << "Nie mozna otworzyc pliku items.txt" << std::endl;
        return;
    }

    std::string line;
    std::regex pattern(
        "id:\\s*" + std::to_string(item_id) +
        R"(.*?img:\s*([^\s]+)\s+)"
        R"(name:\s*([^\s]+)\s+)" 
        R"(type:\s*([^\s]+)\s+)"
        R"(strength:\s*(\d+)\s+)" 
        R"(dexterity:\s*(\d+)\s+)" 
        R"(intelligence:\s*(\d+)\s+)" 
        R"(durability:\s*(\d+)\s+)"
        R"(luck:\s*(\d+)\s+)"
        R"(armor:\s*(\d+))"  
    );

    std::smatch match;
    bool found = false;

    while (std::getline(file, line)) {
        if (std::regex_search(line, match, pattern)) {
            this->id = item_id;

            std::string imagePath =match[1];
            if (!this->texture.loadFromFile(imagePath)) {
               // std::cout << "Nie udalo sie wczytac textury: " << imagePath << std::endl;
            }
            else {
                this->sprite.setTexture(this->texture);
            }
            this->name = match[2];
            std::string typeStr = match[3];
            if (typeStr == "WEAPON")     this->type = ItemType::WEAPON;
            else if (typeStr == "ARMOR")      this->type = ItemType::ARMOR;
            else if (typeStr == "HELMET")     this->type = ItemType::HELMET;
            else if (typeStr == "GLOVES")     this->type = ItemType::GLOVES;
            else if (typeStr == "SHOES")      this->type = ItemType::SHOES;
            else if (typeStr == "RING")       this->type = ItemType::RING;
            else if (typeStr == "NECKLACE")   this->type = ItemType::NECKLACE;
            else if (typeStr == "BELT")       this->type = ItemType::BELT;
            else if (typeStr == "LUCKY_ITEM") this->type = ItemType::LUCKY_ITEM;
            else                                 this->type = ItemType::ANY;

            this->strength = std::stoi(match[4]);
            this->dexterity = std::stoi(match[5]);
            this->intelligence = std::stoi(match[6]);
            this->durability = std::stoi(match[7]);
            this->luck = std::stoi(match[8]);
            this->armor = std::stoi(match[9]);
            found = true;
            break;
        }
    }
    file.close();

    if (!found) {
        std::cerr << "Nie znaleziono itemu o id: " << item_id << std::endl;
    }
}
Item::Item(int id,const std::string& texturePath,const std::string& name,ItemType type,int strength,
    int dexterity,int intelligence,int durability,int luck,int armor,int price = 100): id(id),
    name(name),type(type),strength(strength),dexterity(dexterity),intelligence(intelligence),durability(durability),
    luck(luck),armor(armor),price(price){
    if (!this->texture.loadFromFile(texturePath)) {
     //   std::cout << "Nie udalo sie wczytac textury: " << texturePath << std::endl;
    }
    else {
        this->sprite.setTexture(this->texture);
    }
    this->sprite.setScale(2.f, 2.f);

    std::ofstream out("Data/Items.txt", std::ios::app);
    if (out.is_open()) {
        out
            << "id: " << id
            << " img: " << texturePath
            << " name: " << name
            << " type: " << ItemTypeToString(type)
            << " strength: " << strength
            << " dexterity: " << dexterity
            << " intelligence: " << intelligence
            << " durability: " << durability
            << " luck: " << luck
            << " armor: " << armor
            << "\n";
    }
   // else {
    //    std::cout << "Nie mozna otworzyc pliku Items.txt do dopisania\n";
    //}
}
std::string Item::ItemTypeToString(ItemType t) {
    switch (t) {
    case ItemType::WEAPON:     
        return "WEAPON";
    case ItemType::ARMOR:      
        return "ARMOR";
    case ItemType::HELMET:     
        return "HELMET";
    case ItemType::GLOVES:     
        return "GLOVES";
    case ItemType::SHOES:      
        return "SHOES";
    case ItemType::RING:       
        return "RING";
    case ItemType::NECKLACE:   
        return "NECKLACE";
    case ItemType::BELT:       
        return "BELT";
    case ItemType::LUCKY_ITEM: 
        return "LUCKY_ITEM";
    case ItemType::ANY:
        return "ANY";
    }
    return "ANY";
}

void Item::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

sf::FloatRect Item::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

int Item::getId() const{
    return this->id;
}

ItemType Item::getType() const {
    return type;
}
sf::Texture& Item::getTexture() {
    return texture;
}
int Item::getStrenght() const{
    return strength;
}
int Item::getDexterity() const{
    return dexterity;
}
int Item::getIntelligence() const{
    return intelligence;
}
int Item::getConstitution() const{
    return durability;
}
int Item::getLuck() const{
    return luck;
}
int Item::getArmor() const {
    return armor;
}
std::string Item::getName() const{
    return name;
}
sf::Sprite& Item::getSprite() {
    return sprite;
}

std::vector < std::string>Item::getDescriptionStrings() {
    std::vector < std::string> v;
    if (this->getStrenght() != 0) {
        v.push_back("Strenght: " + std::to_string(this->getStrenght()));
    }
    if (this->getDexterity() != 0) {
        v.push_back("Dexterity: " + std::to_string(this->getDexterity()));
    }
    if (this->getIntelligence() != 0) {
        v.push_back("Intelligence: " + std::to_string(this->getIntelligence()));
    }
    if (this->getConstitution() != 0) {
        v.push_back("Durability: " + std::to_string(this->getConstitution()));
    }
    if (this->getLuck() != 0) {
        v.push_back("Luck: " + std::to_string(this->getLuck()));
    }
    if (this->getArmor() != 0) {
        v.push_back("Armor: " + std::to_string(this->getArmor()));
    }
    return v;
}

int Item::getPrice() const{
    return price;
}
