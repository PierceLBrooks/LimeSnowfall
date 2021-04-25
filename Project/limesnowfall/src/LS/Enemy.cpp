
// Author: Pierce Brooks

#include <LS/Enemy.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Enemy::Enemy(Game* owner, sf3d::Texture* texture, float axis, float goal, int facing, const sf3d::Vector3f& scale, const std::vector<sf3d::SoundBuffer*>& soundBuffers) :
    Shooter(owner),
    goal(goal),
    facing(facing)
{
    step = 0;
    health = 2;
    life = 0.0f;
    target = 0.0f;
    shoot = 0.0f;
    aim = 0.0f;
    pi = PI;
    sprite = new sf3d::Sprite();
    sprite->setTexture(*texture);
    sprite->setOrigin(sf3d::Vector2f(texture->getSize())*0.5f);
    sprite->setPosition(sf3d::Vector3f(axis, 0.0f, 0.0f));
    sprite->setScale(scale);
    sprite->move(sf3d::Vector3f(0.0f, -static_cast<float>(texture->getSize().y)*scale.y, 0.0f));
    rope = new sf3d::RectangleShape();
    rope->setFillColor(sf3d::Color(128, 128, 128));
    rope->setSize(sf3d::Vector3f(5.0f, 5000.0f, 5.0f));
    rope->setOrigin(rope->getSize()*0.5f);
    for (unsigned int i = 0; i != soundBuffers.size(); ++i)
    {
        if (getOwner()->countSound(1))
        {
            sounds.push_back(new sf3d::Sound());
            sounds.back()->setBuffer(*soundBuffers[i]);
        }
        else
        {
            sounds.push_back(nullptr);
        }
    }
    if (facing < 0)
    {
        target = 180.0f;
    }
}

LS::Enemy::~Enemy()
{
    delete sprite;
    delete rope;
    for (unsigned int i = 0; i != sounds.size(); ++i)
    {
        if (sounds[i] != nullptr)
        {
            getOwner()->countSound(-1);
            delete sounds[i];
            sounds[i] = nullptr;
        }
    }
    sounds.clear();
}

bool LS::Enemy::hurt(Bullet* bullet)
{
    if (health <= 0)
    {
        return false;
    }
    float distance = sqrtf(powf(getPosition().x-bullet->getPosition().x, 2.0f)+powf(getPosition().y-bullet->getPosition().y, 2.0f));
    //std::cout << distance << std::endl;
    if (distance > static_cast<float>(sprite->getTexture()->getSize().x)*0.75f)
    {
        return false;
    }
    --health;
    if (!sounds.empty())
    {
        if (health <= 0)
        {
            if (sounds[0] != nullptr)
            {
                sounds[0]->stop();
                delete sounds[0];
                sounds[0] = nullptr;
            }
            if (sounds[1] != nullptr)
            {
                sounds[1]->stop();
                delete sounds[1];
                sounds[1] = nullptr;
            }
            if (sounds[2] != nullptr)
            {
                sounds[2]->play();
            }
        }
        else
        {
            if (sounds[1] != nullptr)
            {
                sounds[1]->play();
            }
        }
    }
    return true;
}

bool LS::Enemy::update(sf3d::RenderTexture* window, float deltaTime, Player* player)
{
    ++step;
    if (sprite->getPosition().y < goal)
    {
        sprite->move(sf3d::Vector3f(0.0f, deltaTime*sprite->getScale().y*static_cast<float>(sprite->getTexture()->getSize().y), 0.0f));
    }
    else
    {
        if (health <= 0)
        {
            for (unsigned int i = 0; i != sounds.size(); ++i)
            {
                if (sounds[i] == nullptr)
                {
                    continue;
                }
                if (sounds[i]->getStatus() == sf3d::SoundSource::Status::Playing)
                {
                    break;
                }
                if (i == sounds.size()-1)
                {
                    for (unsigned int j = 0; j != sounds.size(); ++j)
                    {
                        if (sounds[i] != nullptr)
                        {
                            getOwner()->countSound(-1);
                            delete sounds[i];
                            sounds[i] = nullptr;
                        }
                    }
                    sounds.clear();
                    break;
                }
                else
                {
                    continue;
                }
                sounds[i]->stop();
            }
            sprite->move(sf3d::Vector3f(0.0f, deltaTime*sprite->getScale().y*static_cast<float>(sprite->getTexture()->getSize().y)*5.0f, 0.0f));
            life += deltaTime;
            if ((sprite->getPosition().y > goal*25.0f) || (life > 2.5f))
            {
                return false;
            }
        }
        else
        {
            if (shoot > 0.0f)
            {
                shoot -= deltaTime;
                if (step%5 == 0)
                {
                    getOwner()->enemyShoot(this, target);
                }
            }
            else
            {
                if ((facing > 0) == (player->getPosition().x > sprite->getPosition().x))
                {
                    float difference;
                    float angle = getAngle();
                    target = fmodf(target, 360.0f);
                    difference = fmodf(fabsf(angle-target), 360.0f);
                    if ((difference > 180.0f) && (facing > 0))
                    {
                        difference = 360.0f-difference;
                    }
                    //std::cout << angle << " " << target << " " << difference << std::endl;
                    if (fabsf((target+difference)-angle) < fabsf((target-difference)-angle))
                    {
                        target += difference*deltaTime;
                    }
                    else
                    {
                        target -= difference*deltaTime;
                    }
                    if (fabsf(difference) < 5.0f)
                    {
                        aim += deltaTime;
                        if (aim > 1.0f)
                        {
                            shoot = aim;
                            if (!sounds.empty())
                            {
                                if (sounds[0] != nullptr)
                                {
                                    sounds[0]->play();
                                }
                            }
                        }
                    }
                    sprite->setRotation(target+((facing>0)?0.0f:180.0f));
                }
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
    return (atan2f(getOwner()->getPlayer()->getPosition().y-(sprite->getPosition().y-(sprite->getOrigin().y)), getOwner()->getPlayer()->getPosition().x-(sprite->getPosition().x))*(180.0f/pi));
}
