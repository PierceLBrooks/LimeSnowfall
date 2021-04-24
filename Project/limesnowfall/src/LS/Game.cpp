
// Author: Pierce Brooks

#include <SFML3D/Window/Mouse.hpp>
#include <LS/LimeSnowfall.hpp>
#include <LS/Game.hpp>
#include <iostream>

#define PI (22.0f/7.0f)

LS::Game::Game(sf3d::RenderWindow* output, const sf3d::Vector2u& size)
{
    pi = PI;
    this->output = output;
    window = nullptr;
    player = new Player(this, sf3d::Vector2u(1, 1));
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
        sf3d::Vector3f center = window->getView().getCenter();
        sf3d::Color color = sf3d::Color::White;
        sf3d::Vector2f mouse = sf3d::Vector2f(sf3d::Mouse::getPosition(*output))+(sf3d::Vector2f(center.x, center.y)-(window->getView().getSize()*0.5f));
        return true;
    }
    return false;
}

bool LS::Game::movePlayer(const sf3d::Vector2i& movement)
{
    player->move(movement);
    return true;
}

void LS::Game::update(sf3d::RenderTexture* window, float deltaTime)
{
    this->window = window;
}

LS::Player* LS::Game::getPlayer() const
{
    return player;
}
