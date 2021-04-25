
// Author: Pierce Brooks

#ifndef LS_ENEMY_HPP
#define LS_ENEMY_HPP

#include <LS/Player.hpp>
#include <LS/Ownable.hpp>
#include <LS/Shooter.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>

namespace LS
{
    class Game;

    class Enemy : public Ownable<Game*>, public Shooter
    {
        public:
            Enemy(Game* owner);
            virtual ~Enemy();
            Game* getOwner() const;
            bool update(sf3d::RenderTexture* window, float deltaTime, Player* player);
        private:
            Game* owner;
    };
}

#endif // LS_ENEMY_HPP
