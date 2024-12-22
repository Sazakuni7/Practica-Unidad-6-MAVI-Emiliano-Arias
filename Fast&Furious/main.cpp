#include <SFML/Graphics.hpp>
#include "MoveCircle.h"

int main() {
    const float initialSpeed = 200.0f; //Velocidad inicial
    const float maxSpeed = 800.0f;    //Velocidad final
    const float speedIncrement = 100.0f; //Incremento de velocidad al salir de pantalla

    sf::RenderWindow window(sf::VideoMode(800, 600), "Movimiento de circulo");
    window.setFramerateLimit(60);

    MoveCircle moveCircle(initialSpeed, maxSpeed, speedIncrement);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        moveCircle.update(deltaTime, window);

        window.clear();
        moveCircle.draw(window);
        window.display();
    }

    return 0;
}