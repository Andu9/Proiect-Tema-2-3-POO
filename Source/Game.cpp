#include "../Headers/Game.h"

Game::Game() : window{sf::VideoMode(1044, 585), "Poor Bunny!", sf::Style::Titlebar | sf::Style::Close},
               player{window, "./Iepuri.png"}, currentArrow{window, "./Arrow.png"},
               currentCarrot{window, 1, "./Carrot.png"}, goldenCarrot{window, "./GoldenCarrot.png"},
               lost(false), pause(false), choices({0, 0, 0, 0, 0, 0, 1, 1, 1})  {
    texture.loadFromFile("./Background.jpg");
    background.setTexture(texture);
    background.setPosition(0, 0);
    window.setFramerateLimit(60);

    font.loadFromFile("./yoster.ttf");

    currentHealth.setFont(font);
    currentHealth.setCharacterSize(30.f);
    currentHealth.setFillColor(sf::Color::Red);
    currentHealth.setPosition(25.f, 75.f);

    currentScore.setFont(font);
    currentScore.setCharacterSize(30.f);
    currentScore.setFillColor(sf::Color::Black);
    currentScore.setPosition(25.f, 25.f);

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
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> gen(0, Maxim);
    return gen(eng);
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

    std::string aux = "";
    int temp = player.getHealth() * 10;
    if (temp % 10 == 0) {
        aux = std::to_string(temp / 10);
    } else {
        aux = std::to_string(temp / 10) + "." + std::to_string(temp % 10);
    }

    currentScore.setString("Score:  " + std::to_string(player.getScore()));
    currentHealth.setString("Health: " + aux);

    window.draw(currentScore);
    window.draw(currentHealth);

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

void Game::reset() {
    lost = false;
    choices = {0, 0, 0, 0, 0, 0, 1, 1, 1};

    player = Player{window, "./Iepuri.png"};
    player.initTextures("./Iepuri.png");

    currentArrow = Arrow{window, "./Arrow.png"};
    currentArrow.initTextures("./Arrow.png");

    currentCarrot = Carrot{window, 1, "./Carrot.png"};
    currentCarrot.initTextures("./Carrot.png");

    goldenCarrot = GoldenCarrot{window, "./GoldenCarrot.png"};
    goldenCarrot.initTextures("./GoldenCarrot.png");
    traps.clear();
}

void Game::drawLost() {
    static int sec = totalTimer.getElapsedTime().asSeconds();

    sf::Text youLost, timeSpent, lose;
    youLost.setCharacterSize(100.f);
    youLost.setFont(font);
    youLost.setString("You lost : (");
    youLost.setFillColor(sf::Color::Black);
    youLost.setPosition(200.f, 150.f);

    lose.setCharacterSize(50.f);
    lose.setFont(font);
    lose.setString("Score:  " + std::to_string(player.getScore()));
    lose.setFillColor(sf::Color::Black);
    lose.setPosition(250.f, 300.f);

    timeSpent.setString("Time: " + std::to_string(sec));
    timeSpent.setCharacterSize(50.f);
    timeSpent.setFillColor(sf::Color::Black);
    timeSpent.setFont(font);
    timeSpent.setPosition(550.f, 300.f);

    window.draw(background);
    window.draw(lose);
    window.draw(youLost);
    window.draw(timeSpent);

    sf::RectangleShape escape, playAgain;

    escape.setSize(sf::Vector2f{100.f, 70.f}), playAgain.setSize(sf::Vector2f{100.f, 70.f});
    escape.setFillColor(sf::Color::Red), playAgain.setFillColor(sf::Color::Green);
    escape.setOutlineColor(sf::Color::Black), playAgain.setOutlineColor(sf::Color::Black);
    escape.setOutlineThickness(4.f), playAgain.setOutlineThickness(4.f);
    escape.setPosition(300.f, 400.f), playAgain.setPosition(600.f, 400.f);

    sf::Text leave, play;
    leave.setFont(font), play.setFont(font);
    leave.setFillColor(sf::Color::Black), play.setFillColor(sf::Color::Black);
    leave.setOutlineColor(sf::Color::White), play.setOutlineColor(sf::Color::White);
    leave.setOutlineThickness(3.f), play.setOutlineThickness(3.f);
    leave.setCharacterSize(10.f), play.setCharacterSize(10.f);
    leave.setPosition(330.f, 380.f), play.setPosition(630.f, 380.f);

    window.draw(escape), window.draw(playAgain);
    window.draw(leave), window.draw(play);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f posMouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (posMouse.x >= escape.getPosition().x && posMouse.x <= escape.getPosition().x + escape.getSize().x &&
            posMouse.y >= escape.getPosition().y && posMouse.y <= escape.getPosition().y + escape.getSize().y) {
            window.close();
        } else if (posMouse.x >= playAgain.getPosition().x && posMouse.x <= playAgain.getPosition().x + playAgain.getSize().x &&
                   posMouse.y >= playAgain.getPosition().y && posMouse.y <= playAgain.getPosition().y + playAgain.getSize().y) {
            this->reset();
            this->run();
        }
    }
}

void Game::drawPause() {
    sf::Text paused;
    paused.setCharacterSize(100.f);
    paused.setFont(font);
    paused.setString("Pause");
    paused.setFillColor(sf::Color::Black);
    paused.setPosition(350.f, 150.f);


    window.draw(background);
    window.draw(paused);


    sf::RectangleShape escape, playAgain;

    escape.setSize(sf::Vector2f{100.f, 70.f}), playAgain.setSize(sf::Vector2f{100.f, 70.f});
    escape.setFillColor(sf::Color::Red), playAgain.setFillColor(sf::Color::Green);
    escape.setOutlineColor(sf::Color::Black), playAgain.setOutlineColor(sf::Color::Black);
    escape.setOutlineThickness(4.f), playAgain.setOutlineThickness(4.f);
    escape.setPosition(300.f, 400.f), playAgain.setPosition(600.f, 400.f);

    sf::Text leave, play;
    leave.setFont(font), play.setFont(font);
    leave.setFillColor(sf::Color::Black), play.setFillColor(sf::Color::Black);
    leave.setOutlineColor(sf::Color::White), play.setOutlineColor(sf::Color::White);
    leave.setOutlineThickness(3.f), play.setOutlineThickness(3.f);
    leave.setCharacterSize(10.f), play.setCharacterSize(10.f);
    leave.setPosition(330.f, 380.f), play.setPosition(630.f, 380.f);

    window.draw(escape), window.draw(playAgain);
    window.draw(leave), window.draw(play);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f posMouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        if (posMouse.x >= escape.getPosition().x && posMouse.x <= escape.getPosition().x + escape.getSize().x &&
            posMouse.y >= escape.getPosition().y && posMouse.y <= escape.getPosition().y + escape.getSize().y) {
            window.close();
        } else if ((posMouse.x >= playAgain.getPosition().x && posMouse.x <= playAgain.getPosition().x + playAgain.getSize().x &&
                   posMouse.y >= playAgain.getPosition().y && posMouse.y <= playAgain.getPosition().y + playAgain.getSize().y) ||
                   sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            pause = false;
        }
    }
}

void Game::run() {
    timer.restart();
    totalTimer.restart();
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::P) {
                    pause = true;
                }
            }

        }

        window.clear();

        if (!lost && !pause) {
            if (timer.getElapsedTime().asSeconds() >= 7.f && !choices.empty()) {
                timer.restart();

                int index = getRandom(int(choices.size()) - 1);
                int trapType = choices[index];

                FiniteChoice *newTrap = nullptr;
                if (trapType == 0) {
                    newTrap = new CannonBall("./CannonBall.png");
                } else if (trapType == 1) {
                    newTrap = new SpikeyBall("./SpikeyBall.png");
                }

                newTrap->spawn();
                traps.emplace_back(newTrap);
                choices.erase(choices.begin() + index);
            }

            drawThings();

            if (player.checkCollision(currentCarrot)) {
                player.increaseScore(currentCarrot.getScore());
                currentCarrot.resetCoordinates(window);

                std::cout << "Score: " << player.getScore() << '\n';
            }

            if (player.checkCollision(goldenCarrot)) {
                player.increaseScore(goldenCarrot.getScore());
                goldenCarrot.isTaken();

                std::cout << "Score: " << player.getScore() << '\n';
            }

            if (player.checkCollision(currentArrow)) {
                player.decreaseHealth(currentArrow.getDamage());
                currentArrow.resetCoordinates(window);

                if (player.getHealth() <= 0) {
                    lost = true;
                }

                std::cout << "Health: " << player.getHealth() << '\n';
            }

            for (auto& elem : traps) {
                if (player.checkCollision(static_cast<const Thing&>(*elem))) {
                    if (elem->getHasCollided() == false) {
                        player.decreaseHealth(elem->getDamage());
                        elem->setHasCollided(true);

                        if (player.getHealth() <= 0) {
                            lost = true;
                        }

                        std::cout << "Health: " << player.getHealth() << '\n';
                    }
                } else {
                    elem->setHasCollided(false);
                }
            }
        } else if (lost) {
            drawLost();
        } else if (pause) {
            drawPause();
        }


        window.display();
    }
}

