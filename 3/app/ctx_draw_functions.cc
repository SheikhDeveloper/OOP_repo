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
            text.setPosition(SCREEN_WIDTH / 4 - text.getLocalBounds().width / 2, SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2);
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

    //TBattleshipGroup baseGroup;

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

    Missile missile(missileTexture, planeSprite.getPosition(), sf::Vector2f(aircraftCruiserSprite.getPosition().x + aircraftCruiserSprite.getGlobalBounds().width / 2, aircraftCruiserSprite.getPosition().y + aircraftCruiserSprite.getGlobalBounds().height / 2));

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
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (programState == ProgramState::MAIN_MENU && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.isMouseOver(mousePos)) {
                    programState = ProgramState::PASSIVE_STATE; // Exit the menu
                } else if (quitButton.isMouseOver(mousePos)) {
                    programState = ProgramState::EXIT; // Quit the program
                }
            }
            else if (programState == ProgramState::PASSIVE_STATE && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                menu.handleMouseClick(sf::Mouse::getPosition(window), programState);
            }
            else if (programState == ProgramState::SHIP_TYPE_MENU) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && submitButton.isMouseOver(mousePos)) {
                    std::string type = inputField.getUserInput();
                    if (type == "Carrier") {
                        programState = ProgramState::AIRCRAFTCARRIER_MENU;
                    }
                    else if (type == "Cruiser") {
                        programState = ProgramState::AIRCRAFTCRUISER_MENU;
                    }
                    else if (type == "Covering ship") {
                        programState = ProgramState::COVERINGSHIP_MENU;
                    }
                }
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && quitButton.isMouseOver(mousePos)) {
                    programState = ProgramState::PASSIVE_STATE;
                }
                else {
                    inputField.handleEvent(event);
                }
            }
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
            window.draw(aircraftCarrierSprite);
            window.draw(aircraftCruiserSprite);
            window.draw(coveringShipSprite);

            if (programState == ProgramState::ATTACK_STATE) {
                planeSprite.move(planeSpeed, 0); 
                missile.update(planeSpeed);
                if (planeSprite.getPosition().x > SCREEN_WIDTH) {
                    planeSprite.setPosition(0, SCREEN_HEIGHT / 3);
                    programState = ProgramState::PASSIVE_STATE;
                }
                window.draw(planeSprite);
                if (missile.getPosition().x < aircraftCruiserSprite.getPosition().x + aircraftCruiserSprite.getLocalBounds().width / 7 && 
                    missile.getPosition().y < aircraftCruiserSprite.getPosition().y + aircraftCruiserSprite.getLocalBounds().height / 7) {
                    missile.draw(window);
                }
                else missile.setPosition(planeSprite.getPosition());
            }

            menu.draw(window);
        }
        else if (programState == ProgramState::SHIP_TYPE_MENU) {
            sf::Text text("Select a ship type:", font, 23);
            drawInputScene(window, inputField, quitButton, submitButton, text, pageRect);
        }
        else if (programState == ProgramState::AIRCRAFTCARRIER_MENU) {
            std::vector<sf::Text> texts = {
                sf::Text("Name: ", font, 23),
                sf::Text("Captain name: ", font, 23),
                sf::Text("Captain rank: ", font, 23),
                sf::Text("Captain experience: ", font, 23),
                sf::Text("Survivability: ", font, 23),
                sf::Text("Speed: ", font, 23),
                sf::Text("Crew members amount: ", font, 23),
                sf::Text("Fuel usage: ", font, 23)
            };
        }

        window.display();

    }

    return 0;
}
