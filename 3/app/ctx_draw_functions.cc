#include <SFML/Graphics.hpp>
#include "cloud.h"
#include "button.h"
#include "pop_out_menu.h"
#include "input_field.h"
#include "missile.h"
#include "page_rect.h"
#include "dropdown_field.h"
#include "../lib/headers/battleship_group.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int DELTA_STATS = 10;

void drawPageRectWithText(sf::RenderWindow& window, PageRect& pageRect, sf::Text& text) {
    pageRect.draw(window);
    text.setFillColor(sf::Color::White);
    window.draw(text);
}

void drawInputScene(sf::RenderWindow& window, InputField& inputField, Button& quitButton, Button& submitButton, sf::Text& text, PageRect& pageRect) {
            text.setPosition(inputField.getPosition().x - text.getLocalBounds().width - 10, SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2);
            quitButton.setSize(sf::Vector2f(submitButton.getLocalBounds().width, submitButton.getLocalBounds().height));
            drawPageRectWithText(window, pageRect, text);
            inputField.draw(window);
            submitButton.setPosition(submitButton.getPosition().x, inputField.getPosition().y + 50);
            quitButton.setPosition(submitButton.getPosition().x, submitButton.getPosition().y + submitButton.getLocalBounds().height + 20);
            submitButton.draw(window);
            quitButton.draw(window);
}

void drawOptionsScene(sf::RenderWindow& window, Dropdown& dropdown, Button& quitButton, Button& submitButton, sf::Text& text, PageRect& pageRect) {
    text.setPosition(dropdown.getPosition().x - text.getLocalBounds().width - 10, SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2);
    quitButton.setSize(sf::Vector2f(submitButton.getLocalBounds().width, submitButton.getLocalBounds().height));
    drawPageRectWithText(window, pageRect, text);
    submitButton.setPosition(submitButton.getPosition().x, dropdown.getPosition().y + 50);
    quitButton.setPosition(submitButton.getPosition().x, submitButton.getPosition().y + submitButton.getLocalBounds().height + 20);
    submitButton.draw(window);
    quitButton.draw(window);
    dropdown.draw(window);
}

void drawWeaponryStats(sf::RenderWindow& window, TWeaponry &&weaponry, sf::Font& font, std::vector<sf::Text>& texts, size_t Ind) {
    sf::Text text(weaponry.getName(), font, 23);
    text.setFillColor(sf::Color::White);
    text.setPosition(texts[Ind].getPosition().x + DELTA_STATS + texts[Ind].getLocalBounds().width, texts[Ind].getPosition().y);
    window.draw(text);
    sf::Text text2(weaponry.getType() == WeaponryType::heavy ? "Heavy" : "Light" , font, 23);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(texts[Ind + 1].getPosition().x + DELTA_STATS + texts[Ind + 1].getLocalBounds().width, texts[Ind + 1].getPosition().y);
    window.draw(text2);
    sf::Text text3(std::to_string(weaponry.getAmmoAmount()), font, 23);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(texts[Ind + 2].getPosition().x + DELTA_STATS + texts[Ind + 2].getLocalBounds().width, texts[Ind + 2].getPosition().y);
    window.draw(text3);
    sf::Text text4(std::to_string(weaponry.getDamage()), font, 23);
    text4.setFillColor(sf::Color::White);
    text4.setPosition(texts[Ind + 3].getPosition().x + DELTA_STATS + texts[Ind + 3].getLocalBounds().width, texts[Ind + 3].getPosition().y);
    window.draw(text4);
    sf::Text text5(weaponry.getAmmoName(), font, 23);
    text5.setFillColor(sf::Color::White);
    text5.setPosition(texts[Ind + 4].getPosition().x + DELTA_STATS + texts[Ind + 4].getLocalBounds().width, texts[Ind + 4].getPosition().y);
    window.draw(text5);
}

void drawPlaneStats(sf::RenderWindow& window, TPlane& plane, sf::Font& font, std::vector<sf::Text>& texts, size_t Ind) {
}

void drawShipStatisticsScene(sf::RenderWindow& window, PageRect& pageRect, std::vector<sf::Text>& texts, TBattleship *battleship, sf::Font& font, Button& quitButton) {
    pageRect.draw(window);
    for (int i = 0; i < texts.size(); i++) {
        texts[i].setPosition(SCREEN_WIDTH / 2 - texts[i].getLocalBounds().width / 2, pageRect.getPos().y + 20 * (i + 1));
        texts[i].setFillColor(sf::Color::White);
        window.draw(texts[i]);
    }
    sf::Text name(battleship->getName(), font, 23);
    name.setFillColor(sf::Color::White);
    name.setPosition(texts[0].getPosition().x + texts[0].getLocalBounds().width + DELTA_STATS, texts[0].getPosition().y);
    window.draw(name); 
    sf::Text captain(battleship->getCaptain()._name, font, 23);
    captain.setFillColor(sf::Color::White);
    captain.setPosition(texts[1].getPosition().x + DELTA_STATS + texts[1].getLocalBounds().width, texts[1].getPosition().y);
    window.draw(captain);
    sf::Text rank(battleship->getCaptain()._rank, font, 23);
    rank.setFillColor(sf::Color::White);
    captain.setPosition(texts[2].getPosition().x + DELTA_STATS + texts[2].getLocalBounds().width, texts[2].getPosition().y);
    window.draw(rank);
    sf::Text experience(std::to_string(battleship->getCaptain()._experience), font, 23);
    experience.setFillColor(sf::Color::White);
    experience.setPosition(texts[3].getPosition().x + DELTA_STATS + texts[3].getLocalBounds().width, texts[3].getPosition().y);
    window.draw(experience);
    sf::Text speed(std::to_string(battleship->getSpeed()), font, 23);
    speed.setFillColor(sf::Color::White);
    speed.setPosition(texts[4].getPosition().x + DELTA_STATS + texts[4].getLocalBounds().width, texts[4].getPosition().y);
    window.draw(speed);
    sf::Text survivability(std::to_string(battleship->getSurvivability()), font, 23);
    survivability.setFillColor(sf::Color::White);
    survivability.setPosition(texts[5].getPosition().x + DELTA_STATS + texts[5].getLocalBounds().width, texts[5].getPosition().y);
    window.draw(survivability);
    sf::Text crewMembersAmount(std::to_string(battleship->getCrewMembersAmount()), font, 23);
    crewMembersAmount.setFillColor(sf::Color::White);
    crewMembersAmount.setPosition(texts[6].getPosition().x + DELTA_STATS + texts[6].getLocalBounds().width, texts[6].getPosition().y);
    window.draw(crewMembersAmount);
    sf::Text fuelUsage(std::to_string(battleship->getFuelUsage()), font, 23);
    fuelUsage.setFillColor(sf::Color::White);
    fuelUsage.setPosition(texts[7].getPosition().x + DELTA_STATS + texts[7].getLocalBounds().width, texts[7].getPosition().y);
    window.draw(fuelUsage);
    drawWeaponryStats(window, battleship->getWeaponry(), font, texts, 8);
    sf::Text type;
    type.setFillColor(sf::Color::White);
    type.setPosition(texts[13].getPosition().x + DELTA_STATS + texts[13].getLocalBounds().width, texts[13].getPosition().y);
    type.setFont(font);
    type.setCharacterSize(23);
    TCoveringShip* coveringShip = dynamic_cast<TCoveringShip *>(battleship);
    TAircraftCarrier* carrier = dynamic_cast<TAircraftCarrier *>(battleship);
    if (coveringShip != nullptr && carrier != nullptr) {
        type.setString("Aircraft Cruiser");
    }
    else if (coveringShip != nullptr) {
        type.setString("Covering Ship");
    }
    else if (carrier != nullptr) {
        type.setString("Aircraft Carrier");
    }
    window.draw(type);
    if (coveringShip != nullptr) {
        sf::Text coveredShip(coveringShip->getShipToCover().getName(), font, 23); 
        coveredShip.setFillColor(sf::Color::White);
        coveredShip.setPosition(texts[14].getPosition().x + DELTA_STATS + texts[14].getLocalBounds().width, texts[14].getPosition().y);
        window.draw(coveredShip);
    }
    if (carrier != nullptr) {
        sf::Text numberOfPlanes(std::to_string(carrier->getPlaneInfo().size()), font, 23);
        numberOfPlanes.setFillColor(sf::Color::White);
        numberOfPlanes.setPosition(texts[15].getPosition().x + texts[15].getLocalBounds().width + DELTA_STATS, texts[15].getPosition().y);
        window.draw(numberOfPlanes);
    }
    quitButton.setPosition(SCREEN_WIDTH / 2 - quitButton.getLocalBounds().width / 2, texts[texts.size() - 1].getPosition().y + 3 * DELTA_STATS);
    quitButton.draw(window);
}

int main() {

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generation
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ocean and Sky Scene");
    window.setFramerateLimit(60);

    TBattleshipGroup baseGroup;
    TBattleship *battleship{};
    TPlaneGroup attackGroup = TPlaneGroup();
    TPlane plane;

    // Create the sky
    sf::RectangleShape sky(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
    sky.setFillColor(sf::Color(135, 206, 235)); // Light blue color for the sky

    // Create the ocean
    sf::RectangleShape ocean(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2));
    ocean.setPosition(0, 0.5f);
    ocean.setFillColor(sf::Color(0, 0, 255));

    sf::Texture aircraftCarrierTexture;
    if (!aircraftCarrierTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/aircraft_carrier.png")) {
        throw std::runtime_error("Failed to load aircraft carrier texture");
    }
    sf::Texture aircraftCruiserTexture;
    if (!aircraftCruiserTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/aircraft_cruiser.png")) {
        throw std::runtime_error("Failed to load aircraft cruiser texture");
    }
    sf::Texture coveringShipTexture;
    if (!coveringShipTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/covering_ship.png")) {
        throw std::runtime_error("Failed to load covering ship texture");
    }
    sf::Texture waterTexture;
    if (!waterTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/water.png")) {
        throw std::runtime_error("Failed to load water texture");
    }
    sf::Texture planeTexture;
    if (!planeTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/plane.png")) {
        throw std::runtime_error("Failed to load plane texture");
    }
    sf::Texture missileTexture;
    if (!missileTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/missile.png")) {
        throw std::runtime_error("Failed to load missile texture");
    }

    ProgramState programState = ProgramState::MAIN_MENU;

    sf::Font font;
    if (!font.loadFromFile("/home/sheikh/oop2024/3/app/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    size_t planeCounter = 0;

    sf::Clock clock;

    sf::Sprite aircraftCarrierSprite(aircraftCarrierTexture);
    aircraftCarrierSprite.setScale(0.25f, 0.2f);
    aircraftCarrierSprite.setPosition(SCREEN_WIDTH / 20 + aircraftCarrierSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - aircraftCarrierSprite.getGlobalBounds().height / 2);
    sf::Sprite aircraftCruiserSprite(aircraftCruiserTexture);
    aircraftCruiserSprite.setScale(0.25f, 0.25f);
    aircraftCruiserSprite.setPosition(SCREEN_WIDTH / 20 + aircraftCruiserSprite.getGlobalBounds().width / 2 + aircraftCarrierSprite.getGlobalBounds().width + 50, SCREEN_HEIGHT / 2 - aircraftCruiserSprite.getGlobalBounds().height / 2);
    sf::Sprite coveringShipSprite(coveringShipTexture);
    coveringShipSprite.setScale(0.25f, 0.25f);
    coveringShipSprite.setPosition(SCREEN_WIDTH / 2 - coveringShipSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - coveringShipSprite.getGlobalBounds().height / 2 + aircraftCruiserSprite.getGlobalBounds().height);
    sf::Sprite planeSprite(planeTexture);
    planeSprite.setScale(0.1f, 0.1f);
    planeSprite.setPosition(0, SCREEN_HEIGHT / 3);

    Missile missile(missileTexture, planeSprite.getPosition(), sf::Vector2f(aircraftCruiserSprite.getPosition().x + aircraftCruiserSprite.getGlobalBounds().width / 2, aircraftCruiserSprite.getPosition().y + aircraftCruiserSprite.getGlobalBounds().height / 2), sf::Vector2f(aircraftCruiserSprite.getGlobalBounds().width, aircraftCruiserSprite.getGlobalBounds().height));

    // Create two sprites for the scrolling effect
    sf::Sprite waterSprite1(waterTexture);
    sf::Sprite waterSprite2(waterTexture);

    bool addingToCarrier = false;

    // Position the first sprite at the left half of the screen
    waterSprite1.setPosition(0, SCREEN_HEIGHT / 2);
    // Position the second sprite right next to the first one
    waterSprite2.setPosition(waterTexture.getSize().x, SCREEN_HEIGHT / 2); // Start immediately after the first

    const float cloudWidth = 50;
    const float cloudHeight = 25;
    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile("/home/sheikh/oop2024/3/app/images/cloud.png")) {
        throw std::runtime_error("Failed to load cloud texture");
    }

    std::vector<Cloud> clouds;

    for (int i = 0; i < 20; ++i) {
        float x = rand() % SCREEN_WIDTH + SCREEN_WIDTH; // Start off-screen to the right
        float y = rand() % 200 + 50; // Random vertical position
        clouds.emplace_back(cloudTexture, x, y);
    }

     float cloudSpeed = 2.0f;
     float planeSpeed = 3.0f;

     waterSprite1.setScale(2.0f, 1.0f);
     waterSprite2.setScale(2.0f, 1.0f);

    Button startButton("Start", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 200);
    Button quitButton("Quit", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 100);

    startButton.setColor(sf::Color(0, 0, 0, 128));
    quitButton.setColor(sf::Color(0, 0, 0, 128));

    std::vector<std::string> buttonNames({"Add a battleship", "Add a plane", 
                                          "Search battleship", "Search plane", "Delete a battleship", "Delete a plane",
                                          "Simulate attack", "Exit"});

    std::vector<ProgramState> buttonStates({
    ProgramState::SHIP_TYPE_MENU,
    ProgramState::CARRIER_MENU,
    ProgramState::SHIP_SEARCH_MENU,
    ProgramState::CARRIER_MENU,
    ProgramState::DELETE_SHIP_MENU,
    ProgramState::CARRIER_MENU,
    ProgramState::PLANE_AMOUNT_MENU,
    ProgramState::EXIT });

    std::vector<std::string> shipStats({ "Name:", "Captain:", "Captain rank:" , "Captain experience:", "Survivability:",  
                                         "Speed:", "Crew members amount:", "Fuel usage:", "Weaponry name:",
                                         "Weaponry type:", "Ammo amount:", "Damage:", "Ammo name:", "Ship type:", "Covered ship:", "Plane amount:"});

    PopOutMenu menu(0, 100, buttonNames, buttonStates, 240);

    InputField inputField(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 10, 400, 30);
    Button submitButton("Submit", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 100, 150);
    Dropdown dropdown(sf::Vector2f(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 10), font, 400, 30);

    PageRect pageRect(sf::Vector2f(0.05 * SCREEN_WIDTH, 0.05 * SCREEN_HEIGHT), sf::Vector2f(0.9 * SCREEN_WIDTH, 0.9 * SCREEN_HEIGHT));

    ProgramState prevState = ProgramState::MAIN_MENU;

    while (window.isOpen()) {
        TPlane helperPlane;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (programState == ProgramState::MAIN_MENU) {
                    if (startButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE; // Exit the menu
                    } else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::EXIT; // Quit the program
                    }
                }
                else if (programState == ProgramState::PASSIVE_STATE) {
                    menu.handleMouseClick(sf::Mouse::getPosition(window), programState);
                    if (programState == ProgramState::SHIP_TYPE_MENU) {
                        dropdown.setOptions({"Carrier", "Cruiser", "Covering ship"});
                    }
                }
                else if (programState == ProgramState::SHIP_TYPE_MENU) {
                    if (submitButton.isMouseOver(mousePos) && !dropdown.isOpened()) {
                        std::string type = dropdown.getSelectedText();
                        if (type == "Carrier") {
                            battleship = new TAircraftCarrier();
                            programState = ProgramState::NAME_MENU;
                        }
                        else if (type == "Cruiser") {
                            battleship = new TAircraftCarryingCruiser();
                            programState = ProgramState::NAME_MENU;
                        }
                        else if (type == "Covering ship") {
                            battleship = new TCoveringShip();
                            programState = ProgramState::NAME_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos) && !dropdown.isOpened()) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                    dropdown.handleClick(static_cast<sf::Vector2f>(mousePos));
                }
                else if (programState == ProgramState::NAME_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string name = inputField.getUserInput();
                        battleship->setName(name);
                        programState = ProgramState::CAPTAIN_NAME_MENU;
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::CAPTAIN_NAME_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string name = inputField.getUserInput();
                        TCaptainInfo captainInfo = battleship->getCaptain();
                        captainInfo._name = name;
                        battleship->setCaptain(captainInfo);
                        programState = ProgramState::CAPTAIN_RANK_MENU;
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::CAPTAIN_RANK_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string rank = inputField.getUserInput();
                        TCaptainInfo captainInfo = battleship->getCaptain();
                        captainInfo._rank = rank;
                        battleship->setCaptain(captainInfo);
                        programState = ProgramState::EXPERIENCE_MENU;
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::EXPERIENCE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string experience = inputField.getUserInput();
                        try {
                        size_t exp = std::stoi(experience);
                        TCaptainInfo captainInfo = battleship->getCaptain();
                        captainInfo._experience = exp;
                        battleship->setCaptain(captainInfo);
                        programState = ProgramState::SURVIVABILITY_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::EXPERIENCE_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::SURVIVABILITY_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string survivability = inputField.getUserInput();
                        try {
                            double survivabilityDouble = std::stod(survivability);
                            if (survivabilityDouble >= 0) {
                                battleship->setSurvivability(survivabilityDouble);
                                programState = ProgramState::SPEED_MENU;
                            }
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::SURVIVABILITY_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::SPEED_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string speed = inputField.getUserInput();
                        try {
                            double speedDouble = std::stod(speed);
                            if (speedDouble >= 0) {
                                battleship->setSpeed(speedDouble);
                                programState = ProgramState::FUEL_USAGE_MENU;
                            }
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::SPEED_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::FUEL_USAGE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string fuelUsage = inputField.getUserInput();
                        try {
                            double fuelUsageDouble = std::stod(fuelUsage);
                            if (fuelUsageDouble >= 0) {
                                battleship->setFuelUsage(fuelUsageDouble);
                                programState = ProgramState::CREW_SIZE_MENU;
                            }
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::FUEL_USAGE_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::CREW_SIZE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string crewSize = inputField.getUserInput();
                        try {
                            size_t crewSizeInt = std::stoi(crewSize);
                            battleship->setCrewMembersAmount(crewSizeInt);
                            programState = ProgramState::WEAPONRY_TYPE_MENU;
                            dropdown.setOptions({"Heavy", "Light"});
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::CREW_SIZE_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::WEAPONRY_NAME_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponName = inputField.getUserInput();
                        programState = ProgramState::WEAPONRY_AMMO_MENU;
                        if (battleship != nullptr && !addingToCarrier) {
                            TWeaponry weapon = battleship->getWeaponry();
                            weapon.setName(weaponName);
                            battleship->setWeaponry(weapon);
                        }
                        else {
                            TWeaponry planeWeapon = plane.getWeaponry();
                            planeWeapon.setName(weaponName);
                            plane.setWeaponry(planeWeapon);
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::WEAPONRY_AMMO_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponAmmo = inputField.getUserInput();
                        programState = ProgramState::WEAPONRY_DAMAGE_MENU;
                        if (battleship != nullptr && !addingToCarrier) {
                            TWeaponry weapon = battleship->getWeaponry();
                            weapon.setAmmoName(weaponAmmo);
                            battleship->setWeaponry(weapon);
                        }
                        else {
                            TWeaponry planeWeapon = plane.getWeaponry();
                            planeWeapon.setAmmoName(weaponAmmo);
                            plane.setWeaponry(planeWeapon);
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::WEAPONRY_TYPE_MENU) {
                    if (submitButton.isMouseOver(mousePos) && !dropdown.isOpened()) {
                        std::string weaponType = dropdown.getSelectedText();
                        if (weaponType == "Heavy") {
                            if (battleship != nullptr && !addingToCarrier) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setType(WeaponryType::heavy);
                                TCoveringShip *coverShip = dynamic_cast<TCoveringShip *>(battleship);
                                if (coverShip != nullptr) {
                                    battleship->setWeaponry(weapon);
                                    programState = ProgramState::WEAPONRY_NAME_MENU;
                                }
                            }
                            else {
                                TWeaponry planeWeapon = plane.getWeaponry();
                                planeWeapon.setType(WeaponryType::heavy);
                                if (plane.getType() == TPlaneType::bomber) {
                                    plane.setWeaponry(planeWeapon);
                                    programState = ProgramState::WEAPONRY_NAME_MENU;
                                }
                            }
                        }
                        else if (weaponType == "Light") {
                            if (battleship != nullptr && !addingToCarrier) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setType(WeaponryType::light);
                                battleship->setWeaponry(weapon);
                                programState = ProgramState::WEAPONRY_NAME_MENU;
                            }
                            else {
                                TWeaponry planeWeapon = plane.getWeaponry();
                                if (plane.getType() == TPlaneType::fighter) {
                                    planeWeapon.setType(WeaponryType::light);
                                    plane.setWeaponry(planeWeapon);
                                    programState = ProgramState::WEAPONRY_NAME_MENU;
                                }
                            } 
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos) && !dropdown.isOpened()) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                    dropdown.handleClick(static_cast<sf::Vector2f>(mousePos));
                }
                else if (programState == ProgramState::WEAPONRY_DAMAGE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponDamage = inputField.getUserInput();
                        try {
                            double weaponDamageDouble = std::stod(weaponDamage);
                            if (battleship != nullptr && !addingToCarrier) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setDamage(weaponDamageDouble);
                                battleship->setWeaponry(weapon);
                            }
                            else {
                                TWeaponry planeWeapon = plane.getWeaponry();
                                planeWeapon.setDamage(weaponDamageDouble);
                                plane.setWeaponry(planeWeapon);
                            }
                            programState = ProgramState::WEAPONRY_AMMO_AMOUNT_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::WEAPONRY_DAMAGE_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::WEAPONRY_AMMO_AMOUNT_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponAmmoAmount = inputField.getUserInput();
                        try {
                            size_t weaponAmmoAmountInt = std::stoi(weaponAmmoAmount);
                            if (battleship != nullptr && !addingToCarrier) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setAmmoAmount(weaponAmmoAmountInt);
                                battleship->setWeaponry(weapon);
                                TAircraftCarrier *carrierShip = dynamic_cast<TAircraftCarrier *>(battleship);
                                if (carrierShip != nullptr) {
                                    programState = ProgramState::PLANE_AMOUNT_MENU;
                                }
                                else {
                                    programState = ProgramState::SHIP_TO_COVER_MENU;
                                }
                            }
                            else {
                                TWeaponry planeWeapon = plane.getWeaponry();
                                planeWeapon.setAmmoAmount(weaponAmmoAmountInt);
                                plane.setWeaponry(planeWeapon);
                                if (addingToCarrier) {
                                    TAircraftCarrier *carrierShip = dynamic_cast<TAircraftCarrier *>(battleship);
                                    TPlaneGroup &carrierPlanes = carrierShip->getPlaneInfo();
                                    carrierPlanes.addPlane(plane);
                                }
                                else {
                                    attackGroup.addPlane(plane);
                                }
                                planeCounter--;
                                programState = ProgramState::PLANE_TYPE_MENU;
                                dropdown.setOptions({ "Bomber", "Fighter" });
                            }
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::WEAPONRY_AMMO_AMOUNT_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::PLANE_AMOUNT_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string planeAmount = inputField.getUserInput();
                        try {
                            planeCounter = std::stoi(planeAmount);
                            if (battleship != nullptr) {
                                addingToCarrier = true;
                            }
                            programState = ProgramState::PLANE_TYPE_MENU;
                            dropdown.setOptions({ "Bomber", "Fighter" });
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::PLANE_AMOUNT_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::PLANE_TYPE_MENU) {
                    if (submitButton.isMouseOver(mousePos) && !dropdown.isOpened()) {
                        plane = TPlane();
                        std::string planeType = dropdown.getSelectedText();
                        if (planeType == "Bomber") {
                            plane.setType(TPlaneType::bomber);
                        }
                        else {
                            plane.setType(TPlaneType::fighter);
                        }
                        programState = ProgramState::PLANE_NAME_MENU;
                    }
                    else if (quitButton.isMouseOver(mousePos) && !dropdown.isOpened()) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                    dropdown.handleClick(static_cast<sf::Vector2f>(mousePos));
                }
                else if (programState == ProgramState::PLANE_NAME_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        plane.setName(inputField.getUserInput());
                        programState = ProgramState::PLANE_SURVIVABILITY_MENU;
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::PLANE_SURVIVABILITY_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string planeSurvivability = inputField.getUserInput();
                        try {
                            double planeSurvivabilityDouble = std::stod(planeSurvivability);
                            plane.setSurvivability(planeSurvivabilityDouble);
                            programState = ProgramState::PLANE_FUEL_USAGE_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::PLANE_SURVIVABILITY_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::PLANE_FUEL_USAGE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string planeFuelUsage = inputField.getUserInput();
                        try {
                            double planeFuelUsageDouble = std::stod(planeFuelUsage);
                            plane.setFuelUsage(planeFuelUsageDouble);
                            programState = ProgramState::WEAPONRY_TYPE_MENU;
                            dropdown.setOptions({"Heavy", "Light"});
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::PLANE_FUEL_USAGE_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                        if (addingToCarrier) {
                            addingToCarrier = false;
                        }
                    }
                }
                else if (programState == ProgramState::SHIP_TO_COVER_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string shipToCover = inputField.getUserInput();
                        if (shipToCover != "") {
                            try {
                                TBattleship &coveredShip = baseGroup.getBattleship(shipToCover);
                                TCoveringShip *coveringShip = dynamic_cast<TCoveringShip *>(battleship);
                                coveringShip->setShipToCover(coveredShip);
                                baseGroup.addBattleship(battleship);
                            }
                            catch (std::exception &e) {
                                programState = ProgramState::SHIP_TO_COVER_MENU;
                            }
                        }
                        else {
                            programState = ProgramState::PASSIVE_STATE;
                            baseGroup.addBattleship(battleship);
                            battleship = nullptr;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
                    }
                }
                else if (programState == ProgramState::DELETE_SHIP_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string shipToDelete = inputField.getUserInput();
                        try {
                            baseGroup.removeBattleship(shipToDelete);
                            programState = ProgramState::PASSIVE_STATE;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::DELETE_SHIP_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::DELETE_PLANE_MENU) {
                   if (submitButton.isMouseOver(mousePos)) {
                       std::string planeToDelete = inputField.getUserInput();
                       baseGroup.removePlane(planeToDelete, battleship->getName());
                       programState = ProgramState::PASSIVE_STATE;                           
                       battleship = nullptr;
                   } 
                   else if (quitButton.isMouseOver(mousePos)) {
                       programState = ProgramState::PASSIVE_STATE;
                       battleship = nullptr;
                   }
                }
                else if (programState == ProgramState::CARRIER_ADD_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        try {
                            std::string carrierName = inputField.getUserInput();
                            TAircraftCarrier carrier = baseGroup.getCarrier(carrierName);
                            battleship = &baseGroup.getBattleship(carrierName);
                            addingToCarrier = true;
                            planeCounter = 1;
                            programState = ProgramState::PLANE_TYPE_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::CARRIER_ADD_MENU;
                        }
                    }
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::CARRIER_DELETE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string carrierName = inputField.getUserInput();
                        try {
                            TAircraftCarrier carrier = baseGroup.getCarrier(carrierName);
                            battleship = &baseGroup.getBattleship(carrierName);
                            programState = ProgramState::DELETE_PLANE_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::CARRIER_DELETE_MENU;
                        }
                    }
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::CARRIER_SEARCH_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string carrierName = inputField.getUserInput();
                        try {
                            TAircraftCarrier carrier = baseGroup.getCarrier(carrierName);
                            battleship = &baseGroup.getBattleship(carrierName);
                            programState = ProgramState::PLANE_SEARCH_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::CARRIER_SEARCH_MENU;
                        }
                    }
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::SHIP_SEARCH_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string shipName = inputField.getUserInput();
                        try {
                            battleship = &baseGroup.getBattleship(shipName);
                            programState = ProgramState::SHIP_INFO_MENU;
                        }
                        catch (std::exception &e) {
                            programState = ProgramState::SHIP_SEARCH_MENU;
                        }
                    }
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::PLANE_SEARCH_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string planeName = inputField.getUserInput();
                        try {
                            plane = baseGroup.getPlane(planeName, TPlaneType::fighter, battleship->getName());
                            programState = ProgramState::PLANE_INFO_MENU;
                        }
                        catch (std::exception &e) {
                            try {
                                plane = baseGroup.getPlane(planeName, TPlaneType::bomber, battleship->getName());
                                programState = ProgramState::PLANE_INFO_MENU;
                            }
                            catch (std::invalid_argument &e) {
                                programState = ProgramState::PLANE_SEARCH_MENU;
                            }
                        }
                    }
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::SHIP_INFO_MENU) {
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::PLANE_INFO_MENU) {
                    if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                if ((programState != ProgramState::MAIN_MENU || programState != ProgramState::PASSIVE_STATE) && 
                        (quitButton.isMouseOver(sf::Mouse::getPosition(window)) || submitButton.isMouseOver(sf::Mouse::getPosition(window)))) {
                    inputField.clearInput();
                }
            }
            inputField.handleEvent(event);
        }

        if (programState == ProgramState::EXIT) {
            window.close();
        }

        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        menu.update(mousePos);
        startButton.update(mousePos);
        quitButton.update(mousePos);
        submitButton.update(mousePos);
        dropdown.update(mousePos);

        float deltaTime = clock.restart().asSeconds();
        inputField.update(deltaTime);

        window.clear();

        window.draw(waterSprite1);
        window.draw(waterSprite2);
        // Draw the sky and ocean
        window.draw(sky);

        for (auto& cloud : clouds) {
            cloud.draw(window);
        }

        if (programState == ProgramState::MAIN_MENU) {
            startButton.draw(window);
            quitButton.draw(window);
        }
        else if (programState == ProgramState::PASSIVE_STATE || programState == ProgramState::ATTACK_STATE) {
            if (baseGroup.size() > 0) {
                for (auto& cloud : clouds) {
                    cloud.update(cloudSpeed);
                }

                waterSprite1.move(-cloudSpeed, 0);
                waterSprite2.move(-cloudSpeed, 0);

                // Reset position if a sprite goes off-screen
                if (waterSprite1.getPosition().x + waterTexture.getSize().x < 0) {
                    waterSprite1.setPosition(waterSprite2.getPosition().x + waterTexture.getSize().x, SCREEN_HEIGHT / 2);
                }
                if (waterSprite2.getPosition().x + waterTexture.getSize().x < 0) {
                    waterSprite2.setPosition(waterSprite1.getPosition().x + waterTexture.getSize().x, SCREEN_HEIGHT / 2);
                }

            // Draw the ships
                if (baseGroup.getShipAmount(ShipType::AIRCRAFT_CARRIER) > 0) {
                    window.draw(aircraftCarrierSprite);
                }
                if (baseGroup.getShipAmount(ShipType::AIRCRAFT_CARRYING_CRUISER) > 0) {
                    window.draw(aircraftCruiserSprite);
                }
                if (baseGroup.getShipAmount(ShipType::COVERING_SHIP) > 0) {
                    window.draw(coveringShipSprite);
                }

                if (programState == ProgramState::ATTACK_STATE) {
                    planeSprite.move(planeSpeed, 0); 
                    missile.update(planeSpeed);
                    if (planeSprite.getPosition().x > SCREEN_WIDTH) {
                        planeSprite.setPosition(0, SCREEN_HEIGHT / 3);
                        programState = ProgramState::PASSIVE_STATE;
                        baseGroup.simulateAttack(attackGroup);
                        attackGroup = TPlaneGroup();
                    }
                    window.draw(planeSprite);
                    if (missile.getPosition().x < missile.getTarget().x + missile.getTargetSize().x / 3 || 
                        missile.getPosition().y < missile.getTarget().y + missile.getTargetSize().y / 2) {
                        missile.draw(window);
                    }
                    else missile.setPosition(planeSprite.getPosition());
                }
            }
            else if (programState == ProgramState::ATTACK_STATE) {
                programState = ProgramState::PASSIVE_STATE;
            }

            menu.draw(window);
        }
        else if (programState == ProgramState::SHIP_TYPE_MENU) {
            sf::Text text("Select a ship type:", font, 23);
            drawOptionsScene(window, dropdown, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::NAME_MENU) {
            sf::Text text("Enter ship name:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::CAPTAIN_NAME_MENU) {
            sf::Text text("Enter captain name:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::CAPTAIN_RANK_MENU) {
            sf::Text text("Enter ship captain rank:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::EXPERIENCE_MENU) {
            sf::Text text("Enter captain experience:", font, 23); 
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::SURVIVABILITY_MENU) {
            sf::Text text("Enter ship survivability:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::SPEED_MENU) {
            sf::Text text("Enter ship speed:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::FUEL_USAGE_MENU) {
            sf::Text text("Enter ship fuel usage:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::CREW_SIZE_MENU) {
            sf::Text text("Enter ship crew size:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::WEAPONRY_NAME_MENU) {
            sf::Text text("Enter weapon name:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::WEAPONRY_DAMAGE_MENU) {
            sf::Text text("Enter weapon damage:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::WEAPONRY_AMMO_MENU) {
            sf::Text text("Enter weapon ammo name:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::WEAPONRY_TYPE_MENU) {
            sf::Text text("Enter weapon type:", font, 23);
            drawOptionsScene(window, dropdown, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::WEAPONRY_AMMO_AMOUNT_MENU) {
            sf::Text text("Enter weapon ammo amount:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::PLANE_AMOUNT_MENU) {
            sf::Text text("Enter number of planes:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::SHIP_TO_COVER_MENU) {
            sf::Text text("Enter ship to cover:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::DELETE_SHIP_MENU) {
            sf::Text text("Enter ship name to delete:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::SHIP_SEARCH_MENU) {
            sf::Text text("Enter ship name to search:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::DELETE_PLANE_MENU) {
            sf::Text text("Enter plane name to delete:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::CARRIER_MENU) {
            sf::Text text("Enter carrier name:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::PLANE_TYPE_MENU) {
            if (planeCounter > 0) {
                sf::Text text("Enter plane type:", font, 23);
                drawOptionsScene(window, dropdown, quitButton, submitButton, text, pageRect);
            }
            else if (addingToCarrier) {
                TCoveringShip *covShip = dynamic_cast<TCoveringShip*>(battleship);
                if (covShip != nullptr) {
                    programState = ProgramState::SHIP_TO_COVER_MENU;
                }
                else {
                    programState = ProgramState::PASSIVE_STATE;
                    baseGroup.addBattleship(battleship);
                    battleship = nullptr;
                }
                addingToCarrier = false;
                continue;
            }
            else if (attackGroup.size() > 0) {
                programState = ProgramState::ATTACK_STATE;
                if (baseGroup.getShipAmount(ShipType::AIRCRAFT_CARRYING_CRUISER) == 0) {
                    if (baseGroup.getShipAmount(ShipType::AIRCRAFT_CARRIER) == 0) {
                        missile.setTarget(coveringShipSprite.getPosition(), sf::Vector2f(4 * coveringShipSprite.getGlobalBounds().width / 3, coveringShipSprite.getGlobalBounds().height));
                    }
                    else {
                        missile.setTarget(aircraftCarrierSprite.getPosition(), sf::Vector2f(aircraftCarrierSprite.getGlobalBounds().width / 2, aircraftCarrierSprite.getGlobalBounds().height));
                    }
                }
                else {
                    missile.setTarget(aircraftCruiserSprite.getPosition(), sf::Vector2f(aircraftCruiserSprite.getGlobalBounds().width / 2, aircraftCruiserSprite.getGlobalBounds().height));
                }
                missile.setPosition(planeSprite.getPosition());
                continue;
            }
            else programState = ProgramState::PASSIVE_STATE;
        }
        else if (programState == ProgramState::PLANE_NAME_MENU) {
            sf::Text text("Enter plane name:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::PLANE_FUEL_USAGE_MENU) {
            sf::Text text("Enter plane fuel usage:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::PLANE_SURVIVABILITY_MENU) {
            sf::Text text("Enter plane survivability:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::SHIP_INFO_MENU) {
            std::vector<sf::Text> shipStatTexts(shipStats.size());
            for (auto &stat : shipStatTexts) {
                stat.setFont(font);
                stat.setCharacterSize(23);
                stat.setFillColor(sf::Color::White);
            }
            for (size_t i = 0; i < shipStats.size(); i++) {
                shipStatTexts[i].setString(shipStats[i]);
                shipStatTexts[i].setPosition(50, pageRect.getPos().y + 4 * DELTA_STATS * (i + 1));
            }
            drawShipStatisticsScene(window, pageRect, shipStatTexts, battleship, font, quitButton);
        }
        window.display();

    }

    return 0;
}
