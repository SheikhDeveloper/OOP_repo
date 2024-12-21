#include <SFML/Graphics.hpp>

class ScrollableArea {
public:
    ScrollableArea(float width, float height) 
        : contentWidth(width), contentHeight(height) {
        // Create a large rectangle to represent the content
        content.setSize(sf::Vector2f(contentWidth, contentHeight));
        content.setFillColor(sf::Color(100, 150, 200)); // Light blue color
        content.setPosition(0, 0);
    }

    void handleScroll(float delta) {
        view.move(0, delta); // Move the view vertically
    }

    void draw(sf::RenderWindow& window) {
        window.setView(view);
        window.draw(content);
    }

    void setViewSize(float width, float height) {
        view.setSize(width, height);
        view.setCenter(width / 2, height / 2); // Center the view
    }

private:
    sf::RectangleShape content; // Represents the scrollable content
    float contentWidth;         // Total width of the content
    float contentHeight;        // Total height of the content
    sf::View view;             // The view for scrolling
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Scrollable Area");
    
    ScrollableArea scrollableArea(800, 1200); // Create a scrollable area with height greater than window height
    scrollableArea.setViewSize(800, 600);     // Set the view size to match the window size

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled) {
                scrollableArea.handleScroll(event.mouseWheelScroll.delta * 10); // Adjust scroll speed
            }
        }

        window.clear(sf::Color::White);
        scrollableArea.draw(window);
        window.display();
    }

    return 0;
}
