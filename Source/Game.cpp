#include "../Headers/Game.h"

template<const unsigned short T>
std::array<sf::Vector2f, 2> Game<T>::healthTextPos = {sf::Vector2f{25.f, 75.f}, sf::Vector2f{860.f, 75.f}};

template<const unsigned short T>
std::array<sf::Vector2f, 2> Game<T>::scoreTextPos = {sf::Vector2f{25.f, 25.f}, sf::Vector2f{860.f, 25.f}};

template<const unsigned short T>
Game<T>::Game() : window(sf::RenderWindow(sf::VideoMode(1044, 585), "Poor Bunny!", sf::Style::Titlebar | sf::Style::Close)),
                      currentArrow{window, "./Arrow.png"},
                      currentCarrot{window, 1, "./Carrot.png"}, goldenCarrot{window, "./GoldenCarrot.png"},
                      lost(false), pause(false), choices({0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2})  {
    for (int i = 0; i < T; i += 1) {
        players[i] = Player(window, "./Iepuri" + std::to_string(i) + ".png");
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

    for (int i = 0; i < T; i += 1) {
        currentHealths[i].setFont(font);
        currentHealths[i].setCharacterSize(30.f);
        currentHealths[i].setFillColor(sf::Color::Red);
        currentHealths[i].setPosition(healthTextPos[i]);

        currentScores[i].setFont(font);
        currentScores[i].setCharacterSize(30.f);
        currentScores[i].setFillColor(sf::Color::Black);
        currentScores[i].setPosition(scoreTextPos[i]);
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

    std::string aux;

    for (int i = 0; i < T; i += 1) {
        int temp = static_cast<int>(players[i].getHealth() * 10);
        if (temp % 10 == 0) {
            aux = std::to_string(temp / 10);
        } else {
            aux = std::to_string(temp / 10) + "." + std::to_string(temp % 10);
        }

        currentScores[i].setString("Score:  " + std::to_string(players[i].getScore()));
        currentHealths[i].setString("Health: " + aux);

        window.draw(currentScores[i]);
        window.draw(currentHealths[i]);
    }

    if (!pause) {
        for (int i = 0; i < T; i += 1) {
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

template<const unsigned short T>
void Game<T>::reset() {
    lost = false;

    for (int i = 0; i < T; i += 1) {
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

    int maxim = players[0].getScore();
    for (int i = 1; i < T; i += 1) {
        if (maxim > players[i].getScore()) {
            maxim = players[i].getScore();
        }
    }

    lose.setString("Score:  " + std::to_string(maxim));
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
            if (timer.getElapsedTime().asSeconds() >= 4.f && !choices.empty()) {
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
                if (checkCollision(players[i], currentCarrot)) {
                    players[i].increaseScore(currentCarrot.getScore());
                    currentCarrot.resetCoordinates(window);

                    //std::cout << "Score: " << player.getScore() << '\n';
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
                        lost = true;
                    }

                    //std::cout << "Health: " << player.getHealth() << '\n';
                }

                for (auto& elem : traps) {
                    if (checkCollision(players[i], static_cast<const Thing&>(*elem))) {
                        if (!elem->getHasCollided(i)) {
                            players[i].decreaseHealth(elem->getDamage());
                            elem->setHasCollided(i, true);

                            if (players[i].getHealth() <= 0) {
                                lost = true;
                            }

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


        players = oth.players;

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



