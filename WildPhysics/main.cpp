#include <SFML/Graphics.hpp>
#include <vector>
#include "ballShooter.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Disparar pelotas");
    window.setFramerateLimit(60);

    std::vector<BallShooter> balls;
    sf::Clock spawnClock;
    sf::Clock clock;

    int score = 0;
    sf::Font font;
    font.loadFromFile("assets/fuente.ttf");
    sf::Text scoreText("Score: 0", font, 20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
                for (auto it = balls.begin(); it != balls.end(); ) {
                    if (it->getBounds().contains(clickPosition)) {
                        it = balls.erase(it);
                        score += 10;
                        scoreText.setString("Score: " + std::to_string(score));
                    }
                    else {
                        ++it;
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        //Spawnear bolas cada 1 segundo y como maximo 6 en pantalla
        if (spawnClock.getElapsedTime().asSeconds() > 0.8f && balls.size() < 6) {
            float radius = 25.0f;
            sf::Vector2f position(static_cast<float>(rand() % (window.getSize().x - static_cast<int>(radius * 2)) + radius), radius);
            sf::Vector2f velocity(static_cast<float>(rand() % 200 - 100), static_cast<float>(rand() % 200 - 100));
            balls.emplace_back(radius, position, velocity);
            spawnClock.restart();
        }

        //Actualizar, sumar puntaje al eliminar pelota
        for (auto it = balls.begin(); it != balls.end();) {
            it->update(deltaTime, window);
            if (it->bolaActiva()) {
                it = balls.erase(it);
                score -= 10;
                scoreText.setString("Score: " + std::to_string(score));
            }
            else {
                ++it;
            }
        }

        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                balls[i].rebotarEnPelota(balls[j]);
            }
        }

        window.clear();
        for (const auto& ball : balls) {
            ball.draw(window);
        }
        window.draw(scoreText);
        window.display();
    }
    return 0;
}
