#ifndef LAB3_APP_MISSILE_H
#define LAB3_APP_MISSILE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

class Missile {
public:
    Missile(const sf::Texture& texture, const sf::Vector2f& startPos, const sf::Vector2f& targetPos, const sf::Vector2f& targetSize)
        : target(targetPos), targetSize(targetSize), isExploding(false), explosionTime(0.f) {
        missileSprite.setTexture(texture);
        missileSprite.setPosition(startPos);
        missileSprite.setScale(0.08f, 0.08f);
        
        // Calculate direction
        direction = target - startPos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length; // Normalize
    }

    void update(float deltaTime) {
        if (!isExploding) {

            direction = target - missileSprite.getPosition();
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length; // Normalize

            // Move the missile towards the target
            missileSprite.move(direction * speed * deltaTime);

            // Check if the missile has reached the target
            if (std::abs(missileSprite.getPosition().x - target.x) < 5.0f &&
                std::abs(missileSprite.getPosition().y - target.y) < 5.0f) {
                isExploding = true; // Trigger explosion
            }
        } else {
            explosionTime += deltaTime;
            if (explosionTime > explosionDuration) {
                // Reset or remove the missile after explosion
                reset();
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        if (!isExploding) {
            window.draw(missileSprite);
        } else {
            drawExplosion(window);
        }
    }

    void setPosition(const sf::Vector2f& pos) {
        missileSprite.setPosition(pos);
    }

    void setTarget(const sf::Vector2f& targetPos, const sf::Vector2f& targetS) {
        target = targetPos;
        targetSize = targetS;
        direction = target - missileSprite.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction /= length;
    }

    sf::Vector2f getTarget() const {
        return target;
    }

    sf::Vector2f getTargetSize() const {
        return targetSize;
    }

    sf::Vector2f getPosition() const {
        return missileSprite.getPosition();
    }

private:
    void drawExplosion(sf::RenderWindow& window) {
        // Simple explosion effect (just a circle for demonstration)
        sf::CircleShape explosion(30.f);
        explosion.setFillColor(sf::Color::Yellow);
        explosion.setPosition(missileSprite.getPosition());
        explosion.setOrigin(explosion.getRadius(), explosion.getRadius());
        
        // Animate explosion size
        float scale = 1.f + (explosionTime / explosionDuration);
        explosion.setScale(scale, scale);
        
        window.draw(explosion);
    }

    void reset() {
        // Resetting the missile state (optional)
        isExploding = false;
        explosionTime = 0.f;
        // You can reposition or remove the missile as needed
    }

    sf::Sprite missileSprite;
    sf::Vector2f target;
    sf::Vector2f targetSize;
    sf::Vector2f direction;
    const float speed = 2.f; // Speed of the missile
    bool isExploding;
    float explosionTime;
    const float explosionDuration = 1.f;
};

#endif //LAB3_APP_MISSILE_H
