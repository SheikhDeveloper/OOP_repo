#ifndef LAB3_APP_POP_OUT_MENU_H
#define LAB3_APP_POP_OUT_MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <map>
#include "button.h"

enum class ProgramState {
    MAIN_MENU = 0,
    PASSIVE_STATE,
    ATTACK_STATE,
    SHIP_TYPE_MENU,
    NAME_MENU,
    CAPTAIN_NAME_MENU,
    CAPTAIN_RANK_MENU,
    EXPERIENCE_MENU,
    CREW_SIZE_MENU,
    SURVIVABILITY_MENU,
    SPEED_MENU,
    FUEL_USAGE_MENU,
    SHIP_TO_COVER_MENU,
    PLANE_AMOUNT_MENU,
    WEAPONRY_NAME_MENU,
    WEAPONRY_DAMAGE_MENU,
    WEAPONRY_AMMO_MENU,
    WEAPONRY_TYPE_MENU,
    WEAPONRY_AMMO_AMOUNT_MENU,
    CARRIER_SEARCH_MENU,
    CARRIER_ADD_MENU,
    CARRIER_DELETE_MENU,
    DELETE_SHIP_MENU,
    DELETE_PLANE_MENU,
    SHIP_INFO_MENU,
    PLANE_INFO_MENU,
    PLANE_NAME_MENU,
    PLANE_TYPE_MENU,
    PLANE_FUEL_USAGE_MENU,
    PLANE_SURVIVABILITY_MENU,
    SHIP_SEARCH_MENU,
    PLANE_SEARCH_MENU,
    EXIT
};

class PopOutMenu {
public:
    PopOutMenu(int x, int y, std::vector<std::string> &buttonNames, std::vector<ProgramState> buttonStates, int buttonWidth = 200, int buttonHeight = 50, 
            int SCREEN_WIDTH = 1000, int SCREEN_HEIGHT = 800) : isVisible(false), _buttonWidth(buttonWidth), _buttonHeight(buttonHeight) {
        // Create buttons for the menu
        size_t factor = 0;
        for (size_t i = 0; i < buttonNames.size(); ++i) {
            if (y + i * _buttonHeight > SCREEN_HEIGHT) {
                x += _buttonWidth + 20;
                factor = 0;
            }
            buttons[std::make_unique<Button>(buttonNames[i], x, y + factor * _buttonHeight + 10, _buttonWidth, _buttonHeight)] =  buttonStates[i];
            factor++;
        }

        // Create toggle button
        toggleButton.setSize(sf::Vector2f(_buttonWidth, _buttonHeight));
        toggleButton.setFillColor(sf::Color(0, 0, 0, 128));
        toggleButton.setPosition(x, 0);

        if (!font.loadFromFile("/home/sheikh/oop2024/3/app/fonts/arial.ttf")) { // Ensure you have this font or change the path
            throw std::runtime_error("Failed to load font");
        }

        toggleText.setFont(font);
        toggleText.setString("Menu");
        toggleText.setCharacterSize(24);
        toggleText.setFillColor(sf::Color::White);
        toggleText.setPosition(toggleButton.getPosition().x + toggleButton.getSize().x / 2 - toggleText.getLocalBounds().width / 2, 
                toggleButton.getPosition().y + toggleButton.getSize().y / 2 - toggleText.getLocalBounds().height / 2);
    }

    void update(const sf::Vector2f& mousePos) {
        if (toggleButton.getGlobalBounds().contains(mousePos)) {
            toggleButton.setFillColor(sf::Color(255, 255, 255, 128));
            toggleText.setFillColor(sf::Color(0, 0, 0));
        }
        else {
            toggleButton.setFillColor(sf::Color(0, 0, 0, 128));
            toggleText.setFillColor(sf::Color::White);
        }
        if (isVisible) {
            for (auto& button : buttons) {
                button.first->update(mousePos);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(toggleButton);
        window.draw(toggleText);

        if (isVisible) {
            for (const auto& button : buttons) {
                button.first->draw(window);
            }
        }
    }

    void handleMouseClick(sf::Vector2i mousePos, ProgramState& programState) {
        if (toggleButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            isVisible = !isVisible; // Toggle visibility
            return;
        }

        if (isVisible) {
            for (auto &button : buttons) {
                if (button.first->isMouseOver(mousePos)) {
                    programState = button.second;
                    isVisible = false;
                    break;
                }
            }
        }
    }

private:
    std::map<std::unique_ptr<Button>, ProgramState> buttons; // Use smart pointers to manage Button objects
    sf::RectangleShape toggleButton;
    sf::Text toggleText;
    sf::Font font;
    bool isVisible; // Track visibility of the menu
    int _buttonWidth = 200;
    int _buttonHeight = 50;
};

#endif //LAB3_APP_POP_OUT_MENU_H
