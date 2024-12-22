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
    sf::Vector2f delta = circle.getPosition() - other.circle.getPosition(); //Delta representa la diferencia de posiciones entre ambas pelotas
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y); //Distance la magnitud del vector
    float radiusSum = circle.getRadius() + other.circle.getRadius(); //Y radiusSum la suma de los radios de ambas pelotas

    if (distance < radiusSum) { //Comprueba si ambas pelotas estan chocando
        sf::Vector2f normal = delta / distance; //Permite determinar la direccion exacta del impacto de pelotas 
        sf::Vector2f relativeVelocity = velocity - other.velocity; //La diferencia de velocidades de ambas pelotas

        float speed = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y; //velocidad relativa en la direccion del impacto
        if (speed < 0) return; //Si no hay velocidad, las pelotas ya estan separadas, no hay que hacer ningun rebote
        float acumImpulso = 0.1f; //Aumentar la fuerza del rebote para simular un choque potente con la otra pelota
        float impulso = -(1 + acumImpulso) * speed; //calcular la magnitud en el cambio de velocidad 
        sf::Vector2f vectorImpulso = impulso * normal; //aplicar dicha magnitud a la direccion del impacto
        velocity -= vectorImpulso * 0.3f; //una pelota pierde velocidad en la direccion del impacto proporcional a ese valor
        other.velocity += vectorImpulso * 0.3f; //la otra gana velocidad

        float overlap = radiusSum - distance;  //Se usa este codigo para lograr que entre las pelotas no se enganchen o fusionen, que tengan ese margen de separación y por consiguiente reboten
        circle.setPosition(circle.getPosition() + normal * (overlap / 2.0f));
        other.circle.setPosition(other.circle.getPosition() - normal * (overlap / 2.0f));
    }
}
bool BallShooter::bolaActiva() const {
        return bounceCount >= maxBounces;
}
