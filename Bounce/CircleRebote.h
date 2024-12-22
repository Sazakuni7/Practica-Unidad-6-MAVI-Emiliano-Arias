#ifndef CIRCLEREBOTE_H
#define CIRCLEREBOTE_H

#include <SFML/Graphics.hpp>

class CircleRebote {
public:
    CircleRebote();

    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target);

private:
    sf::CircleShape circle;
    sf::Vector2f speed;
    float gravity;
    float reboteFactor;
    float nivelSuelo;
};

#endif // CIRCLEREBOTE_H