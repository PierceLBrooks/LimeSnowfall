
// Author: Pierce Brooks

#include <LS/Enemy.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Enemy::Enemy(Game* owner, sf3d::Texture* texture, float axis, float goal, int facing, const sf3d::Vector3f& scale) :
    Ownable<Game*>(),
    Shooter(),
    owner(owner),
    goal(goal),
    facing(facing)
{
    health = 2;
    life = 0.0f;
    pi = PI;
    sprite = new sf3d::Sprite();
    sprite->setTexture(*texture);
    sprite->setOrigin(sf3d::Vector2f(texture->getSize())*0.5f);
    sprite->setPosition(sf3d::Vector3f(axis, 0.0f, 0.0f));
    sprite->setScale(scale);
    sprite->move(sf3d::Vector3f(0.0f, -static_cast<float>(texture->getSize().y)*scale.y*2.0f, 0.0f));
    rope = new sf3d::RectangleShape();
    rope->setFillColor(sf3d::Color::White);
    rope->setSize(sf3d::Vector3f(5.0f, 5000.0f, 5.0f));
    rope->setOrigin(rope->getSize()*0.5f);
}

LS::Enemy::~Enemy()
{
    delete sprite;
    delete rope;
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
    if (health <= 0)
    {
        life += deltaTime;
        if ((sprite->getPosition().y > goal*5.0f) || (life > 15.0f))
        {
            return false;
        }
    }
    if (sprite->getPosition().y < goal)
    {
        sprite->move(sf3d::Vector3f(0.0f, deltaTime*sprite->getScale().y*static_cast<float>(sprite->getTexture()->getSize().y)*0.5f, 0.0f));
    }
    else
    {
        if (health <= 0)
        {
            sprite->move(sf3d::Vector3f(0.0f, deltaTime*sprite->getScale().y*static_cast<float>(sprite->getTexture()->getSize().y)*5.0f, 0.0f));
        }
        else
        {
            if ((facing > 0) == (player->getPosition().x > sprite->getPosition().x))
            {
                float angle = getAngle();
                sprite->setRotation(angle);
            }
        }
    }
    if ((health > 0) || (sprite->getPosition().y < goal))
    {
        rope->setPosition(sprite->getPosition());
        rope->move(-rope->getOrigin());
        window->draw(*rope);
    }
    window->draw(*sprite);
    setScale(sprite->getScale());
    setPosition(sprite->getPosition());
    setRotation(sprite->getRotation());
    return true;
}

float LS::Enemy::getAngle() const
{
    return (atan2f(owner->getPlayer()->getPosition().y-(sprite->getPosition().y-(sprite->getOrigin().y)), owner->getPlayer()->getPosition().x-(sprite->getPosition().x))*(180.0f/pi))+((facing>0)?0.0f:180.0f);
}
