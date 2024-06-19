#include "../Headers/Game.h"

template<unsigned short T>
int Game<T>::highScore = 0;

template<unsigned short T>
std::array<sf::Vector2f, 2> Game<T>::healthTextPos = {sf::Vector2f{25.f, 75.f}, sf::Vector2f{860.f, 75.f}};

template<unsigned short T>
std::array<sf::Vector2f, 2> Game<T>::scoreTextPos = {sf::Vector2f{25.f, 25.f}, sf::Vector2f{860.f, 25.f}};

template<unsigned short T>
[[maybe_unused]] Game<T>::Game(int _highScore) : window(sf::RenderWindow(sf::VideoMode(1044, 585), "Poor Bunny!", sf::Style::Titlebar | sf::Style::Close)),
                      currentArrow{window, "./Arrow.png"},
                      currentCarrot{window, 1, "./Carrot.png"}, goldenCarrot{window, "./GoldenCarrot.png"},
                      lost(false), pause(false), choices({0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2})  {
    for (int i = 0; i < T; i += 1) {
        players[i] = Player(window, "./Iepuri" + std::to_string(i) + ".png");
        isAlive[i] = true;
    }

    highScore = _highScore;

    if (!texture.loadFromFile("./Background.jpg")) {
        throw MissingTexture("The texture was not found!\n");
    }
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

template<unsigned short T>
int Game<T>::sum() {
    int res = 0;
    for (auto & it : isAlive) {
        res += it.second;

    }
    return res;
}

template<unsigned short T>
int Game<T>::getRandom(int Maxim) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> gen(0, Maxim);
    return gen(eng);
}

template<unsigned short T>
void Game<T>::drawThings() {
    window.draw(background);

    TextBuilder builder;
    std::string aux;
    for (int i = 0; i < T; i += 1) {
        int temp = static_cast<int>(players[i].getHealth() * 10);

        if (temp <= 0) { temp = 0; }

        if (temp % 10 == 0) {
            aux = std::to_string(temp / 10);
        } else {
            aux = std::to_string(temp / 10) + "." + std::to_string(temp % 10);
        }

        currentHealths[i] = builder.setFont().setSize(30.f).setCol(sf::Color::Red).setPos(healthTextPos[i]).setString("Health: " + aux).build();
        currentScores[i] = builder.setFont().setSize(30.f).setCol(sf::Color::Black).setPos(scoreTextPos[i]).setString("Score:  " + std::to_string(players[i].getScore())).build();

        window.draw(currentHealths[i].getText());
        window.draw(currentScores[i].getText());
    }

    for (int i = 0; i < 8; i += 1) {
        if (i == 1 || i == 3 || i == 4 || i == 6) {
            platforms[i].initTextures("./BigPlatform.png");
        } else {
            platforms[i].initTextures("./SmallPlatform.png");
        }
        platforms[i].setPosition();
        platforms[i].draw(window);
    }


    if (!pause) {
        for (int i = 0; i < T; i += 1) {
            if (!isAlive[i]) {
                continue;
            }

            players[i].initTextures("./Iepuri" + std::to_string(i) + ".png");
            players[i].move(window, platforms, i);
            players[i].setPosition();
            players[i].draw(window);
        }

        currentArrow.move(window);
        currentArrow.setPosition();
        currentArrow.draw(window);

        for (auto& trap : traps) {
            if (auto e = std::dynamic_pointer_cast<CannonBall>(trap)) {
                if (checkCollision((*e), currentArrow)) {
                    currentArrow.resetCoordinates(window);
                }
            } else if (auto f = std::dynamic_pointer_cast<SpikeyBall>(trap)) {
                if (checkCollision((*f), currentArrow)) {
                    currentArrow.resetCoordinates(window);
                }
            }
            trap->move(window);
            trap->setPosition();
            trap->draw(window);
        }

        currentCarrot.setPosition();
        currentCarrot.draw(window);

        goldenCarrot.initTextures("./GoldenCarrot.png");
        goldenCarrot.setPosition();
        goldenCarrot.draw(window);
    }
}

template<unsigned short T>
void Game<T>::reset() {
    lost = false;

    for (int i = 0; i < T; i += 1) {
        isAlive[i] = true;
        players[i].reset(window, "./Iepuri" + std::to_string(i) + ".png");
    }

    choices = {0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2};

    currentArrow = Arrow{window, "./Arrow.png"};
    currentArrow.initTextures("./Arrow.png");

    currentCarrot = Carrot{window, 1, "./Carrot.png"};
    currentCarrot.initTextures("./Carrot.png");

    goldenCarrot = GoldenCarrot{window, "./GoldenCarrot.png"};
    goldenCarrot.initTextures("./GoldenCarrot.png");
    traps.clear();
}

template<unsigned short T>
void Game<T>::drawLost() {
    static int sec = static_cast<int>(totalTimer.getElapsedTime().asSeconds());

    int maxim = players[0].getScore(), winner = 0;
    for (int i = 1; i < T; i += 1) {
        if (maxim < players[i].getScore()) {
            maxim = players[i].getScore(), winner = i;
        }
    }

    Text youLost, timeSpent, lose;
    TextBuilder builder;

    const std::string text = T == 2 ? "Player " + std::to_string(winner + 1) + " won" : "You lost :(";
    youLost = builder.setSize(100.f).setFont().setCol(sf::Color::Black).setPos(200.f, 175.f).setString(text).build();
    lose = builder.setSize(50.f).setFont().setCol(sf::Color::Black).setPos(250.f, 300.f).setString("Score:  " + std::to_string(maxim)).setCol(sf::Color::Black).setPos(250.f, 300.f).build();
    timeSpent = builder.setSize(50.f).setFont().setString("Time: " + std::to_string(sec)).setSize(50.f).setCol(sf::Color::Black).setFont().setPos(550.f, 300.f).build();

    window.draw(background);
    window.draw(lose.getText());
    window.draw(youLost.getText());
    window.draw(timeSpent.getText());

    if (maxim > highScore) {
        highScore = maxim;
        std::ofstream fout("./highScore.txt"); fout << highScore;
    }

    Text highest;
    highest = builder.setSize(80.f).setFont().setCol(sf::Color::Red).setString("Highest score: " + std::to_string(highScore)).setPos(130.f, 80.f).build();
    window.draw(highest.getText());

    sf::RectangleShape escape, playAgain;

    escape.setSize(sf::Vector2f{100.f, 70.f}), playAgain.setSize(sf::Vector2f{100.f, 70.f});
    escape.setFillColor(sf::Color::Red), playAgain.setFillColor(sf::Color::Green);
    escape.setOutlineColor(sf::Color::Black), playAgain.setOutlineColor(sf::Color::Black);
    escape.setOutlineThickness(4.f), playAgain.setOutlineThickness(4.f);
    escape.setPosition(300.f, 400.f), playAgain.setPosition(600.f, 400.f);

    Text leave, play;
    leave = builder.setFont().setString("Leave").setCol(sf::Color::Black).setOutCol(sf::Color::White).setOutThick(2.f).setSize(20.f).setPos(318.f, 421.f).build();
    play = builder.setFont().setString("Play again").setCol(sf::Color::Black).setOutCol(sf::Color::White).setOutThick(2.f).setSize(15.f).setPos(608.f, 426.f).build();

    window.draw(escape), window.draw(playAgain);
    window.draw(leave.getText()), window.draw(play.getText());

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

template<unsigned short T>
void Game<T>::drawPause() {
    drawThings();

    Text paused;
    TextBuilder builder;
    paused = builder.setSize(100.f).setFont().setString("Pause").setCol(sf::Color::Black).setPos(350.f, 150.f).build();
    window.draw(paused.getText());

    sf::RectangleShape escape, playAgain;

    escape.setSize(sf::Vector2f{100.f, 70.f}), playAgain.setSize(sf::Vector2f{100.f, 70.f});
    escape.setFillColor(sf::Color::Red), playAgain.setFillColor(sf::Color::Green);
    escape.setOutlineColor(sf::Color::Black), playAgain.setOutlineColor(sf::Color::Black);
    escape.setOutlineThickness(4.f), playAgain.setOutlineThickness(4.f);
    escape.setPosition(300.f, 400.f), playAgain.setPosition(600.f, 400.f);

    Text leave, play;
    leave = builder.setFont().setString("Leave").setCol(sf::Color::Black).setOutCol(sf::Color::White).setOutThick(2.f).setSize(20.f).setPos(318.f, 421.f).build();
    play = builder.setFont().setString("Resume").setCol(sf::Color::Black).setOutCol(sf::Color::White).setOutThick(2.f).setSize(20.f).setPos(610.f, 421.f).build();

    window.draw(escape), window.draw(playAgain);
    window.draw(leave.getText()), window.draw(play.getText());

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

template<unsigned short T>
void Game<T>::run() {
    timer.restart();
    totalTimer.restart();

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::P || event.key.code == sf::Keyboard::Escape) {
                    pause = !pause;
                }
            }

        }

        window.clear();

        if (!lost && !pause) {
            if (timer.getElapsedTime().asSeconds() >= 7.f && !choices.empty()) {
                timer.restart();

                int index = getRandom(int(choices.size()) - 1);
                int trapType = choices[index];

                //std::cout << trapType << '\n';

                std::shared_ptr<FiniteChoice> newTrap = TrapFactory::getTrap(trapType);

                newTrap->spawn();
                traps.emplace_back(newTrap);
                choices.erase(choices.begin() + index);

            }

            drawThings();

            for (int i = 0; i < T; i += 1) {
                if (!isAlive[i]) {
                    continue;
                }

                if (checkCollision(players[i], currentCarrot)) {
                    players[i].increaseScore(currentCarrot.getScore());
                    currentCarrot.resetCoordinates(window);
                }

                if (checkCollision(players[i], goldenCarrot)) {
                    players[i].increaseHealth(1.f);
                    players[i].increaseScore(goldenCarrot.getScore());
                    goldenCarrot.isTaken();

                    //std::cout << "Score: " << player.getScore() << '\n';
                }

                if (checkCollision(players[i], currentArrow)) {
                    players[i].decreaseHealth(currentArrow.getDamage());
                    currentArrow.resetCoordinates(window);

                    if (players[i].getHealth() <= 0) {
                        isAlive[i] = false;
                    }

                    if (sum() == 0) { lost = true; }

                    std::cout << "Arrow Collision: " << players[i].getHealth() << '\n';
                }

                for (auto& elem : traps) {
                    if (checkCollision(players[i], static_cast<const Thing&>(*elem))) {
                        if (!elem->getHasCollided(i)) {
                            players[i].decreaseHealth(elem->getDamage());
                            elem->setHasCollided(i, true);

                            if (players[i].getHealth() <= 0) {
                                isAlive[i] = false;
                            }

                            if (sum() == 0) { lost = true; }

                            std::cout << "Health: " << i << " " << players[i].getHealth() << '\n';
                        }
                    } else {
                        elem->setHasCollided(i, false);
                    }
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

template<unsigned short T>
void Game<T>::close() {
    window.close();
}

template<unsigned short T>
Game<T>::~Game() {
    traps.shrink_to_fit();
}

template class Game<1>;
template class Game<2>;



