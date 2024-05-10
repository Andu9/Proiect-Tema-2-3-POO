#include "Player.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poor bunny!", sf::Style::Default);
    Player player{window};

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left) {
                    player.moveHorizontal(-1.f);
                } else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                    player.moveHorizontal(1.f);
                } else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                    player.jump();
                }
            }
        }

        window.clear();
        player.draw(window);
        window.display();
    }
    return 0;
}