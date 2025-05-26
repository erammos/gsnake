//
// Created by eram on 22/5/25.
//

#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics/RenderWindow.hpp"

class Game
{
public:
    ~Game() = default;
    Game(uint32_t width, uint32_t height, const std::string& name);
    void run();

private:
    sf::RenderWindow render_window_;
};

#endif //GAME_H
