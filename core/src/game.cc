#include "game.h"

Game::Game() {
    window_.create(sf::VideoMode({800,600}), "SFML window");

    grass_texture_.loadFromFile("../assets/sprites/grass.png");
}

void Game::Loop() {
   sf::Sprite sprite(grass_texture_);

    //Start the game loop
    while (window_.isOpen())
        {
        //Process events
        while (const std::optional event = window_.pollEvent())
            {
            //Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window_.close();
            }
        }

        window_.clear();

        window_.draw(sprite);

        window_.display();
    }
}