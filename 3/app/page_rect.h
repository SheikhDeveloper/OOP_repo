#ifndef LAB3_APP_PAGE_RECT_H
#define LAB3_APP_PAGE_RECT_H

#include <SFML/Graphics.hpp>

class PageRect {
public:

    PageRect(sf::Vector2f pos = sf::Vector2f(0.5f, 0.5f), sf::Vector2f size = sf::Vector2f(0.5f, 0.5f)) {
        _rect.setPosition(pos);
        _rect.setSize(size);
        _rect.setFillColor(sf::Color(0, 0, 0, 128));
    }

    void draw(sf::RenderWindow &window) {
        window.draw(_rect);
    }

    void setPos(sf::Vector2f pos) {
        _rect.setPosition(pos);
    }

    sf::Vector2f getPos() {
        return _rect.getPosition();
    }

    sf::Vector2f getSize() {
        return _rect.getSize();
    }
    
private:
    sf::RectangleShape _rect;
};

#endif //LAB3_APP_PAGE_RECT_H
