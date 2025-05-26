//
// Created by eram on 22/5/25.
//

#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"

class Snake
{
public:
    static constexpr float size = 20.0f;
    Snake();
    void update(float max_width, float max_height);
    void draw(sf::RenderWindow& renderer) const;
    void eat();
    [[nodiscard]] sf::Vector2f get_position() const;
    [[nodiscard]] bool check_collision() const;

private:
    sf::Vector2f head_ = {0, 0};
    sf::Vector2f dir_ = {1, 0};
    std::pmr::deque<sf::Vector2f> list;
    bool eating_ = false;
};

#endif //SNAKE_H
