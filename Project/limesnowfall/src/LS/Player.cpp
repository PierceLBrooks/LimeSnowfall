
// Author: Pierce Brooks

#include <LS/Player.hpp>
#include <LS/Game.hpp>
#include <iostream>

#define PI (22.0f/7.0f)

LS::Player::Player(Game* owner) :
    Ownable<Game*>(),
    owner(owner),
    movement(0, 0),
    facing(1),
    airborne(false),
    briefcase(false),
    limit(240.0f)
{
    center = sf3d::Vector2f(owner->getWindow()->getSize())*0.5f;
    animationSize = sf3d::Vector2i(80, 80);
    animationIndex = 0;
    animation = 0.0f;
    pi = PI;
    handOffset = sf3d::Vector2f(-10.0f, -20.0f);
    offhandOffset = sf3d::Vector2f(-10.0f, -20.0f);
    scale = sf3d::Vector2f(1.0f, 1.0f)*5.0f;
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
    sprite->setOrigin(sf3d::Vector2f(animationSize)*0.5f);
    sprite->setOrigin(sprite->getOrigin().x, sprite->getOrigin().y*2.0f);
    sprite->setScale(sf3d::Vector3f(scale.x, scale.y, 1.0f));
    sprite->setPosition(center.x, center.y*1.5f);
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
    gunImageLeft = new sf3d::Image();
    gunImageLeft->loadFromFile("./Assets/snowden_gun.png");
    gunImageLeft->flipHorizontally();
    gunTextureLeft = new sf3d::Texture();
    gunTextureLeft->loadFromImage(*gunImageLeft);
    gunImageRight = new sf3d::Image();
    gunImageRight->loadFromFile("./Assets/snowden_gun.png");
    gunTextureRight = new sf3d::Texture();
    gunTextureRight->loadFromImage(*gunImageRight);
    hand = new sf3d::Sprite(*gunTextureRight);
    torchImageLeft = new sf3d::Image();
    torchImageLeft->loadFromFile("./Assets/snowden_torch.png");
    torchImageLeft->flipHorizontally();
    torchTextureLeft = new sf3d::Texture();
    torchTextureLeft->loadFromImage(*torchImageLeft);
    torchImageRight = new sf3d::Image();
    torchImageRight->loadFromFile("./Assets/snowden_torch.png");
    torchTextureRight = new sf3d::Texture();
    torchTextureRight->loadFromImage(*torchImageRight);
    briefcaseImageLeft = new sf3d::Image();
    briefcaseImageLeft->loadFromFile("./Assets/snowden_briefcase.png");
    briefcaseImageLeft->flipHorizontally();
    briefcaseTextureLeft = new sf3d::Texture();
    briefcaseTextureLeft->loadFromImage(*briefcaseImageLeft);
    briefcaseImageRight = new sf3d::Image();
    briefcaseImageRight->loadFromFile("./Assets/snowden_briefcase.png");
    briefcaseTextureRight = new sf3d::Texture();
    briefcaseTextureRight->loadFromImage(*briefcaseImageRight);
    if (briefcase)
    {
        offhand = new sf3d::Sprite(*briefcaseTextureRight);
    }
    else
    {
        offhand = new sf3d::Sprite(*torchTextureRight);
    }
}

LS::Player::~Player()
{
    delete sprite;
    delete textureRight;
    delete imageRight;
    delete textureLeft;
    delete imageLeft;
    delete hand;
    delete offhand;
    delete gunTextureRight;
    delete gunImageRight;
    delete gunTextureLeft;
    delete gunImageLeft;
    delete torchTextureRight;
    delete torchImageRight;
    delete torchTextureLeft;
    delete torchImageLeft;
    delete briefcaseTextureRight;
    delete briefcaseImageRight;
    delete briefcaseTextureLeft;
    delete briefcaseImageLeft;
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

bool LS::Player::jump()
{
    std::cout << "jump" << std::endl;
    if (airborne)
    {
        return false;
    }
    airborne = true;
    return true;
}

bool LS::Player::pickup()
{
    std::cout << "pickup" << std::endl;
    if (airborne)
    {
        return false;
    }
    if (briefcase)
    {
        return false;
    }
    briefcase = true;
    if (briefcase)
    {
        offhand->setTexture(*((facing>0)?briefcaseTextureRight:briefcaseTextureLeft));
    }
    else
    {
        offhand->setTexture(*((facing>0)?torchTextureRight:torchTextureLeft));
    }
    return true;
}

bool LS::Player::drop()
{
    std::cout << "drop" << std::endl;
    if (!briefcase)
    {
        return false;
    }
    briefcase = false;
    if (briefcase)
    {
        offhand->setTexture(*((facing>0)?briefcaseTextureRight:briefcaseTextureLeft));
    }
    else
    {
        offhand->setTexture(*((facing>0)?torchTextureRight:torchTextureLeft));
    }
    return true;
}

bool LS::Player::die()
{
    std::cout << "die" << std::endl;
    owner->act(Game::Action::DIE);
    return true;
}

LS::Game* LS::Player::getOwner() const
{
    return owner;
}

sf3d::Sprite* LS::Player::getSprite() const
{
    return sprite;
}

bool LS::Player::update(sf3d::RenderTexture* window, float deltaTime)
{
    animation += deltaTime*static_cast<float>(animations[animationIndex].size());
    if (movement.x != 0)
    {
        animationIndex = 0;
        if (facing != movement.x)
        {
            facing = movement.x;
            sprite->setTexture(*((facing>0)?textureRight:textureLeft));
            hand->setTexture(*((facing>0)?gunTextureRight:gunTextureLeft));
            if (briefcase)
            {
                offhand->setTexture(*((facing>0)?briefcaseTextureRight:briefcaseTextureLeft));
            }
            else
            {
                offhand->setTexture(*((facing>0)?torchTextureRight:torchTextureLeft));
            }
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
    if (sprite->getPosition().x-(0.5f*static_cast<float>(window->getSize().x)) > limit)
    {
        sprite->setPosition(limit+(0.5f*static_cast<float>(window->getSize().x)), sprite->getPosition().y);
    }
    if (sprite->getPosition().x-(0.5f*static_cast<float>(window->getSize().x)) < -limit)
    {
        sprite->setPosition(-limit+(0.5f*static_cast<float>(window->getSize().x)), sprite->getPosition().y);
    }
    hand->setOrigin(sf3d::Vector3f(static_cast<float>(hand->getTexture()->getSize().x)*0.5f, 0.0f, 0.0f));
    hand->setPosition(sprite->getPosition());
    hand->setScale(sprite->getScale());
    hand->move((scale.x*handOffset.x*static_cast<float>((facing>0)?0.5f:2.5f))-(handOffset.x*scale.x*1.5f), (scale.y*handOffset.y)-(sprite->getOrigin().y*2.5f));
    offhand->setOrigin(sf3d::Vector3f(static_cast<float>(offhand->getTexture()->getSize().x)*0.5f, 0.0f, 0.0f));
    offhand->setPosition(sprite->getPosition());
    offhand->setScale(sprite->getScale());
    offhand->move(-handOffset.x*scale.x*1.25f, -sprite->getOrigin().y*2.5f);
    if (briefcase)
    {
        offhand->move(scale.x*((offhandOffset.x*static_cast<float>((facing>0)?1.0f:0.125f))+(1.5f*static_cast<float>((facing>0)?offhandOffset.x:0.0f))), scale.y*(offhandOffset.y-2.5f));
    }
    else
    {
        offhand->move(scale.x*((offhandOffset.x*static_cast<float>((facing>0)?1.0f:2.5f))+2.5f), scale.y*offhandOffset.y);
    }
    window->draw(*hand);
    window->draw(*sprite);
    window->draw(*offhand);
    movement = sf3d::Vector2i();
    return true;
}
