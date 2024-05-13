#include "GoldenCarrot.h"
#include "Player.h"
#include "Collision.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(1044, 585), "Poor bunny!", sf::Style::Default);
    Player player{window};
    window.setFramerateLimit(60);

    Carrot currentCarrot(window, 1);
    GoldenCarrot goldenCarrot(window);

    std::array<Thing, 8> platforms;

    platforms[0] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{225, 358});
    platforms[1] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{472, 358});
    platforms[2] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{757, 358});

    platforms[3] = Thing(sf::Vector2f{115, 27}, sf::Vector2f{290, 237});
    platforms[4] = Thing(sf::Vector2f{115, 27}, sf::Vector2f{640, 237});

    platforms[5] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{225, 114});
    platforms[6] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{472, 114});
    platforms[7] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{757, 114});

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

        player.move(window, platforms);
        player.setPosition();

        window.clear();
        player.draw(window);

        for (auto& platform: platforms) {
            platform.setPosition();
            platform.draw(window);
        }

        currentCarrot.setPosition();
        currentCarrot.draw(window);

        goldenCarrot.setPosition();
        goldenCarrot.draw(window);

        if (player.checkCollision(currentCarrot)) {
            player.increaseScore(currentCarrot.getScore());
            currentCarrot.resetCoordinates(window);

            std::cout << player.getScore() << '\n';
        }

        if (player.checkCollision(goldenCarrot)) {
            player.increaseScore(goldenCarrot.getScore());
            goldenCarrot.isTaken();

            std::cout << player.getScore() << '\n';
        }


        window.display();
    }
    return 0;
}

