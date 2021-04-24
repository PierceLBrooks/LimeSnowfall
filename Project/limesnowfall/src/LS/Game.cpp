
// Author: Pierce Brooks

#include <SFML/Window/Mouse.hpp>
#include <LS/LimeSnowfall.hpp>
#include <LS/Game.hpp>
#include <iostream>

#define PI (22.0f/7.0f)

LS::Game::Game(const sf::Vector2u& size)
{
    pi = PI;
    window = nullptr;
    player = new Player(this, sf::Vector2u(1, 1));
}

LS::Game::~Game()
{
    delete player;
}

bool LS::Game::act(Action action)
{
    switch (action)
    {
    case SHOOT:
        return shoot();
    }
    return false;
}

bool LS::Game::shoot()
{
    if (window == nullptr)
    {
        return false;
    }
    if (player->shoot())
    {
        sf::Color color = level->invert(getFloorColor());
        sf::Vector2f position = level->multiply(sf::Vector2f(player->getPosition()), level->getUnitSize());
        sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(*window))+(window->getView().getCenter()-(window->getView().getSize()*0.5f));
        float direction = level->direction(position, mouse);
        color.a = 255;
        bullets.push_back(new Bullet(this, bulletTexture, position, sf::Vector2f(cosf(direction), sinf(direction))*level->distance(position, mouse), direction*(180.0f/pi)));
        bullets.back()->setColor(color);
        return true;
    }
    return false;
}

bool LS::Game::movePlayer(const sf::Vector2i& movement)
{
    player->move(movement);
    return true;
}

LS::Player* LS::Game::getPlayer() const
{
    return player;
}
