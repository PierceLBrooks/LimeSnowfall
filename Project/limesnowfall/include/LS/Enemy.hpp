
// Author: Pierce Brooks

#ifndef LS_ENEMY_HPP
#define LS_ENEMY_HPP

#include <vector>
#include <LS/Player.hpp>
#include <LS/Ownable.hpp>
#include <LS/Shooter.hpp>
#include <SFML3D/Graphics/RenderTexture.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>
#include <SFML3D/Graphics/RectangleShape.hpp>
#include <SFML3D/Audio/Sound.hpp>

namespace LS
{
    class Game;

    class Enemy : public Shooter
    {
        public:
            Enemy(Game* owner, sf3d::Texture* texture, float axis, float goal, int facing, const sf3d::Vector3f& scale, const std::vector<sf3d::SoundBuffer*>& soundBuffers);
            virtual ~Enemy();
            bool hurt(Bullet* bullet);
            bool update(sf3d::RenderTexture* window, float deltaTime, Player* player);
        private:
            float getAngle() const;
            int health;
            int facing;
            int step;
            float goal;
            float life;
            float pi;
            float target;
            float aim;
            float shoot;
            sf3d::Sprite* sprite;
            sf3d::RectangleShape* rope;
            std::vector<sf3d::Sound*> sounds;
    };
}

#endif // LS_ENEMY_HPP
