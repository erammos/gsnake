//
// Created by eram on 22/5/25.
//

#include <random>
#include <iostream>
#include "Game.h"
#include "Snake.h"
#include "font.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Text.hpp"

Game::Game(uint32_t width, uint32_t height, const std::string& name)
{
    render_window_ = sf::RenderWindow(sf::VideoMode({width, height}), name);
    render_window_.setFramerateLimit(20);
}

static sf::Vector2f get_random_food_position(float max_x, float max_y)
{
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_real_distribution<float> distX(0, max_x / Snake::size);
    std::uniform_real_distribution<float> distY(0, max_y / Snake::size);
    return sf::Vector2f{floor(distX(el)) * Snake::size, floor(distY(el)) * Snake::size};
}

void Game::run()
{
    const auto window_size = render_window_.getView().getSize();

    sf::Font font;
    if (!font.openFromMemory(Kenney_Rocket_ttf, Kenney_Rocket_ttf_len))
    {
        exit(1);
    }
    sf::Text text(font);
    text.setString("End!");
    text.setCharacterSize(64);
    text.setFillColor(sf::Color::Red);
    const auto text_size = text.getLocalBounds().size;
    text.setPosition({
        (window_size.x - text_size.x) / 2, (window_size.y - text_size.y) / 2
    });

    auto is_dead = false;
    Snake snake;

    auto food = get_random_food_position(window_size.x, window_size.y);
    auto food_shape = sf::RectangleShape({Snake::size, Snake::size});
    food_shape.setFillColor({255, 255, 0});

    while (render_window_.isOpen())
    {
        while (const std::optional event = render_window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                render_window_.close();
            }
        }
        if (is_dead)
            continue;

        snake.update(window_size.x, window_size.y);
        if (food == snake.get_position())
        {
            snake.eat();
            food = get_random_food_position(window_size.x, window_size.y);
        }
        if (snake.check_collision())
        {
            is_dead = true;
        }
        render_window_.clear();
        snake.draw(render_window_);
        food_shape.setPosition(food);
        render_window_.draw(food_shape);
        if (is_dead)
        {
            render_window_.draw(text);
        }
        render_window_.display();
    }
}
