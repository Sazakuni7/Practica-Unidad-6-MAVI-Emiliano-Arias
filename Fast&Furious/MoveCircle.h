#ifndef MOVECIRCLE_H
#define MOVECIRCLE_H

#include <SFML/Graphics.hpp>

class MoveCircle {
public:
    MoveCircle(float initialSpeed, float maxSpeed, float speedIncrement);

    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target);

private:
    sf::CircleShape circle;
    float speed;
    float maxSpeed;
    float speedIncrement;
};

#endif // MOVECIRCLE_H