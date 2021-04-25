
// Author: Pierce Brooks

#include <LS/Shooter.hpp>
#include <LS/Bullet.hpp>
#include <LS/Game.hpp>

LS::Shooter::Shooter(Game* owner) :
    Ownable<Game*>(),
    sf3d::Transformable(),
    owner(owner)
{

}

LS::Shooter::~Shooter()
{

}

LS::Game* LS::Shooter::getOwner() const
{
    return owner;
}
