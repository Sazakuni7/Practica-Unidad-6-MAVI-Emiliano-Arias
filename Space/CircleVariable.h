#ifndef CIRCLEVARIABLE_H
#define CIRCLEVARIABLE_H

#include <SFML/Graphics.hpp>

class CircleVariable {
public:
    CircleVariable();

    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target);
    void handleInput();

private:
    sf::CircleShape circle;
    sf::Vector2f speed;
    sf::Vector2f accel;
    float maxSpeed;
    float friction;
};

#endif // CIRCLEMOVER_H