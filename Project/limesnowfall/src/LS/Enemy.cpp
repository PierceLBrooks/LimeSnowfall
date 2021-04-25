
// Author: Pierce Brooks

#include <LS/Enemy.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Enemy::Enemy(Game* owner, sf3d::Texture* texture, float axis, float goal, const sf3d::Vector3f& scale) :
    Ownable<Game*>(),
    Shooter(),
    owner(owner),
    goal(goal)
{
    health = 3;
    life = 0.0f;
    sprite = new sf3d::Sprite();
    sprite->setTexture(*texture);
    sprite->setOrigin(sf3d::Vector2f(texture->getSize())*0.5f);
    sprite->setPosition(sf3d::Vector3f(axis, 0.0f, 0.0f));
    sprite->setScale(scale);
}

LS::Enemy::~Enemy()
{
    delete sprite;
}

LS::Game* LS::Enemy::getOwner() const
{
    return owner;
}

bool LS::Enemy::hurt(Bullet* bullet)
{
    if (health <= 0)
    {
        return false;
    }
    float distance = sqrtf(powf(getPosition().x-bullet->getPosition().x, 2.0f)+powf(getPosition().y-bullet->getPosition().y, 2.0f));
    std::cout << distance << std::endl;
    if (distance > static_cast<float>(sprite->getTexture()->getSize().x)*0.75f)
    {
        return false;
    }
    --health;
    return true;
}

bool LS::Enemy::update(sf3d::RenderTexture* window, float deltaTime, Player* player)
{
    life += deltaTime;
    if (health <= 0)
    {
        return false;
    }
    if (sprite->getPosition().y < goal)
    {
        sprite->move(sf3d::Vector3f(0.0f, deltaTime*sprite->getScale().y*static_cast<float>(sprite->getTexture()->getSize().y)*0.5f, 0.0f));
    }
    window->draw(*sprite);
    setScale(sprite->getScale());
    setPosition(sprite->getPosition());
    return true;
}
