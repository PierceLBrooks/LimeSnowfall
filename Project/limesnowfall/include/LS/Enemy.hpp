
// Author: Pierce Brooks

#ifndef LS_ENEMY_HPP
#define LS_ENEMY_HPP

#include <LS/Player.hpp>
#include <LS/Ownable.hpp>
#include <LS/Shooter.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>

namespace LS
{
    class Game;

    class Enemy : public Ownable<Game*>, public Shooter
    {
        public:
            Enemy(Game* owner, sf3d::Texture* texture, float axis, float goal, const sf3d::Vector3f& scale);
            virtual ~Enemy();
            Game* getOwner() const;
            bool hurt(Bullet* bullet);
            bool update(sf3d::RenderTexture* window, float deltaTime, Player* player);
        private:
            Game* owner;
            int health;
            float goal;
            float life;
            sf3d::Sprite* sprite;
    };
}

#endif // LS_ENEMY_HPP
