
// Author: Pierce Brooks

#include <LS/Player.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Player::Player(Game* owner) :
    Ownable<Game*>(),
    owner(owner),
    movement(0, 0),
    facing(1)
{
    sf3d::Vector2f center = sf3d::Vector2f(owner->getWindow()->getSize())*0.5f;
    imageLeft = new sf3d::Image();
    imageLeft->loadFromFile("./Assets/snowden.png");
    imageLeft->flipHorizontally();
    textureLeft = new sf3d::Texture();
    textureLeft->loadFromImage(*imageLeft);
    imageRight = new sf3d::Image();
    imageRight->loadFromFile("./Assets/snowden.png");
    textureRight = new sf3d::Texture();
    textureRight->loadFromImage(*imageRight);
    sprite = new sf3d::Sprite(*textureRight);
    sprite->setOrigin(sf3d::Vector2f(80.0f, 80.0f)*0.5f);
    sprite->setScale(sf3d::Vector3f(1.0f, 1.0f, 1.0f)*5.0f);
    sprite->setPosition(center.x, center.y);
    animationSize = sf3d::Vector2i(80, 80);
    animationIndex = 0;
    animation = 0.0f;
    animations.push_back(std::vector<sf3d::Vector2i>());
    animations.back().push_back(sf3d::Vector2i(3, 2));
    animations.back().push_back(sf3d::Vector2i(4, 2));
    animations.back().push_back(sf3d::Vector2i(5, 2));
    animations.back().push_back(sf3d::Vector2i(4, 2));
    animations.back().push_back(sf3d::Vector2i(3, 2));
    animations.back().push_back(sf3d::Vector2i(0, 0));
    animations.back().push_back(sf3d::Vector2i(2, 2));
    animations.back().push_back(sf3d::Vector2i(1, 2));
    animations.back().push_back(sf3d::Vector2i(0, 2));
    animations.back().push_back(sf3d::Vector2i(1, 2));
    animations.back().push_back(sf3d::Vector2i(2, 2));
    animations.back().push_back(sf3d::Vector2i(0, 0));
    animations.push_back(std::vector<sf3d::Vector2i>());
    animations.back().push_back(sf3d::Vector2i(0, 0));
}

LS::Player::~Player()
{
    delete sprite;
    delete textureRight;
    delete imageRight;
    delete textureLeft;
    delete imageLeft;
}

bool LS::Player::shoot()
{
    std::cout << "shoot" << std::endl;
    return false;
}

void LS::Player::move(const sf3d::Vector2i& movement)
{
    this->movement = movement;
}

LS::Game* LS::Player::getOwner() const
{
    return owner;
}

sf3d::Sprite* LS::Player::getSprite() const
{
    return sprite;
}

void LS::Player::update(sf3d::RenderTexture* window, float deltaTime)
{
    animation += deltaTime*static_cast<float>(animations[animationIndex].size());
    if (movement.x != 0)
    {
        animationIndex = 0;
        if (facing != movement.x)
        {
            facing = movement.x;
            sprite->setTexture(*((facing>0)?textureRight:textureLeft));
        }
    }
    else
    {
        animationIndex = 1;
    }
    while (static_cast<int>(animation) >= static_cast<int>(animations[animationIndex].size()))
    {
        animation -= static_cast<float>(animations[animationIndex].size());
    }
    while (animation < 0.0f)
    {
        animation += static_cast<float>(animations[animationIndex].size());
    }
    sprite->setTextureRect(sf3d::IntRect(animations[animationIndex][static_cast<unsigned int>(animation)].x*animationSize.x,
                                         animations[animationIndex][static_cast<unsigned int>(animation)].y*animationSize.y,
                                         animationSize.x,
                                         animationSize.y));
    if (facing < 0)
    {
        sprite->setTextureRect(sf3d::IntRect((facing>0)?sprite->getTextureRect().left:(static_cast<int>(sprite->getTexture()->getSize().x-animationSize.x)-sprite->getTextureRect().left),
                                             sprite->getTextureRect().top,
                                             sprite->getTextureRect().width,
                                             sprite->getTextureRect().height));
    }
    sprite->move(sf3d::Vector2f(movement)*deltaTime*500.0f);
    window->draw(*sprite);
    movement = sf3d::Vector2i();
}
