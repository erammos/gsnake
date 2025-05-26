//
// Created by eram on 22/5/25.
//

#include "Snake.h"
#include "Game.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics.hpp"

Snake::Snake(): dir_(sf::Vector2f(1.0f, 0.0f)), list{{0.0f, 0.0f}, {size, 0.0f}, {2 * size, 0.0f}}
{
}

void Snake::update(const float max_width, const float max_height)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Left) && dir_.x <= 0)
    {
        dir_ = {-1, 0};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && dir_.x >= 0)
    {
        dir_ = {1, 0};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && dir_.y <= 0)
    {
        dir_ = {0, -1};
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && dir_.y >= 0)
    {
        dir_ = {0, 1};
    }
    const auto next_pos = head_ + dir_ * size;
    if (next_pos.x >= max_width)
    {
        head_ = {0, head_.y};
    }
    else if (next_pos.x < 0)
    {
        head_ = {max_width, head_.y};
    }
    else if (next_pos.y >= max_height)
    {
        head_ = {head_.x, 0};
    }
    else if (next_pos.y < 0)
    {
        head_ = {head_.x, max_height};
    }
    else
    {
        head_ = next_pos;
    }
    list.push_front(head_);

    if (!eating_)
    {
        list.pop_back();
    }
    eating_ = false;
}

bool Snake::check_collision() const
{
    return std::any_of(list.begin(), list.end(), [this](auto pos)
    {
        return head_ + dir_ * size == pos;
    });
}

void Snake::draw(sf::RenderWindow& renderer) const
{
    auto shape = sf::RectangleShape({size, size});
    shape.setFillColor({150, 50, 250});
    for (auto& part : list)
    {
        shape.setPosition(part);
        renderer.draw(shape);
    }
}

void Snake::eat()
{
    eating_ = true;
}

sf::Vector2f Snake::get_position() const
{
    return head_;
}
