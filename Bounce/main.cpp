#include <SFML/Graphics.hpp>
#include "CircleRebote.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Rebote de circulo");
    window.setFramerateLimit(60);

    CircleRebote circleRebote;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        circleRebote.update(deltaTime, window);

        window.clear();
        circleRebote.draw(window);
        window.display();
    }

    return 0;
}