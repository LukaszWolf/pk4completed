#include "Page.h"
#include "Game.h"
#include <SFML/Graphics.hpp>



PlayerMenu::PlayerMenu(Game& game) : Page(game) {

    dragSource = nullptr;
    this->loggedInUser = game_ref.getLoggedInPlayer();
  
    this->navBar = new NavBar(400, 1080, game);
    this->player_managment_area = new ContentArea(1520, 1080, game, "Textures/player_menu_background2.png", 400, 0);
    this->xp_bar = new XPLoadingBar(600.f, 432.f, 365.f, 33.f, sf::Color::Blue);  

    this->helmet_slot = new ItemSlot("helmet",{ 439, 47 }, {129,129}, ItemType::HELMET, "Textures/test.png", []() {}, nullptr);
    this->armor_slot = new ItemSlot("shield",{ 439, 197 }, {129,129}, ItemType::ARMOR, "Textures/test.png", []() {}, nullptr);
    this->gloves_slot = new ItemSlot("gloves",{ 439, 348 }, {129,129}, ItemType::GLOVES, "Textures/test.png", []() {}, nullptr);
    this->shoes_slot = new ItemSlot("shoes",{ 439, 499 }, {129,129}, ItemType::SHOES, "Textures/test.png", []() {}, nullptr);
    this->weapon_slot = new ItemSlot("weapon",{ 721, 500 }, {129,129}, ItemType::WEAPON, "Textures/test.png", []() {}, nullptr);
    this->necklace_slot = new ItemSlot("necklace",{ 1004, 47 }, {129,129}, ItemType::NECKLACE, "Textures/test.png", []() {}, nullptr);
    this->belt_slot = new ItemSlot("belt", {1004, 198}, {129,129}, ItemType::BELT, "Textures/test.png", []() {}, nullptr);
    this->ring_slot = new ItemSlot("ring",{ 1004, 349 }, {129,129}, ItemType::RING, "Textures/test.png", []() {}, nullptr);
    this->lucky_item_slot = new ItemSlot("luckyitem",{ 1004, 500 }, {129,129}, ItemType::LUCKY_ITEM, "Textures/test.png", []() {}, nullptr);

    this->bag_slot1 = new ItemSlot("slot1",{ 1251, 34 }, {129,129}, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot2 = new ItemSlot("slot2", { 1400,34 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot3 = new ItemSlot("slot3", { 1545,34 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot4 = new ItemSlot("slot4", { 1693,34 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot5= new ItemSlot("slot5", { 1251,177 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot6 = new ItemSlot("slot6", { 1400,177 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot7 = new ItemSlot("slot7", { 1545,177 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->bag_slot8 = new ItemSlot("slot8", { 1693,177 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);

    this->shop_slot1 = new ItemSlot("shop1", { 1250, 682 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->shop_slot2 = new ItemSlot("shop2", { 1250, 824 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->shop_slot3 = new ItemSlot("shop3", { 1397, 824 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->shop_slot4 = new ItemSlot("shop4", { 1543, 824 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->shop_slot5 = new ItemSlot("shop5", { 1691, 824 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);
    this->shop_slot6 = new ItemSlot("shop6", { 1691, 682 }, { 129,129 }, ItemType::ANY, "Textures/test.png", []() {}, nullptr);

    this->refresh_shop_btn = new Button({ 1408, 690 }, { 260, 80 }, "Textures/shop_refresh_btn.png", [this]() {refreshShop(); });

    this->upgrade_strenght_btn = new Button({ 720, 703 }, { 0, 0 }, "Textures/upgrade_stat_button.png", []() {});
    this->upgrade_dexterity_btn = new Button({ 720, 796 }, { 0, 0 }, "Textures/upgrade_stat_button.png", []() {});
    this->upgrade_intelligence_btn = new Button({ 720, 889 }, { 0, 0 }, "Textures/upgrade_stat_button.png", []() {});
    this->upgrade_durability_btn = new Button({ 1042, 703 }, { 0, 0 }, "Textures/upgrade_stat_button.png", []() {});
    this->upgrade_luck_btn = new Button({ 1042, 796 }, { 0, 0 }, "Textures/upgrade_stat_button.png", []() {});

    this->textfont.loadFromFile("Fonts/RodrigoTypo - Tobi Pro ExtraBold.otf");
    
    img_shape = new sf::RectangleShape();
    img_shape->setPosition({ 594,33 });
    img_shape->setSize({ 382,382 });

    strength_text = new sf::Text ("0",textfont,20);
    dexterity_text = new sf::Text("0", textfont, 20);
    intelligence_text = new sf::Text("0", textfont, 20);
    durability_text = new sf::Text("0", textfont, 20);
    luck_text = new sf::Text("0", textfont, 20);
    armor_text = new sf::Text("0", textfont, 20);

    gold_text = new sf::Text("0", textfont, 28);
    level_text = new sf::Text("0", textfont, 28);

    strenght_related_text = new sf::Text("0", textfont, 20);
    dexterity_related_text = new sf::Text("0", textfont, 20);
    intelligence_related_text = new sf::Text("0", textfont, 20);
    durability_related_text = new sf::Text("0", textfont, 20);
    luck_related_text = new sf::Text("0", textfont, 20);
    armor_related_text = new sf::Text("0", textfont, 20);

    strength_text->setPosition({ 675,710 });
    dexterity_text->setPosition({ 675,803 });
    intelligence_text->setPosition({ 675,896 });
    durability_text->setPosition({ 995,710 });
    luck_text->setPosition({ 995,803 });
    armor_text->setPosition({ 995,896 });

    gold_text->setPosition({ 1698,388 });
    level_text->setPosition({ 730,430 });

    strenght_related_text->setPosition({ 675,735 });
    dexterity_related_text->setPosition({ 675,828 });
    intelligence_related_text->setPosition({ 675,921 });
    durability_related_text->setPosition({ 995,735 });
    luck_related_text->setPosition({ 995,828 });
    armor_related_text->setPosition({ 995,921});


    strength_text->setFillColor(sf::Color::White);
    dexterity_text->setFillColor(sf::Color::White);
    intelligence_text->setFillColor(sf::Color::White);
    durability_text->setFillColor(sf::Color::White);
    luck_text->setFillColor(sf::Color::White);
    armor_text->setFillColor(sf::Color::White);

    gold_text->setFillColor(sf::Color::White);
    level_text->setFillColor(sf::Color::White);

    strenght_related_text->setFillColor(sf::Color::Cyan);
    dexterity_related_text->setFillColor(sf::Color::Cyan);
    intelligence_related_text->setFillColor(sf::Color::Cyan);
    durability_related_text->setFillColor(sf::Color::Cyan);
    luck_related_text->setFillColor(sf::Color::Cyan);
    armor_related_text->setFillColor(sf::Color::Cyan);
   


    descriptionBox = new DescriptionBox(textfont, 20);  
    descriptionBox->setPosition({ 0,0 });          
    descriptionBox->setVisible(false);

    allSlots = {
    helmet_slot,
    armor_slot,
    gloves_slot,
    shoes_slot,
    weapon_slot,
    necklace_slot,
    belt_slot,
    ring_slot,
    lucky_item_slot,
    bag_slot1,
    bag_slot2,
    bag_slot3,
    bag_slot4,
    bag_slot5,
    bag_slot6,
    bag_slot7,
    bag_slot8,
    shop_slot1,
    shop_slot2,
    shop_slot3,
    shop_slot4,
    shop_slot5,
    shop_slot6
    };

    xp_bar->updateProgress(0.f, 100.f);

    updateSlots();
    updateTextStats();
    itemSwapped = false;
}

PlayerMenu::~PlayerMenu() {
    delete this->navBar;
    delete this->player_managment_area;
    delete this->player_image;
    delete this->refresh_shop_btn;
    delete this->helmet_slot;
    delete this->armor_slot;
    delete this->gloves_slot;
    delete this->shoes_slot;
    delete this->weapon_slot;
    delete this->necklace_slot;
    delete this->belt_slot;
    delete this->ring_slot;
    delete this->lucky_item_slot;

    delete this->bag_slot1;
    delete this->bag_slot2;
    delete this->bag_slot3;
    delete this->bag_slot4;
    delete this->bag_slot5;
    delete this->bag_slot6;
    delete this->bag_slot7;
    delete this->bag_slot8;

    delete this->shop_slot1;
    delete this->shop_slot2;
    delete this->shop_slot3;
    delete this->shop_slot4;
    delete this->shop_slot5;
    delete this->shop_slot6;

    delete this->upgrade_strenght_btn;
    delete this->upgrade_dexterity_btn;
    delete this->upgrade_intelligence_btn;
    delete this->upgrade_durability_btn;
    delete this->upgrade_luck_btn;

    delete this->strength_text;
    delete this->dexterity_text;
    delete this->intelligence_text;
    delete this->durability_text;
    delete this->luck_text;
    delete this->armor_text;

    delete this->strenght_related_text;
    delete this->dexterity_related_text;
    delete this->intelligence_related_text;
    delete this->durability_related_text;
    delete this->luck_related_text;
    delete this->armor_related_text;

    delete this->descriptionBox;
    delete this->gold_text;
    delete this->level_text;
    delete this->img_shape;
}

void PlayerMenu::draw(sf::RenderWindow& window) {

    if (game_ref.getStatChangedFlag()) {
        updateTextStats();
        xp_bar->updateProgress(static_cast<float>(loggedInUser->getCurrentXP()),
            static_cast<float>(loggedInUser->getXPToNextLevel()));
        game_ref.setStatChangedFlag(false);
    }

    if (navBar != nullptr) {
        navBar->draw(window);
    }

    if (player_managment_area != nullptr) {
        player_managment_area->draw(window);
    }

    for (auto slot : allSlots) {
        if (slot) {
            slot->draw(window);
        }
    }

    
    this->refresh_shop_btn->draw(window);

    if (upgrade_strenght_btn) {
        upgrade_strenght_btn->draw(window);
    }
    if (upgrade_dexterity_btn) {
        upgrade_dexterity_btn->draw(window);
    }
    if (upgrade_intelligence_btn) {
        upgrade_intelligence_btn->draw(window);
    }
    if (upgrade_durability_btn) {
        upgrade_durability_btn->draw(window);
    }
    if (upgrade_luck_btn) {
        upgrade_luck_btn->draw(window);
    }

    if (strength_text) {
        window.draw(*strength_text);
    }
    if (dexterity_text) {
        window.draw(*dexterity_text);
    }
    if (intelligence_text) {
        window.draw(*intelligence_text);
    }
    if (durability_text) {
        window.draw(*durability_text);
    }
    if (luck_text) {
        window.draw(*luck_text);
    }
    if (armor_text) {
        window.draw(*armor_text);
    }


    if (strenght_related_text) {
        window.draw(*strenght_related_text);
    }
    if (dexterity_related_text) {
        window.draw(*dexterity_related_text);
    }
    if (intelligence_related_text) {
        window.draw(*intelligence_related_text);
    }
    if (durability_related_text) {
        window.draw(*durability_related_text);
    }
    if (luck_related_text) {
        window.draw(*luck_related_text);
    }
    if (armor_related_text) {
        window.draw(*armor_related_text);
    }

    if (gold_text) {
        window.draw(*gold_text);
    }

    if (img_shape) {
        window.draw(*img_shape);
    }
    if (xp_bar) {
        xp_bar->draw(window);
    }
    if (level_text) {
        window.draw(*level_text);
    }
    this->descriptionBox->draw(window);

}


void PlayerMenu::handleEvents(sf::Event event, sf::RenderWindow& window) {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    if (navBar) {
        navBar->handleEvents(event, window);
    }

    if (event.type == sf::Event::MouseButtonPressed and
        event.mouseButton.button == sf::Mouse::Left){
        for (auto slot : allSlots) {
            slot->tryStartDrag(mouse_pos, event);
            if (slot->getIsItemDragged()) {
                dragSource = slot;
                break;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased and
        event.mouseButton.button == sf::Mouse::Left and
        dragSource){
        
        sf::IntRect shopArea(1200, 370, 720, 710);
        ItemSlot* hoverSlot = nullptr;
        for (auto slot : allSlots) {
            if (slot->isHovered(mouse_pos)) {
                hoverSlot = slot;
                break;
            }
        }
        //sprzedaz
        if (hoverSlot && hoverSlot->getNameID().rfind("shop", 0) == 0) {
            if (dragSource->getNameID().rfind("shop", 0) == 0) {
            }
            else {
                Item* it = dragSource->getCurrentItem();
                if (loggedInUser and it) {
                    int price = it->getPrice();
                    loggedInUser->setGold(loggedInUser->getGold() + price);
                    delete it;
                    dragSource->setItem(nullptr);
                    loggedInUser->setItem(dragSource->getNameID(), nullptr);
                }
            }
            if (dragSource->getCurrentItem())
                dragSource->getCurrentItem()->setPosition(dragSource->getPosition());
            dragSource->cancelDrag();
            dragSource = nullptr;
            return;
        }

        if (hoverSlot) {

            if (dragSource->getNameID().rfind("shop", 0) == 0) {
                if (hoverSlot->getCurrentItem() == nullptr) {
                    // kupno
                    Item* it = dragSource->getCurrentItem();
                    if (loggedInUser and it) {
                        int price = it->getPrice();
                        loggedInUser->setGold(loggedInUser->getGold() - price);
                        hoverSlot->setItem(it);
                        dragSource->setItem(nullptr);
                        loggedInUser->setItem(hoverSlot->getNameID(), it);
                        loggedInUser->setItem("shop" + std::to_string(
                            std::stoi(dragSource->getNameID().substr(4))), nullptr);
                    }
                }
                else {
                    // blokada kupna na zajęty slot
                    if (dragSource->getCurrentItem())
                        dragSource->getCurrentItem()->setPosition(dragSource->getPosition());
                }
                dragSource->cancelDrag();
                dragSource = nullptr;
                return;
            }
            // jeśli źródło nie jest sklepem zwykly swap
            bool swapped = hoverSlot->endDrag(mouse_pos, event, dragSource, loggedInUser);
            if (swapped) {
                updateSlots();
                dragSource->cancelDrag();
                game_ref.setItemChangedFlag(true);
            }
            else {
                // przywrócenie itemu do źródła
                if (dragSource->getCurrentItem())
                    dragSource->getCurrentItem()->setPosition(dragSource->getPosition());
                dragSource->cancelDrag();
            }
            dragSource = nullptr;
            return;
        }

 // Upuszczenie poza sloty, ale w obszarze sklepu , sprzedaz albo powrot
        if (shopArea.contains(mouse_pos)) {
            if (dragSource->getNameID().rfind("shop", 0) == 0) {
            }
            else {
                Item* it = dragSource->getCurrentItem();
                if (loggedInUser and it) {
                    int price = it->getPrice();
                    loggedInUser->setGold(loggedInUser->getGold() + price);
                    delete it;
                    dragSource->setItem(nullptr);
                    loggedInUser->setItem(dragSource->getNameID(), nullptr);
                }
            }
            if (dragSource->getCurrentItem())
                dragSource->getCurrentItem()->setPosition(dragSource->getPosition());
            dragSource->cancelDrag();
            dragSource = nullptr;
            return;
        }

        //przywrocenie itemu
        if (dragSource->getCurrentItem())
            dragSource->getCurrentItem()->setPosition(dragSource->getPosition());
        dragSource->cancelDrag();
        dragSource = nullptr;
    }

    for (auto slot : allSlots) {
        slot->handleEvents(mouse_pos, event);
    }
    if (refresh_shop_btn) {
        refresh_shop_btn->handleEvents(mouse_pos, event);
    }
//opis
    ItemSlot* hovered = nullptr;
    for (auto slot : allSlots)
        if (slot->isHovered(mouse_pos))
            hovered = slot;
    if (hovered && hovered->getCurrentItem()) {
        descriptionBox->setItem(hovered->getCurrentItem());
        auto b = hovered->getGlobalBounds();
        descriptionBox->setPosition({ b.left + b.width + 10.f, b.top });
    }
    else {
        descriptionBox->setItem(nullptr);
    }

    if (loggedInUser) {
    if (upgrade_strenght_btn) {
        upgrade_strenght_btn->handleEvents(mouse_pos, event);
        if (upgrade_strenght_btn->isClicked(mouse_pos, event)) {
            loggedInUser->upgradeStrength();
            updateTextStats();
        }
    }
    if (upgrade_dexterity_btn) {
        upgrade_dexterity_btn->handleEvents(mouse_pos, event);
        if (upgrade_dexterity_btn->isClicked(mouse_pos, event)) {
            loggedInUser->upgradeDexterity();
            updateTextStats();
        }
    }
    if (upgrade_intelligence_btn) {
        upgrade_intelligence_btn->handleEvents(mouse_pos, event);
        if (upgrade_intelligence_btn->isClicked(mouse_pos, event)) {
            loggedInUser->upgradeIntelligence();
            updateTextStats();
        }
    }
    if (upgrade_durability_btn) {
        upgrade_durability_btn->handleEvents(mouse_pos, event);
        if (upgrade_durability_btn->isClicked(mouse_pos, event)) {
            loggedInUser->upgradeDurability();
            updateTextStats();
        }
    }
    if (upgrade_luck_btn) {
        upgrade_luck_btn->handleEvents(mouse_pos, event);
        if (upgrade_luck_btn->isClicked(mouse_pos, event)) {
            loggedInUser->upgradeLuck();
            updateTextStats();
        }
    }

    if (game_ref.getItemChangedFlag()) {
        updateSlots();
        updateTextStats();
        game_ref.setItemChangedFlag(false);
    }
    }
}


void PlayerMenu::updateSlots() {
    if (loggedInUser) {
        helmet_slot->setItem(loggedInUser->getItem("helmet"));
        armor_slot->setItem(loggedInUser->getItem("shield"));
        gloves_slot->setItem(loggedInUser->getItem("gloves"));
        shoes_slot->setItem(loggedInUser->getItem("shoes"));
        weapon_slot->setItem(loggedInUser->getItem("weapon"));
        necklace_slot->setItem(loggedInUser->getItem("necklace"));
        belt_slot->setItem(loggedInUser->getItem("belt"));
        ring_slot->setItem(loggedInUser->getItem("ring"));
        lucky_item_slot->setItem(loggedInUser->getItem("luckyitem"));

        bag_slot1->setItem(loggedInUser->getItem("slot1"));
        bag_slot2->setItem(loggedInUser->getItem("slot2"));
        bag_slot3->setItem(loggedInUser->getItem("slot3"));
        bag_slot4->setItem(loggedInUser->getItem("slot4"));
        bag_slot5->setItem(loggedInUser->getItem("slot5"));
        bag_slot6->setItem(loggedInUser->getItem("slot6"));
        bag_slot7->setItem(loggedInUser->getItem("slot7"));
        bag_slot8->setItem(loggedInUser->getItem("slot8"));

        shop_slot1->setItem(loggedInUser->getItem("shop1"));
        shop_slot2->setItem(loggedInUser->getItem("shop2"));
        shop_slot3->setItem(loggedInUser->getItem("shop3"));
        shop_slot4->setItem(loggedInUser->getItem("shop4"));
        shop_slot5->setItem(loggedInUser->getItem("shop5"));
        shop_slot6->setItem(loggedInUser->getItem("shop6"));
    }

    else {

        for (auto slot : allSlots) {
            slot->setItem(nullptr);
        }
    }
}

void PlayerMenu::updateTextStats()
{
    if (loggedInUser) {
        gold_text->setString("Monety: "+std::to_string(loggedInUser->getGold()));
        level_text->setString("Poziom "+std::to_string(loggedInUser->getLevel()));
    strength_text->setString(std::to_string(loggedInUser->getStrength()));
    dexterity_text->setString(std::to_string(loggedInUser->getDexterity()));
    intelligence_text->setString(std::to_string(loggedInUser->getIntelligence()));
    durability_text->setString(std::to_string(loggedInUser->getDurability()));
    luck_text->setString(std::to_string(loggedInUser->getLuck()));
    armor_text->setString(std::to_string(loggedInUser->getArmor()));

    strenght_related_text->setString(std::to_string(loggedInUser->calculateDamage()));
    dexterity_related_text->setString(std::to_string(loggedInUser->calculateEvasion()));
    intelligence_related_text->setString(std::to_string(loggedInUser->calculateDamageReduction()));
    durability_related_text->setString(std::to_string(loggedInUser->calculateHP()));
    double crit = loggedInUser->calculateCritChance(); 
    std::ostringstream oss;
    oss << std::setprecision(2)  
        << crit
        <<"%";
    luck_related_text->setString(oss.str());
    armor_related_text->setString(std::to_string(loggedInUser->calculateResistance()));
    }

}

void PlayerMenu::setLoggedInUser(Player* player) {
    this->loggedInUser = player;
    if(loggedInUser){

     //       std::cout << "SETOWANIE TEXTURY GRACZA "<< loggedInUser->getImgName();
            this->img_shape->setTexture(&loggedInUser->getCharacterTexture());
            xp_bar->updateProgress(static_cast<float>(loggedInUser->getCurrentXP()),
                static_cast<float>(loggedInUser->getXPToNextLevel()));
        
        updateSlots();
        updateTextStats();
    }
}

void PlayerMenu::assignRandomStats(int& strength,int& dexterity,int& intelligence,int& durability,int& luck,int& armor) {
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> distValue(0, 50);

    std::vector<int*> stats = {&strength,&dexterity,&intelligence,&durability,&luck,&armor};

    std::vector<int> indices(stats.size());
    for (int i = 0; i < indices.size(); ++i) {
        indices[i] = static_cast<int>(i);
    }
    std::shuffle(indices.begin(), indices.end(), rng);

    for (int i = 0; i < 3; ++i) {
        *stats[indices[i]] = distValue(rng);
    }
}



void PlayerMenu::refreshShop() {
    std::vector<int> ids;
    int id;
    std::string name;
    std::string texture_path;
    ItemType type;
    int strength = 0;
    int dexterity = 0;
    int intelligence = 0;
    int durability = 0;
    int luck = 0;
    int armor = 0;
    int price = 0;

    std::map < std::string, ItemSlot* > slots{
        {"shop1",shop_slot1},
        {"shop2",shop_slot2},
        {"shop3",shop_slot3},
        {"shop4",shop_slot4},
        {"shop5",shop_slot5},
        {"shop6",shop_slot6}, };
    std::ifstream file("Data/Items.txt");
    if (!file.is_open()) {
     //   std::cout << "Nie mozna otworzyc pliku items"<< std::endl;
    }

    std::string line;
    const std::regex pattern(R"(^\s*id:\s*(\d+)\s+img:\s*([^\s]+)\s+name:\s*([^\s]+)\s+type:\s*([^\s]+)\s+strength:\s*(\d+)\s+dexterity:\s*(\d+)\s+intelligence:\s*(\d+)\s+durability:\s*(\d+)\s+luck:\s*(\d+)\s+armor:\s*(\d+)\s*$)");
    std::smatch match;

    while (std::getline(file, line)) {
        if (std::regex_match(line, match, pattern)) {
            ids.push_back(std::stoi(match[1].str()));
        }
    }

    for (auto& slot : slots) {
        strength = 0;
        dexterity = 0;
        intelligence = 0;
        durability = 0;
        luck = 0;
        armor = 0;
        price = 0;
        id = 0;
        for (int i = 100; i <= 999; ++i) {
            bool conflict = false;
            for (auto j : ids) {
                if (i == j) {
                    conflict = true;
                    break;
                }
            }
            if (!conflict) {
                id = i;
                ids.push_back(id);
                break;
            }
        }
        if (id == 0) {
            throw std::runtime_error("Brak dostępnego ID");
        }

        name = "nazwa_itemu";
        type = static_cast<ItemType>(std::rand() % static_cast<int>(ItemType::ANY));

        switch (type) {
        case ItemType::WEAPON:
            texture_path = "Textures/kusza.png";
            break;
        case ItemType::ARMOR:
            texture_path = "Textures/zbroja.png";
            break;
        case ItemType::HELMET:
            texture_path = "Textures/czapka.png";
            break;
        case ItemType::GLOVES:
            texture_path = "Textures/rekawice.png";
            break;
        case ItemType::SHOES:
            texture_path = "Textures/buty.png";
            break;
        case ItemType::RING:
            texture_path = "Textures/pierscien.png";
            break;
        case ItemType::NECKLACE:
            texture_path = "Textures/naszyjnik.png";
            break;
        case ItemType::BELT:
            texture_path = "Textures/pas.png";
            break;
        case ItemType::LUCKY_ITEM:
            texture_path = "Textures/was.png";
            break;
        }
    
        assignRandomStats(strength, dexterity, intelligence, durability, luck, armor);
        static std::mt19937 rng{ std::random_device{}() };
        static std::uniform_int_distribution<int> dist(80, 250);
        price = dist(rng);

        Item* item = new Item(id, texture_path, name, type,strength, dexterity, intelligence,
            durability, luck, armor, price);
        slot.second->setItem(item);
        loggedInUser->setItem(slot.first, slot.second->getCurrentItem());

    }
    loggedInUser->setGold(loggedInUser->getGold() - 10);
    updateSlots();
}

