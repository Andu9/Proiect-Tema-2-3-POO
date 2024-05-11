#include "Player.h"
#include "Collision.h"
#include "Platform.h"

#include <vector>
#include <ctime>

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(400, 600), "Poor bunny!", sf::Style::Default);
    Player player{window};
    window.setFramerateLimit(60);

    const int SIZE = 20;
    static const float gravity = 1.f;



    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        player.move(window);
        player.setPosition();

        window.clear();
        player.draw(window);

        window.display();
    }
    return 0;
}

