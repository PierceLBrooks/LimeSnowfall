
// Author: Pierce Brooks

#ifndef LS_PLAYER_HPP
#define LS_PLAYER_HPP

#include <LS/Shooter.hpp>
#include <LS/Ownable.hpp>
#include <SFML3D/System/Vector2.hpp>
#include <SFML3D/Graphics/Image.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>
#include <SFML3D/Audio/SoundBuffer.hpp>
#include <SFML3D/Audio/Sound.hpp>

namespace LS
{
    class Game;

    class Player : public Ownable<Game*>, public Shooter
    {
        public:
            Player(Game* owner);
            virtual ~Player();
            bool shoot(float& angle);
            bool jump();
            bool pickup();
            bool drop();
            bool die();
            bool hurt(Bullet* bullet);
            void go(const sf3d::Vector2i& movement);
            Game* getOwner() const;
            sf3d::Sprite* getSprite() const;
            bool update(sf3d::RenderTexture* window, float deltaTime, const sf3d::Vector2f& mouse);
        private:
            float getAngle() const;
            Game* owner;
            sf3d::SoundBuffer* shotBuffer;
            sf3d::Sound* shotSound;
            sf3d::Image* imageLeft;
            sf3d::Image* imageRight;
            sf3d::Texture* textureLeft;
            sf3d::Texture* textureRight;
            sf3d::Sprite* sprite;
            sf3d::Image* gunImageLeft;
            sf3d::Image* gunImageRight;
            sf3d::Texture* gunTextureLeft;
            sf3d::Texture* gunTextureRight;
            sf3d::Sprite* hand;
            sf3d::Image* torchImageLeft;
            sf3d::Image* torchImageRight;
            sf3d::Texture* torchTextureLeft;
            sf3d::Texture* torchTextureRight;
            sf3d::Image* briefcaseImageLeft;
            sf3d::Image* briefcaseImageRight;
            sf3d::Texture* briefcaseTextureLeft;
            sf3d::Texture* briefcaseTextureRight;
            sf3d::Sprite* offhandTorch;
            sf3d::Sprite* offhandBriefcase;
            sf3d::Vector2f handOffset;
            sf3d::Vector2f offhandOffset;
            sf3d::Vector2f velocity;
            sf3d::Vector2f center;
            sf3d::Vector2f scale;
            sf3d::Vector2f mouse;
            sf3d::Vector2i movement;
            sf3d::Vector2i animationSize;
            std::vector<std::vector<sf3d::Vector2i>> animations;
            unsigned int animationIndex;
            float animation;
            float gravity;
            float speed;
            float limit;
            float pi;
            float reload;
            int facing;
            int motion;
            int health;
            bool briefcase;
            bool airborne;
    };
}

#endif // LS_PLAYER_HPP
