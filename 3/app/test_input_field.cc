#include "input_field.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Input Field");

    InputField inputField(100, 100, 600, 50); // Create an input field

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            inputField.handleEvent(event); // Handle input for the input field
        }

        window.clear(sf::Color::White);
        inputField.draw(window); // Draw the input field
        window.display();
    }

    return 0;
}
