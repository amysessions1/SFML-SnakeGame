#include <iostream>
#include <SFML/Graphics.hpp>

#include "Snake.h"

using namespace sf;
using namespace std;

Snake::Snake() {
    _gridPos = Vector2f(1.f, 8.f);
    _body.setPosition(_gridPos * 37.f);
    _direction = 1;
    _body.setSize(Vector2f(37,37));
    _body.setFillColor(Color(0,128,128));
}

Snake::Snake( sf::Vector2f gridPos, int direction) {
    if (direction % 2 == 0) {
        gridPos.y -= (direction / 2);
    }
    else {
        gridPos.x += direction;
    }
    _gridPos = gridPos;
    _direction = direction;
    _body.setPosition(_gridPos * 37.f);
    _body.setSize(Vector2f(37.f,37.f));
    _body.setFillColor(Color(0,128,128));
}

Vector2f Snake::getGridPos() const {
    return _gridPos;
}

int Snake::getDirection() const {
    return _direction;
}

void Snake::setDirection(int newDir) {
    _direction = newDir;
}

void Snake::draw(RenderWindow& window) {
    _body.setPosition(_gridPos * 37.f);
    window.draw(_body);
}


