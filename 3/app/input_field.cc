#include "input_field.h"

InputField::InputField(float x, float y, float width, float height) {
    // Set up the input box
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color::Black);

    // Load font
    if (!font.loadFromFile("./fonts/arial.ttf")) { // Ensure you have a font file
        throw std::runtime_error("Failed to load font");
    }

    // Set up text properties
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(x + 5, y + 5); // Padding

    cursor.setSize(sf::Vector2f(2, height - 10)); // Cursor width and height
    cursor.setFillColor(sf::Color::Black);
    cursor.setPosition(x + 5, y + 5); // Cursor position

    isFocused = false;
    blinkCursor = true;
    blinkTimer = 0.0f;
}

void InputField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (box.getGlobalBounds().contains(mousePos)) {
                isFocused = true;
            } else {
                isFocused = false;
            }
        }
    }

    if (isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) { // ASCII range
            if (event.text.unicode == '\b') { // Handle backspace
                if (!inputString.empty()) {
                    inputString.pop_back();
                }
            } else {
                inputString += static_cast<char>(event.text.unicode);
            }
            text.setString(inputString);
            updateCursorPosition();
        }
    }
}

void InputField::update(float deltaTime) {
    if (isFocused) {
        blinkTimer += deltaTime;
        if (blinkTimer >= 0.5f) { // Blink every half second
            blinkCursor = !blinkCursor;
            blinkTimer = 0.0f;
        }
    }
}

void InputField::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    if (isFocused && blinkCursor) {
        window.draw(cursor);
    }
}
