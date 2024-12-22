#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>

class InputField {
public:
    InputField(float x, float y, float width, float height);

    void handleEvent(const sf::Event& event);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    std::string getUserInput() {
        return _inputString;
    }

    void setPosition(float x, float y) {
        _box.setPosition(x, y);
        _text.setPosition(x + 5, y);
    }

    void setSize(float width, float height) {
        _box.setSize(sf::Vector2f(width, height));
    }

    sf::Vector2f getPosition() {
        return _box.getPosition();
    }

    sf::Vector2f getSize() {
        return _box.getSize();
    }

    ~InputField() = default;

private:
    void updateCursorPosition() {
        // Update cursor position based on text length
        float textWidth = _text.getGlobalBounds().width;
        _cursor.setPosition(_box.getPosition().x + 5 + textWidth, _box.getPosition().y + 5);
    }

    sf::RectangleShape _box;       // Input box shape
    sf::Text _text;                // Text display
    sf::Font _font;                // Font for the text
    sf::RectangleShape _cursor;    // Cursor shape
    std::string _inputString;      // String to hold user input
    bool _isFocused;               // Focus state of the input field
    bool blinkCursor;             // State of the blinking cursor
    bool isActive;                // State of the input field
    float blinkTimer;             // Timer for cursor blinking};
};
