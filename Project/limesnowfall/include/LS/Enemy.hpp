
// Author: Pierce Brooks

#ifndef LS_ENEMY_HPP
#define LS_ENEMY_HPP

#include <LS/Player.hpp>
#include <LS/Ownable.hpp>
#include <LS/Shooter.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>
#include <SFML3D/Graphics/RectangleShape.hpp>

namespace LS
{
    class Game;

    class Enemy : public Ownable<Game*>, public Shooter
    {
        public:
            Enemy(Game* owner, sf3d::Texture* texture, float axis, float goal, int facing, const sf3d::Vector3f& scale);
            virtual ~Enemy();
            Game* getOwner() const;
            bool hurt(Bullet* bullet);
            bool update(sf3d::RenderTexture* window, float deltaTime, Player* player);
        private:
            float getAngle() const;
            Game* owner;
            int health;
            int facing;
            float goal;
            float life;
            float pi;
            float target;
            float aim;
            sf3d::Sprite* sprite;
            sf3d::RectangleShape* rope;
    };
}

#endif // LS_ENEMY_HPP
