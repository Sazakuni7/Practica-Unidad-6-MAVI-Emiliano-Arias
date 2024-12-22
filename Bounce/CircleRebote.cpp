#include "CircleRebote.h"

CircleRebote::CircleRebote() {
    circle.setRadius(20.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(400.0f, 50.0f);

    speed = { 0.0f, 0.0f };
    gravity = 2000.0f; //Aceleraci�n gravitatoria en p�xeles/seg�
    reboteFactor = 0.8f; //Rebote al 80% de la velocidad de ca�da
    nivelSuelo = 580.0f; //Altura del suelo, margen de 20px por el radio
}

void CircleRebote::update(float deltaTime, const sf::RenderWindow& window) {
    speed.y += gravity * deltaTime;    //Aplicar gravedad

    sf::Vector2f position = circle.getPosition();  
    position.y += speed.y * deltaTime; //Actualizar posici�n

    if (position.y + circle.getRadius() > nivelSuelo) {  //Detectar colisi�n con el suelo
        position.y = nivelSuelo - circle.getRadius(); //Ajustar al suelo
        speed.y = -speed.y * reboteFactor; //Invertir direcci�n y aplicar factor de rebote

       
        if (std::abs(speed.y) < 50.0f) {  //Evitar que el rebote sea demasiado peque�o, y si lo es, detener movimiento
            speed.y = 0.0f;
        }
    }

    circle.setPosition(position);
}

void CircleRebote::draw(sf::RenderTarget& target) {
    target.draw(circle);
}