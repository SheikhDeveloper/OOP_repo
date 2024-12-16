#ifndef LAB3_APP_CLOUD_H
#define LAB3_APP_CLOUD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Cloud {
public:
    Cloud(const sf::Texture& texture, float x, float y) {
        sprite.setTexture(texture);
        sprite.setPosition(x, y);
        sprite.setScale(0.05f, 0.05f); // Scale down the cloud if necessary
    }

    void update(float speed) {
        sprite.move(-speed, 0); // Move left
        if (sprite.getPosition().x + sprite.getGlobalBounds().width < 0) {
            // Reset position to the right side if it goes off-screen
            sprite.setPosition(1000, sprite.getPosition().y);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
};;

#endif //LAB3_APP_CLOUD_H
