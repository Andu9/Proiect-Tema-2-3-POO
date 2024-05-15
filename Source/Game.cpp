#include "../Headers/Game.h"

Game::Game() : window{sf::VideoMode(1044, 585), "Poor Bunny!", sf::Style::Titlebar | sf::Style::Close},
               player{window, "./Iepuri.png"}, currentArrow{window, "./Arrow.png"},
               currentCarrot{window, 1, "./Carrot.png"}, goldenCarrot{window, "./GoldenCarrot.png"},
               lost(false), choices({0, 0, 0, 0, 0, 0, 1, 1, 1}) {
    texture.loadFromFile("./Background.jpg");
    background.setTexture(texture);
    background.setPosition(0, 0);
    window.setFramerateLimit(60);

    platforms[0] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{232, 358}, "SmallPlatform.png");
    platforms[1] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{467, 358}, "BigPlatform.png");
    platforms[2] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{763, 358}, "SmallPlatform.png");

    platforms[3] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{290, 237}, "BigPlatform.png");
    platforms[4] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{640, 237}, "BigPlatform.png");

    platforms[5] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{232, 120}, "SmallPlatform.png");
    platforms[6] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{468, 118}, "BigPlatform.png");
    platforms[7] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{762, 120}, "SmallPlatform.png");
}

int Game::getRandom(int Maxim) {
    if (Maxim > 0) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<int> gen(0, Maxim);
        return gen(eng);
    }
    return -1;
}

void Game::drawThings() {
    window.draw(background);

    for (int i = 0; i < 8; i += 1) {
        if (i == 1 || i == 3 || i == 4 || i == 6) {
            platforms[i].initTextures("./BigPlatform.png");
        } else {
            platforms[i].initTextures("./SmallPlatform.png");
        }
        platforms[i].setPosition();
        platforms[i].draw(window);
    }

    player.move(window, platforms);
    player.setPosition();
    player.draw(window);

    currentArrow.move(window);
    currentArrow.setPosition();
    currentArrow.draw(window);

    currentCarrot.setPosition();
    currentCarrot.draw(window);

    goldenCarrot.initTextures("./GoldenCarrot.png");
    goldenCarrot.setPosition();
    goldenCarrot.draw(window);

    for (auto& trap : traps) {
        trap->move(window);
        trap->setPosition();
        trap->draw(window);
    }
}

void Game::run() {
    timer.restart();
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.clear();

        if (!lost) {
            if (timer.getElapsedTime().asSeconds() >= 10.f) {
                int index = getRandom(choices.size());
                timer.restart();


                if (index != -1) {
                    int trapType = choices[index];
                    choices.erase(choices.begin() + index);


                    FiniteChoice * newTrap;
                    if (trapType == 0) {
                        newTrap = new CannonBall("./CannonBall.png");
                        newTrap->spawn();
                    } else if (trapType == 1) {
                        newTrap = new SpikeyBall("./SpikeyBall.png");
                        newTrap->spawn();
                    }

                    traps.emplace_back(newTrap);
                }
            }

            drawThings();

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
                    lost = true;
                }

                std::cout << "Viata: " << player.getHealth() << '\n';
            }
        } else {
            window.draw(background);
        }


        window.display();
    }
}

