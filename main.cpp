#include "Headers/GoldenCarrot.h"
#include "Headers/Player.h"
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

    Saw b, c;
    b.spawn();
    c.spawn();

    std::cout << c.getPosition().x << ' ' << c.getPosition().y << '\n';
    std::cout << b.getPosition().x << ' ' << b.getPosition().y << '\n';

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

        for (auto& platform: platforms) {
            platform.setPosition();
            platform.draw(window);
        }

        currentArrow.move(window);
        currentArrow.setPosition();
        currentArrow.draw(window);

        a.move(window);
        a.setPosition();
        a.draw(window);

        b.move(window);
        b.setPosition();
        b.draw(window);

        c.move(window);
        c.setPosition();
        c.draw(window);

        player.move(window, platforms);
        player.setPosition();
        player.draw(window);

        currentCarrot.setPosition();
        currentCarrot.draw(window);

        goldenCarrot.setPosition();
        goldenCarrot.draw(window);

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

            std::cout << "Viata: " << player.getHealth() << '\n';
        }

        if (player.checkCollision(b)) {
            if (b.getHasCollided() == false) {
                player.decreaseHealth(b.getDamage());
                b.setHasCollided(true);

                if (player.getHealth() <= 0) {
                    window.close();
                }

                std::cout << "Viata: " << player.getHealth() << '\n';
            }
        } else {
            b.setHasCollided(false);
        }

        if (player.checkCollision(c)) {
            if (c.getHasCollided() == false) {
                player.decreaseHealth(c.getDamage());
                c.setHasCollided(true);

                if (player.getHealth() <= 0) {
                    window.close();
                }

                std::cout << "Viata: " << player.getHealth() << '\n';
            }
        } else {
            c.setHasCollided(false);
        }

        window.display();
    }
    return 0;
}

