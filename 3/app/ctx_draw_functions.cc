#include <SFML/Graphics.hpp>
#include "cloud.h"
#include "button.h"
#include "pop_out_menu.h"
#include "input_field.h"
#include "missile.h"
#include "page_rect.h"
#include "../lib/headers/battleship_group.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;
const int INPUT_AMOUNT = 11;

void drawInputScene(sf::RenderWindow& window, InputField& inputField, Button& quitButton, Button& submitButton, sf::Text& text, PageRect& pageRect) {
            text.setPosition(inputField.getPosition().x - text.getLocalBounds().width - 10, SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2);
            text.setFillColor(sf::Color::White);
            quitButton.setSize(sf::Vector2f(submitButton.getLocalBounds().width, submitButton.getLocalBounds().height));
            pageRect.draw(window);
            inputField.draw(window);
            submitButton.setPosition(submitButton.getPosition().x, inputField.getPosition().y + 50);
            window.draw(text);
            quitButton.setPosition(submitButton.getPosition().x, submitButton.getPosition().y + submitButton.getLocalBounds().height + 20);
            submitButton.draw(window);
            quitButton.draw(window);
}

int main() {

    srand(static_cast<unsigned int>(time(nullptr))); // Seed for random number generation
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Ocean and Sky Scene");
    window.setFramerateLimit(60);

    TBattleshipGroup baseGroup;
    TBattleship *battleship;
    TPlaneGroup attackGroup;

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

    std::vector<std::string> buttonNames({"Add a battleship", "Add a plane", "Change battleship", "Change name", 
                                          "Lookup battleships", "Lookup planes", "Delete a battleship", "Delete a plane",
                                          "Simulate attack", "Exit"});

    std::vector<ProgramState> buttonStates({
    ProgramState::SHIP_TYPE_MENU,
    ProgramState::PLANE_MENU,
    ProgramState::SHIP_INFO_MENU,
    ProgramState::PLANE_INFO_MENU,
    ProgramState::SHIP_INFO_MENU,
    ProgramState::PLANE_INFO_MENU,
    ProgramState::SHIP_INFO_MENU,
    ProgramState::PLANE_INFO_MENU,
    ProgramState::ATTACK_STATE,
    ProgramState::EXIT });

    PopOutMenu menu(0, 100, buttonNames, buttonStates, 240);

    InputField inputField(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 10, 400, 30);
    Button submitButton("Submit", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 + 100, 150);

    PageRect pageRect(sf::Vector2f(0.05 * SCREEN_WIDTH, 0.05 * SCREEN_HEIGHT), sf::Vector2f(0.9 * SCREEN_WIDTH, 0.9 * SCREEN_HEIGHT));

    while (window.isOpen()) {
        TAircraftCarrier helperCarrier;
        TAircraftCarryingCruiser helperCruiser;
        TCoveringShip helperCoveringShip;
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
                    if (programState == ProgramState::ATTACK_STATE) {
                        if (baseGroup.getShipAmount(ShipType::AIRCRAFT_CARRYING_CRUISER) == 0) {
                            if (baseGroup.getShipAmount(ShipType::AIRCRAFT_CARRIER) == 0) {
                                missile.setTarget(coveringShipSprite.getPosition(), sf::Vector2f(coveringShipSprite.getGlobalBounds().width, coveringShipSprite.getGlobalBounds().height / 4));
                            }
                            else {
                                missile.setTarget(aircraftCarrierSprite.getPosition(), sf::Vector2f(aircraftCarrierSprite.getGlobalBounds().width, aircraftCarrierSprite.getGlobalBounds().height / 4));
                            }
                        }
                    }
                }
                else if (programState == ProgramState::SHIP_TYPE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string type = inputField.getUserInput();
                        if (type == "Carrier") {
                            battleship = new TAircraftCarrier();
                            programState = ProgramState::NAME_MENU;
                        }
                        else if (type == "Cruiser") {
                            TAircraftCarrier *helper = new TAircraftCarryingCruiser(); 
                            battleship = helper;
                            programState = ProgramState::NAME_MENU;
                        }
                        else if (type == "Covering ship") {
                            battleship = new TCoveringShip();
                            programState = ProgramState::NAME_MENU;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                    }
                }
                else if (programState == ProgramState::NAME_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string name = inputField.getUserInput();
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
                            TAircraftCarrier *carrierShip = dynamic_cast<TAircraftCarrier *>(battleship);
                            if (carrierShip != nullptr) {
                                programState = ProgramState::PLANE_AMOUNT_MENU;
                            }
                            else {
                                programState = ProgramState::SHIP_TO_COVER_MENU;
                            }
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
                        if (battleship != nullptr) {
                            TWeaponry weapon = battleship->getWeaponry();
                            weapon.setName(weaponName);
                            battleship->setWeaponry(weapon);
                        }
                        else {
                            TWeaponry planeWeapon = helperPlane.getWeaponry();
                            planeWeapon.setName(weaponName);
                            helperPlane.setWeaponry(planeWeapon);
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                    }
                }
                else if (programState == ProgramState::WEAPONRY_AMMO_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponAmmo = inputField.getUserInput();
                        programState = ProgramState::WEAPONRY_TYPE_MENU;
                        if (battleship != nullptr) {
                            TWeaponry weapon = battleship->getWeaponry();
                            weapon.setAmmoName(weaponAmmo);
                            battleship->setWeaponry(weapon);
                        }
                        else {
                            TWeaponry planeWeapon = helperPlane.getWeaponry();
                            planeWeapon.setAmmoName(weaponAmmo);
                            helperPlane.setWeaponry(planeWeapon);
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                    }
                }
                else if (programState == ProgramState::WEAPONRY_TYPE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponType = inputField.getUserInput();
                        programState = ProgramState::WEAPONRY_AMMO_AMOUNT_MENU;
                        if (weaponType == "Heavy") {
                            if (battleship != nullptr) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setType(WeaponryType::heavy);
                                TCoveringShip *coverShip = dynamic_cast<TCoveringShip *>(battleship);
                                if (coverShip != nullptr) {
                                    battleship->setWeaponry(weapon);
                                    programState = ProgramState::WEAPONRY_DAMAGE_MENU;
                                }
                            }
                            else {
                                TWeaponry planeWeapon = helperPlane.getWeaponry();
                                planeWeapon.setType(WeaponryType::heavy);
                                if (helperPlane.getType() == TPlaneType::bomber) {
                                    helperPlane.setWeaponry(planeWeapon);
                                    programState = ProgramState::WEAPONRY_DAMAGE_MENU;
                                }
                            }
                        }
                        else if (weaponType == "Light") {
                            if (battleship != nullptr) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setType(WeaponryType::light);
                                battleship->setWeaponry(weapon);
                            }
                            else {
                                TWeaponry planeWeapon = helperPlane.getWeaponry();
                                planeWeapon.setType(WeaponryType::light);
                                helperPlane.setWeaponry(planeWeapon);
                            } 
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        if (battleship != nullptr) {
                            delete(battleship);
                            battleship = nullptr;
                        }
                    }
                }
                else if (programState == ProgramState::WEAPONRY_DAMAGE_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponDamage = inputField.getUserInput();
                        try {
                            double weaponDamageDouble = std::stod(weaponDamage);
                            if (battleship != nullptr) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setDamage(weaponDamageDouble);
                                battleship->setWeaponry(weapon);
                            }
                            else {
                                TWeaponry planeWeapon = helperPlane.getWeaponry();
                                planeWeapon.setDamage(weaponDamageDouble);
                                helperPlane.setWeaponry(planeWeapon);
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
                    }
                }
                else if (programState == ProgramState::WEAPONRY_AMMO_AMOUNT_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string weaponAmmoAmount = inputField.getUserInput();
                        try {
                            size_t weaponAmmoAmountInt = std::stoi(weaponAmmoAmount);
                            if (battleship != nullptr) {
                                TWeaponry weapon = battleship->getWeaponry();
                                weapon.setAmmoAmount(weaponAmmoAmountInt);
                                battleship->setWeaponry(weapon);
                            }
                            else {
                                TWeaponry planeWeapon = helperPlane.getWeaponry();
                                planeWeapon.setAmmoAmount(weaponAmmoAmountInt);
                                helperPlane.setWeaponry(planeWeapon);
                            }
                            programState = ProgramState::PASSIVE_STATE;
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
                    }
                }
                else if (programState == ProgramState::PLANE_AMOUNT_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string planeAmount = inputField.getUserInput();
                        try {
                            size_t planeAmountInt = std::stoi(planeAmount);
                            TAircraftCarrier *carrierShip = dynamic_cast<TAircraftCarrier *>(battleship);
                            programState = ProgramState::PASSIVE_STATE;
                            helperCarrier = *carrierShip;
                            baseGroup.addBattleship(helperCarrier);
                            delete(battleship);
                            battleship = nullptr;
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
                else if (programState == ProgramState::SHIP_TO_COVER_MENU) {
                    if (submitButton.isMouseOver(mousePos)) {
                        std::string shipToCover = inputField.getUserInput();
                        if (shipToCover != "") {
                            try {
                                TBattleship &coveredShip = baseGroup.getBattleship(shipToCover);
                                TCoveringShip *coveringShip = dynamic_cast<TCoveringShip *>(battleship);
                                coveringShip->setShipToCover(coveredShip);
                                programState = ProgramState::PASSIVE_STATE;
                                helperCoveringShip = *coveringShip;
                                baseGroup.addBattleship(helperCoveringShip);
                                delete(battleship);
                                battleship = nullptr;
                            }
                            catch (std::exception &e) {
                                programState = ProgramState::SHIP_TO_COVER_MENU;
                            }
                        }
                        else {
                            programState = ProgramState::PASSIVE_STATE;
                            helperCoveringShip = *battleship;
                            baseGroup.addBattleship(helperCoveringShip);
                            delete(battleship);
                            battleship = nullptr;
                        }
                    }
                    else if (quitButton.isMouseOver(mousePos)) {
                        programState = ProgramState::PASSIVE_STATE;
                        delete(battleship);
                        battleship = nullptr;
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
                    }
                    window.draw(planeSprite);
                    if (missile.getPosition().x < missile.getTarget().x + missile.getTargetSize().x / 7 || 
                        missile.getPosition().y < missile.getTarget().y + missile.getTargetSize().y / 7) {
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
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
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
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::WEAPONRY_AMMO_AMOUNT_MENU) {
            sf::Text text("Enter weapon ammo amount:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::SHIP_TO_COVER_MENU) {
            sf::Text text("Enter ship to cover:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        window.display();

    }

    return 0;
}
