
// Author: Pierce Brooks

#ifndef LS_PLAYER_HPP
#define LS_PLAYER_HPP

#include <LS/Ownable.hpp>
#include <SFML3D/System/Vector2.hpp>
#include <SFML3D/Graphics/Image.hpp>
#include <SFML3D/Graphics/Texture.hpp>
#include <SFML3D/Graphics/Sprite.hpp>

namespace LS
{
    class Game;

    class Player : public Ownable<Game*>
    {
        public:
            Player(Game* owner);
            virtual ~Player();
            bool shoot();
            bool jump();
            bool pickup();
            bool drop();
            bool die();
            void move(const sf3d::Vector2i& movement);
            Game* getOwner() const;
            sf3d::Sprite* getSprite() const;
            bool update(sf3d::RenderTexture* window, float deltaTime);
        private:
            Game* owner;
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
            sf3d::Vector2f center;
            sf3d::Vector2f scale;
            sf3d::Vector2i movement;
            sf3d::Vector2i animationSize;
            std::vector<std::vector<sf3d::Vector2i>> animations;
            unsigned int animationIndex;
            float animation;
            float limit;
            float pi;
            int facing;
            bool briefcase;
            bool airborne;
    };
}

#endif // LS_PLAYER_HPP
