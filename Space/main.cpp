#include <SFML/Graphics.hpp>
#include "CircleVariable.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Aceleración de circulo");
    window.setFramerateLimit(60);

    CircleVariable circleVariable;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        circleVariable.update(deltaTime, window);

        window.clear();
        circleVariable.draw(window);
        window.display();
    }

    return 0;
}