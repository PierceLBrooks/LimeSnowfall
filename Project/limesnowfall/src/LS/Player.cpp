
// Author: Pierce Brooks

#include <LS/Player.hpp>
#include <LS/Game.hpp>
#include <iostream>

LS::Player::Player(Game* owner) :
    Shooter(owner),
    movement(0, 0),
    facing(1),
    motion(0),
    airborne(false),
    briefcase(false),
    limit(240.0f),
    speed(500.0f),
    gravity(5000.0f),
    reload(0.0f)
{
    center = sf3d::Vector2f(owner->getWindow()->getSize())*0.5f;
    animationSize = sf3d::Vector2i(80, 80);
    animationIndex = 0;
    animation = 0.0f;
    life = 0.0f;
    heal = 0.0f;
    healthMax = 10;
    health = healthMax;
    pi = PI;
    handOffset = sf3d::Vector2f(-10.0f, -2.0f);
    offhandOffset = sf3d::Vector2f(-10.0f, -2.0f);
    scale = sf3d::Vector2f(1.0f, 1.0f)*3.5f;
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
    sprite->setPosition(center.x, center.y*1.75f);
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
    animations.push_back(std::vector<sf3d::Vector2i>());
    animations.back().push_back(sf3d::Vector2i(0, 1));
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
    offhandBriefcase = new sf3d::Sprite(*briefcaseTextureRight);
    offhandTorch = new sf3d::Sprite(*torchTextureRight);
    shotBuffer = new sf3d::SoundBuffer();
    shotBuffer->loadFromFile("./Assets/shot.wav");
    shotSound = new sf3d::Sound();
    shotSound->setBuffer(*shotBuffer);
    hurtBuffer = new sf3d::SoundBuffer();
    hurtBuffer->loadFromFile("./Assets/snowden_hurt.wav");
    hurtSound = new sf3d::Sound();
    hurtSound->setBuffer(*hurtBuffer);
    dieBuffer = new sf3d::SoundBuffer();
    dieBuffer->loadFromFile("./Assets/snowden_die.wav");
    dieSound = new sf3d::Sound();
    dieSound->setBuffer(*dieBuffer);
    jumpBuffer = new sf3d::SoundBuffer();
    jumpBuffer->loadFromFile("./Assets/jump.wav");
    jumpSound = new sf3d::Sound();
    jumpSound->setBuffer(*jumpBuffer);
    dropBuffer = new sf3d::SoundBuffer();
    dropBuffer->loadFromFile("./Assets/drop.wav");
    dropSound = new sf3d::Sound();
    dropSound->setBuffer(*dropBuffer);
    pickupBuffer = new sf3d::SoundBuffer();
    pickupBuffer->loadFromFile("./Assets/pickup.wav");
    pickupSound = new sf3d::Sound();
    pickupSound->setBuffer(*pickupBuffer);
    healthBar = new sf3d::RectangleShape();
    healthBar->setFillColor(sf3d::Color::Green);
    healthBar->setSize(sf3d::Vector3f(250.0f, 25.0f, 5.0f));
    healthBar->setOrigin(healthBar->getSize()*0.5f);
}

LS::Player::~Player()
{
    delete sprite;
    delete textureRight;
    delete imageRight;
    delete textureLeft;
    delete imageLeft;
    delete hand;
    delete offhandTorch;
    delete offhandBriefcase;
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
    delete shotSound;
    delete shotBuffer;
    delete hurtSound;
    delete hurtBuffer;
    delete dieSound;
    delete dieBuffer;
    delete jumpSound;
    delete jumpBuffer;
    delete dropSound;
    delete dropBuffer;
    delete pickupSound;
    delete pickupBuffer;
    delete healthBar;
}

int LS::Player::getFacing() const
{
    return facing;
}

bool LS::Player::getBriefcase() const
{
    return briefcase;
}

bool LS::Player::getAirborne() const
{
    return airborne;
}

bool LS::Player::shoot(float& angle)
{
    //std::cout << "shoot" << std::endl;
    if (health <= 0)
    {
        return false;
    }
    if (reload > 0.0f)
    {
        return false;
    }
    if (((facing > 0) != (mouse.x > sprite->getPosition().x)) || (mouse.y > (sprite->getPosition().y-(sprite->getOrigin().y))))
    {
        return false;
    }
    reload = 0.25f;
    shotSound->play();
    angle = getAngle();
    if (facing < 0)
    {
        angle += 180.0f;
    }
    if (briefcase)
    {
        angle += sinf(life*pi*50.0f)*7.5f;
    }
    return true;
}

void LS::Player::go(const sf3d::Vector2i& movement)
{
    if (health <= 0)
    {
        return;
    }
    this->movement = movement;
}

bool LS::Player::jump()
{
    //std::cout << "jump" << std::endl;
    if (health <= 0)
    {
        return false;
    }
    if (airborne)
    {
        return false;
    }
    velocity.x = static_cast<float>(motion)*speed;
    velocity.y = -speed*2.5f*((briefcase)?0.75f:1.0f);
    airborne = true;
    if (jumpSound->getStatus() != sf3d::SoundSource::Status::Playing)
    {
        jumpSound->play();
    }
    return true;
}

bool LS::Player::pickup()
{
    std::cout << "pickup" << std::endl;
    if (health <= 0)
    {
        return false;
    }
    if (airborne)
    {
        return false;
    }
    if (briefcase)
    {
        return false;
    }
    briefcase = true;
    if (pickupSound != nullptr)
    {
        if (pickupSound->getStatus() != sf3d::SoundSource::Status::Playing)
        {
            pickupSound->play();
        }
    }
    return true;
}

bool LS::Player::drop()
{
    std::cout << "drop" << std::endl;
    if (health <= 0)
    {
        return false;
    }
    if (!briefcase)
    {
        return false;
    }
    briefcase = false;
    if (dropSound != nullptr)
    {
        if (dropSound->getStatus() != sf3d::SoundSource::Status::Playing)
        {
            dropSound->play();
        }
    }
    return true;
}

bool LS::Player::die()
{
    if (health > 0)
    {
        return false;
    }
    if (dieSound == nullptr)
    {
        return false;
    }
    if (dieSound->getStatus() == sf3d::SoundSource::Status::Playing)
    {
        return false;
    }
    dieSound->play();
    return true;
}

bool LS::Player::hurt(Bullet* bullet)
{
    if (health <= 0)
    {
        return false;
    }
    float distance = sqrtf(powf(getPosition().x-bullet->getPosition().x, 2.0f)+powf(getPosition().y-bullet->getPosition().y, 2.0f));
    //std::cout << distance << std::endl;
    if (distance > static_cast<float>(animationSize.x)*0.75f)
    {
        return false;
    }
    if (hurtSound->getStatus() != sf3d::SoundSource::Status::Playing)
    {
        --health;
        if (health <= 0)
        {
            die();
        }
        else
        {
            hurtSound->play();
        }
    }
    else
    {
        return false;
    }
    return true;
}

sf3d::Sprite* LS::Player::getSprite() const
{
    return sprite;
}

bool LS::Player::update(sf3d::RenderTexture* window, float deltaTime, const sf3d::Vector2f& mouse)
{
    life += deltaTime;
    if (health <= 0)
    {
        if (dieSound->getStatus() != sf3d::SoundSource::Status::Playing)
        {
            getOwner()->act(Game::Action::DIE);
            return false;
        }
    }
    if (reload > 0)
    {
        reload -= deltaTime;
    }
    this->mouse = mouse;
    animation += deltaTime*static_cast<float>(animations[animationIndex].size())*((briefcase)?0.75f:1.0f);
    if (airborne)
    {
        animationIndex = 2;
    }
    else
    {
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
    offhandTorch->setTextureRect(sf3d::IntRect((facing>0)?0:static_cast<int>(offhandTorch->getTexture()->getSize().x),
                                               0,
                                               static_cast<int>(offhandTorch->getTexture()->getSize().x)*((facing>0)?1:-1),
                                               static_cast<int>(offhandTorch->getTexture()->getSize().y)));
    offhandBriefcase->setTextureRect(sf3d::IntRect((facing>0)?0:static_cast<int>(offhandBriefcase->getTexture()->getSize().x),
                                               0,
                                               static_cast<int>(offhandBriefcase->getTexture()->getSize().x)*((facing>0)?1:-1),
                                               static_cast<int>(offhandBriefcase->getTexture()->getSize().y)));
    hand->setTextureRect(sf3d::IntRect((facing>0)?0:static_cast<int>(hand->getTexture()->getSize().x),
                                               0,
                                               static_cast<int>(hand->getTexture()->getSize().x)*((facing>0)?1:-1),
                                               static_cast<int>(hand->getTexture()->getSize().y)));
    if (briefcase)
    {
        if (health < healthMax)
        {
            heal += deltaTime;
            while (heal > 2.5f)
            {
                heal -= 2.5f;
                if (health < healthMax)
                {
                    std::cout << "heal" << std::endl;
                    ++health;
                }
            }
        }
    }
    if (airborne)
    {
        velocity.y += gravity*deltaTime;
        sprite->move(velocity*deltaTime);
        if (sprite->getPosition().y > center.y*1.75f)
        {
            airborne = false;
            sprite->setPosition(sprite->getPosition().x, center.y*1.75f);
        }
    }
    else
    {
        sprite->move(sf3d::Vector2f(movement)*deltaTime*speed*((briefcase)?0.75f:1.0f));
    }
    if (sprite->getPosition().x-(0.5f*static_cast<float>(window->getSize().x)) > limit)
    {
        sprite->setPosition(limit+(0.5f*static_cast<float>(window->getSize().x)), sprite->getPosition().y);
    }
    if (sprite->getPosition().x-(0.5f*static_cast<float>(window->getSize().x)) < -limit)
    {
        sprite->setPosition(-limit+(0.5f*static_cast<float>(window->getSize().x)), sprite->getPosition().y);
    }
    hand->setOrigin(sf3d::Vector3f((facing>0)?0.0f:static_cast<float>(hand->getTexture()->getSize().x), 0.0f, 0.0f));
    hand->setPosition(sprite->getPosition());
    hand->setScale(sprite->getScale());
    hand->move(scale.x*((handOffset.x*static_cast<float>((facing>0)?0.5f:2.5f))-(handOffset.x*1.5f)-(static_cast<float>(hand->getTexture()->getSize().x)*static_cast<float>(facing)*0.5f)), (scale.y*handOffset.y)-(sprite->getOrigin().y*2.5f));
    if (((facing > 0) != (mouse.x > sprite->getPosition().x)) || (mouse.y > (sprite->getPosition().y-(sprite->getOrigin().y))))
    {
        hand->setRotation(0.0f);
    }
    else
    {
        float angle = getAngle();
        hand->setRotation(angle);
    }
    window->draw(*hand);
    window->draw(*sprite);
    if (briefcase)
    {
        offhandBriefcase->setOrigin(sf3d::Vector3f(static_cast<float>(offhandBriefcase->getTexture()->getSize().x)*0.5f, 0.0f, 0.0f));
        offhandBriefcase->setPosition(sprite->getPosition());
        offhandBriefcase->setScale(sprite->getScale());
        offhandBriefcase->move(-handOffset.x*scale.x*1.25f, -sprite->getOrigin().y*2.5f);
        offhandBriefcase->move(scale.x*((offhandOffset.x*static_cast<float>((facing>0)?1.0f:0.125f))+(1.5f*static_cast<float>((facing>0)?offhandOffset.x:0.0f))), scale.y*(offhandOffset.y-2.5f));
        offhandBriefcase->setColor(sf3d::Color::White);
        offhandTorch->setColor(sf3d::Color::Transparent);
    }
    else
    {
        offhandTorch->setOrigin(sf3d::Vector3f((facing>0)?0.0f:static_cast<float>(offhandTorch->getTexture()->getSize().x), 0.0f, 0.0f));
        offhandTorch->setPosition(sprite->getPosition());
        offhandTorch->setScale(sprite->getScale());
        offhandTorch->move(-handOffset.x*scale.x*1.25f, -sprite->getOrigin().y*2.5f);
        offhandTorch->move(scale.x*((offhandOffset.x*static_cast<float>((facing>0)?1.0f:2.5f))+2.5f-(static_cast<float>(offhandTorch->getTexture()->getSize().x)*static_cast<float>(facing)*0.5f)), scale.y*offhandOffset.y);
        offhandBriefcase->setColor(sf3d::Color::Transparent);
        offhandTorch->setColor(sf3d::Color::White);
    }
    window->draw(*offhandTorch);
    window->draw(*offhandBriefcase);
    if (!airborne)
    {
        motion = movement.x;
        movement = sf3d::Vector2i();
    }
    setScale(sprite->getScale());
    setPosition(sprite->getPosition());
    setRotation(sprite->getRotation());
    move(sf3d::Vector3f(0.0f, -sprite->getOrigin().y*2.0f, 0.0f));
    healthBar->setPosition(sf3d::Vector3f(center.x, center.y*1.9f, getPosition().z));
    healthBar->setSize(sf3d::Vector3f(250.0f*(static_cast<float>(health)/static_cast<float>(healthMax)), 25.0f, 5.0f));
    healthBar->setOrigin(healthBar->getSize()*0.5f);
    window->draw(*healthBar);
    return true;
}

float LS::Player::getAngle() const
{
    return (atan2f(mouse.y-(sprite->getPosition().y-(sprite->getOrigin().y)), mouse.x-(sprite->getPosition().x))*(180.0f/pi))+((facing>0)?0.0f:180.0f);
}
