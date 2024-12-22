#include "ballShooter.h"
#include <cmath>

BallShooter::BallShooter(float radius, sf::Vector2f position, sf::Vector2f velocity)
    : velocity(velocity) {
    circle.setRadius(radius);
    circle.setFillColor(sf::Color::Blue);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);
}

void BallShooter::update(float deltaTime, const sf::RenderWindow& window) {
    velocity.y += gravity * deltaTime; //Aplicar gravedad
    sf::Vector2f position = circle.getPosition();
    position += velocity * deltaTime;
    circle.setPosition(position);

    rebotarEnLimites(window);
}

void BallShooter::draw(sf::RenderTarget& target) const{
    target.draw(circle);
}

sf::FloatRect BallShooter::getBounds() const {
    return circle.getGlobalBounds();
}

void BallShooter::rebotarEnLimites(const sf::RenderWindow& window) {
    sf::Vector2f position = circle.getPosition();
    float radius = circle.getRadius();

    if (position.x - radius < 0) {
        velocity.x = std::abs(velocity.x);
        circle.setPosition(radius, position.y);//Corrección de posición
    }
    if (position.x + radius > window.getSize().x) {
        velocity.x = -velocity.x * bounceFactor;
        circle.setPosition(window.getSize().x - radius, position.y);
    }
    if (position.y + radius > window.getSize().y) {
       velocity.y = -velocity.y * bounceFactor; 
        circle.setPosition(position.x, window.getSize().y - radius);
        bounceCount++;
    }
    if (position.y - radius < 0) {
        velocity.y = std::abs(velocity.y);
        circle.setPosition(position.x, radius); 
    }
}

void BallShooter::rebotarEnPelota(BallShooter& other) {
    sf::Vector2f delta = circle.getPosition() - other.circle.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float radiusSum = circle.getRadius() + other.circle.getRadius();

    if (distance < radiusSum) {
        sf::Vector2f normal = delta / distance;
        sf::Vector2f relativeVelocity = velocity - other.velocity;

        float speed = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;
        if (speed < 0) return;
        float acumImpulso = 0.1f;
        float impulso = -(1 + acumImpulso) * speed;
        sf::Vector2f vectorImpulso = impulso * normal;
        velocity -= vectorImpulso * 0.3f;
        other.velocity += vectorImpulso * 0.3f;

        float overlap = radiusSum - distance;  //Se usa este codigo para lograr que entre las pelotas no se enganchen o fusionen, que tengan ese margen de separación y por consiguiente reboten
        circle.setPosition(circle.getPosition() + normal * (overlap / 2.0f));
        other.circle.setPosition(other.circle.getPosition() - normal * (overlap / 2.0f));
    }
}
bool BallShooter::bolaActiva() const {
        return bounceCount >= maxBounces;
}