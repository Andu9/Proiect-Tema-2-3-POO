#include "Headers/GoldenCarrot.h"
#include "Headers/Player.h"
#include "Headers/Collision.h"
#include "Headers/Arrow.h"
#include "Headers/Cannonball.h"
#include "Headers/Saw.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(1044, 585), "Poor bunny!", sf::Style::Default);
    Player player{window};
    window.setFramerateLimit(60);

    Arrow currentArrow(window);

    Carrot currentCarrot(window, 1);
    GoldenCarrot goldenCarrot(window);

    std::array<Thing, 8> platforms;

    CannonBall a, x;
    a.spawn(), x.spawn();

    Saw b;
    b.spawn();

    Saw c;
    c.spawn();
    c.setPosition();

    std::cout << c.getSize().x << ' ' << c.getSize().y << '\n';

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

        window.clear();

        currentCarrot.setPosition();
        currentCarrot.draw(window);

        for (auto& platform: platforms) {
            platform.setPosition();
            platform.draw(window);
        }

        currentArrow.move(window);
        currentArrow.setPosition();
        currentArrow.draw(window);

        goldenCarrot.setPosition();
        goldenCarrot.draw(window);

        player.move(window, platforms);
        player.setPosition();
        player.draw(window);

        for (auto& platform: platforms) {
            platform.setPosition();
            platform.draw(window);
        }

        if (player.checkCollision(currentCarrot)) {
            player.increaseScore(currentCarrot.getScore());
            currentCarrot.resetCoordinates(window);

            std::cout << "Scor: " << player.getScore() << '\n';
        }

        if (player.checkCollision(goldenCarrot)) {
            player.increaseScore(goldenCarrot.getScore());
            goldenCarrot.isTaken();

            std::cout << "Scor: " << player.getScore() << '\n';
        }

        if (player.checkCollision(currentArrow)) {
            player.decreaseHealth(currentArrow.getDamage());
            currentArrow.resetCoordinates(window);

            if (player.getHealth() <= 0) {
                window.close();
            }

            std::cout << "Viata: " << player.getHealth() << '\n';
        }

        if (player.checkCollision(a)) {
            player.decreaseHealth(a.getDamage());
            a.resetCoordinates();

            if (player.getHealth() <= 0) {
                window.close();
            }
        }

        window.display();
    }
    return 0;
}

