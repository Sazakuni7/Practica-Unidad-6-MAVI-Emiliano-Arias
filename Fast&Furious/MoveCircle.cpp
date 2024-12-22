#include "MoveCircle.h"

MoveCircle::MoveCircle(float initialSpeed, float maxSpeed, float speedIncrement)
    : speed(initialSpeed), maxSpeed(maxSpeed), speedIncrement(speedIncrement) {
    circle.setRadius(20.0f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(0,0);
}

void MoveCircle::update(float deltaTime, const sf::RenderWindow& window) {
    sf::Vector2f position = circle.getPosition(); //Obtener la posicion actual del circulo
    position.x += speed * deltaTime; //Incrementar la posicion horizontal en funcion a la velocidad por el tiempo transcurrido desde el ultimo deltaTime

    if (position.x - circle.getRadius() > window.getSize().x) { //Si el borde izquierdo del circulo es mayor que el ancho de la ventana, significa que salió de los limites
        position.x = -circle.getRadius(); //Se reposiciona el circulo al borde izquierdo de la ventana
        speed = std::min(speed + speedIncrement, maxSpeed);   //Se incrementa la velocidad sin que exceda maxSpeed
    }
    if (position.y == 0) { //Verificar si la posicion vertical no ha sido ajustada aun
        position.y = window.getSize().y / 2.0f - circle.getRadius();  //Centrar el circulo en la ventana
    }
    circle.setPosition(position);
}

void MoveCircle::draw(sf::RenderTarget& target) {
    target.draw(circle);
}