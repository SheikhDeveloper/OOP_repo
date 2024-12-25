#ifndef LAB3_APP_BUTTON_H
#define LAB3_APP_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const std::string &text, float x, float y, int buttonWidth = 200, int buttonHeight = 50, 
            sf::Color color = sf::Color(0, 0, 0, 128)) {
        buttonShape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        buttonShape.setFillColor(color);
        buttonShape.setPosition(x, y);

        _font.loadFromFile("/home/sheikh/oop2024/3/app/fonts/arial.ttf");
        buttonText.setFont(_font);
        buttonText.setString(text);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(x + 20, y + 10);

        _isHovered = false;
    }

    Button(std::string &&text, float x, float y, int buttonWidth = 200, int buttonHeight = 50, 
            sf::Color color = sf::Color(0, 0, 0, 128)) {
        buttonShape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        buttonShape.setFillColor(color);
        buttonShape.setPosition(x, y);

        _font.loadFromFile("/home/sheikh/oop2024/3/app/fonts/arial.ttf"); // Load a font file
        buttonText.setFont(_font);
        buttonText.setString(text);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(x + 20, y + 10);

        _isHovered = false;
    }

    void update(const sf::Vector2f& mousePos) {
        _isHovered = buttonShape.getGlobalBounds().contains(mousePos);
        buttonShape.setFillColor(_isHovered ? sf::Color(255, 255, 255, 128) : sf::Color(0, 0, 0, 128));
        buttonText.setFillColor(_isHovered ? sf::Color::Black : sf::Color::White);
    }

    void setColor(sf::Color color) {
        buttonShape.setFillColor(color);
    }

    void setTextColor(sf::Color color) {
        buttonText.setFillColor(color);
    }

    void setPosition(float x, float y) {
        buttonShape.setPosition(x, y);
        buttonText.setPosition(x + 20, y + 10);
    }

    void setSize(sf::Vector2f size) {
        buttonShape.setSize(size);
    }

    sf::Vector2f getPosition() {
        return buttonShape.getPosition();
    }

    sf::FloatRect getGlobalBounds() {
        return buttonShape.getGlobalBounds();
    }

    sf::FloatRect getLocalBounds() {
        return buttonShape.getLocalBounds();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    bool isMouseOver(sf::Vector2i mousePos) {
        return buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
    }

private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    sf::Font _font;
    bool _isHovered;
};

#endif //LAB3_APP_BUTTON_H
