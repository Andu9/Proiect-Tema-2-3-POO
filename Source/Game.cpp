#include "../Headers/Game.h"

Game::Game() : window(new sf::RenderWindow(sf::VideoMode(1044, 585), "Poor Bunny!", sf::Style::Titlebar | sf::Style::Close)),
                      currentArrow{*window, "./Arrow.png"},
                      currentCarrot{*window, 1, "./Carrot.png"}, goldenCarrot{*window, "./GoldenCarrot.png"},
                      lost(false), pause(false), choices({0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2})  {
    player = new Player(*window, "./Iepuri.png");

    if (!texture.loadFromFile("./Background.jpg")) {
        throw MissingTexture("The texture was not found!\n");
    }
    background.setTexture(texture);
    background.setPosition(0, 0);
    window->setFramerateLimit(60);

    if (!font.loadFromFile("./yoster.ttf")) {
        throw MissingFont("The font was not found!\n");
    }

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
    window->draw(background);

    for (int i = 0; i < 8; i += 1) {
        if (i == 1 || i == 3 || i == 4 || i == 6) {
            platforms[i].initTextures("./BigPlatform.png");
        } else {
            platforms[i].initTextures("./SmallPlatform.png");
        }
        platforms[i].setPosition();
        platforms[i].draw(*window);
    }

    Player * auxPlayer = dynamic_cast<Player*>(player);

    std::string aux = "";
    int temp = static_cast<int>(auxPlayer->getHealth() * 10);
    if (temp % 10 == 0) {
        aux = std::to_string(temp / 10);
    } else {
        aux = std::to_string(temp / 10) + "." + std::to_string(temp % 10);
    }

    currentScore.setString("Score:  " + std::to_string(auxPlayer->getScore()));
    currentHealth.setString("Health: " + aux);

    window->draw(currentScore);
    window->draw(currentHealth);

    auxPlayer->move(*window, platforms);
    auxPlayer->setPosition();
    auxPlayer->draw(*window);

    currentArrow.move(*window);
    currentArrow.setPosition();
    currentArrow.draw(*window);

    currentCarrot.setPosition();
    currentCarrot.draw(*window);

    goldenCarrot.initTextures("./GoldenCarrot.png");
    goldenCarrot.setPosition();
    goldenCarrot.draw(*window);

    for (auto& trap : traps) {
        trap->move(*window);
        trap->setPosition();
        trap->draw(*window);
    }
}

void Game::reset() {
    lost = false;
    Player * auxPlayer = dynamic_cast<Player*>(player);
    auxPlayer->setHealth(3);
    auxPlayer->setScore(3);
    choices = {0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2};

    delete player;
    player = new Player(*window, "./Iepuri.png");
    auxPlayer->initTextures("./Iepuri.png");

    currentArrow = Arrow{*window, "./Arrow.png"};
    currentArrow.initTextures("./Arrow.png");

    currentCarrot = Carrot{*window, 1, "./Carrot.png"};
    currentCarrot.initTextures("./Carrot.png");

    goldenCarrot = GoldenCarrot{*window, "./GoldenCarrot.png"};
    goldenCarrot.initTextures("./GoldenCarrot.png");
    traps.clear();
}

void Game::drawLost() {
    static int sec = static_cast<int>(totalTimer.getElapsedTime().asSeconds());

    sf::Text youLost, timeSpent, lose;
    youLost.setCharacterSize(100.f);
    youLost.setFont(font);
    youLost.setString("You lost : (");
    youLost.setFillColor(sf::Color::Black);
    youLost.setPosition(200.f, 150.f);

    lose.setCharacterSize(50.f);
    lose.setFont(font);
    lose.setString("Score:  " + std::to_string(dynamic_cast<Player*>(player)->getScore()));
    lose.setFillColor(sf::Color::Black);
    lose.setPosition(250.f, 300.f);

    timeSpent.setString("Time: " + std::to_string(sec));
    timeSpent.setCharacterSize(50.f);
    timeSpent.setFillColor(sf::Color::Black);
    timeSpent.setFont(font);
    timeSpent.setPosition(550.f, 300.f);

    window->draw(background);
    window->draw(lose);
    window->draw(youLost);
    window->draw(timeSpent);

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

    window->draw(escape), window->draw(playAgain);
    window->draw(leave), window->draw(play);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f posMouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
        if (posMouse.x >= escape.getPosition().x && posMouse.x <= escape.getPosition().x + escape.getSize().x &&
            posMouse.y >= escape.getPosition().y && posMouse.y <= escape.getPosition().y + escape.getSize().y) {
            window->close();
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


    window->draw(background);
    window->draw(paused);


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

    window->draw(escape), window->draw(playAgain);
    window->draw(leave), window->draw(play);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        sf::Vector2f posMouse = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*window));
        if (posMouse.x >= escape.getPosition().x && posMouse.x <= escape.getPosition().x + escape.getSize().x &&
            posMouse.y >= escape.getPosition().y && posMouse.y <= escape.getPosition().y + escape.getSize().y) {
            window->close();
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

    Player * auxPlayer = dynamic_cast<Player*>(player);

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::P) {
                    pause = true;
                }
            }

        }

        window->clear();

        if (!lost && !pause) {
            if (timer.getElapsedTime().asSeconds() >= 0.1f && !choices.empty()) {
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
                currentCarrot.resetCoordinates(*window);

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
                currentArrow.resetCoordinates(*window);

                if (auxPlayer->getHealth() <= 0) {
                    lost = true;
                }

                //std::cout << "Health: " << player.getHealth() << '\n';
            }

            for (auto& elem : traps) {
                if (checkCollision(*auxPlayer, static_cast<const Thing&>(*elem))) {
                    if (!elem->getHasCollided()) {
                        auxPlayer->decreaseHealth(elem->getDamage());
                        elem->setHasCollided(true);

                        if (auxPlayer->getHealth() <= 0) {
                            lost = true;
                        }

                        //std::cout << "Health: " << player.getHealth() << '\n';
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


        window->display();
    }
}

Game::Game(const Game& oth) :
          window(oth.window),
          texture(oth.texture),
          background(oth.background),
          font(oth.font),
          currentScore(oth.currentScore),
          currentHealth(oth.currentHealth),
          currentArrow(oth.currentArrow),
          currentCarrot(oth.currentCarrot),
          goldenCarrot(oth.goldenCarrot),
          lost(oth.lost),
          pause(oth.pause),
          timer(oth.timer),
          totalTimer(oth.totalTimer) {

    delete player;

    if (oth.player != nullptr) {
        player = new Thing(*oth.player);
    } else {
        player = nullptr;
    }

    platforms = oth.platforms;

    for (auto& trap : oth.traps) {
        traps.push_back(trap->clone());
    }

    choices = oth.choices;
}

Game& Game::operator=(const Game& oth) {
    if (this != &oth) {
        window = oth.window;
        texture = oth.texture;
        background = oth.background;
        font = oth.font;
        currentScore = oth.currentScore;
        currentHealth = oth.currentHealth;
        currentArrow = oth.currentArrow;
        currentCarrot = oth.currentCarrot;
        goldenCarrot = oth.goldenCarrot;
        lost = oth.lost;
        pause = oth.pause;
        timer = oth.timer;
        totalTimer = oth.totalTimer;
        choices = oth.choices;

        delete player;

        if (oth.player != nullptr) {
            player = new Thing(*oth.player);
        } else {
            player = nullptr;
        }

        for (auto& trap : traps) {
            delete trap;
        }
        traps.clear();
        for (auto& trap : oth.traps) {
            traps.push_back(trap->clone());
        }

        platforms = oth.platforms;
    }
    return *this;
}

void Game::close() {
    (*window).close();
}

Game::~Game() {
    delete player;
    delete window;
    for (int i = 0; i < (int) traps.size(); i += 1) {
        delete traps[i];
    }
}

