
// Author: Pierce Brooks

#include <LS/Player.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Player::Player(Game* owner, const sf3d::Vector2u& position) :
    Ownable<Game*>(),
    owner(owner),
    position(position)
{
    texture = new sf3d::Texture();
    texture->loadFromFile("./Assets/snowden.png");
    sprite = new sf3d::Sprite(*texture);
    sprite->setOrigin(sf3d::Vector2f(texture->getSize())*0.5f);
}

LS::Player::~Player()
{
    delete sprite;
    delete texture;
}

bool LS::Player::shoot()
{
    return false;
}

void LS::Player::move(const sf3d::Vector2i& movement)
{

}

LS::Game* LS::Player::getOwner() const
{
    return owner;
}

sf3d::Sprite* LS::Player::getSprite() const
{
    return sprite;
}

const sf3d::Vector2u& LS::Player::getPosition() const
{
    return position;
}

void LS::Player::setPosition(const sf3d::Vector2u& position)
{
    this->position = position;
}
