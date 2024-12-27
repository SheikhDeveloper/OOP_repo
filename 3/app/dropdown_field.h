#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Dropdown {
public:
    Dropdown(const sf::Vector2f& position, sf::Font& font, float width = 200, float height = 30)
        : _font(font), isOpen(false), selectedIndex(-1), options() {
        // Set up the main button
        button.setSize(sf::Vector2f(width, height));
        button.setPosition(position);
        button.setFillColor(sf::Color::White);
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::Black);

        // Set up the text for the button
        selectedText.setFont(font);
        selectedText.setCharacterSize(23);
        selectedText.setFillColor(sf::Color::Black);
        selectedText.setPosition(position.x + 10, position.y);
        
        if (!options.empty()) {
            selectedText.setString(options[0]); // Default to the first option
            selectedIndex = 0;
        }

        // Set up the dropdown options
        for (size_t i = 0; i < options.size(); ++i) {
            sf::RectangleShape option;
            option.setSize(sf::Vector2f(width, height));
            option.setPosition(position.x, position.y + height * (i + 1));
            option.setFillColor(sf::Color::White);
            option.setOutlineThickness(2);
            option.setOutlineColor(sf::Color::Black);
            optionTexts.push_back(option);

            sf::Text text;
            text.setFont(font);
            text.setString(options[i]);
            text.setCharacterSize(23);
            text.setFillColor(sf::Color::Black);
            text.setPosition(position.x + 10, position.y + height * (i + 1));
            optionTextsDisplay.push_back(text);
        }
    }

    void update(const sf::Vector2f& mousePos) {
        if (isOpen) {
            for (auto &option : optionTexts) {
                bool isHovered = option.getGlobalBounds().contains(mousePos);
                option.setFillColor(isHovered ? sf::Color(211, 211, 211) : sf::Color::White);
            }
        }
        else {
            bool isHovered = button.getGlobalBounds().contains(mousePos);
            button.setFillColor(isHovered ? sf::Color(211, 211, 211) : sf::Color::White);
        }
    }

    bool isOpened() const {
        return isOpen;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(button);
        window.draw(selectedText);

        if (isOpen) {
            for (size_t i = 0; i < options.size(); ++i) {
                window.draw(optionTexts[i]);
                window.draw(optionTextsDisplay[i]);
            }
        }
    }

    void toggle() {
        isOpen = !isOpen;
    }

    sf::Vector2f getPosition() const {
        return button.getPosition();
    }

    void setOptions(const std::vector<std::string>& newOptions) {
        options = newOptions;
        optionTextsDisplay.clear();
        optionTexts.clear();
        for (size_t i = 0; i < options.size(); ++i) {
            sf::RectangleShape option;
            option.setSize(sf::Vector2f(button.getLocalBounds().width, button.getLocalBounds().height));
            option.setPosition(button.getPosition().x, button.getPosition().y + button.getLocalBounds().height * (i + 1));
            option.setFillColor(sf::Color::White);
            option.setOutlineThickness(2);
            option.setOutlineColor(sf::Color::Black);
            optionTexts.push_back(option);

            sf::Text text;
            text.setFont(_font);
            text.setString(options[i]);
            text.setCharacterSize(23);
            text.setFillColor(sf::Color::Black);
            text.setPosition(button.getPosition().x + 10, button.getPosition().y + button.getLocalBounds().height * (i + 1));
            optionTextsDisplay.push_back(text);
        }
        selectedIndex = 0;
        selectedText.setString(options[0]);
    }

    bool isMouseOver(const sf::Vector2i& mousePos) const {
        return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

    void handleClick(const sf::Vector2f& mousePos) {
        if (button.getGlobalBounds().contains(mousePos)) {
            toggle();
        }

        if (isOpen) {
            for (size_t i = 0; i < optionTexts.size(); ++i) {
                if (optionTexts[i].getGlobalBounds().contains(mousePos)) {
                    selectedIndex = static_cast<int>(i);
                    selectedText.setString(options[selectedIndex]);
                    isOpen = false; // Close the dropdown after selection
                }
            }
        }
    }

    std::string getSelectedText() const {
        return options[selectedIndex];
    }

private:
    sf::Font& _font;
    sf::RectangleShape button;
    std::vector<sf::RectangleShape> optionTexts;
    std::vector<sf::Text> optionTextsDisplay;
    sf::Text selectedText;
    std::vector<std::string> options;
    bool isOpen;
    int selectedIndex;
};
