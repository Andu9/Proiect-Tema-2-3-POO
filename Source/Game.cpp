#include "../Headers/Game.h"

template<const unsigned short T>
Game<T>::Game() : window(sf::RenderWindow(sf::VideoMode(1044, 585), "Poor Bunny!", sf::Style::Titlebar | sf::Style::Close)),
                      currentArrow{window, "./Arrow.png"},
                      currentCarrot{window, 1, "./Carrot.png"}, goldenCarrot{window, "./GoldenCarrot.png"},
                      lost(false), pause(false), choices({0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2})  {
    players[0] = std::make_shared<Player>(window, "./Iepuri.png");
    if constexpr (T == 2) {
        players[1] = std::make_shared<Player>(window, "./Iepuri2.png");
    }

    if (!texture.loadFromFile("./Background.jpg")) {
        throw MissingTexture("The texture was not found!\n");
    }
    background.setTexture(texture);
    background.setPosition(0, 0);
    window.setFramerateLimit(60);

    if (!font.loadFromFile("./yoster.ttf")) {
        throw MissingFont("The font was not found!\n");
    }

    currentHealths[0].setFont(font);
    currentHealths[0].setCharacterSize(30.f);
    currentHealths[0].setFillColor(sf::Color::Red);
    currentHealths[0].setPosition(25.f, 75.f);

    currentScores[0].setFont(font);
    currentScores[0].setCharacterSize(30.f);
    currentScores[0].setFillColor(sf::Color::Black);
    currentScores[0].setPosition(25.f, 25.f);

    if constexpr (T == 2) {
        currentHealths[1].setFont(font);
        currentHealths[1].setCharacterSize(30.f);
        currentHealths[1].setFillColor(sf::Color::Red);
        currentHealths[1].setPosition(860.f, 75.f);

        currentScores[1].setFont(font);
        currentScores[1].setCharacterSize(30.f);
        currentScores[1].setFillColor(sf::Color::Black);
        currentScores[1].setPosition(860.f, 25.f);
    }

    platforms[0] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{232, 358}, "SmallPlatform.png");
    platforms[1] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{467, 358}, "BigPlatform.png");
    platforms[2] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{763, 358}, "SmallPlatform.png");

    platforms[3] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{290, 237}, "BigPlatform.png");
    platforms[4] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{640, 237}, "BigPlatform.png");

    platforms[5] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{232, 120}, "SmallPlatform.png");
    platforms[6] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{468, 118}, "BigPlatform.png");
    platforms[7] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{762, 120}, "SmallPlatform.png");
}

template<const unsigned short T>
int Game<T>::getRandom(int Maxim) {
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<int> gen(0, Maxim);
    return gen(eng);
}

template<const unsigned short T>
void Game<T>::drawThings() {
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

    std::shared_ptr<Player> auxPlayer2 = nullptr;
    std::shared_ptr<Player> auxPlayer = std::dynamic_pointer_cast<Player>(players[0]);

    std::string aux;
    int temp = static_cast<int>(auxPlayer->getHealth() * 10);
    if (temp % 10 == 0) {
        aux = std::to_string(temp / 10);
    } else {
        aux = std::to_string(temp / 10) + "." + std::to_string(temp % 10);
    }

    currentScores[0].setString("Score:  " + std::to_string(auxPlayer->getScore()));
    currentHealths[0].setString("Health: " + aux);

    window.draw(currentScores[0]);
    window.draw(currentHealths[0]);

    if constexpr (T == 2) {
        auxPlayer2 = std::dynamic_pointer_cast<Player>(players[1]);
        temp = static_cast<int>(auxPlayer2->getHealth() * 10);
        if (temp % 10 == 0) {
            aux = std::to_string(temp / 10);
        } else {
            aux = std::to_string(temp / 10) + "." + std::to_string(temp % 10);
        }

        currentScores[1].setString("Score:  " + std::to_string(auxPlayer2->getScore()));
        currentHealths[1].setString("Health: " + aux);

        window.draw(currentScores[1]);
        window.draw(currentHealths[1]);
    }

    if (!pause) {
        auxPlayer->move(window, platforms, 1);
        auxPlayer->setPosition();
        auxPlayer->draw(window);

        if constexpr (T == 2) {
            auxPlayer2 = std::dynamic_pointer_cast<Player>(players[1]);
            auxPlayer2->move(window, platforms, 2);
            auxPlayer2->setPosition();
            auxPlayer2->draw(window);
        }

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
}

template<const unsigned short T>
void Game<T>::reset() {
    lost = false;
    std::shared_ptr<Player> auxPlayer2 = nullptr;
    std::shared_ptr<Player> auxPlayer = std::dynamic_pointer_cast<Player>(players[0]);
    auxPlayer->setHealth(3);
    auxPlayer->setScore(3);

    if constexpr (T == 2) {
        auxPlayer2 = std::dynamic_pointer_cast<Player>(players[1]);
        auxPlayer2->setHealth(3), auxPlayer2->setScore(3);
    }

    choices = {0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2};


    players[0] = std::make_shared<Player>(window, "./Iepuri.png");
    auxPlayer->initTextures("./Iepuri.png");

    if constexpr (T == 2) {
        players[1] = std::make_shared<Player>(window, "./Iepuri2.png");
        auxPlayer2->initTextures("./Iepuri2.png");
    }

    currentArrow = Arrow{window, "./Arrow.png"};
    currentArrow.initTextures("./Arrow.png");

    currentCarrot = Carrot{window, 1, "./Carrot.png"};
    currentCarrot.initTextures("./Carrot.png");

    goldenCarrot = GoldenCarrot{window, "./GoldenCarrot.png"};
    goldenCarrot.initTextures("./GoldenCarrot.png");
    traps.clear();
}

template<const unsigned short T>
void Game<T>::drawLost() {
    static int sec = static_cast<int>(totalTimer.getElapsedTime().asSeconds());

    sf::Text youLost, timeSpent, lose;
    youLost.setCharacterSize(100.f);
    youLost.setFont(font);
    youLost.setString("You lost : (");
    youLost.setFillColor(sf::Color::Black);
    youLost.setPosition(200.f, 150.f);

    lose.setCharacterSize(50.f);
    lose.setFont(font);
    if constexpr (T == 1) {
        lose.setString("Score:  " + std::to_string(std::dynamic_pointer_cast<Player>(players[0])->getScore()));
    } else {
        std::shared_ptr auxPlayer = std::dynamic_pointer_cast<Player>(players[0]);
        std::shared_ptr auxPlayer2 = std::dynamic_pointer_cast<Player>(players[1]);

        int maximum = std::max(auxPlayer->getScore(), auxPlayer2->getScore());

        lose.setString("Score:  " + std::to_string(maximum));
    }
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
    leave.setString("Leave"), play.setString("Play again");
    leave.setFillColor(sf::Color::Black), play.setFillColor(sf::Color::Black);
    leave.setOutlineColor(sf::Color::White), play.setOutlineColor(sf::Color::White);
    leave.setOutlineThickness(2.f), play.setOutlineThickness(2.f);
    leave.setCharacterSize(20.f), play.setCharacterSize(15.f);
    leave.setPosition(318.f, 421.f), play.setPosition(608.f, 426.f);

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

template<const unsigned short T>
void Game<T>::drawPause() {
    drawThings();

    sf::Text paused;
    paused.setCharacterSize(100.f);
    paused.setFont(font);
    paused.setString("Pause");
    paused.setFillColor(sf::Color::Black);
    paused.setPosition(350.f, 150.f);

    window.draw(paused);

    sf::RectangleShape escape, playAgain;

    escape.setSize(sf::Vector2f{100.f, 70.f}), playAgain.setSize(sf::Vector2f{100.f, 70.f});
    escape.setFillColor(sf::Color::Red), playAgain.setFillColor(sf::Color::Green);
    escape.setOutlineColor(sf::Color::Black), playAgain.setOutlineColor(sf::Color::Black);
    escape.setOutlineThickness(4.f), playAgain.setOutlineThickness(4.f);
    escape.setPosition(300.f, 400.f), playAgain.setPosition(600.f, 400.f);

    sf::Text leave, play;
    leave.setFont(font), play.setFont(font);
    leave.setString("Leave"), play.setString("Resume");
    leave.setFillColor(sf::Color::Black), play.setFillColor(sf::Color::Black);
    leave.setOutlineColor(sf::Color::White), play.setOutlineColor(sf::Color::White);
    leave.setOutlineThickness(2.f), play.setOutlineThickness(2.f);
    leave.setCharacterSize(20.f), play.setCharacterSize(20.f);
    leave.setPosition(318.f, 421.f), play.setPosition(610.f, 421.f);

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

template<const unsigned short T>
void Game<T>::run() {
    timer.restart();
    totalTimer.restart();

    std::shared_ptr<Player> auxPlayer2 = nullptr;
    std::shared_ptr<Player> auxPlayer = dynamic_pointer_cast<Player>(players[0]);

    if constexpr (T == 2) {
        auxPlayer2 = std::dynamic_pointer_cast<Player>(players[1]);
    }

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
            if (timer.getElapsedTime().asSeconds() >= 8.f && !choices.empty()) {
                timer.restart();

                int index = getRandom(int(choices.size()) - 1);
                int trapType = choices[index];

                //std::cout << trapType << '\n';

                FiniteChoice *newTrap = nullptr;

                if (trapType == 0) {
                    newTrap = new CannonBall("./CannonBall.png");
                } else if (trapType == 1) {
                    newTrap = new SpikeyBall("./SpikeyBall.png");
                } else if (trapType == 2) {
                    newTrap = new Saw("./Saw.png");
                }

                newTrap->spawn();
                traps.emplace_back(newTrap);
                choices.erase(choices.begin() + index);

            }

            drawThings();

            if (checkCollision(*auxPlayer, currentCarrot)) {
                auxPlayer->increaseScore(currentCarrot.getScore());
                currentCarrot.resetCoordinates(window);

                //std::cout << "Score: " << player.getScore() << '\n';
            }

            if (checkCollision(*auxPlayer, goldenCarrot)) {
                auxPlayer->increaseHealth(1.f);
                auxPlayer->increaseScore(goldenCarrot.getScore());
                goldenCarrot.isTaken();

                //std::cout << "Score: " << player.getScore() << '\n';
            }

            if (checkCollision(*auxPlayer, currentArrow)) {
                auxPlayer->decreaseHealth(currentArrow.getDamage());
                currentArrow.resetCoordinates(window);

                if (auxPlayer->getHealth() <= 0) {
                    lost = true;
                }

                //std::cout << "Health: " << player.getHealth() << '\n';
            }

            for (auto& elem : traps) {
                if (checkCollision(*auxPlayer, static_cast<const Thing&>(*elem))) {
                    if (!elem->getHasCollided(1)) {
                        auxPlayer->decreaseHealth(elem->getDamage());
                        elem->setHasCollided(1, true);

                        if (auxPlayer->getHealth() <= 0) {
                            lost = true;
                        }

                        std::cout << "Health: " << players[0]->getHealth() << '\n';
                    }
                } else {
                    elem->setHasCollided(1, false);
                }
            }

            if constexpr (T == 2) {
                if (checkCollision(*auxPlayer2, currentCarrot)) {
                    auxPlayer2->increaseScore(currentCarrot.getScore());
                    currentCarrot.resetCoordinates(window);

                    //std::cout << "Score: " << player.getScore() << '\n';
                }

                if (checkCollision(*auxPlayer2, goldenCarrot)) {
                    auxPlayer2->increaseHealth(1.f);
                    auxPlayer2->increaseScore(goldenCarrot.getScore());
                    goldenCarrot.isTaken();

                    //std::cout << "Score: " << player.getScore() << '\n';
                }

                if (checkCollision(*auxPlayer2, currentArrow)) {
                    auxPlayer2->decreaseHealth(currentArrow.getDamage());
                    currentArrow.resetCoordinates(window);

                    if (auxPlayer2->getHealth() <= 0) {
                        lost = true;
                    }

                    //std::cout << "Health: " << player.getHealth() << '\n';
                }

                for (auto& elem : traps) {
                    if (checkCollision(*auxPlayer2, static_cast<const Thing&>(*elem))) {
                        if (!elem->getHasCollided(2)) {
                            auxPlayer2->decreaseHealth(elem->getDamage());
                            elem->setHasCollided(2, true);

                            if (auxPlayer2->getHealth() <= 0) {
                                lost = true;
                            }

                            //std::cout << "Health: " << player.getHealth() << '\n';
                        }
                    } else {
                        elem->setHasCollided(2, false);
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


template<const unsigned short T>
Game<T>& Game<T>::operator=(const Game& oth) {
    if (this != &oth) {
        texture = oth.texture;
        background = oth.background;
        font = oth.font;
        currentScores = oth.currentScores;
        currentHealths = oth.currentHealths;
        currentArrow = oth.currentArrow;
        currentCarrot = oth.currentCarrot;
        goldenCarrot = oth.goldenCarrot;
        lost = oth.lost;
        pause = oth.pause;
        timer = oth.timer;
        totalTimer = oth.totalTimer;
        choices = oth.choices;


        for (int i = 0; i < (int) oth.players.size(); i += 1) {
            if (oth.players[i] != nullptr) {
                players[i] = std::make_shared<Player>(*oth.players[i]);
            } else {
                players[i] = nullptr;
            }
        }

        traps.shrink_to_fit();
        for (auto& trap : oth.traps) {
            traps.push_back(trap->clone());
        }

        platforms = oth.platforms;
    }
    return *this;
}

template<const unsigned short T>
void Game<T>::close() {
    window.close();
}

template<const unsigned short T>
Game<T>::~Game() {
    traps.shrink_to_fit();
}

template class Game<1>;
template class Game<2>;

