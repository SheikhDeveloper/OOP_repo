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
        return inputString;
    }

private:
    void updateCursorPosition() {
        // Update cursor position based on text length
        float textWidth = text.getGlobalBounds().width;
        cursor.setPosition(box.getPosition().x + 5 + textWidth, box.getPosition().y + 5);
    }

    sf::RectangleShape box;       // Input box shape
    sf::Text text;                // Text display
    sf::Font font;                // Font for the text
    sf::RectangleShape cursor;    // Cursor shape
    std::string inputString;      // String to hold user input
    bool isFocused;               // Focus state of the input field
    bool blinkCursor;             // State of the blinking cursor
    float blinkTimer;             // Timer for cursor blinking};
};
