#include "input_field.h"

InputField::InputField(float x, float y, float width, float height) {
    // Set up the input box
    _box.setPosition(x, y);
    _box.setSize(sf::Vector2f(width, height));
    _box.setFillColor(sf::Color::White);
    _box.setOutlineThickness(2);
    _box.setOutlineColor(sf::Color::Black);

    // Load font
    if (!_font.loadFromFile("/home/sheikh/oop2024/3/app/fonts/arial.ttf")) { // Ensure you have a font file
        throw std::runtime_error("Failed to load font");
    }

    // Set up text properties
    _text.setFont(_font);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(24);
    _text.setPosition(x + 5, y); // Padding

    _cursor.setSize(sf::Vector2f(2, height - 10)); // Cursor width and height
    _cursor.setFillColor(sf::Color::Black);
    _cursor.setPosition(x + 5, y + 5); // Cursor position

    _isFocused = false;
    blinkCursor = true;
    blinkTimer = 0.0f;
}

void InputField::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (_box.getGlobalBounds().contains(mousePos)) {
                _isFocused = true;
            } else {
                _isFocused = false;
            }
        }
    }

    if (_isFocused && event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) { // ASCII range
            if (event.text.unicode == '\b') { // Handle backspace
                if (!_inputString.empty()) {
                    _inputString.pop_back();
                }
            } else {
                _inputString += static_cast<char>(event.text.unicode);
            }
            _text.setString(_inputString);
            updateCursorPosition();
        }
    }
}

void InputField::update(float deltaTime) {
    if (_isFocused) {
        blinkTimer += deltaTime;
        if (blinkTimer >= 0.5f) { // Blink every half second
            blinkCursor = !blinkCursor;
            blinkTimer = 0.0f;
        }
    }
}

void InputField::draw(sf::RenderWindow& window) {
    window.draw(_box);
    window.draw(_text);
    if (_isFocused && blinkCursor) {
        window.draw(_cursor);
    }
}
