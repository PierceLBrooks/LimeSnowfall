
// Author: Pierce Brooks

#include <LS/Bullet.hpp>
#include <LS/Game.hpp>

LS::Bullet::Bullet(Shooter* owner, float angle) :
    Ownable<Shooter*>(),
    sf3d::Transformable(),
    owner(owner),
    angle(angle)
{
    life = 0.0f;
    pi = PI;
    shape = new sf3d::RectangleShape();
    shape->setFillColor(sf3d::Color::White);
    shape->setSize(sf3d::Vector3f(100.0f, 5.0f, 5.0f));
    shape->setRotation(angle*(180.0f/pi), sf3d::Vector3f(0.0f, 0.0f, 1.0f));
    shape->setOrigin(shape->getSize()*0.5f);
    shape->setPosition(owner->getPosition());
    center = sf3d::Vector2f(owner->getOwner()->getWindow()->getSize())*0.5f;
}

LS::Bullet::~Bullet()
{
    delete shape;
}

LS::Shooter* LS::Bullet::getOwner() const
{
    return owner;
}

bool LS::Bullet::update(sf3d::RenderTexture* window, float deltaTime)
{
    life += deltaTime;
    if (life >= 2.0f)
    {
        return false;
    }
    shape->move(sf3d::Vector2f(cosf(angle), sinf(angle))*5000.0f*deltaTime);
    if (shape->getPosition().y > center.y*1.75f)
    {
        return false;
    }
    setScale(shape->getSize());
    setPosition(shape->getPosition());
    setRotation(shape->getRotation());
    window->draw(*shape);
    return true;
}
