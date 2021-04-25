
// Author: Pierce Brooks

#include <LS/Enemy.hpp>

LS::Enemy::Enemy(Game* owner) :
    Ownable<Game*>(),
    Shooter(),
    owner(owner)
{

}

LS::Enemy::~Enemy()
{

}

LS::Game* LS::Enemy::getOwner() const
{
    return owner;
}

bool LS::Enemy::update(sf3d::RenderTexture* window, float deltaTime, Player* player)
{
    return true;
}
