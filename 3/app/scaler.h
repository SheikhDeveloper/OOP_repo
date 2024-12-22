#ifndef LAB3_APP_SCALER_H
#define LAB3_APP_SCALER_H

#include <SFML/Graphics.hpp>
#include "button.h"

class Scaler {
public:
    Scaler(sf::Vector2f position, sf::Vector2f size) : _plusButton("+", position.x, position.y, size.x, size.y), 
    _minusButton("-", position.x, position.y, size.x, size.y) {}

private:
    Button _plusButton = Button("+", 0, 0, 0, 0);
    Button _minusButton = Button("-", 0, 0, 0, 0);
    int _delta = 1;
    int _count = 0;
};

#endif //LAB3_APP_SCALER_H
