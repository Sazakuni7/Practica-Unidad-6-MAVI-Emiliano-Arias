#include "CircleVariable.h"

CircleVariable::CircleVariable() {
    circle.setRadius(20.0f);
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(400.0f, 300.0f);

    speed = { 0.0f, 0.0f };
    accel = { 0.0f, 0.0f };
    maxSpeed = 500.0f;
    friction = 200.0f; //Reduce la velocidad gradualmente cuando no hay aceleración
}

void CircleVariable::handleInput() {  //Manejar teclas de dirección
    accel = { 0.0f, 0.0f };

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        accel.x = 500.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        accel.x = -500.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        accel.y = 500.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        accel.y = -500.0f;
    }
}

void CircleVariable::update(float deltaTime, const sf::RenderWindow& window) {
    handleInput();

    //Actualizar velocidad
    speed += accel * deltaTime;

    //Aplicar fricción
    if (accel.x == 0.0f) { //Verificar si no hay aceleracion activa en x
        speed.x -= friction * deltaTime * (speed.x > 0 ? 1 : -1); /*Calcular cuanta velocidad debe reducirse, la expresion "friction * deltatime" es la cantidad de velocidad
                                                                  que se resta por fotograma. la expresion "velocity.x > 0 ? 1 : -1" determina si la velocidad es positiva o negativa  
                                                                  Si es positiva, la friccion se resta normal. Si es negativa, la friccion se suma (porque es la direccion opuesta*/
        if (std::abs(speed.x) < friction * deltaTime) { //Esta condición evita que la velocidad siga reduciéndose indefinidamente en pasos muy pequeños
            speed.x = 0.0f;
        }
    }

    if (accel.y == 0.0f) { //Repetir para y
        speed.y -= friction * deltaTime * (speed.y > 0 ? 1 : -1);
        if (std::abs(speed.y) < friction * deltaTime) {
            speed.y = 0.0f;
        }
    }

    //Limitar la velocidad máxima
    if (std::sqrt(speed.x * speed.x + speed.y * speed.y) > maxSpeed) {
        float angle = std::atan2(speed.y, speed.x);
        speed.x = maxSpeed * std::cos(angle);
        speed.y = maxSpeed * std::sin(angle);
    }

    //Actualizar posición
    sf::Vector2f position = circle.getPosition();
    position += speed * deltaTime;

    //Mantener dentro de los límites de la ventana
    if (position.x - circle.getRadius() < 0) {
        position.x = circle.getRadius();
        speed.x = 0;
    }
    else if (position.x + circle.getRadius() > window.getSize().x) {
        position.x = window.getSize().x - circle.getRadius();
        speed.x = 0;
    }

    if (position.y - circle.getRadius() < 0) {
        position.y = circle.getRadius();
        speed.y = 0;
    }
    else if (position.y + circle.getRadius() > window.getSize().y) {
        position.y = window.getSize().y - circle.getRadius();
        speed.y = 0;
    }

    circle.setPosition(position);
}

void CircleVariable::draw(sf::RenderTarget& target) {
    target.draw(circle);
}