
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
            void move(const sf3d::Vector2i& movement);
            Game* getOwner() const;
            sf3d::Sprite* getSprite() const;
            void update(sf3d::RenderTexture* window, float deltaTime);
        private:
            Game* owner;
            sf3d::Image* imageLeft;
            sf3d::Image* imageRight;
            sf3d::Texture* textureLeft;
            sf3d::Texture* textureRight;
            sf3d::Sprite* sprite;
            sf3d::Vector2i movement;
            sf3d::Vector2i animationSize;
            std::vector<std::vector<sf3d::Vector2i>> animations;
            float animation;
            unsigned int animationIndex;
            int facing;
    };
}

#endif // LS_PLAYER_HPP
