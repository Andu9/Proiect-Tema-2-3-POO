#include "Headers/Game.h"

int main() {
    Game currentGame;
    currentGame.run();
 /*   sf::RenderWindow window(sf::VideoMode(1044, 585), "Poor bunny!", sf::Style::Default);

    sf::Texture backText;
    backText.loadFromFile("Background.jpg");

    sf::Sprite background;
    background.setTexture(backText);
    background.setPosition(0, 0);

    Player player{window, "Iepuri.png"};
    window.setFramerateLimit(60);

    std::array<Thing, 8> platforms;

    platforms[0] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{232, 358}, "SmallPlatform.png");
    platforms[1] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{467, 358}, "BigPlatform.png");
    platforms[2] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{763, 358}, "SmallPlatform.png");

    platforms[3] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{290, 237}, "BigPlatform.png");
    platforms[4] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{640, 237}, "BigPlatform.png");

    platforms[5] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{232, 120}, "SmallPlatform.png");
    platforms[6] = Thing(sf::Vector2f{111, 27}, sf::Vector2f{468, 118}, "BigPlatform.png");
    platforms[7] = Thing(sf::Vector2f{54, 27}, sf::Vector2f{762, 120}, "SmallPlatform.png");

    Arrow currentArrow(window, "Arrow.png");

    Carrot currentCarrot(window, 1, "Carrot.png");
    GoldenCarrot goldenCarrot(window, "GoldenCarrot.png");

    CannonBall a("CannonBall.png"), x("CannonBall.png");
    a.spawn(), x.spawn();

    SpikeyBall f("SpikeyBall.png");
    f.spawn();

    Saw b("Saw.png"), c("Saw.png");
    b.spawn(), c.spawn();

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



         window.draw(background);

         int i = 0;
         for (auto& platform: platforms) {
             if (i == 1 || i == 3 || i == 4 || i == 6) {
                 platform.initTextures("BigPlatform.png");
             } else {
                 platform.initTextures("SmallPlatform.png");
             }
             platform.setPosition();
             platform.draw(window);
             i += 1;
         }

         currentArrow.move(window);
         currentArrow.initTextures("Arrow.png");
         currentArrow.setPosition();
         currentArrow.draw(window);

         f.move(window);
         f.initTextures("SpikeyBall.png");
         f.setPosition();
         f.draw(window);


         a.move(window);
         a.initTextures("CannonBall.png");
         a.setPosition();
         a.draw(window);

         b.move(window);
         b.initTextures("Saw.png");
         b.setPosition();
         b.draw(window);

         c.move(window);
         c.initTextures("Saw.png");
         c.setPosition();
         c.draw(window);

         player.move(window, platforms);
         player.setPosition();
         player.draw(window);

         currentCarrot.setPosition();
         currentCarrot.draw(window);

         goldenCarrot.initTextures("GoldenCarrot.png");
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
     }*/
     return 0;
 }

