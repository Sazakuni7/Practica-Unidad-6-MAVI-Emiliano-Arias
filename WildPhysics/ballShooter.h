#ifndef BALLSHOOTER_H
#define BALLSHOOTER_H

#include <SFML/Graphics.hpp>
#include <vector>

class BallShooter {
public:
    BallShooter(float radius, sf::Vector2f position, sf::Vector2f velocity);

    void update(float deltaTime, const sf::RenderWindow& window);
    void draw(sf::RenderTarget& target) const;
    sf::FloatRect getBounds() const;

    void rebotarEnLimites(const sf::RenderWindow& window);
    void rebotarEnPelota(BallShooter& other);
    bool bolaActiva() const;
private:
    sf::CircleShape circle;
    sf::Vector2f velocity;
    static constexpr float gravity = 800.0f;
    static constexpr float bounceFactor = 0.8f;
    int bounceCount = 0;
    static constexpr int maxBounces = 2;
};

#endif // BALLSHOOTER_H